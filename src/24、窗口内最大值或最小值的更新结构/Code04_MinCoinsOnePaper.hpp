#pragma once
#ifndef Code04_MinCoinsOnePaper_HPP
#define Code04_MinCoinsOnePaper_HPP
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include "utility_func.hpp"
#include "stop_watch.hpp"

// 题目：
// arr是货币数组,其中值是正数，给定一个正数aim
// 每个值被认为是一张货币
// 返回组成aim的最少货币数量
// 
namespace Code04_MinCoinsOnePaper {
	class Solution
	{
	public:
		int minCoins(vector<int> & arr, int aim) {
			return process1(arr, 0, aim);
		}
		int process1(vector<int> & arr, int index, int aim)
		{
			if (aim < 0)
			{
				return INT_MAX;
			}
			if (index == arr.size())
			{
				return aim == 0 ? 0 : INT_MAX;
			}
			// 不适用index 面值
			int p1 = process1(arr, index + 1, aim );
			int p2 = INT_MAX;
			int next = process1(arr, index + 1, aim - arr[index]);
			if (next != INT_MAX)
			{
				p2 = next + 1;
			}
			return std::min(p1, p2);
		}

		int dp1(vector<int> & arr, int target) {
			int N = arr.size();
			
			vector<vector<int>> dp(N+1, vector<int>(target+1, 0));
			dp[N][0] = 0;
			for (int aim = 1; aim <= target; aim++)
			{
				dp[N][aim] = INT_MAX;
			}
			for (int index = N - 1; index >= 0; index--)
			{
				for (int aim = 0; aim <= target; aim++)
				{
					int p1 = dp[ index + 1][aim];
					int p2 = INT_MAX;
					int next = INT_MAX;
					if (aim - arr[index] >= 0)
					{
						next = dp[index + 1][aim - arr[index]];
					}
					if (next != INT_MAX)
					{
						p2 = next + 1;
					}
					dp[index][aim] = std::min(p1, p2);
				}
			}
			return dp[0][target];
		}

		struct Info
		{
			vector<int> coins;
			vector<int> zhangs;
		};

		Info getInfo(vector<int> & arr)
		{
			unordered_map<int, int> ump;
			for (auto a : arr)
			{
				ump[a]++;
			}
			Info ans;
			for (auto it : ump)
			{
				ans.coins.push_back(it.first);
				ans.zhangs.push_back(it.second);
			}
			return ans;
		}

		int dp2(vector<int> & arr, int target)
		{
			Info info = getInfo(arr);
			int N = info.coins.size();
			auto & coins = info.coins;
			auto & zhangs = info.zhangs;
			vector<vector<int>> dp(N+1, vector<int>(target +1, 0));
			dp[N][0] = 0;
			for (int i = 1; i <= target; i++)
			{
				dp[N][i] = INT_MAX;
			}
			for (int index = N - 1; index >= 0; index--)
			{
				int value = coins[index];
				for (int aim = 0; aim <= target; aim++)
				{
					dp[index][aim] = INT_MAX;
					for (int zhang = 0; zhang <= zhangs[index]; zhang++)
					{
						if (aim - zhang * value >= 0)
						{
							if (INT_MAX
								!= dp[index + 1]
								[aim - zhang * value])
							{
								dp[index][aim] = std::min(
									dp[index][aim],
									zhang + dp[index + 1][aim - zhang * value]
								);
							}

						}
						else
						{
							break;
						}
						
					}
				
				}
			}

			return dp[0][target];
		}

		int dp3(vector<int> & arr, int target)
		{
			Info info = getInfo(arr);
			int N = info.coins.size();
			auto & coins = info.coins;
			auto & zhangs = info.zhangs;
			vector<vector<int>> dp(N + 1, vector<int>(target + 1, 0));
			dp[N][0] = 0;
			for (int i = 1; i <= target; i++)
			{
				dp[N][i] = INT_MAX;
			}
			for (int index = N - 1; index >= 0; index--)
			{
				int value = coins[index];
				int zhang = zhangs[index];
				for (int mod = 0; mod < std::min(target+1, value); mod++)
				{
					std::deque<int> dq;
					for (int r = mod; r <= target; r += value)
					{
						while (!dq.empty() && (
							INT_MAX == dp[index + 1][dq.back()] ||
							dp[index + 1][dq.back()] >=
							dp[index + 1][r] -
							compensate(dq.back(), r, value)
							)
							) 
						{
							dq.pop_back();
						}
						dq.push_back(r);

						int overdue = r - (zhang + 1)*value;
						if (overdue == dq.front())
						{
							dq.pop_front();
						}

						dp[index][r] =
							dp[index + 1][dq.front()] == INT_MAX ? INT_MAX : compensate(dq.front(), r, value)+ dp[index + 1][dq.front()];
					}
				}
			}
			return dp[0][target];
		}

