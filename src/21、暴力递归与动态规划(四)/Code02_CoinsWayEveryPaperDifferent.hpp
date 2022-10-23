#pragma once
#ifndef Code02_CoinsWayEveryPaperDifferent_HPP
#define Code02_CoinsWayEveryPaperDifferent_HPP
#include <vector>
#include <iostream>
#include "utility_func.hpp"
#include "stop_watch.hpp"
using namespace std;
//	题目二
//	arr是货币数组，其中的值都是正数。再给定一个正数aim。
//	每个值都认为是一张货币，
//	即便是值相同的货币也认为每一张都是不同的，
//	返回组成aim的方法数
//	例如：arr = { 1,1,1 }，aim = 2
//	第0个和第1个能组成2，第1个和第2个能组成2，第0个和第2个能组成2
//	一共就3种方法，所以返回3

namespace Code02_CoinsWayEveryPaperDifferent {

	class Solution
	{
	public:
		int coinWays(vector<int> & arr, int aim) {
			return process1(arr, 0, aim);
		}

		int process1(vector<int> & arr, int index, int aim) {
			if (aim == 0)
			{
				return 1;
			}
			// aim != 0
			if (index == arr.size() && aim != 0)
			{
				return 0;
			}
			int ways = 0;
			// 要 index 的 值
			if (aim - arr[index] >= 0)
			{
				ways += process1(arr, index + 1, aim - arr[index]);
			}
			// 不要index 的值
			ways += process1(arr, index + 1, aim);
			return ways;
		}

		int coinWaysdp(vector<int> & arr, int aim) {
			int N = arr.size();
			vector<vector<int>> dp(N+1, vector<int>(aim+1, 0));
			for (int index = 0; index <= N; index++)
			{
				dp[index][0] = 1;
			}
			for (int index = N - 1; index >= 0; index--)
			{
				for (int a = 0; a <= aim; a++)
				{
					int ways = 0;
					// 要 index 的 值
					if (a - arr[index] >= 0)
					{
						ways += dp[index + 1][a - arr[index]];
					}
					// 不要index 的值
					ways += dp[index + 1][a];
					dp[index][a] = ways;
				}
			}



			return dp[0][aim];
		}


	};
}

void test_Code02_CoinsWayEveryPaperDifferent()
{
	cout << "test_Code02_CoinsWayEveryPaperDifferent begin" << endl;
	int maxvalue = 10;
	int minvalue = 1;
	int test_loop = 10;
	int N = 15;
	int aim = 22;
	Code02_CoinsWayEveryPaperDifferent::Solution sln;
	cout << "测试开始" << endl;
	stop_watch st;
	double elapse_force = 0;
	double elapse_dp = 0.0;
	for (int i = 0; i < test_loop; i++)
	{
		vector<int> arr = generateRandomArray(N, maxvalue, minvalue);
		st.start();
		int ans1 = sln.coinWays(arr, aim);
		st.stop();
		elapse_force += st.elapsed_ms();
		st.start();
		int ans2 = sln.coinWaysdp(arr,aim);
		st.stop();
		elapse_dp += st.elapsed_ms();
		if (ans1 != ans2)
		{
			print(arr);
			cout << "ans1:" << ans1 << /*"," <<*/ endl;
		}

	}
	cout << "测试结束" << endl;
	cout<<"average elapse(ms)"<<endl;
	cout << "force:" << elapse_force / test_loop << endl;
	cout << "dp:" << elapse_dp / test_loop << endl;
	cout << "test_Code02_CoinsWayEveryPaperDifferent end" << endl;
	//	测试开始
	//	测试结束
	//	average elapse(ms)
	//	force:0.0795
	//	dp : 0.0149

}


#endif