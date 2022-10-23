#pragma once
#ifndef Code05_BobDie_HPP
#define Code05_BobDie_HPP
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

//题目五
//给定5个参数，N，M，row，col，k
//表示在N*M的区域上，醉汉Bob初始在(row, col)位置
//Bob一共要迈出k步，且每步都会等概率向上下左右四个方向走一个单位
//任何时候Bob只要离开N*M的区域，就直接死亡
//返回k步之后，Bob还在N*M的区域的概率


namespace Code05_BobDie {

	class Solution
	{
	public:
		double livePosibility1(int row, int col, int k, int N, int M) {
			return (double)process1(row, col, k, N, M) / pow(4, k);
		}
		int process1(int row, int col, int k, int N, int M) {
			if (row < 0 || row == N || col < 0 || col == M)
			{
				return 0;
			}
			if (k == 0)
			{
				return 1;
			}
			int ways = 0;
			ways += process1(row - 1, col, k - 1, N, M);
			ways += process1(row, col + 1, k - 1, N, M);
			ways += process1(row + 1, col, k - 1, N, M);
			ways += process1(row, col - 1, k - 1, N, M);
			return ways;
		}

		// 动态规划方法
		double livePosibility2(int row, int col, int k, int N, int M) {
			return (double)dpways(row, col, k, N, M) / pow(4, k);
		}
		// 可以使用空间优化技巧
		int dpways(int row, int col, int k, int N, int M)
		{
			// 相当于 k = 0 的时候 row col 的变化可能
			vector<vector<int>> dpmatrix(N+1, vector<int>(M+1, 0));
			vector<vector<int>> nextdpmatrix(N+1, vector<int>(M+1, 0));
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					dpmatrix[i][j] = 1;
				}
			}
			
			for (int step = 1; step <= k; step++)
			{
				for (int i = 0; i < N ; i++)
				{
					for (int j = 0; j < M; j++)
					{
						int ways = 0;
						if (i - 1 >= 0)
						{
							ways += dpmatrix[i - 1][j];
						}
						if (j + 1 < M)
						{
							ways += dpmatrix[i][j+1];
						}
						if (i + 1 < N)
						{
							ways += dpmatrix[i + 1][j];
						}
						if (j - 1 >= 0)
						{
							ways += dpmatrix[i][j-1];
						}
						nextdpmatrix[i][j] = ways;
					}
				}
				dpmatrix.swap(nextdpmatrix);
			}
			return dpmatrix[row][col];
		}



	};


}

void test_Code05_BobDie() {
	
	cout << "test_Code05_BobDie begin" << endl;

	Code05_BobDie::Solution sln;
	cout << "测试开始" << endl;
	double elapse_force = 0.0;
	double elapse_dp = 0.0;
	stop_watch st;
	st.start();
	double p1 = sln.livePosibility1(6, 6, 10, 50, 50);
	st.stop();
	elapse_force = st.elapsed_ms();
	st.start();
	double p2 = sln.livePosibility2(6, 6, 10, 50, 50);
	st.stop();
	elapse_dp = st.elapsed_ms();
	cout << "测试结束" << endl;
	cout << "p1:" << p1 << " p2:" << p2 << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:"<< elapse_force << "ms" << endl;
	cout << "dp:" << elapse_dp << "ms" << endl;
	cout << "test_Code05_BobDie end" << endl;
//	某次测试显示
//	p1:0.997021 p2 : 0.997021
//	average elapse(ms)
//	force : 3.622ms
//	dp : 1.06ms

}

#endif