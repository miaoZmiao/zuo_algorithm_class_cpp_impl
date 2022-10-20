#pragma once
#ifndef Code06_Dijkstra_HPP
#define Code06_Dijkstra_HPP
#include "graph.h"
#include <unordered_map>
#include <algorithm>
class Code06_Dijkstra
{
public:
	Node * getMinDistanceAndUnselectedNode(
		unordered_set<Node*> &visited,
		unordered_map<Node*, int> & distance
		)
	{
		Node * minNode = nullptr;
		int maxDistance = INT_MAX;
		for (auto & distanceNode : distance)
		{
			Node * node = distanceNode.first;
			int dist = distanceNode.second;
			if (visited.find(node) == visited.end()&& dist < maxDistance)
			{
				maxDistance = dist;
				minNode = node;
			}
		}
		return minNode;
	}


	unordered_map<Node *, int> dijkstra1(Node * from, Graph &g) 
	{
		
		unordered_map<int, Node*> & allnodes = g.nodes;
		unordered_set<Node*> selected;
		unordered_map<Node*, int> distance;
		distance.insert(std::make_pair(from, 0));
		Node * minNode = getMinDistanceAndUnselectedNode(
			selected, distance);
		while (minNode != nullptr)
		{
			int dist = distance[minNode];
			for (Edge &e : minNode->edges)
			{
				int to = e.to;
				Node * toNode = allnodes[to];
				if (distance.find(toNode) == distance.end())
				{
					distance[toNode] = dist + e.weight;
				}
				else
				{
					distance[toNode] = std::min(
						distance[toNode], 
						dist + e.weight);
				}
			}
			selected.insert(minNode);
			minNode = getMinDistanceAndUnselectedNode(
				selected, distance);

		}
		return distance;
	}

	// 方法2 借助加强堆
	struct Record
	{
		Node * node;
		int distance;
	};
	class NodeHeap {
	public:
		// 底层node容器
		vector<Node *> m_nodearray;
		// node节点到 m_nodearray的位置索引
		unordered_map<Node *, size_t > m_nodeindex;
		// node节点的 距离
		// 
		unordered_map<Node *, int>  m_nodedist;
		size_t m_nodenum = 0;
		NodeHeap(size_t N)
		{
			m_nodearray.resize(N, nullptr);
		}
		void insertHeapify(Node * node , size_t index)
		{
			size_t curIndex = index;
			while (m_nodedist[m_nodearray[curIndex]] < m_nodedist[m_nodearray[(curIndex-1)/2]])
			{
				swapNode(curIndex, (curIndex - 1) / 2);
				curIndex = (curIndex - 1) / 2;
			}
		}

		void Heapify(Node * node, size_t index)
		{
			size_t curIndex = index;
			size_t nextIndex = index * 2 + 1;
			while (nextIndex < m_nodenum)
			{
				size_t mindistIndex = nextIndex;
				if(nextIndex + 1 < m_nodenum)
				{
					// nextindex compare to nextindex+1
					int child1dist = m_nodedist[m_nodearray[nextIndex]];
					int child2dist = m_nodedist[m_nodearray[nextIndex+1]];
					mindistIndex = (child1dist < child2dist ?
						nextIndex : nextIndex + 1);
				}
				int childdist = m_nodedist[m_nodearray[mindistIndex]];
				int parentdist = m_nodedist[m_nodearray[curIndex]];
				if (parentdist <= childdist)
				{
					mindistIndex = curIndex;
				}
				if (mindistIndex == curIndex)
				{
					break;
				}

				swapNode(curIndex, mindistIndex);
				// parentdist > childdist
				curIndex = mindistIndex;
				nextIndex = curIndex * 2 + 1;
			}
		}

		void swapNode(size_t index1, size_t index2)
		{
			if (index1 == index2)
			{
				return ;
			}
			Node * node1 = m_nodearray[index1];
			Node * node2 = m_nodearray[index2];
			Node * tmp = node1;
			m_nodearray[index1] = node2;
			m_nodearray[index2] = tmp;
			m_nodeindex[node1] = index2;
			m_nodeindex[node2] = index1;
		}

		bool inHeap(Node * node)
		{
			if (m_nodedist.find(node) != m_nodedist.end()&&
				m_nodeindex[node] != -1
				)
			{
				return true;
			}
			return false;
		}

		bool isEnter(Node * node)
		{
			return m_nodedist.find(node) == m_nodedist.end() &&
				m_nodeindex.find(node) == m_nodeindex.end();
		}




		void addOrUpdate(Node * node, int distance)
		{
			if (inHeap(node))
			{
				// update 
				int storedist = m_nodedist[node];
				// update
				if (storedist < distance)
				{
					size_t index = m_nodeindex[node];
					insertHeapify(node, index);
				}
			}
			// insert
			if (!isEnter(node))
			{
				m_nodearray[m_nodenum] = node;
				m_nodeindex[node] = m_nodenum;
				m_nodedist[node] = distance;
				insertHeapify(node, m_nodenum);
				m_nodenum++;
			}
			// ignore

		}
		Record pop()
		{
			Record ret;
			Node * retNode = m_nodearray[0];
			ret.distance = m_nodedist[retNode];
			ret.node = retNode;
			swapNode(0, m_nodenum - 1);
			m_nodearray[m_nodenum - 1] = nullptr;
			m_nodeindex[retNode] = -1;
			m_nodedist.erase(retNode);
			m_nodenum--;
			Heapify(m_nodearray[0], 0);
			return ret;
		}
		
		bool isEmpty()
		{
			return m_nodenum == 0;
		}
	};

	unordered_map<Node *, int> dijkstra2(Node * from, Graph &g, size_t N)
	{
		unordered_map<int, Node*> & allnodes = g.nodes;
		NodeHeap nheap(N);
		nheap.addOrUpdate(from, 0);
		unordered_map<Node *, int> ans;
		while (!nheap.isEmpty())
		{
			Record rec = nheap.pop();
			Node * node = rec.node;
			int curdist = rec.distance;
			// ans[node] = curdist;
			ans.insert(std::make_pair(node, curdist));
			for (Edge & e : node->edges)
			{
				int to = e.to;
				Node * toNode = allnodes[to];
				nheap.addOrUpdate(toNode, curdist + e.weight);
			}
		}
		return ans;
	}




};


#endif