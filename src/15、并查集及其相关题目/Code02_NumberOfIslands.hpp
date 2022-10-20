#pragma once
#ifndef __UNION_SET_NumberOfIslands_HPP__
#define __UNION_SET_NumberOfIslands_HPP__
#include <unordered_map>
#include <stack>
#include <vector>
using namespace std;
struct point
{
	point(int r = 0, int c = 0) :
		row(r),
		col(c)
	{
	
	}
	int row;
	int col;
};

struct pointHash
{	
	size_t max_col;
	size_t max_row;

	pointHash(size_t maxrow = 0, size_t maxcol = 0){
		max_row = maxrow;
		max_col = maxcol;
	}

	pointHash(const pointHash & other) {
		max_row = other.max_row;
		max_col = other.max_col;
	}


	std::size_t operator()(const point& pt)
	{
		return (max_col)* pt.row + pt.col;
	}

};


template<class T, class HashFunc>
class Union_Set
{
	// key 是size value 是 T
	std::unordered_map<size_t, T> m_nodes;
	// 
	std::unordered_map<size_t, size_t> m_parents;

	std::unordered_map<size_t, size_t> m_node_size;

	HashFunc m_hs;


public:
	Union_Set(std::vector<T> & inArray, HashFunc hashobj) {
		size_t N = inArray.size();
		//m_set_num = N;
		m_hs = hashobj;
		for (size_t i = 0; i < N; i++)
		{
			size_t key = m_hs(inArray[i]);
			m_nodes[key] = inArray[i];
			m_parents[key] = key;
			m_node_size[key] = 1;
		}
	}


	size_t find(const T & Index) {

		std::stack<size_t>  help_stack;
		size_t current = m_hs(Index);
		while (current != m_parents[current])
		{
			help_stack.push(current);
			current = m_parents[current];
		}
		while (!help_stack.empty())
		{
			auto topnode = help_stack.top();
			m_parents[topnode] = current;
			help_stack.pop();
		}
		return current;
	}


	void union_merge(const T & A, const T & B)
	{
		size_t Aindex = find(A);
		size_t Bindex = find(B);
		if (Aindex == Bindex)
		{
			return;
		}
		// Aindex != Bindex

		if (Aindex >= Bindex)
		{
			m_node_size[Aindex] = m_node_size[Aindex] + m_node_size[Bindex];
			m_parents[Bindex] = Aindex;
			m_node_size.erase(Bindex);
		}
		else
		{
			m_node_size[Bindex] = m_node_size[Bindex] + m_node_size[Aindex];
			m_parents[Aindex] = Bindex;
			m_node_size.erase(Aindex);
		}
		
	}


	bool isSameSet(const T & A, const T & B)
	{
		size_t Aindex = find(A);
		size_t Bindex = find(B);
		return Aindex == Bindex;	
	}
	size_t set_num()
	{
		return m_node_size.size();
	}
};


// 本题为leetcode原题 200
// 测试链接：https://leetcode.com/problems/number-of-islands/ 
class Solution2 {
public:
	int numIslands(vector<vector<char>>& grid) {
		size_t row = grid.size();
		if (0 == row)
		{
			return 0;
		}
		size_t col = grid[0].size();
		if (0 == col)
		{
			return 0;
		}
		pointHash phash(row, col);
		vector<point> pointarray;
		for (size_t r = 0; r < row; r++)
		{
			for (size_t c = 0; c < col; c++)
			{
				if (grid[r][c] == '1')
				{
					point tmppoint(r, c);
					pointarray.push_back(tmppoint);
				}
			}
		}
		Union_Set <point, pointHash> uset(pointarray, phash);
		
		for (size_t r = 1; r < row; r++)
		{
			if (grid[r][0] == '1' && grid[r - 1][0] == '1')
			{
				uset.union_merge(point(r, 0), point(r-1,0));
			}
		}

		for (size_t c = 1; c < col; c++)
		{
			if (grid[0][c] == '1' && grid[0][c-1] == '1')
			{
				uset.union_merge(point(0, c), point(0, c-1));
			}
		}

		for (size_t r = 1; r < row; r++)
		{
			for (size_t c = 1; c < col; c++)
			{
				if (grid[r][c] == '1')
				{
					if (grid[r - 1][c] == '1')
					{
						uset.union_merge(point(r, c), point(r - 1, c));
					}
					if (grid[r][c - 1] == '1')
					{
						uset.union_merge(point(r, c), point(r , c - 1));
					}
				}
			}
		}
		return uset.set_num();
	}
};







#endif