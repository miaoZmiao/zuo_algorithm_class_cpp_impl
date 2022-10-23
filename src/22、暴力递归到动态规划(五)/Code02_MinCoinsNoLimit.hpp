#pragma once
#ifndef Code02_MinCoinsNoLimit_HPP
#define Code02_MinCoinsNoLimit_HPP
#include <vector>
#include <iostream>
#include <algorithm>
#include <algorithm>
#include "utility_func.hpp"
#include "stop_watch.hpp"
//arr是面值数组，其中的值都是正数且没有重复。再给定一个正数aim。
//每个值都认为是一种面值，且认为张数是无限的。
//返回组成aim的最少货币数

using namespace std;

namespace Code02_MinCoinsNoLimit {

	class Solution
	{
	public:
		int minCoins(vector<int> & arr, int aim) {
			int ans = process1(arr, 0, aim);
			return ans == INT_MAX ? -1 : ans;
		}
		int process1(vector<int> & arr, int index, int target) {
			if (index == arr.size())
			{
				return target == 0 ? 0 : INT_MAX;
			}
			int aim = target;
			int ways = INT_MAX;
			int value = arr[index];
			for (int zhang = 0; zhang * value <= aim; zhang++)
			{
				int next = process1(arr, index + 1,
					target - zhang * value);
				if (next != INT_MAX)
				{
					ways = std::min(ways, zhang + next);
				}
			}
			return ways;
		}

		int dp1(vector<int> & arr, int target) {
			
			//int aim = target;
			int N = arr.size();
			vector<vector<int>> dp(N+1, vector<int>(target +1, INT_MAX));
			dp[N][0] = 0;

			for (int index = N - 1; index >= 0; index--)
			{
				int value = arr[index];
				for (int aim = 0; aim <= target; aim++)
				{
					int ways = INT_MAX;
					for (int zhang = 0; zhang * value <= aim; zhang++)
					{
						int next = dp[index + 1][aim - zhang * value];
						if (next != INT_MAX)
						{
							ways = std::min(ways, zhang + next);
						}
					}
					dp[index][aim] = ways;
				}
			}
			return dp[0][target] == INT_MAX?-1:dp[0][target];
		}

		int dp2(vector<int> & arr, int target) {

			//int aim = target;
			int N = arr.size();
			vector<vector<int>> dp(N + 1, vector<int>(target + 1, INT_MAX));
			dp[N][0] = 0;

			for (int index = N - 1; index >= 0; index--)
			{
				int value = arr[index];
				for (int aim = 0; aim <= target; aim++)
				{
					dp[index][aim] = dp[index + 1][aim];
					if (aim - value >= 0 && 
						INT_MAX != dp[index][aim - value])
					{
						dp[index][aim] =
							std::min(dp[index][aim], 
								dp[index][aim - value] + 1);
					}
				}
			}
			return dp[0][target] == INT_MAX ? -1 : dp[0][target];
		}

	};

}

void test_Code02_MinCoinsNoLimit() {

	cout << "test_Code02_MinCoinsNoLimit begin" << endl;
	int maxLen = 30;
	int maxValue = 30;
	int testTime = 10;
	Code02_MinCoinsNoLimit::Solution sln;
	stop_watch st;
	double elapse_force = 0.0;
	double elapse_dp = 0.0;
	double elapse_dp_EO = 0.0;
	std::random_device rd;
	std::mt19937_64 rgen(rd());
	cout << "test begin" << endl;
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(maxLen, maxValue, 1);
		int aim = dist(rgen)*maxValue + 1;
		//[18,3,12,29,7]
		/*vector<int> arr = { 18,3,12,29,7 };
		int aim = 23;*/
		st.start();
		int ans1 = sln.minCoins(arr, aim);
		st.stop();
		elapse_force += st.elapsed_ms();
		st.start();
		int ans2 = sln.dp1(arr, aim);
		st.stop();
		elapse_dp += st.elapsed_ms();
		st.start();
		int ans3 = sln.dp2(arr, aim);
		st.stop();
		elapse_dp_EO += st.elapsed_ms();
		if (ans1 != ans2 || ans2 != ans3)
		{
			print(arr);
			cout << "aim:" << aim << endl;
			cout  << ans1<<","<<ans2<<","<<ans3 << endl;
			break;
		}
	}
	cout << "test end" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force / testTime << "ms" << endl;
	cout << "dp:" << elapse_dp / testTime << "ms" << endl;
	cout << "dpEnumOptimization:" << elapse_dp_EO / testTime << "ms" << endl;
	cout << "test_Code02_MinCoinsNoLimit end" << endl;
	//	test begin
	//	test end
	//	average elapse(ms)
	//	force:1.2113ms
	//	dp : 0.0264ms
	//	dpEnumOptimization : 0.0212ms

}

#endif