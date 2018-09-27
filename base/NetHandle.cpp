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
	async_read(*m_pSocket, buffer(m_cReadBuffer),transfer_exactly(sizeof(SNetMsgHeader)),std::bind(&CNetHandle::ReadHeader, this, _1));
}

void CNetHandle::DoWrite(const char* _body_str)
{
	char _HeaderBuffer[sizeof(SNetMsgHeader) + 1];
	SNetMsgHeader _MsgHeader;

	_MsgHeader.m_iBodyLen = strlen(_body_str);
	memcpy(_HeaderBuffer, &_MsgHeader, sizeof(SNetMsgHeader));
	
	cout<<"mengfan:"<<_HeaderBuffer<<":----mmm"<<endl;
	
	async_write(*m_pSocket, buffer(_HeaderBuffer, sizeof(SNetMsgHeader)), std::bind(&CNetHandle::WriteHeader, this,_1));
	async_write(*m_pSocket, buffer(_body_str, strlen(_body_str)), std::bind(&CNetHandle::WriteBody, this,_1));
}

void CNetHandle::ReadHeader(const boost::system::error_code & err)
{
	std::cout<< strlen(m_cReadBuffer) << ":" <<m_cReadBuffer<<std::endl;

	int body_len;
	SNetMsgHeader _MsgHeader;
	
	memcpy(&_MsgHeader, m_cReadBuffer, sizeof(SNetMsgHeader));
	body_len = _MsgHeader.m_iBodyLen;

	std::cout<<"ReadHeader len:"<<body_len<<std::endl;

	m_fErrorInfoHandle(err);
	if(err)
	{
		return ;
	}
	
	m_cReadBuffer[body_len] = '\0';
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
	DoRead();
}

void CNetHandle::WriteHeader(const boost::system::error_code & err)
{
	m_fErrorInfoHandle(err);
	if(err)
	{
		return ;
	}
}

void CNetHandle::WriteBody(const boost::system::error_code & err)
{
	m_fErrorInfoHandle(err);
	if(err)
	{
		return ;
	}

}