#include"Client.h"

CClient::CClient()
{
}

CClient::~CClient()
{
}

void CClient::OnNetMsgHandle(const char* strMsg)
{
	std::cout<<"ReadBody body-------->2:"<<strMsg<<std::endl;
}

void CClient::OnRunHandle()
{
	m_cConnectServer->Write("hello 56789哈哈阿凡达发放安抚");
	
	m_cConnectServer->Write("你好德尔芬格788yy放松放松是干啥干啥公使馆升格");
}