#include"NetHandle.h"

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

	ip::tcp::socket m_cSocket;
	ip::tcp::endpoint m_cEndPoint;
	CNetHandle m_cNetHandle; 
};

template< typename MsgProcHandle >
void ConnectServer::RegisterMsgProcHandle(MsgProcHandle _MsgProcHandle)
{
	m_cNetHandle.RegisterMsgProcHandle(_MsgProcHandle);
}

//-----------------------------------------
class ConnectClient : public boost::enable_shared_from_this<ConnectClient>
{
public:
	ConnectClient(io_service& _io_service);
	void start();
	void Stop();
	int GetConnectClientId();
	ip::tcp::socket & GetSocket();

	template< typename MsgProcHandle >
	void RegisterMsgProcHandle(MsgProcHandle _MsgProcHandle);
	void Write(char* _body_str);

private:
	void OnErrorHandle(const boost::system::error_code & err);

	int m_iConnectClientId;
	ip::tcp::socket m_cSocket;
	CNetHandle m_cNetHandle; 
};

template< typename MsgProcHandle >
void ConnectClient::RegisterMsgProcHandle(MsgProcHandle _MsgProcHandle)
{
	m_cNetHandle.RegisterMsgProcHandle(_MsgProcHandle);
}

typedef boost::shared_ptr<ConnectClient> ConnectClientPtr;

class ConnectClientMgr
{
public:
	static void AddConnectClient(int _connect_client_id, ConnectClientPtr _connect_client_ptr);
	static void RemoveConnectClient(int _connect_client_id);
	static ConnectClientPtr& GetConnectClient(int _connect_client_id);
	static std::map<int, ConnectClientPtr>& GetConnectClientMap();

private:
	static std::map<int, ConnectClientPtr> m_cConnectClientMap;
};