		int compensate(int pre , int cur, int value)
		{
			return (cur - pre) / value;
		}






	};
}

void test_Code04_MinCoinsOnePaper()
{
	cout << "test_Code04_MinCoinsOnePaper begin" << endl;
	int maxLen = 5;
	int maxValue = 10;
	int testTime = 10;
	std::random_device rd;
	std::mt19937 gen(rd());
	int aimexpect = maxLen * maxValue / 2;
	std::uniform_int_distribution<> dist(aimexpect - aimexpect /2, aimexpect + aimexpect /2);
	cout << "功能测试开始" << endl;
	Code04_MinCoinsOnePaper::Solution sln;
	for (int i = 0; i < testTime; i++)
	{
		int aim = dist(gen);
		vector<int> arr = generateRandomArray(maxLen, maxValue, 1);
		int ans1 = sln.minCoins(arr, aim);
		int ans2 = sln.dp1(arr, aim);
		int ans3 = sln.dp2(arr, aim);
		int ans4 = sln.dp3(arr,aim);
		if (ans1 != ans2 || ans2 != ans3 || ans3 != ans4)
		{
			print(arr);
			cout << "aim:" << aim << endl;
			cout << ans1 <<","<< ans2 << ","<<ans3 
				<<","<<ans4<<endl;
			break;
		}
	}
	cout << "功能测试结束" << endl;
	cout << "==========" << endl;
	cout << "性能测试开始" << endl;
	maxLen = 30000;
	maxValue = 20;
	int aim = 60000;
	stop_watch sw;
	vector<int> arr = generateRandomArray(maxLen, maxValue, 1);
	sw.start();
	int ans2 = sln.dp2(arr, aim);
	sw.stop();
	cout << "dp2答案:" << ans2 <<",耗时:"<<
		sw.elapsed_ms()<<"ms"<< endl;
	sw.start();
	int ans3 = sln.dp3(arr, aim);
	sw.stop();
	cout << "dp3答案:" << ans3 << ",耗时:" <<
		sw.elapsed_ms() << "ms" << endl;

	cout << "货币大量重复出现情况下，" << endl;
	cout << "大数据量测试dp3开始" << endl;
	maxLen = 20000000;
	aim = 10000;
	maxValue = 10000;
	arr = generateRandomArray(maxLen, maxValue, 1);
	sw.start();
	ans3 = sln.dp3(arr, aim);
	sw.stop();
	cout<<"dp3运行时间 : " << sw.elapsed_ms() <<" ms"<<endl;
	cout << "大数据量测试结束" << endl;
	cout << "===========" << endl;
	cout << "当货币很少出现重复，dp2比dp3有常数时间优势" << endl;
	cout << "当货币大量出现重复，dp3时间复杂度明显优于dp2" << endl;
	cout << "dp3的优化用到了窗口内最小值的更新结构" << endl;
	cout << "test_Code04_MinCoinsOnePaper end" << endl;
	/*	功能测试开始
		功能测试结束
		==========
		性能测试开始
		dp2答案 : 3082, 耗时 : 54913.8ms
		dp3答案 : 3082, 耗时 : 452.878ms
		货币大量重复出现情况下，
		大数据量测试dp3开始
		dp3运行时间 : 52176.1 ms
		大数据量测试结束
		========== =
		当货币很少出现重复，dp2比dp3有常数时间优势
		当货币大量出现重复，dp3时间复杂度明显优于dp2
		dp3的优化用到了窗口内最小值的更新结构*/


}
#endif