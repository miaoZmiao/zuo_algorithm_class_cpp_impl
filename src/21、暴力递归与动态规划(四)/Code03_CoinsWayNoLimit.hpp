#pragma once
#ifndef Code03_CoinsWayNoLimit_HPP
#define Code03_CoinsWayNoLimit_HPP
#include <vector>
#include <iostream>
#include "utility_func.hpp"
#include "stop_watch.hpp"
//题目三
//arr是面值数组，其中的值都是正数且没有重复。再给定一个正数aim。
//每个值都认为是一种面值，且认为张数是无限的。
//返回组成aim的方法数
//例如：arr = { 1,2 }，aim = 4
//方法如下：1 + 1 + 1 + 1、1 + 1 + 2、2 + 2
//一共就3种方法，所以返回3
namespace Code03_CoinsWayNoLimit
{	
	class Solution
	{
	public:
		int coinWays(vector<int> & arr, int aim) {
			return process1(arr, 0, aim);
		}
		// 暴力递归版本的process
		int process1(vector<int> & arr, int index, int aim)
		{
			if (index == arr.size())
			{
				return aim == 0 ? 1 : 0;
			}
			// 在 index 
			// 用0张 arr[index]
			// 用1张 arr[index]
			// 用2张 arr[index]
			// 用3张 arr[index]
			// 用4张 arr[index]
			// .....
			int ways = 0;
			for (int zhang = 0; arr[index] * zhang <= aim; zhang++)
			{
				ways += process1(arr, index+1, 
					aim- arr[index] * zhang);
			}
			return ways;
		}

		
		int coinWaysDP(vector<int> & arr, int target) {
			int N = arr.size();
			//int aim = target;
			vector<vector<int>> dp(N+1, vector<int>(target+1, 0));
			dp[N][0] = 1;
		
			for (int index = N - 1; index >= 0; index--)
			{
				for (int aim = 0; aim <= target; aim++)
				{
					int ways = 0;
					for (int zhang = 0; arr[index] * zhang <= aim; zhang++)
					{
						ways += dp[index + 1][aim - arr[index] * zhang];
					}
					dp[index][aim] = ways;
				}
			}
			return dp[0][target];

		}

		// 枚举优化
		int coinWaysDPEnum(vector<int> & arr, int target) {
			int N = arr.size();
			//int aim = target;
			vector<vector<int>> dp(N + 1, vector<int>(target+1, 0));
			dp[N][0] = 1;

			for (int index = N - 1; index >= 0; index--)
			{
				for (int aim = 0; aim <= target; aim++)
				{
					int ways = 0;
					if ((aim - arr[index]) >= 0)
					{
						ways += dp[index][aim - arr[index]];
					}
					ways += dp[index + 1][aim];
					dp[index][aim] = ways;
				}
			}
			return dp[0][target];

		}



	};
}

void test_Code03_CoinsWayNoLimit()
{
	int maxvalue = 10;
	int minvalue = 1;
	int test_loop = 10;
	int N = 15;
	int aim = 22;
	Code03_CoinsWayNoLimit::Solution sln;
	cout << "测试开始" << endl;
	stop_watch st;
	double elapse_force = 0;
	double elapse_dp = 0.0;
	double elapse_dp_enum = 0.0;
	for (int i = 0; i < test_loop; i++)
	{
		vector<int> arr = generateRandomArray(N, maxvalue, minvalue);
		st.start();
		int ans1 = sln.coinWays(arr, aim);
		st.stop();
		elapse_force += st.elapsed_ms();
		st.start();
		int ans2 = sln.coinWaysDP(arr, aim);
		st.stop();
		elapse_dp += st.elapsed_ms();
		st.start();
		int ans3 = sln.coinWaysDPEnum(arr, aim);
		st.stop();
		elapse_dp_enum += st.elapsed_ms();
		if (ans1 != ans2 || ans2 != ans3)
		{
			print(arr);
			cout << ans1 << "," << ans2<<","<<ans3 <<endl;
			break;
		}

	}
	cout << "测试结束" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force / test_loop << endl;
	cout << "dp:" << elapse_dp / test_loop << endl;
	cout << "dpEnumOptimization:" << elapse_dp_enum/ test_loop << endl;

	/*	测试开始
		测试结束
		average elapse(ms)
		force:5.5128
		dp : 0.0322
		dpEnumOptimization : 0.0136*/

}




#endif