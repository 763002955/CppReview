#include<iostream>
#include<stack>
using namespace std;

class getMinStack{
	private:
	stack<int> stk;
	stack<int> MinStk;
	public:
	getMinStack() {
		
	}
	void push(int newNum);
	int pop();
	int getMin();
}; 
//push pop ��һ ��pushʱѡ���ظ�ѹ����Сֵ��popstk��minstk��pop���� 
/*
void getMinStack::push(int newNum)
{
	stk.push(newNum);
	if(MinStk.empty())
		MinStk.push(newNum);
	else 
	{
		if(newNum<=MinStk.top())MinStk.push(newNum);
		else MinStk.push(MinStk.top());
	}
}
int getMinStack::pop()
{
	if(stk.empty()) 
	{
		cout<<"stk is empty!"<<endl;
		return -1;
	}
	
	else
	{
		int x=stk.top();
		stk.pop();
		MinStk.pop();
		return x;
	}
	
}*/
//push pop������pushʱ���ظ�ѹ����Сֵ��������popʱ��minstkѡ����pop 
void getMinStack::push(int newNum)
{
	stk.push(newNum);
	if(MinStk.empty())
		MinStk.push(newNum);
	else 
	{
		if(newNum<=MinStk.top())MinStk.push(newNum);
	//	else MinStk.push(MinStk.top());
	//���ظ�ѹ����Сֵ 
	}
}
int getMinStack::pop()
{
	if(stk.empty()) 
	{
		cout<<"stk is empty!"<<endl;
		return -1;
	}
	
	else
	{
		int x=stk.top();
		stk.pop();
		if(MinStk.top()==stk.top()) 
			MinStk.pop();
		return x;
	}
	
}
int getMinStack::getMin()
{
	if(MinStk.empty()){
		cout<<"stk is empty!"<<endl;
		return -1;
	}
	return MinStk.top();
}
int main()
{
	
	getMinStack *s=new getMinStack();
	s->push(4);
	cout<<s->getMin()<<endl;
	s->push(2);
	cout<<s->getMin()<<endl;
	s->push(3);
	s->push(1);
	cout<<s->getMin()<<endl;
	s->push(6);
	cout<<s->getMin()<<endl;
	s->pop();
	s->push(0);
	cout<<s->getMin()<<endl;
	return 0;
}
