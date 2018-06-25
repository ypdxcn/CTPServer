#include "MyBCQuote.h"
#include <atomic>
#include "BroadcastPacket.h"
#include <filesystem>
//#include "timer.hpp"
#include "MyGateIoApi.h"
#include <iostream>
#include <unordered_map>

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

#include "Poco/JSON/Object.h"  
#include "Poco/JSON/Parser.h"  
#include "Poco/Dynamic/Var.h"  


//C:\Program Files (x86)\Windows Kits\8.1\Include\um\ws2tcpip.h(483): error C2632: 'int' followed by 'int' is illegal

using namespace::Poco::JSON;
using namespace std;
//
URI                 m_uri;
HTTPClientSession   m_session;
HTTPRequest         m_request;
HTTPResponse        m_response;
string              m_strContent;
string              m_path;;


bool      	m_bStop = true;
MyBCQuote::MyBCQuote( )
{

	m_bLoginSuccessed = false;
	//日志初始化
	m_pConfig = new CConfigImpl();
	
}

MyBCQuote::~MyBCQuote()
{
	if (0 != m_pConfig)
	{
		delete m_pConfig;
		m_pConfig = nullptr;
	}
}

void MyBCQuote::setLog(const string&  str)
{
	CRLog(E_DEBUG, str.c_str());
}

void    MyBCQuote::setMainWidget(void *widget)
{
	mainHandle = widget;
}


MyBCQuote * MyBCQuote::Instance()
{
	static  MyBCQuote  trade;
	return  &trade;
}



CBroadcastPacket   pack;
///深度行情通知
///每秒两次行情
//void MyBCQuote::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
//{
//	if (pDepthMarketData->OpenPrice >= LDBL_MAX)
//		pDepthMarketData->OpenPrice = 0;
//
//	if (pDepthMarketData->HighestPrice >= LDBL_MAX)
//		pDepthMarketData->HighestPrice = 0;
//
//	if (pDepthMarketData->LowestPrice >= LDBL_MAX)
//		pDepthMarketData->LowestPrice = 0;
//
//	if (pDepthMarketData->ClosePrice >= LDBL_MAX)
//		pDepthMarketData->ClosePrice = 0;
//
//	if (pDepthMarketData->PreClosePrice >= LDBL_MAX)
//		pDepthMarketData->PreClosePrice = 0;
//
//	string str = "Quote SDK 接收行情信息:InstrumentID:";
//	str  += pDepthMarketData->InstrumentID ;
//	str += " TradingDay:";   str += pDepthMarketData->TradingDay;
//	str += " LastPrice:"; str += to_string(pDepthMarketData->LastPrice);
//	str += " Volume:"; str += to_string(pDepthMarketData->Volume);
//	str += " OpenPrice:"; str += to_string(pDepthMarketData->OpenPrice);
//	str += " HighestPrice:"; str += to_string(pDepthMarketData->HighestPrice);
//	str += " LowestPrice:";  str += to_string(pDepthMarketData->LowestPrice);
//	str += " ClosePrice:"; str += to_string(pDepthMarketData->ClosePrice);
//	str += " PreClosePrice:"; str += to_string(pDepthMarketData->PreClosePrice);
//	str += " UpdateTime:"; str += pDepthMarketData->UpdateTime;
//	CRLog(E_APPINFO, str.c_str());
//	//本地保存
//	//转发到界面
//
//	m_mapInstrumentQuote[pDepthMarketData->InstrumentID] = *pDepthMarketData;
//
//	pack.SetParameter("InstrumentId", pDepthMarketData->InstrumentID);
//	pack.SetParameter("TradingDay", pDepthMarketData->TradingDay);
//	pack.SetParameter("OpenPrice", pDepthMarketData->OpenPrice);
//	pack.SetParameter("HighestPrice", pDepthMarketData->HighestPrice);
//	pack.SetParameter("LowestPrice", pDepthMarketData->LowestPrice);
//	pack.SetParameter("ClosePrice", pDepthMarketData->ClosePrice);
//	pack.SetParameter("PreClosePrice", pDepthMarketData->PreClosePrice);
//	pack.SetParameter("UpperLimitPrice", pDepthMarketData->UpperLimitPrice);
//	pack.SetParameter("LowerLimitPrice", pDepthMarketData->LowerLimitPrice);
//	pack.SetParameter("AskPrice1", pDepthMarketData->AskPrice1);
//	pack.SetParameter("AskVolume1", pDepthMarketData->AskVolume1);
//	pack.SetParameter("BidPrice1", pDepthMarketData->BidPrice1);
//	pack.SetParameter("BidVolume1", pDepthMarketData->BidVolume1);
//	pack.SetParameter("LastPrice", pDepthMarketData->LastPrice);
//	pack.SetParameter("Volume", pDepthMarketData->Volume);
//
//
//	//给上层转发
//	// 广播报文
//	for (VPKTRECEIVER::iterator it = m_vPketReceiver.begin(); it < m_vPketReceiver.end(); it++)
//	{
//		(*it)->Receive(pack);
//	}
//
//}



