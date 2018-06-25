#pragma once

#include "BCBase.h"
#include <string>

using namespace  std;


BCSAMPLE_EXPORT string parsePaires(string & str);

//3.交易市场订单参数
BCSAMPLE_EXPORT string parseMarketinfo(string & str);

//4.交易市场行情API(数字币交易市场)
BCSAMPLE_EXPORT  string parseMarketlist(string & str);

//6.单项，指定交易的行情
//返回最新，最高，最低 交易行情和交易量，每10秒钟更新 :
BCSAMPLE_EXPORT  string parseMarketTicker(string & str);

//7.指定合约的深度行情
//返回最新，最高，最低 交易行情和交易量，30档行情 :
BCSAMPLE_EXPORT  string parseMarketOrderBooks(string & str);