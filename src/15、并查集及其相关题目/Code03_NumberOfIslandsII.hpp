#pragma once
#ifndef UNION_SET_Code03_NumberOfIslandsII
#define UNION_SET_Code03_NumberOfIslandsII
#include <vector>

using namespace std;

class UNION_SET_3
{
	vector<int> m_parents;
	vector<int> m_size;
	vector<int> m_help;
	int m_row;
	int m_col;

	int m_setnum;

public:
	UNION_SET_3(int m, int n) {
		m_row = m;
		m_col = n;
		int N = m * n;
		m_parents.resize(N, 0);
		m_size.resize(N, 0);
		m_help.resize(N, 0);
		m_setnum = 0;
	}


	int index(int m, int n) {
		return m * m_col + n;
	}

	int find(int idx) {
		int current = idx;
		int accidx = 0;
		while (current != m_parents[current])
		{
			m_help[accidx++] = current;
			current = m_parents[current];
		}
		for (int i = accidx - 1; i >= 0; i--)
		{
			m_parents[accidx] = current;
		}
		return current;
	}


	void union_merge(int row1, int col1, int row2, int col2)
	{
		int index1 = index(row1, col1);
		int index2 = index(row2, col2);
		int parent1 = find(index1);
		int parent2 = find(index2);
		if (parent1 == parent2)
		{
			return;
		}
		//  index1 != index2
		if (m_size[parent1] >= m_size[parent2])
		{
			m_size[parent1] = m_size[parent1] + m_size[parent2];
			m_parents[parent2] = parent1;
		}
		else
		{
			m_size[parent2] = m_size[parent2] + m_size[parent1];
			m_parents[parent1] = parent2;
		}
		m_setnum--;
	}


	int dot(int row, int col) {
		int idx = index(row, col);
		if (m_size[idx] == 0)
		{
			m_parents[idx] = idx;
			m_size[idx] = 1;
			m_setnum++;
			
			//up
			if (row - 1 >= 0 && m_size[index(row - 1, col)] > 0)
			{
				union_merge(row, col, row - 1, col);
			}
			//down
			if (row + 1 <= m_row-1 && m_size[index(row + 1, col)] > 0)
			{
				union_merge(row, col, row + 1, col);
			}
			//left
			if (col-1 >=0 && m_size[index(row , col-1)] > 0)
			{
				union_merge(row, col, row, col - 1);
			}
			//right
			if (col + 1 <= m_col-1 && m_size[index(row, col + 1)] > 0)
			{
				union_merge(row, col, row, col + 1);
			}
		}

		return m_setnum;
	}


};





class Solution3 {
public:
	vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
		UNION_SET_3 us(m,n);
		vector<int> ans(positions.size(), 0);
		for (int i = 0; i < positions.size(); i++)
		{
			ans[i] = us.dot(positions[i][0], positions[i][1]);
		}

		return ans;
	}

};






#endif