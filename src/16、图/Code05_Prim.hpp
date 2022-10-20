#pragma once
#ifndef Code05_Prim_HPP
#define Code05_Prim_HPP
#include "graph.h"
#include <vector>
#include <queue>
using namespace std;
class Code05_Prim
{
public:
	vector<Edge> primMST(Graph  & graph)
	{
		auto edgecmp = [](const Edge & left, const Edge & right) {
			return left.weight > right.weight;
		};
		std::priority_queue<Edge, vector<Edge>, decltype(edgecmp)>
			pq(edgecmp);

		vector<Edge> ans;
		unordered_map<int, Node*> & allnodes = graph.nodes;
		unordered_set<Node*> visited;
		for (auto & it : allnodes)
		{
			Node* curnode = it.second;
			if (visited.find(curnode) == visited.end())
			{
				for (Edge & e : curnode->edges)
				{
					pq.push(e);
				}
				while (!pq.empty())
				{
					Edge e = pq.top();
					pq.pop();
					int to = e.to;
					Node * toNode = allnodes[to];
					if (visited.find(toNode) == visited.end())
					{
						visited.insert(toNode);
						ans.push_back(e);
						for (Edge & e : toNode->edges)
						{
							pq.push(e);
						}
					}
				}
			}
		}
		return ans;
	}
	// 请保证graph是连通图
	// graph[i][j]表示点i到点j的距离，如果是系统最大值代表无路
	// 返回值是最小连通图的路径之和
	int prim(vector<vector<int>> & graph) {
		int ans = 0;
		size_t nodesize = graph.size();
		vector<int> distance(nodesize, 0);
		vector<bool> visited(nodesize, false);
		//  从 0 点开始
		visited[0] = true;
		for (int i = 0; i < distance.size(); i++)
		{
			distance[i] = graph[0][i];
		}

		for (int i = 1; i < nodesize; i++)
		{
			int minLength = INT_MAX;
			int minIndex = -1;
			for (int j = 0; j < nodesize; j++)
			{
				if (!visited[j] && distance[j] < minLength)
				{
					minLength = distance[j];
					minIndex = j;
				}
			}
			if (minIndex == -1)
			{
				return ans;
			}
			ans += minLength;
			visited[minIndex] = true;
			// update distance
			for (int j = 0; j < nodesize; j++)
			{
				if (!visited[j] && distance[j] > graph[minIndex][j])
				{
					distance[j] = graph[minIndex][j];
				}
			}
		}
		return ans;
	}



};



#endif