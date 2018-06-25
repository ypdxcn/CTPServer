#ifndef _PROCESS_INTERFACE_NM_H
#define _PROCESS_INTERFACE_NM_H


#include "FramworkNm.h"
#include "NetMgr.h"
#include "FramworkNmConstant.h"
#include "ProtocolProcess.h"
#include "NmConstant.h"

//using namespace FramworkNmConst;
using namespace NmConst;
enum 
{
	E_TCP_CLIENT,
	E_TCP_SERVER
};

class FRAMWORKNM_CLASS CProcessInterfaceNm
{
	class CIfMgrModule: public CNmoModule
	{
	public:
		CIfMgrModule():m_pParent(0){}
		virtual ~CIfMgrModule(){}
		void Bind(CProcessInterfaceNm* p){m_pParent = p;}
		//网管单个查询接口
		int Query(CNMO& oNmo) const
		{
			if (0 == m_pParent)
				return -1;

			return m_pParent->Query(oNmo);
		}
		//批量查询接口
		int Query(vector< CNMO > & vNmo) const
		{
			for (vector< CNMO >::iterator it = vNmo.begin(); it != vNmo.end(); ++it)
			{
				Query(*it);
			}
			return 0;
		}
		//控制接口
		int Operate(const string &sOid, int nflag, const string &sDstValue, const string &sParamer) {return -1;}
	private:
		CProcessInterfaceNm* m_pParent;
	};
public:
	CProcessInterfaceNm()
	:m_nRegisted(0)
	,m_nConnState(gc_nTcpDisConneted)
	,m_sNmKey("")
	{
		m_oMgrModule.Bind(this);
	}
	virtual ~CProcessInterfaceNm(){}
	int Query(CNMO& oNmo)
	{

		CMutexGuard oGuard(m_csIfNm);
		if (oNmo.m_sOid == gc_sTcpInBytesAve || oNmo.m_sOid == gc_sTcpOutBytesAve
			|| oNmo.m_sOid == gc_sTcpInBytesTotal || oNmo.m_sOid == gc_sTcpOutBytesTotal
			|| oNmo.m_sOid == gc_sTcpOutBufBytes || oNmo.m_sOid == gc_sTcpOutBufPkts
			|| oNmo.m_sOid == gc_sTcpOutBufBytesTotal || oNmo.m_sOid == gc_sTcpOutBufPktsTotal
			|| oNmo.m_sOid == gc_sTcpOutBufCount)
		{
			unsigned int uiInTotalStat = 0, uiInAveBytes = 0,uiOutTotalStat = 0,uiOutAveBytes = 0, uiOutBufBytes = 0, uiOutBufPkts = 0, uiOutBufBytesTotal = 0, uiOutBufPktsTotal = 0, uiOutBufCount = 0;
			GetFlowStaticsInOut(uiInTotalStat,uiInAveBytes,uiOutTotalStat,uiOutAveBytes,uiOutBufBytes,uiOutBufPkts,uiOutBufBytesTotal,uiOutBufPktsTotal,uiOutBufCount);
			oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
			if (oNmo.m_sOid == gc_sTcpInBytesAve)
			{
				oNmo.m_sValue = ToString<unsigned int>(uiInAveBytes);
			}
			else if (oNmo.m_sOid == gc_sTcpOutBytesAve)
			{
				oNmo.m_sValue = ToString<unsigned int>(uiOutAveBytes);
			}
			else if (oNmo.m_sOid == gc_sTcpInBytesTotal)
			{
				oNmo.m_sValue = ToString<unsigned int>(uiInTotalStat);
			}
			else if (oNmo.m_sOid == gc_sTcpOutBytesTotal)
			{
				oNmo.m_sValue = ToString<unsigned int>(uiOutTotalStat);
			}
			else if (oNmo.m_sOid == gc_sTcpOutBufBytes)
			{
				oNmo.m_sValue = ToString<unsigned int>(uiOutBufBytes);
			}
			else if (oNmo.m_sOid == gc_sTcpOutBufPkts)
			{
				oNmo.m_sValue = ToString<unsigned int>(uiOutBufPkts);
			}
			else if (oNmo.m_sOid == gc_sTcpOutBufBytesTotal)
			{
				oNmo.m_sValue = ToString<unsigned int>(uiOutBufBytesTotal);
			}
			else if (oNmo.m_sOid == gc_sTcpOutBufPktsTotal)
			{
				oNmo.m_sValue = ToString<unsigned int>(uiOutBufPktsTotal);
			}
			else if (oNmo.m_sOid == gc_sTcpOutBufCount)
			{
				oNmo.m_sValue = ToString<unsigned int>(uiOutBufCount);
			}
		}
		else if (oNmo.m_sOid == gc_sTcpState)
		{
			oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
			oNmo.m_sValue = ToString<int>(m_nConnState);
		}
		return 0;
	}
protected:
	CIfMgrModule	m_oMgrModule;
	int				m_nConnState;
	int				m_nRegisted;
	string			m_sNmKey;
	string	m_sLocalIpNm;
	int		m_nLocalPortNm;
	string	m_sPeerIpNm;
	int		m_nPeerPortNm;
	mutable CGessMutex	m_csIfNm;

