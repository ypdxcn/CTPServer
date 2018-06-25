#include "NanoMsgService.h"
#include <cassert>
#include "nn.h"
#include "pubsub.h" 

NanoMsgService::NanoMsgService()
{
}


NanoMsgService::~NanoMsgService()
{
}

NanoMsgService* NanoMsgService::Instance()
{
	static NanoMsgService  nanomsgSrv;
	return &nanomsgSrv;
}


void NanoMsgService::InitUrl(const char *url)
{
	m_socket = nn_socket(AF_SP, NN_PUB);
	assert(m_socket >= 0);
	assert(nn_bind(m_socket, url) >= 0);
}

void NanoMsgService::send(const char *buffer,int length)
{

	int bytes = nn_send(m_socket,buffer, length, 0);
	assert(bytes == sz_d);

}