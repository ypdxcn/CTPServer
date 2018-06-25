#ifndef _FRAMWORKNM_CONSTANT_H_
#define _FRAMWORKNM_CONSTANT_H_

#include <string>
using namespace std;

namespace FramworkNmConst
{
	//const string gc_CtrQuit		            = "0";				//退出进程命令
	//const string gc_CtrRestar		        = "1";				//重启进程命令
	//const string gc_CtrStar			        = "2";				//启动进程命令
	//const string gc_CtrDetach			    = "3";				//detach进程命令
	//const string gc_CtrAttach			    = "4";				//attach进程命令

	//const int gc_nThreadRun					= 0;				//运行
	//const int gc_nThreadBlock				= 1;				//阻塞
	//const int gc_nThreadQuit				= 2;				//退出

	//const int gc_nTcpInit					= 0;				//初始化
	//const int gc_nTcpConneted				= 1;				//连接正常
	//const int gc_nTcpDisConneted			= 2;				//连接中断

	//const int gc_ProceRun				    = 0;				//运行    进程运行状态
	//const int gc_ProceStop					= 1;				//未运行
	//const int gc_ProceNoHeart				= 2;				//无心跳

	////MIB
	//const std::string mibCpuRadio			= "1.1.1.1.1";		//cpu使用率
	//const std::string mibCpuTemperature		= "1.1.1.1.2";		//cpu温度

	//const std::string mibEmsTotal			= "1.1.1.2.1.1";		//内存总数
	//const std::string mibEmsUse				= "1.1.1.2.1.2";		//内存使用数
	//const std::string mibEmsRadio			= "1.1.1.2.1.3";		//内存使用率


	//const std::string mibDiskNum			= "1.1.1.3.1";		//硬盘分区数
	//const std::string mibPartIndex		    = "1.1.1.3.2.1.1";	//硬盘分区索引
	//const std::string mibDiskPhyTotal		= "1.1.1.3.2.1.2";	//硬盘的物理容量大小
	//const std::string mibDisk_Used			= "1.1.1.3.2.1.3";	//硬盘已经使用的大小
	//const std::string mibDisk_Used_Ratio    = "1.1.1.3.2.1.4";	//硬盘使用率
	//const std::string mibDiskTemperature    = "1.1.1.3.3";		//硬盘温度

	//const std::string gc_sThreadNum			= "1.1.2.1";		//线程数量
	//const std::string gc_sThreadIdx			= "1.1.2.2.1.1";	//线程索引
	//const std::string gc_sThreadState		= "1.1.2.2.1.2";	//线程状态

	//const std::string gc_sTcpLocalIp		= "1.1.3.2.1.2";	//本地IP
	//const std::string gc_sTcpLocalPort		= "1.1.3.2.1.3";	//本地端口
	//const std::string gc_sTcpRemoteIp		= "1.1.3.2.1.4";	//对端IP
	//const std::string gc_sTcpRemotePort		= "1.1.3.2.1.5";	//对端端口
	//const std::string gc_sTcpState			= "1.1.3.2.1.6";	//连接状态
	//const std::string gc_sTcpInBytesAve		= "1.1.3.2.1.7";	//平均入字节数
	//const std::string gc_sTcpInBytesTotal	= "1.1.3.2.1.8";	//总入字节数
	//const std::string gc_sTcpOutBytesAve	= "1.1.3.2.1.9";	//平均出字节数
	//const std::string gc_sTcpOutBytesTotal		= "1.1.3.2.1.A";	//总出字节数
	//const std::string gc_sTcpOutBufBytes		= "1.1.3.2.1.B";	//发送缓存字节数
	//const std::string gc_sTcpOutBufPkts			= "1.1.3.2.1.C";	//发送缓存报文个数	
	//const std::string gc_sTcpOutBufBytesTotal	= "1.1.3.2.1.D";	//发送缓存字节数累计
	//const std::string gc_sTcpOutBufPktsTotal	= "1.1.3.2.1.E";	//发送缓存报文个数累计
	//const std::string gc_sTcpOutBufCount		= "1.1.3.2.1.F";	//发送缓存报文次数

	//const std::string mib_NodeId		    = "1.2.6.1.1.1";	//结点ID     多记录
	//const std::string mib_NodeSta    	    = "1.2.6.1.1.2";	//结点状态
	//const std::string mib_NodeCtr			= "1.2.6.1.1.3";	//结点控制  0 1 2 重启，停止，开始
	//const std::string mibQueNum 		    = "1.1.4.1.1.2";	//队列中报文数量
}

#endif