	virtual int GetNmKey(string& sKey) = 0;
	virtual int GetFlowStaticsInOut(unsigned int& uiInTotalStat,unsigned int& uiInAveBytes,unsigned int& uiOutTotalStat,unsigned int& uiOutAveBytes, unsigned int& uiOutBufBytes, unsigned int& uiOutBufPkts,unsigned int& uiOutBufBytesTotal,unsigned int& uiOutBufPktsTotal,unsigned int& uiOutBufCount) = 0;
	void OnConnect(const string& sLocalIpNm, int nLocalPortNm,const string& sPeerIpNm,int nPeerPortNm)
	{
		if (0 == m_nRegisted)
		{
			GetNmKey(m_sNmKey);
			RegisterTcpConn(m_sNmKey, sLocalIpNm, nLocalPortNm, sPeerIpNm, nPeerPortNm);
			m_nRegisted = 1;
		}

		m_nConnState = gc_nTcpConneted;
		ReportTcpConn(m_sNmKey, sLocalIpNm, nLocalPortNm, sPeerIpNm, nPeerPortNm);
	}
	void OnAccept(const string& sLocalIpNm, int nLocalPortNm,const string& sPeerIpNm,int nPeerPortNm)
	{
		m_nConnState = gc_nTcpConneted;

		GetNmKey(m_sNmKey);
		RegisterTcpConn(m_sNmKey, sLocalIpNm, nLocalPortNm, sPeerIpNm, nPeerPortNm);
		ReportTcpConn(m_sNmKey, sLocalIpNm, nLocalPortNm, sPeerIpNm, nPeerPortNm);
	}
	void OnClose(const string& sLocalIpNm, int nLocalPortNm,const string& sPeerIpNm,int nPeerPortNm, int nTcpType = E_TCP_CLIENT)
	{
		m_nConnState = E_DISCONNECTED;
		if (E_TCP_SERVER == nTcpType)
		{
			UnRegisterTcpConn();
		}
		else
		{
			ReportTcpConn(m_sNmKey, sLocalIpNm, nLocalPortNm, sPeerIpNm, nPeerPortNm);
		}
	}
	void UnRegisterTcpConn()
	{
		CNetMgr::Instance()->UnRegisterModule(&m_oMgrModule);
	}
	void RegisterTcpConn(const string& sNmKey, const string& sLocalIpNm, int nLocalPortNm,const string& sPeerIpNm,int nPeerPortNm)
	{
		vector< pair<string,string> > vpaOid;
		pair<string,string> pa;
		
		pa.first = gc_sTcpLocalIp;
		pa.second = gc_sTcpLocalIp + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpLocalPort;
		pa.second = gc_sTcpLocalPort + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpRemoteIp;
		pa.second = gc_sTcpRemoteIp + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpRemotePort;
		pa.second = gc_sTcpRemotePort + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpState;
		pa.second = gc_sTcpState + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpInBytesAve;
		pa.second = gc_sTcpInBytesAve + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpOutBytesAve;
		pa.second = gc_sTcpOutBytesAve + "." + sNmKey;
		vpaOid.push_back(pa);


		pa.first = gc_sTcpInBytesTotal;
		pa.second = gc_sTcpInBytesTotal + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpOutBytesTotal;
		pa.second = gc_sTcpOutBytesTotal + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpOutBufBytes;
		pa.second = gc_sTcpOutBufBytes + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpOutBufPkts;
		pa.second = gc_sTcpOutBufPkts + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpOutBufBytesTotal;
		pa.second = gc_sTcpOutBufBytesTotal + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpOutBufPktsTotal;
		pa.second = gc_sTcpOutBufPktsTotal + "." + sNmKey;
		vpaOid.push_back(pa);

		pa.first = gc_sTcpOutBufCount;
		pa.second = gc_sTcpOutBufCount + "." + sNmKey;
		vpaOid.push_back(pa);

		CNetMgr::Instance()->Register(&m_oMgrModule,vpaOid);
	}

