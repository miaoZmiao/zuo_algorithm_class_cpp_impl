#pragma once
#ifndef Code01_IndexTree_HPP
#define Code01_IndexTree_HPP
#include <iostream>
#include <vector>
#include "utility_func.hpp"
using namespace std;
namespace Code01_IndexTree {

	class Solution {
	public:
		vector<long> m_tree;
		int m_size;
		void reset(int size)
		{
			m_size = size + 1;
			m_tree.resize(m_size, 0);
		}

		long sum(int index)
		{
			long ans = 0;
			while (index !=0)
			{
				ans += m_tree[index];
				index -= index & (-index);
			}
			return ans;
		}

		void add(int index, int C) {

			while (index <= m_size)
			{
				m_tree[index] += C;
				index += index & (-index);
			}
		}
	};

	class Right {
	public:
		vector<long> m_arr;
		int m_size;
		void reset(int N)
		{
			m_size = N + 1;
			m_arr.resize(m_size, 0);
		}
		long sum(int index)
		{
			long ans = 0;
			for (int i = 1; i <= index; i++)
			{
				ans += m_arr[i];
			}
			return ans;
		}

		void add(int index, int C)
		{
			m_arr[index] += C;
		}
	};
}
void test_Code01_IndexTree() {
	Code01_IndexTree::Solution sln;
	Code01_IndexTree::Right duishuqi;
	int N = 100;
	int V = 100;
	int testTime = 2000000;
	sln.reset(N);
	duishuqi.reset(N);
	std::random_device  rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> r_dist(0.0, 1.0);
	cout << "test Code01_IndexTree begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		int index = r_dist(mt)*N + 1;
		if (r_dist(mt) < 0.5)
		{
			int C = r_dist(mt)*V;
			sln.add(index, C);
			duishuqi.add(index, C);
		}
		else
		{
			long ans1 = sln.sum(index);
			long ans2 = duishuqi.sum(index);
			if (ans1 != ans2)
			{
				cout << index << endl;
				cout << ans1 << "," << ans2 << endl;
				break;
			}
		}
	}
	cout << "test Code01_IndexTree end" << endl;
}

#endif