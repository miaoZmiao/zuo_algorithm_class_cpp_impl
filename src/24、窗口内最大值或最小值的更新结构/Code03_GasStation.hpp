#pragma once
#ifndef Code03_GasStation_HPP
#define Code03_GasStation_HPP
#include <vector>
#include <deque>
#include "stop_watch.hpp"
#include "utility_func.hpp"
using namespace std;
// 测试链接 https://leetcode.com/problems/gas-station
// 在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

//你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i + 1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。
//
//给定两个整数数组 gas 和 cost ，如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 - 1 。如果存在解，则 保证 它是 唯一 的。
//
namespace Code03_GasStation {
	class Solution {
	public:
		int canCompleteCircuit(vector<int>& gas, 
			vector<int>& cost) 
		{
			int N1 = gas.size();
			int N2 = cost.size();
			if (N1 != N2)
			{
				return -1;
			}
			vector<bool> ans = goodArray(gas, cost);
			for (int i = 0; i < N1; i++)
			{
				if (ans[i] == true)
				{
					return i;
				}
			}
			return -1;
		}

		vector<bool> goodArray(vector<int>& g, 
			vector<int>& c)
		{
			int N = g.size();
			int M = N << 1;
			vector<int> arr(M, 0);
			for (int i = 0; i < N; i++)
			{
				arr[i] = g[i] - c[i];
				arr[i + N] = g[i] - c[i];
			}
			for (int i = 1; i < M; i++)
			{
				arr[i] += arr[i - 1];
			}
			deque<int> dq;
			for (int i = 0; i < N; i++)
			{
				while (!dq.empty() && 
					arr[dq.back()] >= arr[i])
				{
					dq.pop_back();
				}
				dq.push_back(i);
			}
			vector<bool> ans(N, false);
			int pre = 0;
			for (int i = 0, j = N; j < M; i++, j++)
			{
				if (arr[dq.front()] - pre >= 0)
				{
					ans[i] = true;
				}
				while (!dq.empty() && 
					arr[dq.back()] >= arr[j])
				{
					dq.pop_back();
				}
				dq.push_back(j);
				if (dq.front() == i)
				{
					dq.pop_front();
				}
				pre = arr[i];
			}
			return ans;
		}
	};
	
}

void test_Code03_GasStation(){
	Code03_GasStation::Solution sln;
	cout << "test_Code03_GasStation begin" << endl;
	vector<int> gas{ 1,2,3,4,5 };
	vector<int> cost{ 3,4,5,1,2 };
	stop_watch st;
	st.start();
	int ans = sln.canCompleteCircuit(gas, cost);
	st.stop();
	cout << "ans:" << ans << endl;
	cout << "elapse:" << st.elapsed_ms() << endl;
	cout << "test_Code03_GasStation end" << endl;
}


#endif