
#include<iostream>
using namespace std;

class A
{	
	public:
		virtual void fun(int values = 1)
		{
			cout<<"call A:fun()"<<endl;
		}
	private :
		virtual void func(int values = 1)
		{
			cout<<"call A:func()"<<endl;
		}
	
};

class AA:public A
{
	private:
		virtual void fun(int values = 2)
		{
			cout<<"call AA:fun()"<<endl;
		}		
};	

class B
{	
	private:
		virtual void fun()
		{
			cout<<"call B:fun()"<<endl;
		}
	
};

class BB :public B
{	
};


int main(void)
{
	A *a = new AA;
	
	/*���õ���AA�����,���ǲ���ȴ��A�ģ��麯���ı׶�*/
	a->fun();
	
	B *b = new BB;
	
	typedef void (*Fun)(void);
	
	/*���õ���B�����,�麯���ı׶�*,һ���׵�ַΪָ��vtbl��ָ�룬Ҳ����vptr*/
	Fun fptr = (Fun)*((int*)*(int*)(b) + 0);
	
	fptr();	
	
	
	return 1;	
}
