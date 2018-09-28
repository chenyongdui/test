#include"common.h"
#include"network.h"

class CClientBase: public boost::enable_shared_from_this<CClientBase> 
{
public:
	CClientBase();
	virtual ~CClientBase();

	bool Init(const char* ip, int port);
	void run();

	void NetMsgHandle(const char* strMsg);

private:
	virtual void OnNetMsgHandle(const char* strMsg) = 0;
	virtual void OnRunHandle() = 0;

	io_service m_cIoService;
	time_t m_iLastTime;

	void run_handle();

protected:
	std::shared_ptr<ConnectServer> m_cConnectServer;
};