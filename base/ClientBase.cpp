#include"ClientBase.h"

Client::Client(const char* ip, int port)
{
	m_cConnectServer = std::shared_ptr<ConnectServer>(new ConnectServer(m_cIoService));
	m_cConnectServer->RegisterMsgProcHandle(std::bind(&Client::NetMsgHandle, this, _1));
	m_cConnectServer->Connect(ip, port);
	
}

void Client::NetMsgHandle(const char* strMsg)
{
	std::cout<<"ReadBody body:"<<strMsg<<std::endl;
}

void Client::run_handle()
{
	time_t now_time = time(nullptr);
	if(now_time - m_iLastTime >= 5)
	{
		m_iLastTime = time(nullptr);
		std::cout<<"now"<< now_time <<std::endl;
		
		m_cConnectServer->Write("hello 56789哈哈阿凡达发放安抚");
	}
	m_cIoService.post(std::bind(&Client::run_handle,this));
}

void Client::run()
{
	m_cIoService.post(std::bind(&Client::run_handle,this));
	std::cout<<"hello world! 5555"<<std::endl;
	m_iLastTime = time(nullptr);
	m_cIoService.run();
}
