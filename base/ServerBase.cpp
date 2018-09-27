#include"ServerBase.h"

CServiceBase::CServiceBase(int port)
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
}

void CServiceBase::run_handle()
{
	time_t now_time = time(nullptr);
	if(now_time - m_iLastTime >= 2)
	{
		m_iLastTime = time(nullptr);
		std::cout<<"now"<< now_time <<std::endl;
		
		for(auto _connect_client : ConnectClientMgr::GetConnectClientMap())
		{
			char tmp[100];
			sprintf(tmp, "connect_client——id:%d\n", _connect_client.first);
			
			std::cout<<"send:"<<tmp<<std::endl;

			_connect_client.second->Write(tmp);


			strcpy(tmp,"安抚染发法国 79878787aa");
			_connect_client.second->Write(tmp);
			
			strcpy(tmp,"啊发发7575757%&%&%&% 79878787aa事故发生灌水灌水65654456454放首发申购");
			_connect_client.second->Write(tmp);
		}
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