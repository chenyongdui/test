#include<ctime>
#include <boost/timer.hpp>
#include"../include/hello.h"
#include <boost/asio.hpp>
using namespace boost::asio;

void test_boost()
{
	boost::timer t;  
    cout << "max timespan:"<<t.elapsed_max()/3600<<"h"<<endl;  
    cout << "min tmiespan:"<<t.elapsed_min()<<"s"<<endl;  
    cout<<"now time elapsed:"<<t.elapsed()<<"s"<<endl;  
}

void test_boost_asio()
{
	try
    {
        io_service io;
        ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 80);
        ip::tcp::socket sock(io);
		
		cout<<"11111"<<endl;
        sock.connect(ep);
		
		string send = "GET /test.php HTTP/1.1\r\n";
		send += "host:127.0.0.1\r\n";
		send += "Connection:Keep-Alive\r\n";
		send += "Content-Type: text/html\r\n\r\n";
		
		sock.write_some(buffer(send));
		
		cout<<"2222"<<endl;
        char str[1024];
        sock.read_some(buffer(str));
		
		cout<<"3333"<<endl;
        std::cout << "receive from" << sock.remote_endpoint().address() << std::endl;;
        std::cout << str << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "hello=> :" << e.what() << std::endl;
    }
}

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
	test_boost();
	test_boost_asio();
}
