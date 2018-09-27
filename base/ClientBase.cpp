#include"ClientBase.h"

CClientBase::CClientBase(const char* ip, int port)
{
	m_cConnectServer = std::shared_ptr<ConnectServer>(new ConnectServer(m_cIoService));
	m_cConnectServer->RegisterMsgProcHandle(std::bind(&CClientBase::NetMsgHandle, this, _1));
	m_cConnectServer->Connect(ip, port);
	
}

void CClientBase::NetMsgHandle(const char* strMsg)
{
	std::cout<<"ReadBody body:"<<strMsg<<std::endl;
}

void CClientBase::run_handle()
{
	time_t now_time = time(nullptr);
	if(now_time - m_iLastTime >= 5)
	{
		m_iLastTime = time(nullptr);
		std::cout<<"now"<< now_time <<std::endl;
		
		m_cConnectServer->Write("hello 56789哈哈阿凡达发放安抚");
		
		m_cConnectServer->Write("你好德尔芬格788yy放松放松是干啥干啥公使馆升格");
	}
	m_cIoService.post(std::bind(&CClientBase::run_handle,this));
}

void CClientBase::run()
{
	m_cIoService.post(std::bind(&CClientBase::run_handle,this));
	std::cout<<"hello world! 5555"<<std::endl;
	m_iLastTime = time(nullptr);
	m_cIoService.run();
}
