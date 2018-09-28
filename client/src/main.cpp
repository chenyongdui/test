#include"Client.h"

int main()
{
	CClient client;
	client.Init("127.0.0.1", 8005);
	client.run();
	return 0;
}
