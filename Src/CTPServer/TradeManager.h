#pragma once



/***
 *@名称:交易管理器
 *@  功能1:日志管理
 *   功能2:交易管理
 *   功能3:行情管理
 *   功能4:数据路由管理
 *   功能5:报单管理器
 *   功能6:风控管理器

 @规划：暂时统一管理，逐步分层管理，划分为：报单管理器(OM)，风控管理器(RM)，策略管理器(SM)

 @使用的基础技术:
 1.Poco c++
 2.Nanomsg
 3.C++11
 4.Boost

***/

#include "..\CTPSample\MyCTPQuote.h"
#include "..\CTPSample\MyCTPTrade.h"
#include "ConfigImpl.h"
#include "Singleton.h"

#include "XQueue.h"
#include "XQueueIO.h"
#include "BroadcastPacket.h"//内部K-value广播格式
#include "samplerpacket.h"//标准行情格式

#include <string>
//template<typename >
//class CSingleton;

class CConfigImpl;

class  TradeManager:public CPacketReceiver
{
	//friend class CSingleton< TradeManager>;
protected:
	TradeManager();
	~TradeManager();

private:
	//内部逻辑
	void readCfg();
	void InitLogger(const string& strPath);

public:
	void  Init();
	static TradeManager *Instance();
	void InitCTP(const char *user ,const char*pswd ,const char *broker);

	void setLog(const string &strLog);
	void setQuotation(const CThostFtdcDepthMarketDataField &pDepthMarketData);
	virtual void Receive(CBroadcastPacket &pkt) override;
private:
	CConfigImpl*	 m_pConfig;
	string			 m_user;
	string			 m_pswd;
	string			 m_broker;
	string           m_path;

	vector< CXQueueIo<QUOTATION>* > m_vecQueueIo;
};

