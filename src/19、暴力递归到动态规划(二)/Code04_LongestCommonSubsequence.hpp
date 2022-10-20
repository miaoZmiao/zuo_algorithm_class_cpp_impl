#pragma once
#ifndef Code04_LongestCommonSubsequence_HPP
#define Code04_LongestCommonSubsequence_HPP
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
namespace Code04_LongestCommonSubsequence
{
	class Solution
	{
	public:
		int longestCommonSubsequence(string text1, string text2) 
		{
			if (text2.size() == 0 || text1.size() == 0)
			{
				return 0;
			}
			//int ret = process1(text1, text2, 0, 0);
			int dp = dpways(text1, text2);
			return dp == INT_MAX ? 0: dp;
		}

		int process1(string s1, string s2, int s1index, int s2index)
		{
			if(s1index == s1.size() || s2.size() == s2index)
			{
				return 0;
			}
			int longest = INT_MIN;

			// 

			if (s1[s1index] == s2[s2index])
			{
				int p1 = process1(s1, s2, s1index+1,s2index+1) + 1;
				longest = std::max(longest, p1);
			}
			// s1[s1index,......] 和 s2[s2index+1 ..... ]比
			longest = std::max(longest, process1(s1, s2, s1index, s2index + 1));
			// s1[s1index+1, ......] 和 s2[s2index ..... ]比
			longest = std::max(longest, process1(s1, s2, s1index+1, s2index));

			return longest;
		}

		int dpways(string s1, string s2)
		{
			int N = s1.size();
			int M = s2.size();
			vector<vector<int>> dp(N+1, vector<int>(M+1, 0));
			
			for (int i = N - 1; i >= 0; i--)
			{
				for (int j = M - 1; j >= 0; j--)
				{
					int longest = INT_MIN;
					if (s1[i] == s2[j])
					{
						int p1 = dp[i + 1][j + 1] + 1;
						longest = std::max(longest, p1);
					}
					longest = std::max(longest, dp[i][j+1]);

					longest = std::max(longest, dp[i + 1][j]);
					dp[i][j] = longest;
				}
			}
			return dp[0][0];
		}
	};
	
	
}

// 这个问题leetcode上可以直接测
// 链接：https://leetcode.com/problems/longest-common-subsequence/

void test_Code04_LongestCommonSubsequence()
{
	Code04_LongestCommonSubsequence::Solution sln;
	string text1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	string text2 =
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";


	int ret = sln.longestCommonSubsequence(text1, text2);

	cout << "longestCommonSubsequence:" << ret << endl;

}

#endif