#pragma once
#ifndef Code01_SplitSumClosed_HPP
#define Code01_SplitSumClosed_HPP
#include <vector>
#include <algorithm>
#include "utility_func.hpp"
#include "stop_watch.hpp"
using namespace  std;
// 题目一
//给定一个正数数组arr，
//请把arr中所有的数分成两个集合，尽量让两个集合的累加和接近
//返回：
//最接近的情况下，较小集合的累加和

namespace Code01_SplitSumClosed {

	class Solution {
	public:
		int right(vector<int> & arr) {
			if (arr.size() < 2) {
				return 0;
			}
			int sum = 0;
			for (int num : arr) {
				sum += num;
			}
			return process1(arr, 0, sum / 2);
		}

		int process1(vector<int> & arr, int index, int sum)
		{
			if(index== arr.size())
			{
				return 0;
			}
			int p1 = process1(arr, index + 1, sum);
			int p2 = INT_MIN;
			if (sum - arr[index] >= 0)
			{
				p2 = arr[index] + process1(arr, index + 1, sum - arr[index]);
			}
			return std::max(p1, p2);
		}

		int dp1(vector<int> & arr) 
		{
			if (arr.size() < 2) {
				return 0;
			}
			int sum = 0;
			for (int num : arr) {
				sum += num;
			}
			int N = arr.size();
			int halfsum = sum / 2;
			vector<vector<int>> dp(N + 1, vector<int>(halfsum + 1, 0));

			for (int index = N - 1; index >= 0; index--)
			{
				for (int s = 0; s <= halfsum; s++)
				{
					int p1 = dp[index + 1][s];
					int p2 = INT_MIN;
					if (s - arr[index] >= 0)
					{
						p2 = arr[index] + dp[index + 1][s - arr[index]];
					}
					dp[index][s] = std::max(p1, p2);
				}
			}
			return dp[0][halfsum];
		}


	};

}


void test_Code01_SplitSumClosed() {

	cout << "test_Code01_SplitSumClosed begin" << endl;
	Code01_SplitSumClosed::Solution sln;
	stop_watch st;
	double elapse_force = 0.0;
	double elapse_dp = 0.0;
	double elapse_dp_EO = 0.0;
	int maxLen = 20;
	int maxValue = 50;
	int testTime = 10;
	cout << "test begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(maxLen, maxValue,1);
		st.start();
		int ans1 = sln.right(arr);
		st.stop();
		elapse_force += st.elapsed_ms();
		st.start();
		int ans2 = sln.dp1(arr);
		st.stop();
		elapse_dp += st.elapsed_ms();
		if (ans1 != ans2)
		{
			print(arr);
			cout << ans1<<","<<ans2<< endl;
		}
	}
	cout << "test end" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force / testTime << "ms" << endl;
	cout << "dp:" << elapse_dp / testTime << "ms" << endl;
	cout << "test_Code01_SplitSumClosed end" << endl;
	//	test begin
	//	test end
	//	average elapse(ms)
	//	force:19.4786ms
	//	dp : 0.1969ms
}


#endif