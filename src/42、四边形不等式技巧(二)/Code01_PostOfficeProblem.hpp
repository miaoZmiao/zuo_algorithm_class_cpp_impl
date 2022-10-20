#pragma once
#ifndef Code01_PostOfficeProblem_HPP
#define Code01_PostOfficeProblem_HPP
#include "utility_func.hpp"
#include <algorithm>
namespace Code01_PostOfficeProblem {

	int min1(vector<int> & arr, int postnum) {
		if (arr.size() < 1 || postnum < 1 || arr.size() < postnum)
		{
			return 0;
		}
		int N = arr.size();
		vector<vector<int>> w(N + 1, vector<int>(N + 1, 0));
		for (int L = 0; L < N; L++)
		{
			for (int R = L + 1; R < N; R++)
			{
				w[L][R] = w[L][R - 1] + arr[R] - arr[((L + R) >> 1)];
			}
		}
		vector<vector<int>> dp(N, vector<int>(postnum + 1, 0));
		
		for (int i = 0; i < N; i++)
		{
			dp[i][1] = w[0][i];
		}

		for (int i = 1; i < N; i++)
		{
			for (int j = 2; j <= std::min(i,postnum); j++)
			{
				int ans = INT_MAX;
				for (int rest = i; rest >= 0; rest--)
				{
					int leftcost = dp[rest][j - 1];
					int rightcost = w[rest + 1][i];
					int costsum = leftcost + rightcost;
					ans = std::min(ans, costsum);
				}
				dp[i][j] = ans;
			}
		}
		return dp[N - 1][postnum];
	}

	int min2(vector<int> & arr, int postnum) {
		if (arr.size() < 1 || postnum < 1 || arr.size() < postnum)
		{
			return 0;
		}
		int N = arr.size();
		vector<vector<int>> w(N + 1, vector<int>(N + 1, 0));
		for (int L = 0; L < N; L++)
		{
			for (int R = L + 1; R < N; R++)
			{
				w[L][R] = w[L][R - 1] + arr[R] - arr[((L + R) >> 1)];
			}
		}
		vector<vector<int>> dp(N, vector<int>(postnum + 1, 0));
		vector<vector<int>> dpbest(N, vector<int>(postnum + 1, 0));
		for (int i = 0; i < N; i++)
		{
			dp[i][1] = w[0][i];
			dpbest[i][1] = -1;
		}

		for (int j = 2; j <= postnum; j++)
		{
			for (int i = N - 1; i >= j; i--)
			{
				int ans = INT_MAX;
				int bestchoose = -1;
				int up = i == N - 1 ? N - 1 : dpbest[i + 1][j];
				int down = dpbest[i][j - 1];
				for (int leftEnd = down; leftEnd <= up; leftEnd++)
				{
					int leftsum = leftEnd == -1 ? 0 : dp[leftEnd][j];
					int rightsum = i == N - 1 ? 0 : w[leftEnd + 1][i];
					int cur = leftsum + rightsum;
					if (ans > cur)
					{
						ans = cur;
						bestchoose = leftEnd;
					}
				}
				dp[i][j] = ans;
				dpbest[i][j] = bestchoose;
			}
		}

		return dp[N - 1][postnum];
	}


}

void test_Code01_PostOfficeProblem() {
	
	int N = 30;
	int maxValue = 100;
	int minValue = 1;
	int testTime = 10000;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);
	cout << "test_Code01_PostOfficeProblem begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		int len = int(dist(mt) * N) + 1;
		vector<int> arr = generateRandomNoRepeatArray(len, maxValue, minValue);
		std::sort(arr.begin(), arr.end());
		int num = int(dist(mt) * N) + 1;
		int ans1 = Code01_PostOfficeProblem::min1(arr, num);
		int ans2 = Code01_PostOfficeProblem::min2(arr, num);
		if (ans1 != ans2)
		{
			print(arr);
			cout << "num:" << num << endl;
			cout << ans1 << "," << ans2 << endl;
			break;
		}
	}
	cout << "test_Code01_PostOfficeProblem end" << endl;

}

#endif