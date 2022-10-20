#pragma once
#ifndef Code02_IndexTree2D_HPP
#define Code02_IndexTree2D_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include "utility_func.hpp"
using namespace std;

namespace Code02_IndexTree2D {

	// 
	class Solution{
	public:
		vector<vector<long>> m_tree;
		vector<vector<long>> m_nums;
		int m_row = 0;
		int m_col = 0;

		Solution(vector<vector<int>>& matrix) {
			reset(matrix);
		}

		Solution() {}

		// row >0 col >0
		void reset(vector<vector<int>>& matrix)
		{
			m_row = matrix.size();
			m_col = matrix[0].size();
			m_nums.resize(matrix.size(), vector<long>(matrix[0].size(), 0));
			for (int i = 0; i < m_row; i++)
			{
				std::memset(m_nums[i].data(), 0, m_nums[i].size()*sizeof(long));	;
			}
			m_tree.resize(m_row+1, vector<long>(m_col+1, 0));
			for (int i = 1; i <= m_row; i++)
			{
				std::memset(m_tree[i].data(), 0, m_tree[i].size() * sizeof(long));
			}

			for (int i = 0; i < matrix.size(); i++)
			{
				for (int j = 0; j < matrix[0].size(); j++)
				{
					update(i, j, matrix[i][j]);
				}
			}

		}

		void update(int row, int col, int val)
		{
			if (!checkrow(row) || !checkcol(col))
			{
				return;
			}
			long add = val - m_nums[row][col];
			m_nums[row][col] = val;
			for (int i = row + 1; i <= m_row; i+=(i)&(-i))
			{
				for (int j = col + 1; j <= m_col; j += (j)&(-j))
				{
					m_tree[i][j] += add;
				}
			}
		}

		long sum(int row, int col)
		{
			if (!checkrow(row) || !checkcol(col))
			{
				return 0;
			}
			long ans = 0;
			for (int i = row + 1; i > 0; i -= (i)&(-i))
			{
				for (int j = col + 1; j > 0; j -= (j)&(-j))
				{
					ans += m_tree[i][j];
				}
			}
			return ans;
		}

		// row  [0 .....  m_row -1]
		bool checkrow(int row)
		{
			if (row < 0 || row > m_row - 1)
			{
				return false;
			}
			return true;
		}
		// col  [0 .....  m_col -1]
		bool checkcol(int col)
		{
			if (col < 0 || col > m_row - 1)
			{
				return false;
			}
			return true;
		}
		


		long sumRegion(int row1, int col1, int row2, int col2)
		{
			if (m_col == 0 || m_row== 0 ||
				!checkrow(row1)||
				!checkrow(row2) ||
				!checkcol(col1)||
				!checkcol(col2)) {
				return 0;
			}
			int small_col = std::min(col1, col2);
			int big_col= std::max(col1, col2);

			int small_row = std::min(row1, row2);
			int big_row = std::max(row1, row2);
			long ans = sum(big_row, big_col) +
				sum(small_row - 1, small_col - 1) -
				sum(small_row - 1, big_col) -
				sum(big_row, small_col - 1);
			return ans;
		}

	};

	class Right {

	public:
		vector<vector<long>> m_nums;
		int m_row = 0;
		int m_col = 0;

		void reset(vector<vector<int>>& matrix) {
			m_row = matrix.size();
			m_col = matrix[0].size();
			m_nums.resize(m_row, vector<long>(m_col, 0));
			for (int i = 0; i < m_row; i++)
			{
				for (int j = 0; j < m_col; j++)
				{
					m_nums[i][j] = matrix[i][j];
				}
			}
			return;
		}


		long sumRegion(int row1, int col1, int row2, int col2)
		{
			if (m_col == 0 || m_row == 0 ||
				!checkrow(row1) ||
				!checkrow(row2) ||
				!checkcol(col1) ||
				!checkcol(col2)) {
				return 0;
			}
			int r_col1 = std::min(col1, col2);
			int r_col2 = std::max(col1, col2);

			int r_row1 = std::min(row1, row2);
			int r_row2 = std::max(row1, row2);
			long ans = 0;
			for (int i = r_row1; i <= r_row2; i++)
			{
				for (int j = r_col1; j <= r_col2; j++)
				{
					ans += m_nums[i][j];
				}
			}
			return ans;
		}


		// row  [0 .....  m_row -1]
		bool checkrow(int row)
		{
			if (row < 0 || row > m_row - 1)
			{
				return false;
			}
			return true;
		}
		// col  [0 .....  m_col -1]
		bool checkcol(int col)
		{
			if (col < 0 || col > m_row - 1)
			{
				return false;
			}
			return true;
		}




	};


}

void test_Code02_IndexTree2D() {

	// row
	int N = 5;
	// col
	int M = 5;
	int testTime = 10;
	Code02_IndexTree2D::Solution sln;
	Code02_IndexTree2D::Right duishuqi;
	std::random_device rd;
	std::mt19937 sd(rd());
	std::uniform_real_distribution<> dist(0.0,1.0);
	cout << "test Code02_IndexTree2D begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		vector<vector<int>> matrix = 
			generate_M_N_matrix(N,M,1,10);
		sln.reset(matrix);
		duishuqi.reset(matrix);
		int row1 = dist(sd)*N;
		int row2 = dist(sd)*N;
		int col1 = dist(sd)*M;
		int col2 = dist(sd)*M;
		/*int row1 = 0;
		int row2 = 2;
		int col1 = 0;
		int col2 = 2;*/
		int rowbig = std::max(row1, row2);
		int rowsmall = std::min(row1, row2);
		int colbig = std::max(col1, col2);
		int colsmall = std::min(col1,col2);

		long ans1 = sln.sumRegion(rowsmall, colsmall,
			rowbig, colbig);
		long ans2 = duishuqi.sumRegion(rowsmall, colsmall,
			rowbig, colbig);
		if (ans1 != ans2)
		{
			printMatrix(matrix);
			cout << "row:" << rowsmall << "," << rowbig << endl;
			cout << "col:" << colsmall << "," << colbig << endl;
			cout << ans1 << "," << ans2 << endl;
			break;
		}
	
	}
	cout << "test Code02_IndexTree2D end" << endl;

	
}


#endif