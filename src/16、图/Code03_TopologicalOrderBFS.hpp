#pragma once
#ifndef TOPOLOGICALORDERBFS_HPP
#define TOPOLOGICALORDERBFS_HPP
// OJÁ´½Ó£ºhttps://www.lintcode.com/problem/topological-sorting

#include <vector>
#include <unordered_map>
#include <queue>
/**
 * Definition for Directed graph.
 */
using namespace std;
 struct DirectedGraphNode {
	int label;
	std::vector<DirectedGraphNode *> neighbors;
	DirectedGraphNode(int x) : label(x) {};
	
};
class Solution {
public:
	/**
	 * @param graph: A list of Directed graph node
	 * @return: Any topological order for the given graph.
	 */
	vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*> graph) {
		// write your code here
		// BFS
		// compute in and out
		std::unordered_map<DirectedGraphNode*, int> indegree;

		for (int i = 0; i < graph.size(); i++)
		{
			auto curNode = graph[i];
			// from 
			if (indegree.count(curNode) == 0)
			{
				indegree[curNode] = 0;
			}
			for (auto it : curNode->neighbors)
			{
				if (indegree.count(it) == 0)
				{
					indegree[it] = 1;
				}
				else
				{
					indegree[it]++;
				}
			}
		}
		std::vector<DirectedGraphNode*> ans;
		std::queue<DirectedGraphNode*> zeroq;
		for (auto & it : indegree)
		{
			if (it.second == 0)
			{
				zeroq.push(it.first);
			}
		}

		while (!zeroq.empty())
		{
			auto cur = zeroq.front();
			ans.push_back(cur);
			zeroq.pop();
			for (auto & it : cur->neighbors)
			{
				indegree[it]--;
				if (indegree[it] == 0)
				{
					zeroq.push(it);
				}				
			}
		}
		return ans;
	}
};


#endif