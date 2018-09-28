#include"../../base/ServerBase.h"

class CCService:public CServiceBase
{
public:
	CCService();
	~CCService();

private:
	void OnNetMsgHandle(const char* strMsg) override;
	void OnRunHandle() override;
};