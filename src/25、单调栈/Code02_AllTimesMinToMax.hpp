#pragma once
#ifndef Code02_AllTimesMinToMax_HPP
#define Code02_AllTimesMinToMax_HPP
#include <vector>
#include <algorithm>
#include <deque>
#include <iostream>
#include "utility_func.hpp"
#include "stop_watch.hpp"
using namespace std;
// 题目二
// 给定一个只包含正数的数组arr，arr中任何一个子数组sub，
//一定都可以算出(sub累加和 )* (sub中的最小值)是什么，
// 那么所有子数组中，这个值最大是多少？

namespace Code02_AllTimesMinToMax {

	class Solution {
	public:
		// 暴力算法
		int max1(vector<int> & arr)
		{
			if (arr.size() == 0)
			{
				return 0;
			}
			if (arr.size() == 1)
			{
				return arr[0] * arr[0];
			}
			int N = arr.size();
			int ans = INT_MIN;
			for (int L = 0; L < N; L++)
			{
				int sum = arr[L];
				int Lstart_min = arr[L];
				ans = std::max(ans, sum*Lstart_min);
				for (int R = L+1; R < N; R++)
				{
					sum += arr[R];
					Lstart_min = std::min(Lstart_min, arr[R]);
					ans = std::max(ans, sum*Lstart_min);
				}
				
			}
			return ans;
		}
		//单调栈
		int max2(vector<int> & arr)
		{
			if (arr.size() == 0)
			{
				return 0;
			}
			if (arr.size() == 1)
			{
				return arr[0] * arr[0];
			}
			int N = arr.size();
			vector<int> presum(N, 0);
			presum[0] = arr[0];
			for (int i = 1; i < N; i++)
			{
				presum[i] = arr[i];
				presum[i] += presum[i-1];
			}
			deque<int> dq;
			int ans = INT_MIN;;
			for (int i = 0; i < N; i++)
			{
				while (!dq.empty() && 
					arr[dq.back()]>= arr[i])
				{
					// 以 some_pre_index
					// 做为最小元素的的
					int some_pre_index = dq.back();
					dq.pop_back();
					int leftsum = dq.empty() ? 0 : presum[dq.back()];
					int rightsum = presum[i - 1];
					ans = std::max(ans, 
						(rightsum - leftsum)*arr[some_pre_index]
					);
				}
				dq.push_back(i);
			}
			
			while (!dq.empty())
			{
				int some_pre_index = dq.back();
				dq.pop_back();
				int leftsum = dq.empty() ? 0 : presum[dq.back()];
				int rightsum = presum[N - 1];
				ans = std::max(ans,
					(rightsum - leftsum)*arr[some_pre_index]
				);
			}
			return ans;
		}
	};


}
void test_Code02_AllTimesMinToMax() {

	Code02_AllTimesMinToMax::Solution sln;
	int testTimes = 20;
	cout << "test begin" << endl;
	int maxlen = 10000;
	int maxValue = 10000;
	stop_watch sw;
	double elapse_force = 0.0;
	double elapse_monostack = 0.0;
	for (int i = 0; i < testTimes; i++) {
		vector<int> arr = generateRandomArray(maxlen, maxValue, 1);
		sw.start();
		int ans1 = sln.max1(arr);
		sw.stop();
		elapse_force += sw.elapsed_ms();
		sw.start();
		int ans2 = sln.max2(arr);
		sw.stop();
		elapse_monostack += sw.elapsed_ms();
		if(ans1 != ans2)
		{
			print(arr);
			cout << ans1 << "," << ans2 << endl;
			break;
		}
	}
	cout <<"test finish" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force / testTimes << endl;
	cout << "monostack:" << elapse_monostack / testTimes << endl;
	/*	test begin
		test finish
		average elapse(ms)
		force:525.514
		monostack : 3.1351*/

}
#endif