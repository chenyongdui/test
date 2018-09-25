#include<iostream>
using namespace std;

#include"../base/study.h"
#include"../include/network.h"

/*boost::asio::io_service ios;
void foo()
{
    std::cout << "Hello asio!" << std::endl;
	//ios.post(foo);
	ios.dispatch(foo);
}

int main(int argc, char* argv[])
{
    ios.dispatch(foo);

    std::cout << "after post" << std::endl;

    ios.run();
    return 0;
}*/

int main()
{
	Service service(8005);
	service.run();
	return 0;
}


/*class a {};
class b{
	
	
	void test(){}
	
	static int xa;
};
class c:public a{
 virtual void fun()=0;
};

class e
{
	virtual void fun()=0;
};

class d:public b,public c{};

void test()
{
	cout<<"sizeof(a)"<<sizeof(a)<<endl;
 cout<<"sizeof(b)"<<sizeof(b)<<endl;
 cout<<"sizeof(c)"<<sizeof(c)<<endl;
 cout<<"sizeof(d)"<<sizeof(d)<<endl;
 cout<<"sizeof(e)"<<sizeof(e)<<endl;
 
 a f;
 cout<<"sizeof(f)"<<sizeof(f)<<endl;
}*/

/*class a{
private: 
int data;
};

class b{ 
private:
     int data;
  static int data1;
};
 int b::data1=0;

void test()
{
 cout<<"sizeof(a)="<<sizeof(a)<<endl;
 cout<<"sizeof(b)="<<sizeof(b)<<endl;
}*/


/*class Empty {};
class HoldsAnInt {
public:
    int x;
    Empty e;
	
	void test(){}
};

class A{
    public:
    void a(){cout<<"a";}
    void b(){}
    void c(){}
};

template<typename dst_type,typename src_type>
dst_type union_cast(src_type src)
{
    union{
        src_type s;
        dst_type d;
    }u;
    u.s = src;
    return u.d;
}


void ptest()
{
	cout<<1213<<endl;
}

void test()
{
	cout<<"sizeof(HoldsAnInt)="<<sizeof(HoldsAnInt)<<endl;
	
	HoldsAnInt qa, b;
	
	void (HoldsAnInt::*ptr)() = &HoldsAnInt::test;
	
	//void(A::*ptr)()=&A::a;
	
	//A a;
	//(a.*ptr)();
	
	(b.*ptr)();
	
	cout<< "=" <<(void*)&ptest<<endl;
	
	
	cout<< union_cast<void*>(&HoldsAnInt::test) << " " << &HoldsAnInt::test<<endl;
	
	char buf [64] = {0};  
	sprintf(buf , "%x", &HoldsAnInt::test);  
	cout<<buf<<endl;
	
	sprintf(buf , "%x", &ptest);  
	cout<<buf<<endl;
	
	int a[3][3] = { {10,20,30},{40, 50, 60}, {70,80,90} };
	
	int (*p)[3] = a;
	//int ** parr = a;
	
	cout<< p + 1<<endl;
	
	cout<< (p+1)[1][1]<<endl;
	cout<< *((p+1)[1])<<endl;
	
	cout<< *(p + 1)<<endl;
	
	cout<< (*(p+1))[1]<<endl;
	
	cout<< *(*(p+1) + 1)<<endl;
	
	cout<< p[1][1]<<endl;
	
	int da = 1, db = 2, c = 3;
    //定义一个指针数组
    int *arr[3] = {&da, &db, &c};//也可以不指定长度，直接写作 int *parr[]
    //定义一个指向指针数组的指针,即二级指针
    int **parr = arr;
    printf("%d, %d, %d\n", *arr[0], *arr[1], *arr[2]);
    printf("%d, %d, %d\n", **(parr+0), **(parr+1), **(parr+2));
	//cout<< *((*(p+1))[1])<<endl;
}*/


/*class A
{
public:
	A(){ cout<< "A::A" <<endl;}
	
	virtual ~A(){ cout<< "A::~A" <<endl;}
	
	virtual void print(){cout<< "A::print" <<endl; }
};

class B:public A
{
public:
	B(){ cout<< "B::B" <<endl;}
	
	~B(){ cout<< "B::~B" <<endl;}
	
	void print(){cout<< "B::print" <<endl; }
};


void test()
{
	A* p = new B;
	
	
	p->print();
	delete p;
}*/


/*int checkCPU()
{
    {
        union w
        {
            int a;
            char b;
        } c;
        c.a = 1;
        return (c.b == 1);
    }
}*/

/*void test()
{
	//定义,1,2,3,4,5,6,7,8,9,10,11,12,13
	
	//checkCPU();
}*/

/*int main()
{
 test();
 return  0;
}*/





