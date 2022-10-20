#pragma once
#ifndef Code03_TopologySort_HPP
#define Code03_TopologySort_HPP
#include "graph.h"
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;
class Code03_TopologySort
{
public:
	vector<Node*> sortedTopology(const Graph & g) {
		
		// º∆À„»Î∂»
		unordered_map<Node*, int> inmap;
		std::queue<Node*>  zeroq;
		for (auto & it : g.nodes)
		{
			auto curnode = it.second;
			if (0 == curnode->in)
			{
				zeroq.push(curnode);
			}
			inmap[curnode] = curnode->in;
		}

		vector<Node*> ans;
		while (!zeroq.empty())
		{
			auto curnode = zeroq.front();
			ans.push_back(curnode);
			zeroq.pop();
			for (auto & it : curnode->nexts)
			{
				inmap[it]--;
				if (0 == inmap[it])
				{
					zeroq.push(it);
				}
			
			}		
		}

		return ans;
	}

};




#endif