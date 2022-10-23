#pragma once
#ifndef Code01_MinPathSum_HPP
#define Code01_MinPathSum_HPP
#include <vector>
#include <iostream>
#include <algorithm>
#include "utility_func.hpp"
#include "stop_watch.hpp"
using namespace std;
//Code1
//给定一个二维数组matrix，一个人必须从左上角出发，最后到达右下角
//沿途只可以向下或者向右走，沿途的数字都累加就是距离累加和
//返回最小距离累加和

namespace Code01_MinPathSum {

	// 可以做状态压缩
	class Solution
	{
	public:
		int minPathSum1(vector<vector<int>> & matrix)
		{
			int N = matrix.size();
			if (N == 0)
			{
				return 0;
			}
			int M = matrix[0].size();
			if (M == 0)
			{
				return 0;
			}

			return process1(matrix, N, M, 0, 0);
		}

		int process1(vector<vector<int>> & matrix, int N, int M,
			int x, int y)
		{
			if ((x == N-1 )&& (y == M-1))
			{
				return matrix[x][y];
			}
			if (x == N || y == M)
			{
				return INT_MAX;
			}

			int min_path = process1(matrix, N, M, x, y + 1);
		
			min_path = std::min(min_path, process1(matrix, N, M, x + 1, y)); ;

			return matrix[x][y] + min_path;
		}

		//  dp版本
		int minPathSum2(vector<vector<int>> & matrix)
		{
			int N = matrix.size();
			if (N == 0)
			{
				return 0;
			}
			int M = matrix[0].size();
			if (M == 0)
			{
				return 0;
			}
			vector<vector<int>> dp(N, vector<int>(M, 0));
			dp[N - 1][M - 1] = matrix[N - 1][M - 1];
			for (int x = N - 2; x >= 0; x--)
			{
				dp[x][N - 1] = dp[x + 1][N - 1] + matrix[x][N - 1];
			}

			for (int y = M - 2; y >= 0; y--)
			{
				dp[N-1][y] = dp[N - 1][y+1] + matrix[N - 1][y];
			}
			for (int x = N - 2; x >= 0; x--)
			{
				for (int y = M - 2; y >= 0; y--)
				{
					int min_path = dp[x][y + 1];

					min_path = std::min(min_path, dp[x + 1][y]); ;

					dp[x][y] = matrix[x][y] + min_path;
				}
			}
			return dp[0][0];
		}

		//  dp版本 空间优化
		int minPathSum3(vector<vector<int>> & matrix)
		{
			int N = matrix.size();
			if (N == 0)
			{
				return 0;
			}
			int M = matrix[0].size();
			if (M == 0)
			{
				return 0;
			}
			vector<int> dp(M, 0);
			dp[M - 1] = matrix[N - 1][M - 1];
			for (int y = M - 2; y >= 0; y--)
			{
				dp[y] = dp[y + 1] + matrix[N - 1][y];
			}

			for (int x = N - 2; x >= 0; x--)
			{
				dp[M - 1] = dp[M - 1] + matrix[x][M - 1];
				for (int y = M - 2; y >= 0; y--)
				{
					int min_path = dp[y + 1];
					min_path = std::min(min_path, dp[y]); ;
					dp[y] = matrix[x][y] + min_path;
				}
			}
			return dp[0];
		}
	};

}

void test_Code01_MinPathSum()
{
	cout << "test_Code01_MinPathSum begin" << endl;
	int M = 10;
	int N = 10;
	int maxvalue = 10;
	int minvalue = 1;
	int test_loop = 10;
	Code01_MinPathSum::Solution sln;
	cout << "测试开始" << endl;
	stop_watch st;
	double elapse_force = 0;
	double elapse_dp = 0;
	for(int i = 0; i < test_loop;i++)
	{
		auto matrix = generate_M_N_matrix(M, N, minvalue, maxvalue);
		st.start();
		int ans1 = sln.minPathSum1(matrix);
		st.stop();
		elapse_force += st.elapsed_ms();
		st.start();
		int ans2 = sln.minPathSum2(matrix);
		st.stop();
		elapse_dp += st.elapsed_ms();
		if (ans1 != ans2)
		{
			cout << ans1 << "," << ans2 << endl;
			printMatrix(matrix);
			break;
		}
	}
	cout << "测试结束" << endl;
	cout << "average elapse (ms)" << endl;
	cout << "force:" << elapse_force/ test_loop << endl;
	cout << "dp:" << elapse_dp / test_loop << endl;
	cout << "test_Code01_MinPathSum end" << endl;

	//	测试开始
	//	测试结束
	//	average elapse(ms)
	//	force:2.4475
	//	dp : 0.0066
}



#endif