#include"../base/common.h"
#include"../base/study.h"

/* 2-10：2-10
   J   : 11
   Q   : 12
   K   : 13
   A   ：14
   小王：15
   大王：16
1、先统计每种牌的数量
2、再统计三张牌的组数和剩余牌的张数，统计时并处理三张牌的不同类型牌之间是否连续，从3点开始，因为2点不会和别的组成飞机
3、判断三张牌的组数是否大于等于2，并且三张牌的组数是否等于剩余牌的张数*/

#define DOUDIZHU_CHECK_SIZE 18
bool check_plane(int target[], int n)
{
	int set[DOUDIZHU_CHECK_SIZE];
	int i;
	int last,cnt,cnt2;

	memset(set,0, sizeof(set));
	for(i = 0; i < n; i++)
	{
		set[target[i]] ++ ;
	}

	last = 0;
	cnt = 0;
	cnt2 = set[2];
	for(i = 3; i < DOUDIZHU_CHECK_SIZE;i++)
	{
		cnt2 += set[i];
		
		if(set[i] >= 3 && ( last == 0 || i - 1 == last ))
		{
			last = i;
			cnt ++;
			cnt2 -= 3;
		}
	}
	if(cnt >=2 && cnt == cnt2)
	{
		return true;
	}
	return false;
}

/*
1-9万：1-9
1-9条：11-19
1-9饼：21-29
东：31，南：33，西：35，北：37，中：39，发：41，白：43
和牌规则：有一对对子做将牌，剩余的能组成顺子或刻子，刻子三张一样，顺子三张连续的牌
*/
#define MAJIANG_CHECK_WIN 45
bool majiang_check(int set[], int n, int count, int index)
{
	int i;
	int flag = 1;
	
	if(0 == count)
	{
		return true;
	}
	
	for(i = index; i < n;i++)
	{
		if(set[i] >= 3)
		{
			set[i] -= 3;
			count -= 3;
			if(majiang_check(set,n,count,i))
			{
				return true;
			}
			set[i] += 3;
			count += 3;
		}
		if( i+2 < n && set[i] >= 1 && set[i+1] >= 1 && set[i+2] >= 1)
		{
			set[i] -= 1;
			set[i+1] -= 1;
			set[i+2] -= 1;
			count -= 3;
			if(majiang_check(set,n,count,i))
			{
				return true;
			}
			set[i] += 1;
			set[i+1] += 1;
			set[i+2] += 1;
			count += 3;
		}
	}
	return false;
}

bool majiang_check_win(int target[], int count)
{
	int set[MAJIANG_CHECK_WIN];
	int i;
	
	memset(set,0, sizeof(set));
	for(i = 0; i < count; i++)
	{
		set[target[i]] ++ ;
	}

	for(i=1;i< MAJIANG_CHECK_WIN; i ++)
	{
		if(set[i] >= 2)
		{
			set[i] -= 2;
			count -= 2;
			if(majiang_check(set, MAJIANG_CHECK_WIN, count, 1))
			{
				return true;
			}
			set[i] += 2;
			count += 2;
		}
	}
	return false;
}

class A
{
public:
	A(){ id=cnt++; cout<<"A::A"<<endl; }
	~A(){ cout<<"A::~A"<<endl; }
	int get(){ return id; }
	static void reset(){ cnt = 1; }

private:
	static int cnt;
	int id;
};
int A::cnt = 1;

void pointer_test()
{
	cout<<"============1=========="<<endl;
	A* pa = new A[3];
	delete[] pa;

	cout<<"============2=========="<<endl;
	A* pb[3];
	pb[0] = new A;
	pb[1] = new A;
	pb[2] = new A;
	delete pb[0];
	delete pb[1];
	delete pb[2];						//不能使用delete[] pb;

	cout<<"============3=========="<<endl;
	A::reset();
	A a[3][3];
	A (*pc)[3];

	pc = a;
	cout<<"(**pc).get():"<<(**pc).get()<<endl;
	cout<<"(*pc)->get():"<<(*pc)->get()<<endl;
	cout<<"pc[1][1].get():"<<pc[1][1].get()<<endl;
	cout<<"pc[1]->get():"<<pc[1]->get()<<endl;
	cout<<"(pc[1] + 1)->get():"<<(pc[1] + 1)->get()<<endl;
	cout<<"(pc+1)[1][1].get():"<<(pc+1)[1][1].get()<<endl;
	cout<<"((pc+1)[1]+1)[1].get():"<<((pc+1)[1]+1)[1].get()<<endl;
	cout<<"(*(pc+1))->get():"<<(*(pc+1))->get()<<endl;
	cout<<"(**(pc+1)).get():"<<(**(pc+1)).get()<<endl;
	cout<<"(*(pc+1)[1]).get():"<<(*(pc+1)[1]).get()<<endl;
	cout<<"(*(*(pc+1)+1)).get():"<<(*(*(pc+1)+1)).get()<<endl;
}



void test()
{ 
}



















