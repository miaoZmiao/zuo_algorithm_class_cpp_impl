#pragma once
#ifndef Code01_BurstBalloons_HPP
#define Code01_BurstBalloons_HPP
#include "utility_func.hpp"
#include <iostream>
#include <algorithm>
namespace Code01_BurstBalloons {

	class Solution {

	public:
		int maxCoins0(vector<int>& arr) {
			int N = arr.size();
			vector<int> marr(N+2,0);
			marr[0] = 1;
			marr[N + 1] = 1;
			for (int i = 0; i < N; i++)
			{
				marr[i + 1] = arr[i];
			}
			return func(marr, 1, N);
		}

		int func(vector<int>& arr, int L, int R) {
			if (L == R)
			{
				return arr[L - 1] * arr[L] * arr[L + 1];
			}
			// left ballon
			int left = arr[L - 1] * arr[L] * arr[R + 1] + func(arr, L + 1, R);
			int right = arr[L - 1] * arr[R] * arr[R + 1] + func(arr, L, R - 1);
			int ans = std::max(left, right);
			
			for (int lastExplosion = L + 1; lastExplosion < R; lastExplosion++)
			{
				int tmp_ans = arr[L - 1] * arr[lastExplosion] * arr[R + 1] +
					func(arr, L, lastExplosion - 1) +
					func(arr, lastExplosion + 1, R);
				ans = std::max(ans, tmp_ans);
			}
			return ans;
		}

		int maxCoinsdp(vector<int>& arr) {
			int N = arr.size();
			vector<int> help(N + 2, 0);
			help[0] = 1;
			help[N + 1] = 1;
			for (int i = 0; i < N; i++)
			{
				help[i + 1] = arr[i];
			}

			vector<vector<int>> dp(N + 2, vector<int>(N + 2, 0));
			for (int i = 1; i <= N; i++)
			{
				dp[i][i] = help[i - 1]*help[i]*help[i + 1];
			}

			for (int L = N; L>=1; L--)
			{
				for (int R = L + 1; R <= N; R++)
				{
					int ans = help[L - 1] * help[L] * help[R + 1] + dp[L + 1][R];
					ans = std::max(ans, arr[L - 1] * arr[R] * arr[R + 1] + dp[L][R - 1]);
					for (int split = L + 1; split < R; split++)
					{
						int left = dp[L][split - 1];
						int right = dp[split + 1][R];
						int cur = help[L-1]* help[split] * help[R + 1];
						ans = std::max(ans, left + right + cur);
					}
					dp[L][R] = ans;
				}
				
			}
			return dp[1][N];
		}





	};

	
}

void test_Code01_BurstBalloons() {


}

#endif