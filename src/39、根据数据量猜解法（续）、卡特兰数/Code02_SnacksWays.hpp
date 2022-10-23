#pragma once
#ifndef Code02_SnacksWays_HPP
#define Code02_SnacksWays_HPP
#include <vector>
#include "utility_func.hpp"
using namespace std;
namespace Code02_SnacksWays {

	// 吃零食问题，背包问题
	// 从左往右的经典模型
	// 还剩的容量是rest，arr[index...]自由选择，
	// 返回选择方案
	// index ： 0～N
	// rest : 0~w
	int process1(vector<int> & arr, int index, int rest);
	int ways1(vector<int> & arr, int w) 
	{
		return process1(arr, 0, w);
	}
	int process1(vector<int> & arr, int index, int rest)
	{
		if (rest < 0)
		{
			return 0;
		}
		if (index == arr.size())
		{
			return 1;
		}

		int next1 = process1(arr, index + 1, rest);
		int next2 = process1(arr, index + 1, rest - arr[index]);
		return next1 + next2;
	}

	int dp1(vector<int> & arr, int w) {
		
		int N = arr.size();
		vector<vector<int>> dp(N + 1, vector<int>(w + 1, 0));
		for (int i = 0; i <= w; i++)
		{
			dp[N][i] = 1;
		}
		for (int index = N - 1; index >= 0; index--)
		{
			for (int rest = 0; rest <= w; rest++)
			{
				dp[index][rest] = dp[index + 1][rest];
				if (rest - arr[index] >= 0)
				{
					dp[index][rest] += dp[index + 1][rest - arr[index]];
				}
			}
		}
		return dp[0][w];
	}

	int dp2(vector<int> & arr, int w)
	{
		int N = arr.size();
		vector<vector<int>> dp(N, vector<int>(w + 1, 0));
		for (int i = 0; i < N; i++)
		{
			dp[i][0] = 1;
		}
		dp[0][arr[0]] = 1;
		for (int index = 1; index < N; index++)
		{
			for (int ww = 1; ww <= w; ww++)
			{
				dp[index][ww] = dp[index - 1][ww];
				if (ww - arr[index] >= 0)
				{
					dp[index][ww] += dp[index - 1][ww - arr[index]];
				}
			}
		}
		int ans = 0;
		for (int ww = 0; ww <= w; ww++)
		{
			ans += dp[N - 1][ww];
		}
		return ans;
	}



}


void test_Code02_SnacksWays() {

	cout << "test_Code02_SnacksWays begin" << endl;
	vector<int> arr = { 4, 3, 2, 9 };
	int w = 8;
	cout << Code02_SnacksWays::ways1(arr, w) << endl;
	cout << Code02_SnacksWays::dp1(arr, w) << endl;
	cout << Code02_SnacksWays::dp2(arr, w) << endl;
	cout << "test_Code02_SnacksWays end" << endl;
}

#endif