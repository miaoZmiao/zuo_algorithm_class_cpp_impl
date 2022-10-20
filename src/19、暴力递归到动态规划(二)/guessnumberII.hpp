#pragma once
#ifndef GUESS_NUMBER_II
#define GUESS_NUMBER_II

//375. 猜数字大小 II
//我们正在玩一个猜数游戏，游戏规则如下：
//
//我从 1 到 n 之间选择一个数字。
//你来猜我选了哪个数字。
//如果你猜到正确的数字，就会 赢得游戏 。
//如果你猜错了，那么我会告诉你，我选的数字比你的 更大或者更小 ，并且你需要继续猜数。
//每当你猜了数字 x 并且猜错了的时候，你需要支付金额为 x 的现金。如果你花光了钱，就会 输掉游戏 。
//给你一个特定的数字 n ，返回能够 确保你获胜 的最小现金数，不管我选择那个数字 。

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

namespace GUESS_NUMBER_II
{
	class Solution {
	public:
		int getMoneyAmount(int n) {
			return  process(1, n);
		}

		int minGold(int n)
		{
			return dpways(n);
		}

		//
		// 1,2,3,4,5,6
		//	 2	 4 5
		// 1,2,3,4,5,6,7,8
		//         5
		//        
		int process(int L, int R)
		{
			if (L >= R)
			{
				return 0;
			}
			if (L + 1 == R)
			{
				return L;
			}
			int p1 = L + process(L+1, R);
			int p2 = R + process(L, R - 1);
			int mincost = std::min(p1, p2);
			for (int i = L + 1; i < R; i++)
			{
				int c1 = process(L, i-1);
				int c2 = process(i + 1, R);
				int cur = i + std::max(c1, c2);
				mincost = std::min(mincost, cur);
			}
			return mincost;
		}

		int dpways(int N)
		{
			vector<vector<int>> dp(N+1, vector<int>(N+1, 0));
			for (int i = 0; i < N; i++)
			{
				dp[i][i + 1] = i;
			}

			for (int col = 2; col < N + 1; col++)
			{
				int L = 1;
				int R = col;
				while (L <= N && R <= N)
				{
					int p1 = L + dp[L + 1][R];
					int p2 = R + dp[L][R - 1];
					int mincost = std::min(p1, p2);
					for (int i = L + 1; i < R; i++)
					{
						int c1 = dp[L][i - 1];
						int c2 = dp[i + 1][R];
						int cur = i + std::max(c1, c2);
						mincost = std::min(mincost, cur);
					}
					dp[L][R] = mincost;
					L++;
					R++;
				}
			}
			return dp[1][N];
		}



	};

}

void test_guess_number_ii()
{
	int N = 10;
	GUESS_NUMBER_II::Solution sln;
	int input = 1;
	while (input <= N)
	{
		int ret = sln.getMoneyAmount(input);
		int ret_dp = sln.minGold(input);
		if (ret != ret_dp)
		{
			cout << "input:"<< input << endl;
			cout << "ret_dp:" << ret_dp << endl;
		}
		else
		{
			cout << "test_OK for input:" << input << endl;
		}
		input++;
	}
	
}


#endif

