#include"../../base/ClientBase.h"

int main()
{
	Client client("127.0.0.1", 8005);
	client.run();
	return 0;
}
