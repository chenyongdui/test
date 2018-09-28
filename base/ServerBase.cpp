#include"ServerBase.h"

CServiceBase::CServiceBase()
{
}

CServiceBase::~CServiceBase()
{
}

bool CServiceBase::Init(int port)
{
	m_cAcceptor = boost::shared_ptr<ip::tcp::acceptor>(new ip::tcp::acceptor(m_cIoService,ip::tcp::endpoint(ip::tcp::v4(), port)));
	ConnectClientPtr new_connect_client = ConnectClientPtr(new ConnectClient(m_cIoService));
	
	new_connect_client->RegisterMsgProcHandle(std::bind(&CServiceBase::NetMsgHandle, this, _1));
	m_cAcceptor->async_accept(new_connect_client->GetSocket(), std::bind(&CServiceBase::handle_accept, this, new_connect_client, _1));
}


void CServiceBase::handle_accept(ConnectClientPtr _seesion, const boost::system::error_code & err)
{
	ConnectClientMgr::AddConnectClient(_seesion->GetConnectClientId(), _seesion);
	_seesion->start();
	ConnectClientPtr new_connect_client = ConnectClientPtr(new ConnectClient(m_cIoService));
	
	new_connect_client->RegisterMsgProcHandle(std::bind(&CServiceBase::NetMsgHandle, this, _1));
	m_cAcceptor->async_accept(new_connect_client->GetSocket(), std::bind(&CServiceBase::handle_accept, this, new_connect_client, _1));
}

void CServiceBase::NetMsgHandle(const char* strMsg)
{
	std::cout<<"ReadBody body:"<<strMsg<<std::endl;
	OnNetMsgHandle(strMsg);
}

void CServiceBase::run_handle()
{
	time_t now_time = time(nullptr);
	if(now_time - m_iLastTime >= 2)
	{
		m_iLastTime = time(nullptr);
		std::cout<<"now"<< now_time <<std::endl;
		
		OnRunHandle();
	}
	m_cIoService.post(std::bind(&CServiceBase::run_handle,this));
}

void CServiceBase::run()
{
	m_cIoService.post(std::bind(&CServiceBase::run_handle,this));
	std::cout<<"hello world! 5555"<<std::endl;
	m_iLastTime = time(nullptr);
	m_cIoService.run();
}