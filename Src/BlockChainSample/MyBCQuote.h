#pragma once

#include "BCbase.h"
#include <vector>
#include <thread>
#include <map>
#include <mutex>



#include "BroadcastPacket.h"
#include "ConfigImpl.h"


#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include <Poco/Net/HTTPCredentials.h>
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;





//定义一个管理器，管理行情接收
class   BCSAMPLE_EXPORT  MyBCQuote
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

	void    setGetParam(string &uri);
	void    getMarketlist(string &uri);
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

	URI                 m_uri;
	HTTPClientSession   m_session;
	HTTPRequest         m_request;
	HTTPResponse        m_response;
	string              m_strContent;
	string              m_path;;
};
