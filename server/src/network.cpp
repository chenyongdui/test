#include"../base/common.h"
#include"../include/network.h"

ConnectClient::ConnectClient(io_service& _io_service):m_cSocket(_io_service)
{
	m_iConnectClientId = time(nullptr);
	std::cout<<"m_iConnectClientId:"<<m_iConnectClientId<<std::endl;
	
	m_cNetHandle.RegisterErrorInfoHandle(std::bind(&ConnectClient::OnErrorHandle, this, _1));
}

int ConnectClient::GetConnectClientId()
{
	return m_iConnectClientId;
}


ip::tcp::socket& ConnectClient::GetSocket()
{
	return m_cSocket;
}

void ConnectClient::start()
{
	m_cNetHandle.SetSocket(&m_cSocket);
	m_cNetHandle.DoRead();
	/*memset(m_cReadBuffer, '\0', sizeof(m_cReadBuffer));
	async_read(m_cSocket, buffer(m_cReadBuffer),transfer_exactly(MESSAGE_HEADER_LEN),std::bind(&ConnectClient::ReadHeader, shared_from_this(), _1));*/
}

void ConnectClient::Stop()
{
	m_cSocket.close();
	ConnectClientMgr::RemoveConnectClient(m_iConnectClientId);
}

/*void ConnectClient::ReadHeader(const boost::system::error_code & err)
{
	std::cout<< strlen(m_cReadBuffer) << ":" <<m_cReadBuffer<<std::endl;


	std::cout<<"ReadHeader:"<<m_cReadBuffer<<std::endl;
	

	int body_len;

	body_len = atoi(m_cReadBuffer);
	
	std::cout<<"ReadHeader len:"<<body_len<<std::endl;
	
	if(err)
	{
		Stop();
		return ;
	}

	memset(m_cReadBuffer, '\0', sizeof(m_cReadBuffer));
	async_read(m_cSocket, buffer(m_cReadBuffer),transfer_exactly(body_len),std::bind(&ConnectClient::ReadBody, shared_from_this(), _1));
}

void ConnectClient::ReadBody(const boost::system::error_code & err)
{
	std::cout<<"ReadBody body:"<<m_cReadBuffer<<std::endl;
	std::cout<<"err err err err body:"<<err<<std::endl;
	
	if(err)
	{
		Stop();
		return ;
	}

	memset(m_cReadBuffer, '\0', sizeof(m_cReadBuffer));
	async_read(m_cSocket, buffer(m_cReadBuffer),transfer_exactly(MESSAGE_HEADER_LEN),std::bind(&ConnectClient::ReadHeader, shared_from_this(), _1));
}*/

void ConnectClient::Write(char* _body_str)
{
	//char* _header_buffer = new char[MESSAGE_HEADER_LEN+1];
	//char* _body_buffer = new char[1024];
	
	//char _header_buffer[1024];
	//char _body_buffer[1024];
	
	m_cNetHandle.DoWrite(_body_str);
	//sprintf(_header_buffer, "%04d", strlen(_body_str));
	//stpcpy(_body_buffer, _body_str);

	//std::cout<<"m_cWriteHeaderBuffer:"<< _header_buffer <<std::endl;
	/*async_write(m_cSocket, buffer(_header_buffer, strlen(_header_buffer)), std::bind(&ConnectClient::WriteHeader, shared_from_this(),_header_buffer, _body_buffer, _1));
	async_write(m_cSocket, buffer(_body_buffer, strlen(_body_buffer)), std::bind(&ConnectClient::WriteBody, shared_from_this(),_body_buffer, _1));*/
	
	/*async_write(m_cSocket, buffer(_header_buffer, strlen(_header_buffer)), std::bind(&ConnectClient::WriteHeader, shared_from_this(),_1));
	async_write(m_cSocket, buffer(_body_str, strlen(_body_str)), std::bind(&ConnectClient::WriteBody, shared_from_this(), _1));*/
}

