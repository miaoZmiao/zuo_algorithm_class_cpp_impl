#pragma once
#ifndef Code03_TopologicalOrderDFS1
#define Code03_TopologicalOrderDFS1
#include "Code03_TopologicalOrderBFS.hpp"
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// 借助辅助结构deep
// 保存每个node的深度 deep

class Solution2
{
public:

	struct Record
	{
		DirectedGraphNode* node = nullptr;
		int deep = 0;
	};

	int help_func(DirectedGraphNode* node,
		unordered_map<DirectedGraphNode*, Record> & order)
	{
		if (order.find(node) != order.end())
		{
			return order[node].deep;
		}

		int deep = 0;

		for (auto & it : node->neighbors)
		{
			deep = std::max(deep, help_func(it, order));
		}
		Record rec;
		rec.deep = deep + 1;
		rec.node = node;
		order[node] = rec;
		return deep + 1;
	}


	// 这回用DFS来实现
	vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*> graph) {

		unordered_map<DirectedGraphNode*, Record> order;

		for (auto & it : graph)
		{
			help_func(it, order);
		}

		vector<Record> help_ans;

		for (auto & it : order)
		{
			help_ans.push_back(it.second);
		}

		auto cmp = [](const Record & left, const Record & right) ->bool {
			return left.deep > right.deep;
		};

		std::sort(help_ans.begin(), help_ans.end(), cmp);

		vector<DirectedGraphNode*> ans;
		for (auto & it : help_ans)
		{
			ans.push_back(it.node);
		}
		return ans;
	}

};



#endif