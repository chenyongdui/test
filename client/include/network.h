#include<boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include"NetHandle.h"

using namespace boost::asio;
using namespace std::placeholders;

class ConnectServer: public boost::enable_shared_from_this<ConnectServer> 
{
public:
	ConnectServer(io_service& _io_service);
	void Connect(const char* ip, int port);
	void Stop();

	template< typename MsgProcHandle >
	void RegisterMsgProcHandle(MsgProcHandle _MsgProcHandle);
	void Write(char* _body_str);

private:
	void OnConnect(const boost::system::error_code& err);

	void OnErrorHandle(const boost::system::error_code & err);
	//void WriteHeader(const char* _header, const char* _body, const boost::system::error_code & err);
	//void WriteBody(const char* _body, const boost::system::error_code & err);
	
	/*void WriteHeader(const boost::system::error_code & err);
	void WriteBody(const boost::system::error_code & err);
	
	void ReadHeader(const boost::system::error_code & err);
	void ReadBody(const boost::system::error_code & err);*/

	ip::tcp::socket m_cSocket;
	ip::tcp::endpoint m_cEndPoint;
	//char m_cReadBuffer[1024];
	CNetHandle m_cNetHandle; 
};

template< typename MsgProcHandle >
void ConnectServer::RegisterMsgProcHandle(MsgProcHandle _MsgProcHandle)
{
	m_cNetHandle.RegisterMsgProcHandle(_MsgProcHandle);
}

class Client: public boost::enable_shared_from_this<ConnectServer> 
{
public:
	Client(const char* ip, int port);
	void run();

	void NetMsgHandle(const char* strMsg);

private:
	io_service m_cIoService;
	time_t m_iLastTime;
	std::shared_ptr<ConnectServer> m_cConnectServer;

	void run_handle();
};

