#pragma once
#ifndef Code03_LargestRectangleInHistogram_HPP
#define Code03_LargestRectangleInHistogram_HPP
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
// 测试链接：
//https:
//leetcode.com/problems/largest-rectangle-in-histogram
// 题目三
// 给定一个非负数组arr，代表直方图
// 返回直方图的最大长方形面积

namespace Code03_LargestRectangleInHistogram {

	class Solution {
	public:
		int largestRectangleArea(vector<int>& heights) {
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

void test_Code03_LargestRectangleInHistogram() {

	//
	cout << "test_Code03_LargestRectangleInHistogram begin" << endl;

	Code03_LargestRectangleInHistogram::Solution sln;
	cout << "test_Code03_LargestRectangleInHistogram end" << endl;

}

#endif