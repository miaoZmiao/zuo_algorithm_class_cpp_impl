#pragma once
#ifndef Code01_KillMonster_HPP
#define Code01_KillMonster_HPP
#include <math.h>
#include "utility_func.hpp"
#include "stop_watch.hpp"
#include <iostream>
#include <iomanip>

//	题目一

//	给定3个参数，N，M，K
//	怪兽有N滴血，等着英雄来砍自己
//	英雄每一次打击，都会让怪兽流失[0~M]的血量
//	到底流失多少？每一次在[0~M]上等概率的获得一个值
//	求K次打击之后，英雄把怪兽砍死的概率


namespace Code01_KillMonster {

	class Solution
	{
	public:
		double right(int N, int M, int K) {
			if (N < 1 || M < 1 || K < 1) {
				return 0;
			}
			unsigned long all = (long)pow(M + 1, K);
			unsigned long kill = process1(M, K, N);
			return (double)((double)kill / (double)all);
		}

		//			 
		unsigned long process1(int M, int restK, int restHP)
		{
			if (restK == 0)
			{
				return restHP <= 0 ? 1 : 0;
			}
			if (restHP <= 0)
			{
				return pow(M+1, restK);
			}
			unsigned long ways = 0;
			for (int i = 0; i <= M; i++)
			{
				ways += process1(M, restK - 1, restHP - i);
			}
			return ways;
		}

		double dp1(int N, int M, int K) {
			if (N < 1 || M < 1 || K < 1) {
				return 0;
			}
			unsigned long all = (long)pow(M + 1, K);
			vector<vector<unsigned long>> dp(K+1, vector<unsigned long>(N+1, 0));
			dp[0][0] = 1;
			for (int row = 1; row <= K; row++)
			{
				dp[row][0] = pow(M + 1, row);
			}
			// row 从上到下
			for (int restK = 1; restK <= K; restK++)
			{
				// col从左到右
				for (int restHP = 1; restHP <= N; restHP++)
				{
					unsigned long ways = 0;
					for (int i = 0; i <= M; i++)
					{
						if (restHP - i >= 0)
						{
							ways += dp[restK - 1][restHP - i];
						}
						else // restHP - i < 0
						{
							ways += dp[restK - 1][0];
						}
					}
					dp[restK][restHP] = ways;
				}
			}
			return (double)((double)dp[K][N]/(double)all);
		}

		// 动态规划，枚举优化
		double dp2(int N, int M, int K)
		{
			if (N < 1 || M < 1 || K < 1) {
				return 0;
			}
			unsigned long all = (long)pow(M + 1, K);
			vector<vector<unsigned long>> dp(K + 1, vector<unsigned long>(N + 1, 0));
			dp[0][0] = 1;
			for (int row = 1; row <= K; row++)
			{
				dp[row][0] = pow(M + 1, row);
			}
			// row 从上到下
			for (int restK = 1; restK <= K; restK++)
			{
				// col从左到右
				for (int restHP = 1; restHP <= N; restHP++)
				{
					//unsigned long ways = 0;
					dp[restK][restHP] = dp[restK - 1][restHP];
					if (restHP > M)
					{
						dp[restK][restHP] += dp[restK][restHP - 1];
						dp[restK][restHP] -= dp[restK-1][restHP - 1- M];
					}
					else if (restHP <= M)
					{
						dp[restK][restHP] += dp[restK][restHP - 1];
						dp[restK][restHP] -= dp[restK - 1][0];
					}
				}
			}
			return (double)((double)dp[K][N] / (double)all);
		}

	};

}

void test_Code01_KillMonster()
{
	int NMax = 10;
	int MMax = 10;
	int KMax = 10;
	int testTime = 200;
	Code01_KillMonster::Solution sln;
	std::random_device rd;
	std::mt19937_64 rgen(rd());
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	stop_watch st;
	double elapse_force = 0.0;
	double elapse_dp = 0.0;
	double elapse_dp_EO = 0.0;
	cout << "test begin" << endl;
	std::cout << std::setprecision(6) << endl;
	for (int i = 0; i < testTime; i++)
	{
		int N = (int)(dist(rgen) * NMax) + 1;
		int M = (int)(dist(rgen) * MMax) + 1;
		int K = (int)(dist(rgen) * KMax) + 1;
		st.start();
		double ans1 = sln.right(N, M, K);
		st.stop();
		elapse_force += st.elapsed_ms();
		st.start();
		double ans2 = sln.dp1(N, M, K);
		st.stop();
		elapse_dp += st.elapsed_ms();
		st.start();
		double ans3 = sln.dp2(N, M, K);
		st.stop();
		elapse_dp_EO += st.elapsed_ms();
		//cout << ans1 << "," << ans2<< endl;
		if (ans1 != ans2 || ans2 != ans3)
		{
			cout << ans1 << "," << ans2 <<","<<ans3<< endl;
			cout << "N:" << N << " M:" << M << " K:" << K << endl;
			break;
		}
		/* // 出现负数的概率是因为计 int 类型的内部计算过程溢出了
		// 改成 unsigned long 类型做为计数，消除了负概率
		if (ans1 < 0.0 || ans1 > 1.0)
		{
			cout << "N:" << N << " M:" << M << " K:" << K << endl;
		}*/
	}
	cout << "test end" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force/ testTime << "ms" << endl;
	cout << "dp:" << elapse_dp/ testTime << "ms" << endl;
	cout << "dpEnumOptimization:" << elapse_dp_EO / testTime << "ms" << endl;

	//	average elapse(ms)
	//	force:0.176545ms
	//	dp : 0.003655ms
	//	dpEnumOptimization : 0.003045ms

}


#endif