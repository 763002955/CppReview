#include<iostream>
#include<vector>
using namespace std;
//数组实现栈 利用index标志需要填入数据的位置即可 
class ArrayStack{
	private:
		int *arr; 
		int size;//arr最大容量 
		int index;//要填入数据的位置 
	public:
		ArrayStack(int size);
		~ArrayStack();
		int peek();//return top  
		bool push(int num);
		int pop();
}; 
ArrayStack::ArrayStack(int s)
{
	size = s;
	arr = new int[size];
	index=0;
}
int ArrayStack::peek()
{
	if(index==0) return NULL;
	return arr[index-1];
}
int ArrayStack::pop()
{
	if(index==0) return NULL;
	return arr[--index];
} 
bool ArrayStack::push(int num)
{
	if(index==size) return false; 
	arr[index++]=num;
	return true;
} 
//数组实现队列  需要标志填入和弹出的位置 
class ArrayQueue{
	private:
		int *arr;
		int size;//队列内数数量
		int maxSize;//数组固定大小 
		int start,end;
	public:
		ArrayQueue(int size);
		~ArrayQueue();
		int peek();//return top  
		bool push(int num);
		int poll();
};
ArrayQueue::ArrayQueue(int s)
{
	maxSize=s;
	arr=new int[maxSize];
	size=0;//size判断空/非空 
	start=0;//弹出的位置 
	end=0; // 写入的位置 
}
int ArrayQueue::peek() 
{
	if(size==0) return NULL;
	return arr[start];
}
int ArrayQueue::poll()
{
	if(size==0)return false;
	size--;
	return arr[(start++)%maxSize];
}
bool ArrayQueue::push(int num)
{
	if(size==maxSize)return false;
	size++;
	arr[end]=num;
	end=(end+1)%maxSize;
	return true;
}
int main()
{
	
	ArrayStack *s=new ArrayStack(5);
	cout<<s->pop()<<endl;
	cout<<s->peek()<<endl;
	cout<<s->push(1)<<endl;
	cout<<s->push(21)<<endl;
	cout<<s->push(4)<<endl;
	cout<<s->push(5)<<endl;
	cout<<s->push(2)<<endl;
	cout<<s->pop()<<endl;
	cout<<s->push(7)<<endl;
	cout<<s->peek()<<endl;
	
	
	
	ArrayQueue *s=new ArrayQueue(5);
	cout<<s->poll()<<endl;
	cout<<s->peek()<<endl;
	cout<<s->push(1)<<endl;
	cout<<s->push(21)<<endl;
	cout<<s->push(4)<<endl;
	cout<<s->push(5)<<endl;
	cout<<s->push(2)<<endl;
	cout<<s->poll()<<endl;
	cout<<s->push(7)<<endl;
	cout<<s->poll()<<endl;
	cout<<s->poll()<<endl;
	cout<<s->poll()<<endl;
	
	return 0;
}
