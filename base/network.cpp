#include"common.h"
#include"network.h"

ConnectServer::ConnectServer(io_service& _io_service):m_cSocket(_io_service)
{
	m_cNetHandle.RegisterErrorInfoHandle(std::bind(&ConnectServer::OnErrorHandle, this, _1));
}

void ConnectServer::Connect(const char * ip, int port)
{
	m_cEndPoint = ip::tcp::endpoint(ip::address_v4::from_string(ip), port);
	m_cSocket.async_connect(m_cEndPoint, std::bind(&ConnectServer::OnConnect, this, _1));
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
	m_cNetHandle.SetSocket(&m_cSocket);
	m_cNetHandle.DoRead();
}

void ConnectServer::OnErrorHandle(const boost::system::error_code & err)
{
	if(err)
	{
		Stop();
	}
}

void ConnectServer::Write(const char* _body_str)
{
	m_cNetHandle.DoWrite(_body_str);
}

//-------------------------------------------------
ConnectClient::ConnectClient(io_service& _io_service):m_cSocket(_io_service)
{
	m_iConnectClientId = time(nullptr);
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
}

void ConnectClient::Stop()
{
	m_cSocket.close();
	ConnectClientMgr::RemoveConnectClient(m_iConnectClientId);
}

void ConnectClient::Write(const char* _body_str)
{
	m_cNetHandle.DoWrite(_body_str);
}

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
