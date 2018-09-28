#include"Server.h"

CCService::CCService()
{
}

CCService::~CCService()
{
}

void CCService::OnNetMsgHandle(const char* strMsg)
{
	std::cout<<"ReadBody body-------->2:"<<strMsg<<std::endl;
}

void CCService::OnRunHandle()
{
	for(auto _connect_client : ConnectClientMgr::GetConnectClientMap())
	{
		char tmp[100];
		sprintf(tmp, "connect_client——id:%d\n", _connect_client.first);
		
		std::cout<<"send:"<<tmp<<std::endl;

		_connect_client.second->Write(tmp);


		strcpy(tmp,"安抚染发法国 79878787aa");
		_connect_client.second->Write(tmp);
		
		strcpy(tmp,"啊发发7575757%&%&%&% 79878787aa事故发生灌水灌水65654456454放首发申购");
		_connect_client.second->Write(tmp);
	}
}