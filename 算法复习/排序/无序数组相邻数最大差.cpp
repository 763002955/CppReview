#include<iostream>
#include<vector>
using namespace std;
int bucket(int num,int len,int min,int max)//�ж�ĳ��Ӧ�ý����ĸ�Ͱ 
{
	return (num-min)*len/(max-min);
}
int maxGap(vector<int>& nums) 
{
	if(nums.size()<2)return 0;
	int N=nums.size();
	int min=INT_MAX,max=INT_MIN;
	for(int i=0;i<N;i++)//�ҵ��������Сֵ&���ֵ 
	{
		min = (nums[i]<min)?nums[i]:min;
		max = (nums[i]>max)?nums[i]:max;
	}
	//����Ͱ
	vector<bool> hasNum(N+1,false);//Ͱ���Ƿ�Ϊ�� 
	vector<int> maxs(N+1,INT_MIN);//ÿ��Ͱ�����ֵ 
	vector<int> mins(N+1,INT_MAX);//ÿ��Ͱ����Сֵ 
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
	//�����ѣ������ڷǿն�֮��Ѱ������ֵ 
	int res=0;//result 
	int lastMax=maxs[0];//��¼��һ���ǿնѵ����ֵ 
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
	//��������ÿ�����ұ��ж��ٸ�������С
	vector<int> nums = {4,3,5,0,6};
	cout<<maxGap(nums);
	return 0;
}
