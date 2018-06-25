#include "MyBCTrade.h"
#include "MyBCQuote.h"


#include "strutils.h"
#include <filesystem>
//#include <string>

MyBCTrade::MyBCTrade()
{
	m_bLoginSuccessed = false;

	//日志初始化
	m_pConfig = new CConfigImpl();
}

MyBCTrade::~MyBCTrade()
{

	if (0 != m_pConfig)
	{
		delete m_pConfig;
		m_pConfig = nullptr;
	}

}

void    MyBCTrade::setMainWidget(void *widget)
{
	mainHandle = widget;
}

void MyBCTrade::setLog(const string&  str)
{
	CRLog(E_DEBUG, str.c_str());
}


MyBCTrade * MyBCTrade::Instance()
{
	static  MyBCTrade  trade;
	return  &trade;
}
/////////////////////////////////////////////////////////////////////////
void MyBCTrade::Init(const char  *User,const char  *pswd ,const char  *broker, const char *pszAddress)
{
	//m_bQryIns   = false;// 是否正在查询合约，如果正在查询，行情服务就不自己主动去订阅行情，因为查询合约完成后，会有订阅行情的动作
	//m_bQryInsOK = false;// 是否查询合约成功，成功订阅行情的动作


	//if(m_userLoginInfo == nullptr)
	//	m_userLoginInfo = new CThostFtdcReqUserLoginField();

	//strcpy(m_userLoginInfo->BrokerID, broker);
	//strcpy(m_userLoginInfo->UserID, User);
	//strcpy(m_userLoginInfo->Password, pswd);

	////当前路径
	//std::tr2::sys::path path1  = std::tr2::sys::current_path();
	//path1.append("/CTP/TradeCon");
	////实例化
	//m_reqApi  = CThostFtdcTraderApi::CreateFtdcTraderApi(path1.string().c_str());
	////注册事件
	//m_reqApi->RegisterSpi(m_RecvSpi);
	////注册前置机
	//m_reqApi->RegisterFront((char *)pszAddress);// (char *)"tcp://27.17.62.149:40205");	//模拟
	//m_reqApi->SubscribePrivateTopic(THOST_TERT_QUICK);
	//m_reqApi->SubscribePublicTopic(THOST_TERT_QUICK);
	//m_reqApi->Init();
	////m_reqApi->Join();

	////初始化配置，读出日志地址
	//auto   path = std::tr2::sys::current_path();
	//if (m_pConfig->Load(path.string() + "\\config.cfg") != 0)
	//	return;

	//// 初始化日志，对应的动作有，如果关于日志的配置不存在，则要初始化
	//if (CLogger::Instance()->Initial(m_pConfig->GetProperties("logger")) != 0)
	//	return;

	//// 启动日志
	//if (CLogger::Instance()->Start() != 0)
	//	return;

	//CRLog(E_DEBUG, "CTP交易模块初始化成功");
}


