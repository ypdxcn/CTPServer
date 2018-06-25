// CTPServer.cpp : 定义控制台应用程序的入口点。
//

#include "TradeManager.h"
#include "NanoMsgService.h"

#include <windows.h>
#include <iostream>


int main()
{
	const char *url = "tcp://127.0.0.1:5560";
	NanoMsgService::Instance()->InitUrl(url);
	TradeManager::Instance()->Init();

	//system("pause");
	getchar();
    return 0;
}

