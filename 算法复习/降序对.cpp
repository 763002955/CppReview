#include<iostream>
#include<vector>
using namespace std;
int res;
//�鲢���� o(nlogn) o(n) �ݹ� 
void mergesort(vector<int>& nums,int l,int r,int mid)
{
	int i=l,j=mid+1;
	vector<int> temp;
	while(i<=mid&&j<=r)
	{
		if(nums[i]<nums[j])
		{
			
			temp.push_back(nums[i++]);
		}
			
		else
		{
			temp.push_back(nums[j++]);
			res+=(mid-i+1) ;
		} 
			
	}
	while(i<=mid)temp.push_back(nums[i++]);
	while(j<=r)temp.push_back(nums[j++]);
	for(int h=0;h<temp.size();h++)
		nums[l+h]=temp[h];
		
}
void merge(vector<int>& nums,int l,int r)
{
	if(l==r) return ;//base case �ݹ����ֹ���� ��д 
	int mid =  l+(r-l)/2;//>>1 = /2
	merge(nums,l,mid);
	merge(nums,mid+1,r);
	mergesort(nums,l,r,mid);
}


int main()
{
	//��������ÿ�����ұ��ж��ٸ�������С
	vector<int> nums = {4,3,5,0,6};
	res=0;
	merge(nums,0,nums.size()-1);
	cout<<res;
	return 0;
}
