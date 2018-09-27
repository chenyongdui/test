#include"common.h"
#include"network.h"

class Service : public boost::enable_shared_from_this<ConnectClient>
{
public:
	Service(int port);
	void run();
	
	void NetMsgHandle(const char* strMsg);

private:
	io_service m_cIoService;
	boost::shared_ptr<ip::tcp::acceptor> m_cAcceptor;
	time_t m_iLastTime;

	void run_handle();
	void handle_accept(ConnectClientPtr _seesion, const boost::system::error_code & err);
};