/*void ConnectClient::WriteHeader(const boost::system::error_code & err)
//void ConnectClient::WriteHeader(const char* _header, const char* _body, const boost::system::error_code & err)
{
	//delete[] _header;
	std::cout<<"WriteHeader:"<< err <<std::endl;
	//std::cout<<"m_cWriteBuffer:"<< _body <<std::endl;
	if(err)
	{
		Stop();
	}
}

void ConnectClient::WriteBody(const boost::system::error_code & err)
//void ConnectClient::WriteBody(const char* _body, const boost::system::error_code & err)
{
	//delete[] _body;
	std::cout<<"WriteBody:"<< err <<std::endl;
	if(err)
	{
		Stop();
	}
}*/

void ConnectClient::OnErrorHandle(const boost::system::error_code & err)
{
	if(err)
	{
		Stop();
	}
}

std::map<int, ConnectClientPtr> ConnectClientMgr::m_cConnectClientMap;

void ConnectClientMgr::AddConnectClient(int _connect_client_id, ConnectClientPtr _connect_client_ptr)
{
	std::cout<<"m_iConnectClientId--add-:"<<_connect_client_id<<std::endl;
	m_cConnectClientMap[_connect_client_id] = _connect_client_ptr;
}

void ConnectClientMgr::RemoveConnectClient(int _connect_client_id)
{
	auto _connect_client = m_cConnectClientMap.find(_connect_client_id);
	if(_connect_client != m_cConnectClientMap.end())
	{
		m_cConnectClientMap.erase(_connect_client);
	}
}

ConnectClientPtr& ConnectClientMgr::GetConnectClient(int _connect_client_id)
{
	return m_cConnectClientMap[_connect_client_id];
}

std::map<int, ConnectClientPtr>& ConnectClientMgr::GetConnectClientMap()
{
	return m_cConnectClientMap;
}

Service::Service(int port)
{
	m_cAcceptor = boost::shared_ptr<ip::tcp::acceptor>(new ip::tcp::acceptor(m_cIoService,ip::tcp::endpoint(ip::tcp::v4(), port)));
	ConnectClientPtr new_connect_client = ConnectClientPtr(new ConnectClient(m_cIoService));
	
	new_connect_client->RegisterMsgProcHandle(std::bind(&Service::NetMsgHandle, this, _1));
	m_cAcceptor->async_accept(new_connect_client->GetSocket(), std::bind(&Service::handle_accept, this, new_connect_client, _1));
}

void Service::handle_accept(ConnectClientPtr _seesion, const boost::system::error_code & err)
{
	ConnectClientMgr::AddConnectClient(_seesion->GetConnectClientId(), _seesion);
	_seesion->start();
	ConnectClientPtr new_connect_client = ConnectClientPtr(new ConnectClient(m_cIoService));
	
	new_connect_client->RegisterMsgProcHandle(std::bind(&Service::NetMsgHandle, this, _1));
	m_cAcceptor->async_accept(new_connect_client->GetSocket(), std::bind(&Service::handle_accept, this, new_connect_client, _1));
}

void Service::NetMsgHandle(const char* strMsg)
{
	
}

void Service::run_handle()
{
	time_t now_time = time(nullptr);
	if(now_time - m_iLastTime >= 1)
	{
		m_iLastTime = time(nullptr);
		std::cout<<"now"<< now_time <<std::endl;
		
		for(auto _connect_client : ConnectClientMgr::GetConnectClientMap())
		{
			char tmp[50];
			sprintf(tmp, "connect_client——id:%d\n", _connect_client.first);
			
			std::cout<<"send:"<<tmp<<std::endl;

			_connect_client.second->Write(tmp);


			strcpy(tmp,"安抚染发法国 79878787aa");
			_connect_client.second->Write(tmp);
		}
	}
	m_cIoService.post(std::bind(&Service::run_handle,this));
}

void Service::run()
{
	m_cIoService.post(std::bind(&Service::run_handle,this));
	std::cout<<"hello world! 5555"<<std::endl;
	m_iLastTime = time(nullptr);
	m_cIoService.run();
}