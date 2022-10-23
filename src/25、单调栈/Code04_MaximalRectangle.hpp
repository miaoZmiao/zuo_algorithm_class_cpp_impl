#pragma once
#ifndef Code04_MaximalRectangle_HPP
#define Code04_MaximalRectangle_HPP
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;
// 给定一个二维数组matrix，其中的值不是0就是1，
// 返回全部由1组成的最大子矩形，内部有多少个1

// 测试链接：https://leetcode.com/problems/maximal-rectangle/
namespace Code04_MaximalRectangle
{
	class Solution {
	public:
		int maximalRectangle(vector<vector<char>>& matrix) {
			if (matrix.size() == 0)
			{
				return 0;
			}
			if (matrix[0].size() == 0)
			{
				return 0;
			}
			int N = matrix[0].size();
			int ROW = matrix.size();
			vector<int> heights(N, 0);
			int ans = 0;
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < N; j++)
				{
					heights[j] = (matrix[i][j] == '1' ?
						heights[j] + 1:
						0
						);
				}
				ans = std::max(ans, largestRectangleArea(heights));
			}
			return ans;
		}

		int largestRectangleArea(vector<int>& heights)
		{
			if (heights.size() == 0)
			{
				return 0;
			}
			if (heights.size() == 1)
			{
				return heights[0];
			}
			int N = heights.size();
			stack<int> st;
			int ans = 0;
			for (int i = 0; i < N; i++)
			{
				while (!st.empty() &&
					heights[st.top()] >= heights[i])
				{
					int heightindex = st.top();
					st.pop();
					int leftindex =
						st.empty() ? -1 : st.top();
					int area = (i - leftindex - 1)*heights[heightindex];
					ans = std::max(ans, area);
				}
				st.push(i);

			}
			while (!st.empty())
			{
				int heightindex = st.top();
				st.pop();
				int leftindex = st.empty() ? -1 : st.top();
				int righindex = N - 1;
				int area = (righindex - leftindex)*heights[heightindex];
				ans = std::max(area, ans);
			}
			return ans;
		
		}
	};
}

void test_Code04_MaximalRectangle() {
	cout << "test_Code04_MaximalRectangle begin" << endl;

	Code04_MaximalRectangle::Solution sln;
	cout << "test_Code04_MaximalRectangle end" << endl;
}


#endif