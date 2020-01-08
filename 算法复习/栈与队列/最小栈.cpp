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
//push pop 法一 ：push时选择重复压入最小值，popstk与minstk都pop即可 
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
//push pop法二：push时不重复压入最小值，而是在pop时候，minstk选择性pop 
void getMinStack::push(int newNum)
{
	stk.push(newNum);
	if(MinStk.empty())
		MinStk.push(newNum);
	else 
	{
		if(newNum<=MinStk.top())MinStk.push(newNum);
	//	else MinStk.push(MinStk.top());
	//不重复压入最小值 
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
