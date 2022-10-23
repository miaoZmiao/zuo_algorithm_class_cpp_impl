#pragma once
#ifndef Code03_SplitNumber_HPP
#define Code03_SplitNumber_HPP
#include <iostream>
#include <vector>
#include "utility_func.hpp"
#include "stop_watch.hpp"
using namespace std;

namespace Code03_SplitNumber {

	class Solution {
	public:
		int ways(int n) {
			if (n < 0) {
				return 0;
			}
			if (n == 1) {
				return 1;
			}
			return process1(1, n);
		}
		int process1(int zuixiao, int guafen)
		{
			if (0 == guafen)
			{
				return 1;
			}
			if (zuixiao > guafen)
			{
				return 0;
			}
			int ways = 0;
			for (int i = zuixiao; i <= guafen; i++)
			{
				ways += process1(i, guafen - i);
			}
			return ways;
		}
		int dp1(int n)
		{
			if (n < 0) {
				return 0;
			}
			if (n == 1) {
				return 1;
			}
			int N = n;
			vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));
			for (int zuixiao = 1; zuixiao <= N; zuixiao++)
			{
				dp[zuixiao][0] = 1;
			}
			for (int zuixiao = N; zuixiao >= 1; zuixiao--)
			{
				for (int guafen = zuixiao; guafen <= N; guafen++)
				{
					int ways = 0;
					for (int i = zuixiao; i <= guafen; i++)
					{
						ways += dp[i][guafen - i];
					}
					dp[zuixiao][guafen] = ways;
				}
			}
			return dp[1][n];
		}

		int dp2(int n)
		{
			if (n < 0) {
				return 0;
			}
			if (n == 1) {
				return 1;
			}
			int N = n;
			vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));
			for (int zuixiao = 1; zuixiao <= N; zuixiao++)
			{
				dp[zuixiao][0] = 1;
				dp[zuixiao][zuixiao] = 1;
			}

			for (int zuixiao = N-1; zuixiao >= 1; zuixiao--)
			{
				for (int guafen = zuixiao+1; guafen <= N; guafen++)
				{
					// 
					dp[zuixiao][guafen] = dp[zuixiao + 1][guafen];
					dp[zuixiao][guafen] += dp[zuixiao][guafen - zuixiao];
					
				}
			}
			return dp[1][n];
		}
	};

}

void test_Code03_SplitNumber() {

	cout << "test_Code03_SplitNumber begin" << endl;
	Code03_SplitNumber::Solution sln;

	int testTime = 1;
	int loop_ = 1;
	int cur_test_begin = 100;
	stop_watch st;
	double elapse_force = 0.0;
	double elapse_dp = 0.0;
	double elapse_dp_EO = 0.0;
	cout << "¿ªÊ¼²âÊÔ" << endl;
	
	while (loop_ <= testTime)
	{
		st.start();
		int ans1 = sln.ways(cur_test_begin);
		st.stop();
		elapse_force += st.elapsed_ms();
		st.start();
		int ans2 = sln.dp1(cur_test_begin);
		st.stop();
		elapse_dp += st.elapsed_ms();
		st.start();
		int ans3 = sln.dp2(cur_test_begin);
		st.stop();
		elapse_dp_EO += st.elapsed_ms();
		if (ans1 != ans2 || ans2 != ans3)
		{
			cout << ans1 << "," << ans2 <<","<<ans3<<endl;
			break;
		}
		cur_test_begin++;
		loop_++;
	}
	cout << "²âÊÔ½áÊø" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force / testTime << "ms" << endl;
	cout << "dp:" << elapse_dp / testTime << "ms" << endl;
	cout << "dpEnumOptimization:" << elapse_dp_EO / testTime << "ms" << endl;
	cout << "test_Code03_SplitNumber end" << endl;
	//	¿ªÊ¼²âÊÔ
	//	²âÊÔ½áÊø
	//	average elapse(ms)
	//	force:3310.31ms
	//	dp : 1.509ms
	//	dpEnumOptimization : 0.181ms
}

#endif