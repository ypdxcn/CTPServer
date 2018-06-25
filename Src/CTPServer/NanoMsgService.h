#pragma once



class  NanoMsgService
{
public:
	NanoMsgService();
	~NanoMsgService();

	static NanoMsgService* Instance();

	void InitUrl(const char *url);
	void send(const char *buffer, int length);

	int m_socket;
};

