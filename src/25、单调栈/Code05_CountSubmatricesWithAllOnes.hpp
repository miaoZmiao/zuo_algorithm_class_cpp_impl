#pragma once
#ifndef Code05_CountSubmatricesWithAllOnes_HPP
#define Code05_CountSubmatricesWithAllOnes_HPP
#include <vector>
#include <stack>
#include <iostream>
using namespace std;
// 测试链接：
// https://leetcode.com/problems/
// count-submatrices-with-all-ones
// 题目五

// 给定一个二维数组matrix，其中的值不是0就是1，
// 返回全部由1组成的子矩形数量

namespace Code05_CountSubmatricesWithAllOnes {

	class Solution {
	public:
		int numSubmat(vector<vector<int>>& mat) {
			if (mat.size() == 0)
			{
				return 0;
			}
			if (mat[0].size() == 0)
			{
				return 0;
			}
			int COL = mat[0].size();
			int ROW = mat.size();
			vector<int> rectangle(COL, 0);
			int ans = 0;
			for (int r = 0; r < ROW; r++)
			{
				for (int c = 0; c < COL; c++)
				{
					if (mat[r][c] == 1)
					{
						rectangle[c] += 1;
					}
					else
					{
						rectangle[c] = 0;
					}
				}
				ans += countRectangle(rectangle);
			}
			return ans;
		}

		int countRectangle(vector<int> & arr)
		{
			int N = arr.size();
			stack<int> st;
			int ans = 0;
			for (int i = 0; i < N; i++)
			{
				while (!st.empty() 
					&& arr[st.top()]>arr[i]
					)
				{
					int height = arr[st.top()];
					int rightindex = st.top();
					while (!st.empty()
						&&
						height == arr[st.top()])
					{
						st.pop();
					}
					int leftindex = st.empty() ? -1 : st.top();
					int blocks = i - leftindex - 1;
					int rightheight = arr[i];
					int leftheight = (leftindex == -1 ? 0 : arr[st.top()]);
					int down = std::max(rightheight, leftheight);
				
					
					ans += (height-down)*blocks * (blocks + 1) / 2;
					
					
				}
				st.push(i);
			}
			
			while (!st.empty())
			{
				int height = arr[st.top()];
				int rightindex = N - 1;
				while (!st.empty()
					&&
					height == arr[st.top()])
				{
					st.pop();
				}
				int leftindex = st.empty() ? -1 : st.top();
				int blocks = rightindex - leftindex;
				int rightheight = 0;
				int leftheight = (leftindex == -1 ? 0 : arr[st.top()]);
				int down = std::max(rightheight, leftheight);
				
				ans += (height-down)* blocks * (blocks + 1) / 2;
				
				
			}
			return ans;

		}

	};
}


void test_Code05_CountSubmatricesWithAllOnes()
{

	/*[[1, 0, 1], [1, 1, 0], [1, 1, 0]]*/
	/*[[0, 1, 1, 0], [0, 1, 1, 1], [1, 1, 1, 0]]*/
	vector<vector<int>> mat= { {0, 1, 1, 0},
	{0, 1, 1, 1},{1, 1, 1, 0} };
	Code05_CountSubmatricesWithAllOnes::Solution sln;
	printMatrix(mat);
	int ans = sln.numSubmat(mat);
	
	cout << ans << endl;
	
}


#endif