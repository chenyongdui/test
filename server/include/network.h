#include<boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
using namespace boost::asio;
using namespace std::placeholders;

class ConnectClient : public boost::enable_shared_from_this<ConnectClient>
{
public:
	ConnectClient(io_service& _io_service);
	void start();
	void Stop();
	int GetConnectClientId();
	ip::tcp::socket & GetSocket();
	void Write(char* _body_str);

private:
	void ReadHeader(const boost::system::error_code & err);
	void ReadBody(const boost::system::error_code & err);
	void WriteHeader(const char* _header,const  char* _body, const boost::system::error_code & err);
	void WriteBody(const char* _body,const boost::system::error_code & err);

	int m_iConnectClientId;
	ip::tcp::socket m_cSocket;
	char m_cReadBuffer[1024];
};

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

class Service
{
public:
	Service(int port);
	void run();

private:
	io_service m_cIoService;
	boost::shared_ptr<ip::tcp::acceptor> m_cAcceptor;
	time_t m_iLastTime;

	void run_handle();
	void handle_accept(ConnectClientPtr _seesion, const boost::system::error_code & err);
};