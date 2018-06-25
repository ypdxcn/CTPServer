#include "ProcessInterfaceNm.h"

CProcessInterfaceClnNm::CProcessInterfaceClnNm(void)
{
	m_oMgrModule.Bind(this);
}

CProcessInterfaceClnNm::~CProcessInterfaceClnNm(void)
{
}

// 作客户端连接成功后回调
int CProcessInterfaceClnNm::OnConnect()
{
	GetPeerInfo(m_sLocalIpNm,m_nLocalPortNm,m_sPeerIpNm,m_nPeerPortNm);
	CProcessInterfaceNm::OnConnect(m_sLocalIpNm,m_nLocalPortNm,m_sPeerIpNm,m_nPeerPortNm);
	return 0;
}

// 断开连接时调用
void CProcessInterfaceClnNm::OnClose()
{
	GetPeerInfo(m_sLocalIpNm,m_nLocalPortNm,m_sPeerIpNm,m_nPeerPortNm);
	CProcessInterfaceNm::OnClose(m_sLocalIpNm,m_nLocalPortNm,m_sPeerIpNm,m_nPeerPortNm,E_TCP_CLIENT);
}

int CProcessInterfaceClnNm::GetFlowStaticsInOut(unsigned int& uiInTotalStat,unsigned int& uiInAveBytes,unsigned int& uiOutTotalStat,unsigned int& uiOutAveBytes, unsigned int& uiOutBufBytes, unsigned int& uiOutBufPkts, unsigned int& uiOutBufBytesTotal, unsigned int& uiOutBufPktsTotal, unsigned int& uiOutBufCount)
{
	CTcpAppProcessClient::GetFlowStatics(uiInTotalStat,uiInAveBytes,uiOutTotalStat,uiOutAveBytes);	
	return 0;
}

CProcessInterfaceSvrNm::CProcessInterfaceSvrNm(void)
{
}

CProcessInterfaceSvrNm::~CProcessInterfaceSvrNm(void)
{
}

// 作服务端接收到连接后回调
int CProcessInterfaceSvrNm::OnAccept()
{
	GetPeerInfo(m_sLocalIpNm,m_nLocalPortNm,m_sPeerIpNm,m_nPeerPortNm);
	CProcessInterfaceNm::OnAccept(m_sLocalIpNm,m_nLocalPortNm,m_sPeerIpNm,m_nPeerPortNm);
	return 0;
}

// 断开连接时调用
void CProcessInterfaceSvrNm::OnClose()
{
	GetPeerInfo(m_sLocalIpNm,m_nLocalPortNm,m_sPeerIpNm,m_nPeerPortNm);
	CProcessInterfaceNm::OnClose(m_sLocalIpNm,m_nLocalPortNm,m_sPeerIpNm,m_nPeerPortNm,E_TCP_SERVER);	
}

int CProcessInterfaceSvrNm::GetFlowStaticsInOut(unsigned int& uiInTotalStat,unsigned int& uiInAveBytes,unsigned int& uiOutTotalStat,unsigned int& uiOutAveBytes, unsigned int& uiOutBufBytes, unsigned int& uiOutBufPkts, unsigned int& uiOutBufBytesTotal, unsigned int& uiOutBufPktsTotal, unsigned int& uiOutBufCount)
{
	CTcpAppProcessServer::GetFlowStatics(uiInTotalStat,uiInAveBytes,uiOutTotalStat,uiOutAveBytes);	
	return 0;
}