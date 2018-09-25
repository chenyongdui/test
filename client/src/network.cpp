#include"../base/common.h"
#include"../include/network.h"

void ConnectServer::Connect(const char * ip, int port)
{
	m_cEndPoint = ip::tcp::endpoint(ip::address_v4::from_string(ip), port);
	m_cSocket.async_connect(m_cEndPoint, std::bind(&ConnectServer::OnConnect, this, _1));
}

ConnectServer::ConnectServer(io_service& _io_service):m_cSocket(_io_service)
{
}

void ConnectServer::Stop()
{
	m_cSocket.close();
}

void ConnectServer::OnConnect(const boost::system::error_code& err)
{
	if(err)
	{
		std::cout<<err <<std::endl;
		return;
	}
	Write("hello world");

	Write("hello 12345");

	memset(m_cReadBuffer, '\0', sizeof(m_cReadBuffer));
	async_read(m_cSocket, buffer(m_cReadBuffer),transfer_exactly(MESSAGE_HEADER_LEN),std::bind(&ConnectServer::ReadHeader, this, _1));
}

void ConnectServer::ReadHeader(const boost::system::error_code & err)
{
	std::cout<< strlen(m_cReadBuffer) << ":" <<m_cReadBuffer<<std::endl;

	std::cout<<"ReadHeader:"<<m_cReadBuffer<<std::endl;
	std::cout<<"error_code:"<<err<<std::endl;


	int body_len;

	body_len = atoi(m_cReadBuffer);

	
	std::cout<<"ReadHeader len:"<<body_len<<std::endl;
	
	if(err)
	{
		Stop();
		return ;
	}

	memset(m_cReadBuffer, '\0', sizeof(m_cReadBuffer));
	async_read(m_cSocket, buffer(m_cReadBuffer),transfer_exactly(body_len),std::bind(&ConnectServer::ReadBody, this, _1));
}

void ConnectServer::ReadBody(const boost::system::error_code & err)
{
	std::cout<<"ReadBody body:"<<m_cReadBuffer<<std::endl;

	Write("hello world");
	Write("hello 56789");
	
	if(err)
	{
		Stop();
		return ;
	}

	memset(m_cReadBuffer, '\0', sizeof(m_cReadBuffer));
	async_read(m_cSocket, buffer(m_cReadBuffer),transfer_exactly(MESSAGE_HEADER_LEN),std::bind(&ConnectServer::ReadHeader, this, _1));
}


void ConnectServer::Write(char* _body_str)
{
	char* _header_buffer = new char[1024];
	char* _body_buffer = new char[1024];
	sprintf(_header_buffer, "%04d", strlen(_body_str));
	stpcpy(_body_buffer, _body_str);


	async_write(m_cSocket, buffer(_header_buffer, strlen(_header_buffer)), std::bind(&ConnectServer::WriteHeader, this,_header_buffer, _body_buffer, _1));
	async_write(m_cSocket, buffer(_body_buffer, strlen(_body_buffer)), std::bind(&ConnectServer::WriteBody, this,_body_buffer, _1));
}

void ConnectServer::WriteHeader(const char* _header, const char* _body, const boost::system::error_code & err)
{
	delete[] _header;
	std::cout<<"WriteHeader:"<< err <<std::endl;
	if(err)
	{
		Stop();
	}
}

void ConnectServer::WriteBody(const char* _body, const boost::system::error_code & err)
{
	delete[] _body;
	std::cout<<"WriteBody:"<< err <<std::endl;
	if(err)
	{
		Stop();
	}
}

Client::Client(const char* ip, int port)
{
	m_cConnectServer = std::shared_ptr<ConnectServer>(new ConnectServer(m_cIoService));
	m_cConnectServer->Connect(ip, port);
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


