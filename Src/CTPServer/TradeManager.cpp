#include "TradeManager.h"
//#include <boost/filesystem.hpp>
//去掉boost，使用标准C++system
#include <filesystem>

#include "Logger.h"
#include "strutils.h"
#include "NanoMsgService.h"


TradeManager *TradeManager::Instance()
{
	static TradeManager tradeMgr;
	return &tradeMgr;
}

TradeManager::TradeManager()
{
	//日志初始化
	m_pConfig = new CConfigImpl();

	
}


TradeManager::~TradeManager()
{
	if (0 != m_pConfig)
	{
		delete m_pConfig;
		m_pConfig = nullptr;
	}
}
void TradeManager::Init()
{
	readCfg();
	InitCTP("","","");
}

void TradeManager::readCfg()
{
	//读取配置
	//auto   path   =  std::experimental::filesystem::current_path();//ok
	auto   path   = std::tr2::sys::current_path();

	m_path = path.string() + "\\config.cfg";
	
	InitLogger(m_path);
	
}

void TradeManager::InitLogger(const string& strPath)
{
	//CRLog(E_DEBUG, "非法的长度字段尺寸: %d", m_PacketInfo.nLengthBytes);//E_APPINFO       E_SYSINFO

	//初始化配置，读出日志地址
	if (m_pConfig->Load(strPath) != 0)
		return ;


	// 初始化日志，对应的动作有，如果关于日志的配置不存在，则要初始化
	if (CLogger::Instance()->Initial(m_pConfig->GetProperties("logger")) != 0)
		return ;

	// 启动日志
	if (CLogger::Instance()->Start() != 0)
		return ;

	CRLog(E_DEBUG, "配置初始化成功");
	//网络初始化
	//内部逻辑初始化
	//CTP初始化
	//内部数据路由的初始化
	//初始创建共享内存
	string sTmp;
	unsigned int uiXQueNum = 2;
	if (0 == m_pConfig->GetProperty("XQUE_NUM", sTmp))
	{
		uiXQueNum = strutils::FromString<unsigned int>(sTmp);
		if (uiXQueNum > 10)
			uiXQueNum = 2;
	}

	for (unsigned int uiIndex = 1; uiIndex <= uiXQueNum; uiIndex++)
	{
		string sCfgName = "XQUE" + strutils::ToString<unsigned int>(uiIndex);

		CConfig *pCfgWriter;
		pCfgWriter = m_pConfig->GetProperties(sCfgName);
		if (0 != pCfgWriter && !pCfgWriter->IsEmpty())
		{
		}
		else
		{
			pCfgWriter = m_pConfig;
		}
		CRLog(E_APPINFO, "初始化[%s]发布点", sCfgName.c_str());
		CXQueueIo<QUOTATION>* pWriter = new CXQueueIo<QUOTATION>();
		pWriter->Init(pCfgWriter);//跟配置文件名绑定在一起
		m_vecQueueIo.push_back(pWriter);

	}


	//启动
	int nCount = 0;
	for (vector< CXQueueIo<QUOTATION>* >::iterator it = m_vecQueueIo.begin(); it != m_vecQueueIo.end(); ++it)
	{
		nCount++;
		if (0 != *it)
		{
			CRLog(E_APPINFO, "启动[XQUE%d]", nCount);
			(*it)->Start();
		}
	}


}

/***************************/
string UserID = "087614";
string Pswd   = "ypdxcn";
string Broker = "9999";
string INSTRU = "a1805";
/***************************/
void TradeManager::InitCTP(const char *user, const char*pswd, const char *broker)
{
	MyCTPTrade::Instance()->setMainWidget(this);
	MyCTPQuote::Instance()->setMainWidget(this);

	int  loginNum = 0;
	while (true)
	{
		static int num = 1;//用于行情轮动
		string  strTradeFront;
		string  strQuoteFront;
		string strTradeFiled = "CTPFront.trade";
		string strQuoteFiled = "CTPFront.quote";

		strTradeFiled += strutils::intstr(num % 4);
		strQuoteFiled += strutils::intstr(num % 4);

		num = num == 0 ? 1 : num;

		m_pConfig->GetProperty(strTradeFiled, strTradeFront);
		m_pConfig->GetProperty(strQuoteFiled, strQuoteFront);
		if(!MyCTPTrade::Instance()->m_bLoginSuccessed)
			MyCTPTrade::Instance()->Init(UserID.c_str(), Pswd.c_str(), Broker.c_str(), strTradeFront.c_str());//初始化交易
		if (!MyCTPQuote::Instance()->m_bLoginSuccessed)
			MyCTPQuote::Instance()->Init(UserID.c_str(), Pswd.c_str(), Broker.c_str(), strQuoteFront.c_str());//初始化行情
		
		Sleep(7000);
		loginNum++;
		num++;

		if (MyCTPTrade::Instance()->m_bLoginSuccessed && MyCTPQuote::Instance()->m_bLoginSuccessed)
		{
			CRLog(E_APPINFO, "登录CTP成功，登陆次数[%d]，成功订阅行情", loginNum);

			MyCTPQuote::Instance()->Subscribe(this);
			break;
		}

		if (loginNum > 20)
			break;
    }

	//MyCTPTrade::Instance()->Init(UserID.c_str(), Pswd.c_str(), Broker.c_str(), (char *)"tcp://180.168.146.187:10001");//初始化交易
	//MyCTPQuote::Instance()->Init(UserID.c_str(), Pswd.c_str(), Broker.c_str(), (char *)"tcp://180.168.146.187:10011");//初始化行情
																													  
    //上期模拟   ----ok    交易日，16：00～次日09：00；非交易日，16：00～次日15：00。
	//MyCTPTrade::Instance()->Init(UserID.c_str(), Pswd.c_str(), Broker.c_str(), (char *)"tcp://180.168.146.187:10030");//初始化交易
	//MyCTPQuote::Instance()->Init(UserID.c_str(), Pswd.c_str(), Broker.c_str(), (char *)"tcp://180.168.146.187:10031");//初始化行情
	
}

void TradeManager::setLog(const string &strLog)
{
	CRLog(E_DEBUG, strLog.c_str());
}


void TradeManager::setQuotation(const CThostFtdcDepthMarketDataField &pDepthMarketData)
{

}

QUOTATION quo = { 0 };
void TradeManager::Receive(CBroadcastPacket &pkt)
{
	//建立nanomsg服务
	unsigned int  nLen = 0;
	const char* pcBuf = pkt.Encode(nLen);

	//提供实时服务
	NanoMsgService::Instance()->send(pcBuf, nLen);

	//分发给相应队列处理
	quo.Decode(pcBuf, nLen);

	int uiCount = 0;
	string sXQueName, sTmp;
	for (vector< CXQueueIo<QUOTATION>* >::iterator it = m_vecQueueIo.begin(); it != m_vecQueueIo.end(); ++it)
	{
		uiCount++;
		if (0 != *it)
		{
			(*it)->Enque(quo);

			sXQueName = "XQUE" + strutils::ToString<unsigned int>(uiCount);
			sXQueName += ".XQUE_NAME";

			if (0 == m_pConfig->GetProperty(sXQueName, sTmp))
				sXQueName = sTmp;

			CRLog(E_APPINFO, "共享队列XQueue[%s]写完成", sXQueName.c_str());
		}

	}//end for

	//Sleep(10); // 1 s
}