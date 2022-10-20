#pragma once
#ifndef Code01_PalindromeSubsequence_HPP
#define  Code01_PalindromeSubsequence_HPP
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
namespace Code01_PalindromeSubsequence {
	class Solution {
	public:
		int longestPalindromeSubseq(string s) {
			if (s.size() <= 1)
			{
				return s.size();
			}
			//return process1(s,0,s.size()-1);
			return dpways(s);
		}

		int process1(const string & s, int L ,int R) {
			if (L > R)
			{
				return 0;
			}
			if (L == R)
			{
				return 1;
			}
			if (L + 1 == R)
			{
				return s[L] == s[R] ? 2 : 1;
			}
			int longest = INT_MIN;
			longest = std::max(longest, process1(s, L + 1, R)) ;
			longest = std::max(longest, process1(s, L, R - 1)) ;
			if (s[L] == s[R])
			{
				longest = std::max(longest, process1(s, L+1, R - 1) +2);
			}
			return longest;
		}

		int dpways(string s)
		{
			int N = s.size();
			vector<vector<int>> dp(N, vector<int>(N, 0));
			for (int i = 0; i < N-1; i++)
			{
				dp[i][i] = 1;
				dp[i][i + 1] = (s[i] == s[i + 1] ? 2 : 1);
			}
			dp[N - 1][N - 1] = 1;

			for (int L = N - 3; L >= 0; L--)
			{
				for (int R = L+2; R <= N - 1; R++)
				{
					int longest = INT_MIN;
					longest = std::max(longest, dp[L + 1][ R]);
					longest = std::max(longest, dp[L][R - 1]);
					if (s[L] == s[R])
					{
						longest = std::max(longest, dp[L + 1][R - 1]		 + 2);
					}
					dp[L][R] = longest;
				}
			}
			return dp[0][N - 1];
		}
	};
}

// ²âÊÔÁ´½Ó£º
// https://leetcode.com/problems/longest-palindromic-subsequence/

void test_Code01_PalindromeSubsequence(){

	string input = "abcdef";
	Code01_PalindromeSubsequence::Solution sln;
	int ret = sln.longestPalindromeSubseq(input);

	cout << "longestPalindromeSubseq:"<< ret << endl;

}
#endif