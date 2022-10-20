#include "GraphGenerator.hpp"
#include "Code03_TopologicalOrderBFS.hpp"
#include "Code03_TopologicalOrderDFS1.hpp"
#include "Code03_TopologicalOrderDFS2.hpp"
#include "Code03_TopologySort.hpp"
#include "Code04_Kruskal.hpp"
#include "Code05_Prim.hpp"
#include "Code06_Dijkstra.hpp"
#include <string>
void test_generate_graph()
{
	Graph g = generate_Graph(4, 1, 5, 1, 10);
	g.release();
}
void test_Code03_TopologicalOrderBFS()
{
	vector<DirectedGraphNode*> g;
	Solution sln;
	sln.topSort(g);
}
void test_Code03_TopologicalOrderDFS1()
{
	vector<DirectedGraphNode*> g;
	Solution2 sln;
	sln.topSort(g);
}
void test_Code03_TopologicalOrderDFS2()
{
	vector<DirectedGraphNode*> g;
	Solution3 sln;
	sln.topSort(g);
}
void test_Code03_TopologySort()
{
	Graph g = generate_Graph(4, 1, 5, 1, 10);
	Code03_TopologySort sln;
	vector<Node*> ans =  sln.sortedTopology(g);
	cout << "[";
	for (auto & it : ans)
	{
		cout << it->id << " ";
	}
	cout << "]" << endl;;
	g.release();
}
void test_pair_conflict(int N)
{
	// generate pair
	vector<std::pair<int, int>> test_pairs;
	unordered_set<std::pair<int, int>, pair_hash_x, pair_hash_equal> sameSet;
	auto print_pair = [](std::pair<int, int> & p) {
		std::string res = "[" + to_string(p.first) + ","
			+ to_string(p.second) + "]";
		return res;
	};
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			auto tmppair = std::make_pair(i,j);
			test_pairs.push_back(tmppair);
			if (sameSet.find(tmppair) == sameSet.end())
			{
				size_t hashcode = pair_hash_x()(tmppair);
				cout << print_pair(tmppair) << " hashcode :" << hashcode << endl;
				sameSet.insert(tmppair);
			}
			else
			{
				// 
				auto tmpiter = *sameSet.find(tmppair);
				cout << print_pair(tmppair) << " is conflict with " <<
					print_pair(tmpiter) << endl;;
			}
		}
	}
	char c;
	cin >> c;
}
void test_Code04_Kruskal() {
	Graph g = generate_Graph(4, 1, 5, 1, 10);
	
	Code04_Kruskal sln;
	auto ans = sln.kruskalMST(g);
	g.release();
}
void test_Code05_Prim()
{
	Graph g = generate_Graph(4, 1, 5, 1, 10);
	Code05_Prim sln;
	auto ans = sln.primMST(g);
	g.release();
}

void test_Code06_Dijkstra()
{
	Graph g = generate_Graph(4, 1, 5, 1, 10);
	Code06_Dijkstra sln;

	unordered_map<Node *, int> ans1 = sln.dijkstra1(g.nodes.begin()->second, g);

	unordered_map<Node *, int> ans2 = sln.dijkstra2(g.nodes.begin()->second, g, g.nodes.size());


}


int main()
{
	//test_pair_conflict(4);
	char c;
	cin >> c;
	return 0;
}