	void ReportTcpConn(const string& sNmKey, const string& sLocalIpNm, int nLocalPortNm,const string& sPeerIpNm,int nPeerPortNm)
	{
		vector<CNMO> vNmo;
		CNMO oNmo;
		oNmo.m_sOid = gc_sTcpLocalIp;
		oNmo.m_sOidIns = gc_sTcpLocalIp + "." + sNmKey;
		oNmo.m_sValue = m_sLocalIpNm;
		oNmo.m_nQuality = gc_nQuolityGood;
		oNmo.m_sTimeStamp = CGessDate::NowToString() + " " + CGessTime::NowToString();
		vNmo.push_back(oNmo);

		oNmo.m_sOid = gc_sTcpLocalPort;
		oNmo.m_sOidIns = gc_sTcpLocalPort + "." + sNmKey;
		oNmo.m_sValue = ToString<int>(m_nLocalPortNm);
		vNmo.push_back(oNmo);

		oNmo.m_sOid = gc_sTcpRemoteIp;
		oNmo.m_sOidIns = gc_sTcpRemoteIp + "." + sNmKey;
		oNmo.m_sValue = m_sPeerIpNm;
		vNmo.push_back(oNmo);

		oNmo.m_sOid = gc_sTcpRemotePort;
		oNmo.m_sOidIns = gc_sTcpRemotePort + "." + sNmKey;
		oNmo.m_sValue = ToString<int>(m_nPeerPortNm);
		vNmo.push_back(oNmo);

		oNmo.m_sOid = gc_sTcpState;
		oNmo.m_sOidIns = gc_sTcpState + "." + sNmKey;
		oNmo.m_sValue = ToString<int>(m_nConnState);
		vNmo.push_back(oNmo);

		oNmo.m_sOid = gc_sTcpInBytesAve;
		oNmo.m_sOidIns = gc_sTcpInBytesAve + "." + sNmKey;
		oNmo.m_sValue = ToString<int>(0);
		vNmo.push_back(oNmo);

		oNmo.m_sOid = gc_sTcpOutBytesAve;
		oNmo.m_sOidIns = gc_sTcpOutBytesAve + "." + sNmKey;
		oNmo.m_sValue = ToString<int>(0);
		vNmo.push_back(oNmo);
		CNetMgr::Instance()->Report(vNmo);
	}	
	void NotifyEvent(const string& sEvt, int nGrade = 1)
	{
		//事件通知
		CEventSimple e;
		e.m_nEvtCategory = 0;
		e.m_nEvtType = 0;
		e.m_nGrade = nGrade;
		e.m_sDateTime = CGessDate::NowToString("-") + " " + CGessTime::NowToString(":");		
		e.m_sEvtContent = sEvt;
		CNetMgr::Instance()->OnEvtNotify(e);
	}
};

class FRAMWORKNM_CLASS CProcessInterfaceClnNm: public CTcpAppProcessClient, public CProcessInterfaceNm
{
public:
	CProcessInterfaceClnNm();
	~CProcessInterfaceClnNm();

	virtual int OnConnect();		// 作客户端连接成功后回调
	virtual void OnClose();			// 断开连接时调用
private:
	
	int GetFlowStaticsInOut(unsigned int& uiInTotalStat,unsigned int& uiInAveBytes,unsigned int& uiOutTotalStat,unsigned int& uiOutAveBytes, unsigned int& uiOutBufBytes, unsigned int& uiOutBufPkts, unsigned int& uiOutBufBytesTotal, unsigned int& uiOutBufPktsTotal, unsigned int& uiOutBufCount) ;
};

class FRAMWORKNM_CLASS CProcessInterfaceSvrNm: public CTcpAppProcessServer, public CProcessInterfaceNm
{
public:
	CProcessInterfaceSvrNm();
	~CProcessInterfaceSvrNm();

	virtual int OnAccept();		// 作服务端接收到连接后回调
	virtual void OnClose();		// 断开连接时调用
private:
	int GetFlowStaticsInOut(unsigned int& uiInTotalStat,unsigned int& uiInAveBytes,unsigned int& uiOutTotalStat,unsigned int& uiOutAveBytes, unsigned int& uiOutBufBytes, unsigned int& uiOutBufPkts, unsigned int& uiOutBufBytesTotal, unsigned int& uiOutBufPktsTotal, unsigned int& uiOutBufCount);
};

#endif