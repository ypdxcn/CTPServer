#pragma once

#include "BlcokSample.h"
#include <vector>
#include <thread>
#include <map>
#include <mutex>

#include "BroadcastPacket.h"
#include "ConfigImpl.h"








//定义一个管理器，管理行情接收
class   BLCOKSAMPLE_EXPORT  MyBCQuote
{
public:
	MyBCQuote( );
	~MyBCQuote();

	void    setMainWidget(void *widget);
	//// 订阅广播报文
	//void Subscribe(CPacketReceiver *pPacketReceiver);

	//// 取消广播报文订阅
	//void Unsubscribe(CPacketReceiver *pPacketReceiver);


	static  MyBCQuote *Instance();

	void   getQuote(const char *pszAddress);

	void   setLog(const string&  str);
	bool   m_bLoginSuccessed;

	//void    setGetParam(string &uri);
	//void    getMarketlist(string &uri);
private:

	vector<string /*InstrumentID*/> m_vecInstrumentId;//合约ID
	int         requestID;
	string   m_TradingDay;

	

	mutex m_mutex;
	///用户登录信息

	void  *mainHandle;

	//用于给上层订阅
	//typedef vector<CPacketReceiver*> VPKTRECEIVER;
	//VPKTRECEIVER            m_vPketReceiver;



	//CConfigImpl*	 m_pConfig;


	//web get
	 CConfigImpl  *m_pConfig;

};
