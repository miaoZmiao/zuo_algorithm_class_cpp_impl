#pragma once
#ifndef Code01_SegmentTree_HPP
#define Code01_SegmentTree_HPP
#include <vector>
#include <iostream>
#include "utility_func.hpp"
using namespace std;
namespace Code01_SegmentTree {

	class Solution {
		int N;
		vector<int> m_origin;
		vector<int> m_sum;
		vector<int> m_lazy;
		vector<bool> m_update;
		vector<int> m_change;
	public:

		void segmentTree(vector<int> & arr)
		{
			m_origin = arr;
			N = arr.size() + 1;
			for (int i = 1; i < N; i++)
			{
				m_origin[i] = arr[i - 1];
			}
			m_sum.resize(N << 2, 0);
			m_lazy.resize(N << 2, 0);
			m_update.resize(N << 2, false);
			m_change.resize(N << 2, 0);
		}

		void build(int left, int right, int rt) {
			
			if (left == right)
			{
				m_sum[rt] = m_origin[left];
				return;
			}
			int mid = (left + right) >> 1;
			build(left, mid, rt << 1);
			build(mid + 1, right, (rt << 1) | 1);
			pushUp(rt);
		}

		void pushUp(int rt)
		{
			m_sum[rt] = m_sum[rt << 1] + m_sum[(rt << 1) | 1];
		}

		void pushDown(int rt, int left_n, int right_n)
		{
			if (m_update[rt])
			{
				m_sum[rt << 1] = m_change[rt] * left_n;
				m_sum[(rt << 1) | 1] = m_change[rt] * right_n;
				m_change[rt << 1] = m_change[rt];
				m_change[(rt << 1) | 1] = m_change[rt];
				m_lazy[rt << 1] = 0;
				m_lazy[(rt << 1) | 1] = 0;
				m_update[rt << 1] = true;
				m_update[(rt << 1) | 1] = true;
				m_update[rt] = false;
			}
			if (m_lazy[rt] != 0)
			{
				m_lazy[rt << 1] += m_lazy[rt];
				m_lazy[(rt << 1) | 1] += m_lazy[rt];
				m_sum[rt << 1] += left_n * m_lazy[rt];
				m_sum[(rt << 1) | 1] += right_n * m_lazy[rt];
				m_lazy[rt] = 0;
			}
		}


		void add(int L, int R, int C, int left, int right, int rt)
		{
			if (L <= left && right <= R)
			{
				m_lazy[rt] += C;
				m_sum[rt] += C * (right - left + 1);
				return;
			}
			// 
			int mid = (left + right) >> 1;
			pushDown(rt, mid - left + 1, right - mid);

			// L R
			if (L <= mid)
			{
				add(L, R, C, left, mid, rt << 1);
			}
			if (R > mid)
			{
				add(L, R, C, mid+1, right, (rt << 1) | 1);
			}
			pushUp(rt);
		}

		void update(int L, int R, int C, int left, int right, int rt)
		{
			if (L <= left && right <= R)
			{
				m_lazy[rt] = 0;
				m_sum[rt] = C * (right - left + 1);
				m_update[rt] = true;
				m_change[rt] = C;
				return;
			}
			int mid = (left + right) >> 1;
			pushDown(rt, mid - left + 1, right - mid);
			if (L <= mid)
			{
				update(L, R, C, left, mid, rt << 1);
			}
			if (R > mid)
			{
				update(L, R, C, mid + 1, right, (rt << 1) | 1);
			}
			pushUp(rt);
		}

		long query(int L, int R, int left, int right, int rt) {
			if (L <= left && right<=R)
			{
				return m_sum[rt];
			}
			int mid = (left + right) >> 1;
			pushDown(rt, mid - left + 1, right - mid);
			long ans = 0;
			if (L <= mid)
			{
				ans += query(L, R, left, mid, rt << 1);
			}
			if (R > mid)
			{
				ans += query(L, R, mid + 1, right, (rt << 1) | 1);
			}
			return ans;
		}
	};


	// ¶ÔÊýÆ÷
	class Right {
		
	public:
		vector<int> m_origin;
		Right(vector<int> & arr)
		{
			int N = arr.size()+1;
			m_origin.resize(N, 0);
			for (int i = 1; i <N; i++)
			{
				m_origin[i] = arr[i - 1];
			}
		}
		void add(int L, int R, int C)
		{
			for (int i = L; i <= R; i++)
			{
				m_origin[i] += C;
			}
		}

		void update(int L, int R, int C)
		{
			for (int i = L; i <= R; i++)
			{
				m_origin[i] = C;
			}
		}

		long query(int L, int R)
		{
			long ans = 0;
			for (int i = L; i <= R; i++)
			{
				ans += m_origin[i];
			}
			return ans;
		}
	};

}





void test_Code01_SegmentTree() {

	int len = 100;
	int max = 1000;
	int testTimes = 5000;
	int addOrUpdateTimes = 1000;
	int queryTimes = 500;
	Code01_SegmentTree::Solution sln;
	using Right = Code01_SegmentTree::Right;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);
	cout << "test Code01_SegmentTree begin" << endl;
	for (int i = 0; i < testTimes; i++)
	{
		vector<int> arr = generateRandomArray(len, max, 1);
		int S = 1;
		int N = arr.size();
		int root = 1;
		sln.segmentTree(arr);
		sln.build(S, N, root);
		Right duishuqi(arr);
		bool need_return = false;
		for (int j = 0; j < addOrUpdateTimes; j++) {
			int num1 = dist(mt)*N + 1;
			int num2 = dist(mt)*N + 1;
			int L = std::min(num1, num2);
			int R = std::max(num1, num2);
			int C = (int)(dist(mt) * max) - (int)(dist(mt) * max);
			if (dist(mt) < 0.5)
			{
				sln.add(L, R, C, S, N, root);
				duishuqi.add(L,R,C);
			}
			else
			{
				sln.update(L, R, C, S, N, root);
				duishuqi.update(L, R, C);
			}
		}

		for (int i = 0; i < queryTimes; i++)
		{
			int num1 = dist(mt)*N + 1;
			int num2 = dist(mt)*N + 1;
			int L = std::min(num1, num2);
			int R = std::max(num1, num2);
			long ans1 = sln.query(L, R, S, N, root);
			long ans2 = duishuqi.query(L, R);
			if (ans1 != ans2) {
				cout << "error" << endl;
				print(duishuqi.m_origin);
				cout << ans1 << "," << ans2 << endl;	
				cout << "L:" << L << "\tR:" << R << endl;
				need_return = true;
				break;
			}
			
		}
		if (need_return == true)
		{
			break;
		}
	}
	cout << "test Code01_SegmentTree end" << endl;


}


#endif