#include<iostream>
#include<vector>
#include<windows.h>
using namespace std;
//冒泡排序 时间o(n2) 空间o(1) 
void bubble(vector<int>& nums) 
{
	int n=nums.size();
	if(n<2)return;
	for(int i=0;i<n-1;i++) 
	{
		for(int j=0;j<n-1-i&&nums[j]>nums[j+1];j++)
		{
		//	if(nums[j]>nums[j+1])
				swap(nums[j],nums[j+1]);
		}
	}
}
//插入排序 时间o(n2) 空间o(1) 
void insert(vector<int>& nums)
{
	int n=nums.size();
	if(n<2)return;
	for(int i=1;i<n;i++)
	{
		for(int j=i;j>0&&nums[j]<nums[j-1];j--)
		{
		//	if(nums[j]<nums[j-1]) 
				swap(nums[j],nums[j-1]);
		}
	}
}
//归并排序 o(nlogn) o(n) 递归 
void mergesort(vector<int>& nums,int l,int r,int mid)
{
	int i=l,j=mid+1;
	vector<int> temp;
	while(i<=mid&&j<=r)
	{
		if(nums[i]<nums[j])
			temp.push_back(nums[i++]);
		else
			temp.push_back(nums[j++]);
	}
	while(i<=mid)temp.push_back(nums[i++]);
	while(j<=r)temp.push_back(nums[j++]);
	for(int h=0;h<temp.size();h++)
		nums[l+h]=temp[h];
		
}
void merge(vector<int>& nums,int l,int r)
{
	if(l==r) return ;//base case 递归的终止条件 先写 
	int mid =  l+(r-l)/2;//>>1 = /2
	merge(nums,l,mid);
	merge(nums,mid+1,r);
	mergesort(nums,l,r,mid);
}

//快速排序 o(nlogn) o(logn) 
int *partition(vector<int>& nums, int l, int r)//荷兰国旗问题 
{
	int small=l-1,big=r;//大小区域的边界
//	cout<<l<<"  "<<r<<endl;
	while(l<big)
	{
		if(nums[l]<nums[r])
			swap(nums[++small],nums[l++]);
		else if(nums[l]==nums[r])
			l++;
		else
			swap(nums[--big],nums[l]);
	}
	swap(nums[r],nums[big]);
//	cout<<small+1<<"  "<<big<<endl;
	return new int[2]{small+1,big};
}
void quick(vector<int>& nums,int l,int r)
{
	if(l<r)
	{
		int *p=partition(nums,l,r);
		//cout<<l<<p[0]-1<<"  "<<p[1]+1<<r<<endl;
	//	Sleep(1000);
		quick(nums,l,p[0]-1);
		quick(nums,p[1]+1,r);
	}
	else return;
}
//堆排序 o(nlogn) o(1)
void insertHeap(vector<int>& nums, int i)//大数往上跑的过程 
{
	while(nums[i]>nums[(i-1)/2])
	{
		swap(nums[i],nums[(i-1)/2]);
		i=(i-1)/2;
	}
}
void heapify(vector<int>& nums,int index, int size)
{
	int left=index*2+1;//找到左孩子
	while(left<size) 
	{
		//找到左右孩子的最大值 
		int largest=(left+1<size && nums[left+1]>nums[left]) ?left+1:left;
		largest=nums[largest]>nums[index]?largest:index;
		if(largest==index)break;//父节点仍是最大的
		swap(nums[largest],nums[index]) ;
		index=largest;
		left=index*2+1;
	}
}
void heap(vector<int>& nums)
{
	if(nums.size()<=1) return;
	//建大根堆
	for(int i=0;i<nums.size();i++) 
		insertHeap(nums,i);
	int size=nums.size()-1;
	swap(nums[0],nums[size]);
	while(size>0)
	{
		heapify(nums,0,size);
		swap(nums[0],nums[--size]);
	}
	return;
}

int main()
{
	vector<int> nums = {8,5,0,2,0,9,3,0,5};
//	bubble(nums);
//	insert(nums);
//	merge(nums,0,nums.size()-1);
//	quick(nums,0,nums.size()-1);
//	partition(nums,0,nums.size()-1);
	heap(nums);
	for(int h=0;h<nums.size();h++)
		cout<<nums[h]<<endl;
	return 0;
}
