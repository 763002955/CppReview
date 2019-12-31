#include<iostream>
#include<vector>
using namespace std;
//����ʵ��ջ ����index��־��Ҫ�������ݵ�λ�ü��� 
class ArrayStack{
	private:
		int *arr; 
		int size;//arr������� 
		int index;//Ҫ�������ݵ�λ�� 
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
//����ʵ�ֶ���  ��Ҫ��־����͵�����λ�� 
class ArrayQueue{
	private:
		int *arr;
		int size;//������������
		int maxSize;//����̶���С 
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
	size=0;//size�жϿ�/�ǿ� 
	start=0;//������λ�� 
	end=0; // д���λ�� 
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
