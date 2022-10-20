#pragma once
#ifndef Code01_RobotWalk_HPP
#define Code01_RobotWalk_HPP
#include <vector>
#include <iostream>
using namespace std;

namespace Code01_RobotWalk {
	int process1(int N, int start, int aim, int K);
	int way1(int N, int start, int aim, int K)
	{
		if (N<2||start < 1 || start >N || aim <1 || aim > N || K < 1)
		{
			return -1;
		}
		return process1(N, start, aim, K);
	}

	int process1(int N, int start, int aim, int K)
	{
		if (K == 0)
		{
			return aim == start ? 1 : 0;
		}
		if (start == 1)
		{
			return  process1(N, 2, aim, K-1);
		}
		if (start == N)
		{
			return  process1(N, N-1, aim, K - 1);
		}
		int p1 = process1(N, start-1, aim, K-1);
		int p2 = process1(N, start+1, aim, K - 1);
		return p1 + p2;
	}
	int process2(int N, int start, int aim, int K, 
		vector<vector<int>> & dp);
	// 用傻缓存的方法
	int way2(int N, int start, int aim, int K)
	{
		if (N < 2 || start < 1 || start > N || aim < 1 || aim > N || K < 1) {
			return -1;
		}
		vector<vector <int> > dp(N+1, vector<int>(K+1));
		for (int i = 0; i < N + 1; i++)
		{
			for (int j = 0; j < K + 1; j++)
			{
				dp[i][j] = -1;
			}
		}
		return process2(N, start, aim, K, dp);
	}

	int process2(int N, int start, int aim, int K,
		vector<vector<int>> & dp) {
		if (K == 0)
		{
			if (dp[start][K] = -1)
			{
				dp[start][K] = (aim == start ? 1 : 0);
			}
		}
		// K != 0
		if (dp[start][K] != -1)
		{
			return dp[start][K];
		}
		int ans = 0;
		if (start == 1)
		{
			ans = process2(N, 2, aim, K - 1, dp);
		}
		else if (start == N)
		{
			ans = process2(N, N-1, aim, K - 1, dp);
		}
		else
		{
			ans = process2(N, start -1, aim, K - 1, dp) + 
				process2(N, start + 1, aim, K - 1, dp);
		}
		dp[start][K] = ans;
		return ans;
	}


	int way3(int N, int start, int aim, int K)
	{
		if (N < 2 || start < 1 || start >N 
			|| aim <1 || aim > N || K < 1)
		{
			return -1;
		}

		vector<vector <int> > dp(N + 1, vector<int>(K + 1, 0));
		dp[aim][0] = 1;
		for (int rest = 1; rest < K + 1; rest++)
		{
			for (int loc = 1; loc < N + 1; loc++)
			{
				if (loc == 1)
				{
					dp[loc][rest] = dp[2][rest-1];
				}
				else if (loc == N)
				{
					dp[loc][rest] = dp[N - 1][rest - 1];
				}
				else
				{
					dp[loc][rest] = dp[loc - 1][rest - 1] +
						dp[loc + 1][rest - 1];
				}
			}
		}
		return dp[start][K];
	}



}

void test_Code01_RobotWalk()
{
	cout << "test test_Code01_RobotWalk" << endl;
	vector<int> input = { 5, 2, 4, 6 };
	
	cout << "way1:" << Code01_RobotWalk::way1(5, 2, 4, 6) << endl;
	cout << "way2:" << Code01_RobotWalk::way2(5, 2, 4, 6) << endl;
	cout << "way3:" << Code01_RobotWalk::way3(5, 2, 4, 6) << endl;
}





#endif