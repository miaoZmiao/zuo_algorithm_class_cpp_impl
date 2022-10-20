#pragma once
#ifndef Code03_StoneMerge_HPP
#define Code03_StoneMerge_HPP
#include "utility_func.hpp"
#include <iostream>
#include <algorithm>
//摆放着n堆石子。现要将石子有次序地合并成一堆//规定每次只能选相邻的2堆石子合并成新的一堆，//并将新的一堆石子数记为该次合并的得分//求出将n堆石子合并成一堆的最小得分（或最大得分）合并方案

namespace Code03_StoneMerge {



	vector<int> constructSum(vector<int>& arr) {
	
		int N = arr.size();
		vector<int> ans(N+1, 0);
		for (int i = 1; i <= N; i++)
		{
			ans[i] = ans[i - 1] + arr[i - 1];
		}
		return ans;
	}

	int getsum(vector<int> & sum, int L, int R)
	{
		return  sum[R + 1] - sum[L];
	}

	int MyForce(vector<int> & sum, int L, int R)
	{
		if (L == R)
		{
			return 0;
		}
		int ans = INT_MAX;
		for (int s = L; s < R; s++)
		{
			int sumL = MyForce(sum, L, s);
			int sumR = MyForce(sum, s + 1, R);
			ans = std::min(ans, sumL + sumR);
		}
		return ans + getsum(sum, L, R);
	}
	int min1(vector<int>& arr) {
		if (arr.size() < 2) {
			return 0;
		}
		int N = arr.size();
		vector<int> sum = constructSum(arr);

		return MyForce(sum, 0, N-1);
	}

	// 
	int dp1(vector<int>& arr) {
		if (arr.size() < 2) {
			return 0;
		}
		int N = arr.size();
		vector<int> sum = constructSum(arr);

		vector<vector<int>> dp(N, vector<int>(N, 0));
		// dp[i][i] = 0;
		
		for (int L = N - 2; L >= 0; L--)
		{
			for (int R = L + 1; R <= N - 1; R++)
			{
				int ans = INT_MAX;
				for (int s = L; s < R; s++)
				{
					int sumL = dp[L][s];
					int sumR = dp[s + 1][R];
					ans = std::min(ans, sumL + sumR);
				}
				dp[L][R] = ans + getsum(sum, L, R);
			}
		}

		return dp[0][N - 1];
	}

	int dp2(vector<int>& arr)
	{
		if (arr.size() < 2) {
			return 0;
		}
		int N = arr.size();
		vector<int> sum = constructSum(arr);

		vector<vector<int>> dp(N, vector<int>(N, 0));
		vector<vector<int>> best(N, vector<int>(N, 0));
		for (int i = 0;i < N-1; i++)
		{
			best[i][i + 1] = i;
			dp[i][i + 1] = getsum(sum, i, i + 1);
		}

		for (int L = N - 3; L >= 0; L--)
		{
			for (int R = L + 2; R < N; R++)
			{
				int ans = INT_MAX;
				int best_index = best[L][R - 1];
				for (int i= best[L][R - 1]; i <= best[L + 1][R]; i++)
				{
					if (ans >= dp[L][i] + dp[i + 1][R])
					{
						ans = dp[L][i] + dp[i + 1][R];
						best_index = i;
					}
				}
				dp[L][R] = ans + getsum(sum, L, R);
				best[L][R] = best_index;
			}
		}
		return dp[0][N - 1];
	}


}

void test_Code03_StoneMerge() {
	
	int N = 15;
	int maxValue = 100;
	int minValue = 1;
	int testTime = 1000;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);

	cout<<"test_Code03_StoneMerge begin"<<endl;
	for (int i = 0; i < testTime; i++) {
		int len = (int)(dist(mt) * N)+1;
		vector<int> arr = generateRandomArray(len, maxValue, minValue);
		int ans1 = Code03_StoneMerge::min1(arr);
		int ans2 = Code03_StoneMerge::dp1(arr);
		int ans3 = Code03_StoneMerge::dp2(arr);
		if (ans1 != ans2 || ans1 != ans3) {
			print(arr);
			cout << ans1 << "," << ans2 <<","<<ans3 <<endl;
			break;
		}
	}
	cout << "test_Code03_StoneMerge end " << endl;
}

#endif