//bool  doRequest(HTTPClientSession& session, HTTPRequest& request, HTTPResponse& response, std::string &str)
//{
//	session.sendRequest(request);
//	std::istream& rs = session.receiveResponse(response);
//	std::cout << response.getStatus() << " " << response.getReason() << std::endl;
//	if (response.getStatus() != HTTPResponse::HTTP_UNAUTHORIZED)
//	{
//
//		StreamCopier::copyToString(rs, str);
//
//		return  true;
//
//	}
//	else
//	{
//		Poco::NullOutputStream null;
//		StreamCopier::copyStream(rs, null);
//		return false;
//	}
//}

//void    setGetParam(string &uri)
//{
//	//m_uri = ("http://data.gateio.io/api2/1/pairs");
//	m_uri = uri;
//	m_path = (m_uri.getPathAndQuery());
//	if (m_path.empty()) m_path = "/";
//
//	m_session.setHost(m_uri.getHost());
//	m_session.setPort(m_uri.getPort());
//	
//	m_request.setURI(m_path);
//
//}
//
//void   getMarketlist(string & uri)
//{
//	setGetParam(std::move(uri));
//
//	m_strContent.clear();
//	if (!doRequest(m_session, m_request, m_response, m_strContent))
//	{
//	}
//
//	parseMarketlist(m_strContent);
//}

/////////////////////////////////////////////////////////////////////////
void MyBCQuote::getQuote(const char *pszAddress)
{
	m_bStop = true;

	//URI                 m_uri;
	//HTTPClientSession   m_session;
	//HTTPRequest         m_request;
	//HTTPResponse        m_response;
	//string              m_strContent;
	//string              m_path;;

	//m_request.setMethod(HTTPRequest::HTTP_GET);
	//m_request.setURI(m_path);
	//m_request.setVersion(HTTPMessage::HTTP_1_1);

	//Timer t;
	//一直循环获，异步定时取行情
	while (m_bStop)
	{
		//
		//周期性执行定时任务
		/*
		t.StartTimer(1000, std::bind(&MyBCQuote::getMarketlist, MyBCQuote::Instance(), "http://data.gateio.io/api2/1/pairs"));
		std::this_thread::sleep_for(std::chrono::seconds(4));
		std::cout << "try to expire timer!" << std::endl;
		t.Expire();

		/*
		//周期性执行定时任务
		t.StartTimer(1000, std::bind(&MyBCQuote::getMarketlist, MyBCQuote::Instance(), std::move("hello c++11!")));
		std::this_thread::sleep_for(std::chrono::seconds(4));
		std::cout << "try to expire timer!" << std::endl;
		t.Expire();

		std::this_thread::sleep_for(std::chrono::seconds(2));

		//只执行一次定时任务
		//同步
		t.SyncWait(1000, &MyBCQuote::getMarketlist, MyBCQuote::Instance(), "hello world!");
		//异步
		t.AsyncWait(1000, &MyBCQuote::getMarketlist, MyBCQuote::Instance(), "hello c++11!");
		*/
		//this_thread::sleep_for(chrono::milliseconds(50));
	}
	//if(m_userLoginInfo == nullptr)
	//	m_userLoginInfo = new CThostFtdcReqUserLoginField();

	//strcpy(m_userLoginInfo->BrokerID, broker);
	//strcpy(m_userLoginInfo->UserID, User);
	//strcpy(m_userLoginInfo->Password, pswd);

	////当前路径
	//std::tr2::sys::path path = std::tr2::sys::current_path();
	//path.append("/CTP/MdCon");
	////实例化
	//m_reqApi = CThostFtdcMdApi::CreateFtdcMdApi(path.string().c_str());
	////注册事件
	//m_reqApi->RegisterSpi(m_RecvSpi);
	////注册前置机
	//m_reqApi->RegisterFront((char *)pszAddress);// (char *)"tcp://27.17.62.149:40205");	//模拟

	////注册前置机
	//m_reqApi->RegisterFront((char *)pszAddress);//再次运行，切换地址

	//m_reqApi->Init();
	////m_reqApi->Join();

	//CRLog(E_DEBUG, "CTP行情模块初始化成功");

}


//void MyBCQuote::Subscribe(CPacketReceiver *pPacketReceiver)
//{
//	VPKTRECEIVER::iterator it = find(m_vPketReceiver.begin(), m_vPketReceiver.end(), pPacketReceiver);
//	if (it == m_vPketReceiver.end())
//	{
//		m_vPketReceiver.push_back(pPacketReceiver);
//	}
//}
//
//void MyBCQuote::Unsubscribe(CPacketReceiver *pPacketReceiver)
//{
//	VPKTRECEIVER::iterator it = find(m_vPketReceiver.begin(), m_vPketReceiver.end(), pPacketReceiver);
//	if (it != m_vPketReceiver.end())
//	{
//		m_vPketReceiver.erase(it);
//	}
//}