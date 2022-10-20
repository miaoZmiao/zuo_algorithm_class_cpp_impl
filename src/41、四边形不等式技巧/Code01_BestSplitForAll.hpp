#pragma once
#ifndef Code01_BestSplitForAll_HPP
#define Code01_BestSplitForAll_HPP
#include <algorithm>
#include "utility_func.hpp"
//给定一个非负数组arr，长度为N，//那么有N - 1种方案可以把arr切成左右两部分//每一种方案都有，min{ 左部分累加和，右部分累加和 }//求这么多方案中，min{ 左部分累加和，右部分累加和 }的最大值是多少？//整个过程要求时间复杂度O(N)
namespace Code01_BestSplitForAll {

	int bestSplit1(vector<int>& arr)
	{
		if (arr.size() < 2)
		{
			return 0;
		}
		int N = arr.size();
		int ans = 0;
		for (int s = 0; s < N; s++)
		{
			int sumL = 0;
			for (int i = 0; i <= s; i++)
			{
				sumL += arr[i];
			}
			int sumR = 0;
			for (int i = s + 1; i < N; i++)
			{
				sumR += arr[i];
			}
			ans = std::max(ans, std::min(sumL, sumR));
		}
		return ans;
	}

	int bestSplit2(vector<int>& arr)
	{
		if (arr.size() < 2)
		{
			return 0;
		}
		int N = arr.size();
		vector<int> sum(N, 0);
		sum[0] = arr[0];
		for (int i = 1; i < N; i++)
		{
			sum[i] += sum[i - 1] + arr[i];
		}
		int ans = 0;
		for (int i = 0; i < N; i++)
		{
			int sumL = sum[i];
			int sumR = sum[N - 1] - sumL;
			ans = std::max(ans, std::min(sumL, sumR));
		}
		return ans;
	}

}


void test_Code01_BestSplitForAll() {
	int len = 100;
	int maxvalue = 200;
	int minvalue = 0;
	int testTime = 10000;
	cout << "test_Code01_BestSplitForAll begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(len, maxvalue, minvalue);
		int ans1 = Code01_BestSplitForAll::bestSplit1(arr);
		int ans2 = Code01_BestSplitForAll::bestSplit2(arr);
		if (ans1 != ans2)
		{
			print(arr);
			cout << ans1 << "," << ans2 << endl;
			break;
		}
	}
	cout << "test_Code01_BestSplitForAll end" << endl;
}

#endif