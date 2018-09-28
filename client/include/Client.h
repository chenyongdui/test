#include"../../base/ClientBase.h"

class CClient: public CClientBase
{
public:
	CClient();
	~CClient();
	
private:
	void OnNetMsgHandle(const char* strMsg) override;
	void OnRunHandle() override;
};