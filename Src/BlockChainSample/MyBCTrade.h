#pragma once

#include "BCbase.h"
#include <vector>
#include <thread>
#include <map>
#include <atomic>
#include <mutex>
#include "ConfigImpl.h"

using namespace std;


//定义一个管理器，管理行情接受
class  BCSAMPLE_EXPORT  MyBCTrade
{

	//thread
public:
	MyBCTrade();
	~MyBCTrade();

	static  MyBCTrade *Instance();
	
	void    setMainWidget(void *widget);
	void    Init(const char  *User, const  char  *pswd, const  char  *broker, const char *pszAddress);
	

	void     setLog(const string&  str);

	bool      m_bLoginSuccessed;
public:

	string   m_TradingDay;

	int    m_session ;
	int    m_frontId ;
	string  m_serverOrderRef ;

    int		m_nOrderRef;


	mutex   m_getInstru;
	void    *mainHandle;
	// 保存合约
	//map<string, CThostFtdcInstrumentField>					m_mapInstrument;//合约ID，合约信息
	//map<wstring, map<wstring, map<wstring, CThostFtdcInstrumentField>>>	m_mapInstrument2;//交易所，板块，合约信息

	

	CConfigImpl*	 m_pConfig;
};
