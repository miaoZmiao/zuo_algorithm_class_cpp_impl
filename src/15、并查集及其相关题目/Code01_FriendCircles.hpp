#pragma once
#ifndef __UNION_SET_FriendCircles_HPP__
#define __UNION_SET_FriendCircles_HPP__
#include <vector>
using namespace std;




class RAW_UNION_SET
{
	// 节点的父节点
	//  m_parent[i] = j, i 节点的父节点 是 j
	std::vector<int> m_parent;
	//  集合的大小数组
	// m_size[i] = j, 以i 为父节点的所有集合大小是j
	std::vector<int> m_size;
	// 辅助数组
	std::vector<int> m_help;
	// 所有集合的数量
	int m_sets_num = 0;


public:

	RAW_UNION_SET(int N  = 10/*元素数量 默认10*/) {

		m_parent.resize(N);
		m_size.resize(N);
		m_help.resize(N, 0);
		m_sets_num = N;
		for (int i = 0; i < N; i++)
		{
			m_parent[i] = i;
			m_size[i] = 1;
			m_help[i] = 0;
		}
	}
	~RAW_UNION_SET() {}

	int find(int index)
	{
		int current = index;
		int help_index = 0;
		while (current != m_parent[current])
		{
			m_help[help_index++] = current;
			current = m_parent[current];
		}
		for (int i = help_index - 1; i >= 0; i--)
		{
			m_parent[m_help[i]] = current;
		}
		return current;
	}

	void union_merge(int i, int j)
	{
		int parent1 = find(i);
		int parent2 = find(j);
		if (parent1 == parent2)
		{
			return;
		}
		// 走到这里说明 两个父节点不一样
		// 需要合并
		// parent1 != parent2
		int set1_count = m_size[parent1];
		int set2_count = m_size[parent2];
		
		if (set1_count >= set2_count)
		{
			m_size[parent1] = m_size[parent1] + m_size[parent2];
			//m_size[parent2] = 0;
			m_parent[parent2] = parent1;
		}
		else
		{
			m_size[parent2] = m_size[parent2] + m_size[parent1];
			//m_size[parent1] = 0;
			m_parent[parent1] = parent2;
		
		}
		m_sets_num--;
	}

	int set_size()
	{
		return m_sets_num;
	}

};


//  leetcode 547 
//  https://leetcode-cn.com/problems/number-of-provinces/ 
class Solution {
public:
	int findCircleNum(vector<vector<int>>& isConnected) {
		size_t N = isConnected.size();
		if (N == 0 || N != isConnected[0].size())
		{
			return 0;
		}

		RAW_UNION_SET union_set(N);

		for (int i = 0; i < N; i++)
		{
			for (int j = i; j < N; j++)
			{
				if (isConnected[i][j] == 1)
				{
					union_set.union_merge(i, j);
				}
			}
		}
		return union_set.set_size();
	}
};






#endif