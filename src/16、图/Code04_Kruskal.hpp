#pragma once
#ifndef Code04_Kruskal_HPP
#define Code04_Kruskal_HPP
#include "graph.h"
#include <unordered_map>
#include <stack>
#include <set>
#include <queue>
class Code04_Kruskal
{
public:
	class UnionFind
	{
	public:
		unordered_map<Node*, Node*> m_parents;
		unordered_map<Node*, size_t> m_sizemap;



		UnionFind(vector<Node*>& nodes) {
			size_t N = nodes.size();
			for (size_t i = 0; i < N; i++)
			{
				m_parents[nodes[i]] = nodes[i];
				m_sizemap[nodes[i]] = 1;
			}
		}

		UnionFind(unordered_map<int, Node*> & nodes) {
			size_t N = nodes.size();

			size_t i = 0;
			for (auto & it : nodes)
			{
				m_parents[it.second] = it.second;
				m_sizemap[it.second] = 1;
			}
		
		}


		Node* find(Node* node)
		{
			std::stack<Node*> st;
			Node * cur = node;
			while (cur != m_parents[cur])
			{
				st.push(cur);
				cur = m_parents[cur];
			}
			while (!st.empty())
			{
				auto tmp = st.top();
				st.pop();
				m_parents[tmp] = cur;
			}
			return cur;
		}

		bool isSameSet(Node* node1, Node * node2)
		{
			return find(node1) == find(node2);
		}

		void union_merge(Node* node1, Node * node2)
		{
			Node * parent1 = find(node1);
			Node * parent2 = find(node2);
			if (parent1 == parent2)
			{
				return;
			}
			if (m_sizemap[parent1] >= m_sizemap[parent2])
			{
				m_sizemap[parent1] = m_sizemap[parent1] + 
					m_sizemap[parent2];
				m_parents[parent2] = parent1;
				m_sizemap.erase(parent2);
			}
			else
			{
				m_sizemap[parent2] = m_sizemap[parent2] +
					m_sizemap[parent1];
				m_parents[parent1] = parent2;
				m_sizemap.erase(parent1);
			}
		}

		size_t set_num() {
			return m_sizemap.size();
		}
	};

	vector<Edge> kruskalMST(Graph graph)
	{
		vector<Edge> ans;
		UnionFind uf(graph.nodes);

		auto edgecmp = [](const Edge & left, const Edge & right ) {
			return left.weight > right.weight;
		};
		
		std::priority_queue<Edge, vector<Edge>, decltype(edgecmp)> 
			pq(edgecmp);

		while (!pq.empty())
		{
			Edge curEdge = pq.top();
			pq.pop();
			int from = curEdge.from;
			int to = curEdge.to;
			Node* fromNode = graph.nodes[from];
			Node* toNode = graph.nodes[to];
			if (!uf.isSameSet(fromNode, toNode)) {
				uf.union_merge(fromNode, toNode);
				ans.push_back(curEdge);
			}
		}
		return ans;
	}





};






#endif // _DEBUG
