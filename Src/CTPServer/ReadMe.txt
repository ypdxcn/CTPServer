========================================================================
    控制台应用程序：CTPServer 项目概述
========================================================================

/////////////////////////////////////////////////////////////////////////////
20180412
1.引入POCO C++的日志模块
在logger文件里面封装了Logger的函数，使用时，在TradManager构造函数里面自动初始化

使用的时候，引用头文件，直接使用全局函数poco_information(logger_handle, "initLogSys()");


2.引入nanomsg库，用作服务端。


20180413
1.boost获取当前执行程序的路径1两种方式：

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>

	//auto file_path = boost::filesystem::current_path() / "log"; //取得当前程序所在目录 
	//auto file_path1 = boost::filesystem::initial_path<boost::filesystem::path>() / "log";


20180419
//#include <boost/filesystem.hpp>
//去掉boost，使用标准C++system
#include <filesystem>


boost代码:
	//auto   path   =  std::experimental::filesystem::current_path();//ok
	auto   path   = std::tr2::sys::current_path();
	//m_path        =  path.string();
	//auto path = boost::filesystem::current_path(); //取得当前程序所在目录 

	//if (!boost::filesystem::exists(path))  //判断文件存在性    
	//{
	//	boost::filesystem::create_directory(path);  //目录不存在，创建
	//}
	m_path = path.string() + "\\config.cfg";




改为:以下两句都可以
auto   path   =  std::tr2::sys::current_path();
auto   path   =  std::experimental::filesystem::current_path();



20180507   测试POCO功能，【日志】代码片


#include  "Poco\Logger.h"
#include  "Poco\Channel.h"
#include  "Poco\FileChannel.h"
#include  "Poco\FormattingChannel.h"
#include  "Poco\AutoPtr.h"
#include  "Poco\PatternFormatter.h"


	//测试POCO功能--【日志功能】
	Poco::AutoPtr<Poco::Channel> channel;
	{
		Poco::AutoPtr<Poco::FileChannel> fileChannel(new Poco::FileChannel);
		fileChannel->setProperty("path", "log/test.log");		//指定日志路径及文件名
		fileChannel->setProperty("archive", "timestamp");	    //日志文件加时间戳
		Poco::AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter());
		patternFormatter->setProperty("pattern", "%Y %m %d %H:%M:%S %s(%l): %t");	//每条日志时间
		channel = new Poco::FormattingChannel(patternFormatter, fileChannel);//初始化　Channel

	}
	Poco::Logger::root().setChannel(channel);

	Poco::Logger::root().information(" this is  information");
	Poco::Logger::root().warning(" this is warning information");
	Poco::Logger::root().critical(" this is critical information");
	Poco::Logger::root().error(" this is error information");
	//测试Poco完毕