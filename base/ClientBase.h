#include"common.h"
#include"network.h"

class CClientBase: public boost::enable_shared_from_this<CClientBase> 
{
public:
	CClientBase(const char* ip, int port);
	void run();

	void NetMsgHandle(const char* strMsg);

private:
	io_service m_cIoService;
	time_t m_iLastTime;
	std::shared_ptr<ConnectServer> m_cConnectServer;

	void run_handle();
};