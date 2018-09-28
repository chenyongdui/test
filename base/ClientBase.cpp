#include"ClientBase.h"

CClientBase::CClientBase()
{	
}

CClientBase::~CClientBase()
{
}

bool CClientBase::Init(const char* ip, int port)
{
	m_cConnectServer = std::shared_ptr<ConnectServer>(new ConnectServer(m_cIoService));
	m_cConnectServer->RegisterMsgProcHandle(std::bind(&CClientBase::NetMsgHandle, this, _1));
	m_cConnectServer->Connect(ip, port);
	return true;
}


void CClientBase::NetMsgHandle(const char* strMsg)
{
	std::cout<<"ReadBody body:"<<strMsg<<std::endl;
	OnNetMsgHandle(strMsg);
}

void CClientBase::run_handle()
{
	time_t now_time = time(nullptr);
	if(now_time - m_iLastTime >= 5)
	{
		m_iLastTime = time(nullptr);
		std::cout<<"now"<< now_time <<std::endl;

		OnRunHandle();
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
