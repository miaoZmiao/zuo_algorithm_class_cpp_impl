#pragma once
#ifndef Code02_ThrowChessPiecesProblem_HPP
#define Code02_ThrowChessPiecesProblem_HPP

#include "utility_func.hpp"


namespace Code02_ThrowChessPiecesProblem {

	int process1(int rest, int k)
	{
		if (rest == 0)
		{
			return 0;
		}
		if (k == 1)
		{
			return rest;
		}
		int ans = INT_MAX;
		for (int i = 1; i <= rest; i++)
		{
			int suile = process1(i - 1, k - 1);
			int meisui = process1(rest - i, k);
			ans = std::min(ans, std::max(suile, meisui));
		}
		return ans + 1;
	}

	int superEggDrop1(int kChess, int nLevel) {
		if (nLevel < 1 || kChess < 1) {
			return 0;
		}
		return process1(nLevel, kChess);
	}

	// dp
	int superEggDrop2(int kChess, int nLevel)
	{
		if (nLevel < 1 || kChess < 1) {
			return 0;
		}
		vector<vector<int>> dp(nLevel + 1, vector<int>(kChess + 1, 0));

		for (int i = 1; i <= nLevel; i++)
		{
			dp[i][1] = i;
		}
		for (int rest = 1; rest <= nLevel; rest++)
		{
			for (int k = 2; k <= kChess; k++)
			{
				int ans = INT_MAX;
				for (int i = 1; i <= rest; i++)
				{
					int suile = dp[i - 1][k - 1];
					int meisui = dp[rest - i][k];
					ans = std::min(ans, std::max(suile, meisui));
				}
				dp[rest][k] = ans + 1;
			}
		}
		return dp[nLevel][kChess];
	}

	int superEggDrop3(int kChess, int nLevel) {
		if (nLevel < 1 || kChess < 1) {
			return 0;
		}
		vector<vector<int>> dp(nLevel + 1, vector<int>(kChess + 1, 0));
		vector<vector<int>> dpbest(nLevel + 1, vector<int>(kChess + 1, 0));
		for (int i = 1; i <= nLevel; i++)
		{
			dp[i][1] = i;
		}
		for (int i = 1; i <= kChess; i++)
		{
			dp[1][i] = 1;
			dpbest[1][i] = 1;
		}

		for (int level = 2; level <= nLevel; level++)
		{
			for (int k = kChess; k > 1; k--)
			{
				int ans = INT_MAX;
				int bestchoose = -1;
				int up = k==kChess?level: dpbest[level][k + 1];
				int down = dpbest[level - 1][k];
				for (int LeftEnd = down; LeftEnd <= up; LeftEnd++)
				{
					int suile = dp[LeftEnd - 1][k - 1];
					int meisui = dp[level - LeftEnd][k];
					int cur = std::max(suile, meisui);
					if (cur <= ans)
					{
						ans = cur;
						bestchoose = LeftEnd;
					}
				}
				dp[level][k] = ans + 1;
				dpbest[level][k] = bestchoose;
			}
		}
		return dp[nLevel][kChess];
	}

	// 
	int superEggDrop4(int kChess, int nLevel) {
		
		if (nLevel < 1 || kChess < 1) {
			return 0;
		}
		vector<int> dp(kChess, 0);
		int throw_time = 0;
		//throw_time++;// throw_time = 1;
		//for (int i = 0; i < kChess; i++)
		//{
		//	dp[i] = 1;
		//}
		
		while (true)
		{
			throw_time++;
			int prev = 0;
			for (int i = 0; i < kChess; i++)
			{
				int tmp = dp[i];
				dp[i] = dp[i] + prev + 1;
				prev = tmp;
				if (dp[i] >= nLevel)
				{
					return throw_time;
				}
			}
		
		}
		return throw_time;
	}
}

void test_Code02_ThrowChessPiecesProblem() {
	int maxN = 100;
	int maxK = 50;
	int testTime = 1000;	
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);

	cout << "test_Code02_ThrowChessPiecesProblem begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		double m1 = dist(mt);
		double m2 = dist(mt);
		int N = (int(maxN * m1)) + 1;
		int K = (int(maxK*m2)) + 1;
		//int ans1 = Code02_ThrowChessPiecesProblem::superEggDrop1(K, N);
		int ans2 = Code02_ThrowChessPiecesProblem::superEggDrop2(K, N);
		int ans3 = Code02_ThrowChessPiecesProblem::superEggDrop3(K, N);
		int ans4 = Code02_ThrowChessPiecesProblem::superEggDrop4(K, N);
		if (/*ans1 != ans2 ||*/ ans2 != ans3 || ans3 != ans4)
		{
			cout << "K:" << K << ",N:" << N << endl;
			cout /*<< ans1<<","*/<<ans2<<","<<ans3<<","<<ans4 << endl;
			break;
		}
	}
	cout << "test_Code02_ThrowChessPiecesProblem end" << endl;
}



#endif