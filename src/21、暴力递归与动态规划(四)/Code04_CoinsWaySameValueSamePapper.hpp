#pragma once
#ifndef Code04_CoinsWaySameValueSamePapper_HPP
#define Code04_CoinsWaySameValueSamePapper_HPP
#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace  std;;
//	题目四
//	arr是货币数组，其中的值都是正数。再给定一个正数aim。
//	每个值都认为是一张货币，
//	认为值相同的货币没有任何不同，
//	返回组成aim的方法数
//	例如：arr = { 1,2,1,1,2,1,2 }，aim = 4
//	方法：1 + 1 + 1 + 1、1 + 1 + 2、2 + 2
//	一共就3种方法，所以返回3

namespace Code04_CoinsWaySameValueSamePapper {

	class Solution
	{
	public:
		 // 需要预处理
		int coinWays(vector<int> & arr, int aim) {
			// 预处理
			std::map<int, int> mp;
			for (auto & i : arr)
			{
				if (mp.find(i) != mp.end())
				{
					mp[i]++;
				}
				else
				{
					mp[i] = 1;
				}
			}
			vector<int> coins;
			vector<int> zhangs;
			for (auto& m : mp)
			{
				coins.push_back(m.first);
				zhangs.push_back(m.second);
			}
			return process1(coins, zhangs, 0, aim);
		}
		int process1(vector<int> & coins, vector<int> & zhangs,
			int index, int aim) 
		{
			if (index == coins.size())
			{
				return aim == 0 ? 1 : 0;
			}
			int ways = 0;
			int value = coins[index];
			for (int zhang = 0; zhang <=zhangs[index]; zhang++)
			{
				if (aim - zhang * value < 0)
				{
					break;
				}
				ways += process1(coins, zhangs, 
					index+1, aim- zhang * value);
			}
			return ways;
		}

		// 需要预处理
		int coinWaysDP(vector<int> & arr, int aim) {
			// 预处理
			std::map<int, int> mp;
			for (auto & i : arr)
			{
				if (mp.find(i) != mp.end())
				{
					mp[i]++;
				}
				else
				{
					mp[i] = 1;
				}
			}
			vector<int> coins;
			vector<int> zhangs;
			for (auto& m : mp)
			{
				coins.push_back(m.first);
				zhangs.push_back(m.second);
			}
			return dpways(coins, zhangs, aim);
		}
		// 动态规划
		// 无优化
		int dpways(vector<int> & coins, vector<int> & zhangs, int target)
		{
			int N = coins.size();
			
			vector<vector<int>> dp(N + 1, vector<int>(target + 1, 0));
			dp[N][0] = 1;

			for (int index = N - 1; index >= 0; index--)
			{
				for (int aim = 0; aim <= target;aim++)
				{
					int ways = 0;
					int value = coins[index];
					for (int zhang = 0; zhang <= zhangs[index]; zhang++)
					{
						if (aim - zhang * value < 0)
						{
							break;
						}
						ways += dp[index + 1][aim - zhang * value];
					}
					dp[index][aim] = ways;
				}
			}
			return dp[0][target];
		}

		// 动态规划，枚举行为可以被优化掉
		// dpwaysEO = dpwaysEnumOptimization
		int dpwaysEO(vector<int> & coins, vector<int> & zhangs,
			int target) 
		{
			int N = coins.size();
			vector<vector<int>> dp(N + 1, vector<int>(target + 1, 0));
			dp[N][0] = 1;

			for (int index = N - 1; index >= 0; index--)
			{
				for (int aim = 0; aim <= target; aim++)
				{
					int value = coins[index];
					dp[index][aim] = dp[index + 1][aim];
					int zhang = zhangs[index];
					if (aim - value >= 0)
					{
						dp[index][aim] += dp[index][aim - value];
						if (aim - (zhang + 1)*value >= 0)
						{
							dp[index][aim] -= dp[index + 1][aim - (zhang + 1)*value];
						}
					}
					
				}
			}
			return dp[0][target];
		}

		// 需要预处理
		int coinWaysDPEnum(vector<int> & arr, int aim) {
			// 预处理
			std::map<int, int> mp;
			for (auto & i : arr)
			{
				if (mp.find(i) != mp.end())
				{
					mp[i]++;
				}
				else
				{
					mp[i] = 1;
				}
			}
			vector<int> coins;
			vector<int> zhangs;
			for (auto& m : mp)
			{
				coins.push_back(m.first);
				zhangs.push_back(m.second);
			}
			return dpwaysEO(coins, zhangs, aim);
		}
	};
}

void test_Code04_CoinsWaySameValueSamePapper() {

	int maxvalue = 10;
	int minvalue = 1;
	int test_loop = 10;
	int N = 20;
	int aim = 22;
	cout << "测试开始" << endl;
	stop_watch st;
	double elapse_force = 0;
	double elapse_dp = 0.0;
	double elapse_dp_enum = 0.0;
	Code04_CoinsWaySameValueSamePapper::Solution sln;
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
			cout << ans1 << "," << ans2 << "," << ans3 << endl;
			break;
		}
	}
	cout << "测试结束" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force / test_loop << endl;
	cout << "dp:" << elapse_dp / test_loop << endl;
	cout << "dpEnumOptimization:" << elapse_dp_enum / test_loop << endl;


	//	测试开始
	//	测试结束
	//	average elapse(ms)
	//	force:0.0831
	//	dp : 0.0241
	//	dpEnumOptimization : 0.0217


}

#endif