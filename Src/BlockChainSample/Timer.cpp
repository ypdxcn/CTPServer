#include<iostream>
#include<string>
#include<memory>
#include"Timer.hpp"

//参考:https://www.cnblogs.com/gtarcoder/p/4924097.html

void EchoFunc(std::string&& s) 
{
	std::cout << "test : " << s << endl;
}

/*   example

int main() 
{
	Timer t;
	//周期性执行定时任务
	t.StartTimer(1000, std::bind(EchoFunc, "hello world!"));
	std::this_thread::sleep_for(std::chrono::seconds(4));
	std::cout << "try to expire timer!" << std::endl;
	t.Expire();

	//周期性执行定时任务
	t.StartTimer(1000, std::bind(EchoFunc, "hello c++11!"));
	std::this_thread::sleep_for(std::chrono::seconds(4));
	std::cout << "try to expire timer!" << std::endl;
	t.Expire();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	//只执行一次定时任务
	//同步
	t.SyncWait(1000, EchoFunc, "hello world!");
	//异步
	t.AsyncWait(1000, EchoFunc, "hello c++11!");

	std::this_thread::sleep_for(std::chrono::seconds(2));

	return 0;
}

*/