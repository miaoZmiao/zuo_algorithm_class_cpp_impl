#pragma once
#ifndef Code02_SplitSumClosedSizeHalf_HPP
#define Code02_SplitSumClosedSizeHalf_HPP
#include <iostream>
#include "utility_func.hpp"
#include "stop_watch.hpp"
using namespace std;

namespace Code02_SplitSumClosedSizeHalf {

	class Solution {
	public:
		int right(vector<int> & arr) {
			if (arr.size() < 2)
			{
				return 0;
			}
			int sum = 0;
			for (auto & e : arr)
			{
				sum += e;
			}
			int N = arr.size();
			if ((N & 1 )== 0)
			{
				return process1(arr, 0, N / 2, sum / 2);
			}
			else
			{
				return std::min(process1(arr, 0, N / 2, sum / 2),
					process1(arr, 0, N / 2 + 1, sum / 2)
				);
			}
		}

		int process1(vector<int> & arr, int index, int picks,int sum)
		{
			if (index == arr.size())
			{
				return picks == 0 ? 0 : -1;
			}
			// ²»pick µ±Ç°
			int p1 = process1(arr, index + 1, picks, sum);
			int p2 = -1;
			int next = -1;
			if (sum - arr[index] >= 0)
			{
				next = process1(arr, index + 1, picks - 1, sum - arr[index]);
			}
			if (next != -1)
			{
				p2 = next + arr[index];
			}
			return std::max(p1, p2);
		}

		int dp1(vector<int> & arr) {
			if (arr.size() < 2)
			{
				return 0;
			}
			int sum = 0;
			for (auto & e : arr)
			{
				sum += e;
			}
			int N = arr.size();
			int picks = (N + 1 )/ 2;
			int halfsum = sum / 2;
			vector<vector<vector<int>>> dp(
			N+1,vector<vector<int>>(picks+1, vector<int>(halfsum+1, -1))
			);
			for (int i = 0;i<=halfsum;i++)
			{
				dp[N][0][i] = 0;
			}

			for (int index = N - 1; index >= 0; index--)
			{
				for (int pick = 0; pick <= picks; pick++)
				{
					for (int s = 0; s <= halfsum; s++)
					{
						int p1 = dp[index + 1][pick][s];
						int p2 = -1;
						int next = -1;
						if (s - arr[index] >= 0 && pick-1>=0)
						{
							next = dp[index + 1][pick - 1][s - arr[index]];
						}
						if (next != -1)
						{
							p2 = next + arr[index];
						}
						dp[index][pick][s] = std::max(p1, p2);
					}
				}
			}
			if ((N & 1) == 0)
			{
				return dp[0][ N / 2] [sum / 2];
			}
			else
			{
				return std::min(dp[0] [N / 2] [sum / 2],
					dp[0][ N / 2 + 1][sum / 2]
				);
			}
		}


	};

}

void test_Code02_SplitSumClosedSizeHalf() {

	Code02_SplitSumClosedSizeHalf::Solution sln;
	stop_watch st;
	double elapse_force = 0.0;
	double elapse_dp = 0.0;
	double elapse_dp_EO = 0.0;
	int maxLen = 20;
	int maxValue = 50;
	int testTime = 10;
	cout << "test begin" << endl;
	for (int i = 0; i < testTime; i++) {
		vector<int> arr = generateRandomArray(maxLen, maxValue, 1);
		st.start();
		int ans1 = sln.right(arr);
		st.stop();
		elapse_force += st.elapsed_ms();
		st.start();
		int ans2 = sln.dp1(arr);
		st.stop();
		elapse_dp += st.elapsed_ms();
		//int ans3 = sln.dp2(arr);
		if (ans1 != ans2 /*|| ans1 != ans3*/) {
			print(arr);
			cout << ans1 << "," << ans2 << endl;
			break;
		}
	}
	cout << "test end" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force / testTime << "ms" << endl;
	cout << "dp:" << elapse_dp / testTime << "ms" << endl;
	//	test begin
	//	test end
	//	average elapse(ms)
	//	force:18.0823ms
	//	dp : 2.7757ms
}



#endif