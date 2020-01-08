#include<iostream>
#include<stack>
#include<queue>
using namespace std;
//队列实现栈 
/* 
class QueueToStack{
	private:
		queue<int> q;
	public:
		QueueToStack(){
			
		}
		~QueueToStack();
		int top()//return top  
		{
			for(int i=0;i<q.size()-1;i++)
			{
				q.push(q.front());
				q.pop();
			}
			int x=q.front();
			q.push(q.front());
			q.pop();
			return x;
		}
		void push(int num)
		{
			q.push(num);
		}
		int pop(){
			//把之前的元素重新入队列，排到栈顶的后面，然后pop栈顶 
			for(int i=0;i<q.size()-1;i++)
			{
				q.push(q.front());
				q.pop();
			}
			int x=q.front();
			q.pop();
			return x;
		}
		bool empty()
		{
			return q.empty();
		}
}; */

//栈实现队列 
class StackToQueue{
	private:
		stack<int> stk1,stk2;
	public:
		StackToQueue(){
			
		} 
		~StackToQueue();
		int peek()//return top  
		{
			if(stk2.empty())
			{
				while(!stk1.empty())
				{
					stk2.push(stk1.top());
					stk1.pop();
				}
			}
			return stk2.top();
		}
		void push(int num)
		{
			stk1.push(num);
		}
		int pop()
		{
			if(stk2.empty())
				while(!stk1.empty())
				{
					stk2.push(stk1.top());
					stk1.pop();
				}
			int x=stk2.top();
			stk2.pop();
			return x;
		}
		bool empty()
		{
			return stk1.empty()&&stk2.empty();
		}		
}; 
int main()
{
/*	QueueToStack *s = new QueueToStack();
	s->push(2);s->push(3);
	cout<< s->pop()<<s->empty()<<endl;
	s->push(1);
	cout<<s->top()<<endl;
	*/
	StackToQueue *q = new StackToQueue();
	q->push(2);q->push(3);q->push(4);
	cout<<q->peek()<<endl;
	cout<<q->pop();
	return 0;
}
