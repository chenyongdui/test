#include"NetHandle.h"

CNetHandle::CNetHandle()
{
	
}

CNetHandle::~CNetHandle()
{
	
}

void CNetHandle::SetSocket(ip::tcp::socket* _pSocket)
{
	m_pSocket = _pSocket;
}

void CNetHandle::DoRead()
{
	memset(m_cReadBuffer, '\0', sizeof(m_cReadBuffer));
	async_read(*m_pSocket, buffer(m_cReadBuffer),transfer_exactly(MESSAGE_HEADER_LEN),		std::bind(&CNetHandle::ReadHeader, this, _1));
}

void CNetHandle::DoWrite(const char* _body_str)
{
	//char* _header_buffer = new char[1024];
	//char* _body_buffer = new char[1024];
	
	char _header_buffer[1024];
	sprintf(_header_buffer, "%04d", strlen(_body_str));
	//stpcpy(_body_buffer, _body_str);


	/*async_write(m_cSocket, buffer(_header_buffer, strlen(_header_buffer)), std::bind(&ConnectServer::WriteHeader, this,_header_buffer, _body_buffer, _1));
	async_write(m_cSocket, buffer(_body_buffer, strlen(_body_buffer)), std::bind(&ConnectServer::WriteBody, this,_body_buffer, _1));*/
	
	
	async_write(*m_pSocket, buffer(_header_buffer, strlen(_header_buffer)), std::bind(&CNetHandle::WriteHeader, this,_1));
	async_write(*m_pSocket, buffer(_body_str, strlen(_body_str)), std::bind(&CNetHandle::WriteBody, this,_1));
}

void CNetHandle::ReadHeader(const boost::system::error_code & err)
{
	std::cout<< strlen(m_cReadBuffer) << ":" <<m_cReadBuffer<<std::endl;

	int body_len;

	body_len = atoi(m_cReadBuffer);

	
	std::cout<<"ReadHeader len:"<<body_len<<std::endl;

	m_fErrorInfoHandle(err);
	if(err)
	{
		return ;
	}
	

	memset(m_cReadBuffer, '\0', sizeof(m_cReadBuffer));
	async_read(*m_pSocket, buffer(m_cReadBuffer),transfer_exactly(body_len),std::bind(&CNetHandle::ReadBody, this, _1));
}

void CNetHandle::ReadBody(const boost::system::error_code & err)
{
	m_fMsgProcHandle(m_cReadBuffer);
	m_fErrorInfoHandle(err);
	if(err)
	{
		return ;
	}

	memset(m_cReadBuffer, '\0', sizeof(m_cReadBuffer));
	async_read(*m_pSocket, buffer(m_cReadBuffer),transfer_exactly(MESSAGE_HEADER_LEN),std::bind(&CNetHandle::ReadHeader, this, _1));
}

void CNetHandle::WriteHeader(const boost::system::error_code & err)
{
	//delete[] _header;
	m_fErrorInfoHandle(err);
	if(err)
	{
		return ;
	}
}

void CNetHandle::WriteBody(const boost::system::error_code & err)
{
	//delete[] _body;
	m_fErrorInfoHandle(err);
	if(err)
	{
		return ;
	}

}