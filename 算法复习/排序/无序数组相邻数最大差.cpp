#include<iostream>
#include<vector>
using namespace std;
int bucket(int num,int len,int min,int max)//判断某数应该进入哪个桶 
{
	return (num-min)*len/(max-min);
}
int maxGap(vector<int>& nums) 
{
	if(nums.size()<2)return 0;
	int N=nums.size();
	int min=INT_MAX,max=INT_MIN;
	for(int i=0;i<N;i++)//找到数组的最小值&最大值 
	{
		min = (nums[i]<min)?nums[i]:min;
		max = (nums[i]>max)?nums[i]:max;
	}
	//建立桶
	vector<bool> hasNum(N+1,false);//桶内是否为空 
	vector<int> maxs(N+1,INT_MIN);//每个桶内最大值 
	vector<int> mins(N+1,INT_MAX);//每个桶内最小值 
	for(int i=0;i<N;i++) 
	{
		int b_id=bucket(nums[i],N,min,max);
		if(hasNum[b_id]==true)
		{
			mins[b_id] = (nums[i]<mins[b_id])?nums[i]:mins[b_id];
			maxs[b_id] = (nums[i]>maxs[b_id])?nums[i]:maxs[b_id];
		}
		else
		{
			mins[b_id] = nums[i];
			maxs[b_id] = nums[i];
			hasNum[b_id]=true;
		}
	}
	//遍历堆，在相邻非空堆之间寻找最大差值 
	int res=0;//result 
	int lastMax=maxs[0];//记录上一个非空堆的最大值 
	for(int i=1;i<=N;i++)
	{
		if(hasNum[i])
		{
			res=(mins[i]-lastMax)>res?(mins[i]-lastMax):res;
			lastMax=maxs[i];
		}
	}
	return res;
}

int main()
{
	//题意是找每个数右边有多少个数比他小
	vector<int> nums = {4,3,5,0,6};
	cout<<maxGap(nums);
	return 0;
}
