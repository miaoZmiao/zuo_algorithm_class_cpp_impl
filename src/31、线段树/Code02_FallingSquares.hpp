#pragma once
#ifndef Code02_FallingSquares_HPP
#define Code02_FallingSquares_HPP
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "utility_func.hpp"
using namespace std;
// 线段树实例二
// 想象一下标准的俄罗斯方块游戏，X轴是积木最终下落到底的轴线
// 下面是这个游戏的简化版：
// 1）只会下落正方形积木
// 2）[a,b] -> 代表一个边长为b的正方形积木，积木左边缘沿着X = a这条线从上方掉落
// 3）认为整个X轴都可能接住积木，也就是说简化版游戏是没有整体的左右边界的
// 4）没有整体的左右边界，所以简化版游戏不会消除积木，因为不会有哪一层被填满。

// 给定一个N*2的二维数组matrix，可以代表N个积木依次掉落，
// 返回每一次掉落之后的最大高度
// 
// https://leetcode.com/problems/falling-squares/
namespace Code02_FallingSquares {

	class SegmentTree {

		vector<int> m_origin;
		
		vector<int> m_change;
		vector<bool> m_update;
		vector<int> m_max;
		//vector<int> m_sum;


	public:
		SegmentTree(int N) {
			reset(N);
		}

		void reset(int N) {
			int len = N + 1;
			m_max.resize(len << 2, 0);
			m_origin.resize(len << 2, 0);
			m_change.resize(len << 2, 0);
			m_update.resize(len << 2, false);
		}
		// 不需要build
		void pushUp(int rt) {
			m_max[rt] = std::max(m_max[rt << 1], m_max[rt << 1 | 1]);
		}

		void pushDown(int rt, int left_n, int right_n)
		{
			if (m_update[rt] == true)
			{
				m_change[rt << 1] = m_change[rt];
				m_change[rt << 1 | 1] = m_change[rt];
				m_update[rt << 1] = true;
				m_update[rt << 1 | 1] = true;
				m_max[rt << 1] = m_change[rt];
				m_max[rt << 1 | 1] = m_change[rt];			m_update[rt] = false;
			}
		}

		void update(int L, int R, int C, int left, int right, int rt)
		{
			if (L <= left && right <= R)
			{
				m_update[rt] = true;
				m_change[rt] = C;
				m_max[rt] = C;
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
				update(L, R, C, mid + 1, right, rt << 1 | 1);
			}
			pushUp(rt);
		}


		long query(int L, int R, int left, int right, int rt) {
			if (L <= left && right <= R)
			{
				return m_max[rt];
			}
			int mid = (left + right) >> 1;
			pushDown(rt, mid - left + 1, right - mid);
			int query1 = -1;
			int query2 = -1;
			if (L <= mid)
			{
				query1 = query(L, R, left, mid, rt << 1);
			}
			if (R > mid)
			{
				query2 = query(L, R, mid + 1, right, rt << 1 | 1);
			}
			return std::max(query1,query2);
		}
	};


	class Solution {
	public:
		map<int, int> index(vector<vector<int>> & positions) {
			std::set<int> idx;
			for (auto &square : positions)
			{
				idx.insert(square[0]);
				idx.insert(square[0] + square[1] - 1);
			}
			map<int, int> mp;
			int count = 0;
			for (auto & i : idx)
			{
				mp[i] = ++count;
			}
			return mp;
		}

		vector<int> fallingSquares(
			vector<vector<int>> & positions)
		{
			auto mp = index(positions);
			int height = 0;
			int N = mp.size();
			SegmentTree st(N);
			vector<int> ans(positions.size(), 0);
			for (int i = 0;i<positions.size();i++)
			{
				vector<int> & square = positions[i];
				int L = mp[square[0]];
				int R = mp[square[0] + square[1] - 1];
				int queryheight = st.query(L, R, 1, N, 1)
					+ square[1];
				height = std::max(queryheight, height);
				ans[i] = height;
				st.update(L, R, queryheight, 1, N, 1);
			}

			return ans;
		}


	};

}

void test_Code02_FallingSquares() {
	vector<vector<int>> positions{ {6,4 },{2,7 },{6,9} };
	Code02_FallingSquares::Solution sln;
	vector<int> ans = sln.fallingSquares(positions);

	print(ans);

};
	


#endif