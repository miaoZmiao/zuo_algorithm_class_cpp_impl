#pragma once
#ifndef Code03_TopologicalOrderDFS2
#define Code03_TopologicalOrderDFS2
#include "Code03_TopologicalOrderBFS.hpp"


class  Solution3
{
public:
	struct Record
	{
		DirectedGraphNode* node = nullptr;
		long  nodes= 0;
	};

	int help_func(DirectedGraphNode* node,
		unordered_map<DirectedGraphNode*, Record> & order)
	{
		if (order.find(node) != order.end())
		{
			return order[node].nodes;
		}

		long nodes_count = 0;

		for (auto & it : node->neighbors)
		{
			nodes_count += help_func(it, order);
		}
		Record rec;
		rec.nodes = nodes_count + 1;
		rec.node = node;
		order[node] = rec;
		return rec.nodes;
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
			return left.nodes > right.nodes;
		};

		std::sort(help_ans.begin(), help_ans.end(), cmp);

		vector<DirectedGraphNode*> ans;
		for (auto & it : help_ans)
		{
			ans.push_back(it.node);
		}
		return ans;
	}
protected:
private:
};


#endif