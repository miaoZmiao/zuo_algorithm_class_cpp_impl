#pragma once
#ifndef Code01_StrangePrinter_HPP
#define Code01_StrangePrinter_HPP
#include <string>
#include "utility_func.hpp"
// ±æÃ‚≤‚ ‘¡¥Ω” : https://leetcode.com/problems/strange-printer/
#include <algorithm>
namespace  Code01_StrangePrinter{

	class Solution {
	public:
		int strangePrinter(string s) {
			if (s.size() == 0)
			{
				return 0;
			}
			int N = s.size();

			return process1(s, 0, N - 1);
		}

		int process1(const string & str, int L, int R)
		{
			if (L == R)
			{
				return 1;
			}
			int ans = R - L + 1;

			for (int split = L + 1; split <= R; split++)
			{
				int l = process1(str, L, split - 1);
				int r = process1(str, split, R);
				int tmpans = l + r - (str[L] == str[split] ? 1 : 0);
				ans = std::min(ans, tmpans);
			}
			return ans;
		}

		int dpway(const string & str) 
		{
			if (str.size() == 0)
			{
				return 0;
			}
			int N = str.size();
			
			vector<vector<int>> dp(N, vector<int>(N, 0));
			for (int i = 0; i < N; i++)
			{
				dp[i][i] = 1;
			}	
			for (int L = N - 2; L >= 0; L--)
			{
				for (int R = L + 1; R < N; R++)
				{
					int ans = R - L + 1;
					for (int split = L + 1; split <= R; split++)
					{
						int l = dp[L][split - 1];
						int r = dp[split][ R];
						int tmpans = l + r - (str[L] == str[split] ? 1 : 0);
						ans = std::min(ans, tmpans);
					}
					dp[L][R] = ans;
				}
			}
			return dp[0][N - 1];
		}


	};

}

void test_Code01_StrangePrinter() {


}


#endif