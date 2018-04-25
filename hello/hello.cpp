#include<ctime>
#include"../include/hello.h"

void SayHello()
{
	int i = 0;
	auto j = i;
	for(; j<5; j++)
		cout<<"hello world oo "<<j<<endl;
	cout<<"start"<<endl;

	time_t t;
	time(&t);
	cout<<asctime(localtime(&t))<<endl;
	cout<<"end"<<endl;
}
