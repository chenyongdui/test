#pragma once
#include<boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
using namespace boost::asio;
using namespace std::placeholders;
#include"common.h"

class CNetHandle: public boost::enable_shared_from_this<CNetHandle> 
{
public:
	CNetHandle();
	~CNetHandle();

	void SetSocket(ip::tcp::socket* _pSocket);

	template< typename MsgProcHandle >
	void RegisterMsgProcHandle(MsgProcHandle _MsgProcHandle);

	template<typename ErrorInfoHandle >
	void RegisterErrorInfoHandle(ErrorInfoHandle _ErrorInfoHandle);
	
	void DoRead();
	void DoWrite(const char* _body_str);

private:
	void WriteHeader(const boost::system::error_code & err);
	void WriteBody(const boost::system::error_code & err);
	
	void ReadHeader(const boost::system::error_code & err);
	void ReadBody(const boost::system::error_code & err);

	ip::tcp::socket* m_pSocket;
	char m_cReadBuffer[1024];
	struct SNetMsgHeader
	{
		int m_iBodyLen;
	};

	std::function<void(const boost::system::error_code &)> m_fErrorInfoHandle;
	std::function<void(const char*)> m_fMsgProcHandle;
};

template< typename MsgProcHandle >
void CNetHandle::RegisterMsgProcHandle(MsgProcHandle _MsgProcHandle)
{
	m_fMsgProcHandle = _MsgProcHandle;
}

template<typename ErrorInfoHandle >
void CNetHandle::RegisterErrorInfoHandle(ErrorInfoHandle _ErrorInfoHandle)
{
	m_fErrorInfoHandle = _ErrorInfoHandle;
}

