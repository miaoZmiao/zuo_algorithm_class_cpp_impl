#pragma once
#ifndef __DFS__
#define __DFS__
#include "node.h"
#include <queue>
#include <unordered_set>
#include <iostream>
#include <stack>
void DFS(Node * root)
{
	if (root == nullptr)
	{
		return;
	}
	std::stack<Node*> st;
	std::unordered_set<int> visited;
	st.push(root);
	cout << "nodeid : " << root->id << endl;
	visited.insert(root->id);
	while (!st.empty())
	{
		auto curnode = st.top();
		st.pop();
		
		for (auto & next : curnode->nexts)
		{
			if (visited.end() == visited.find(next->id))
			{
				cout << "nodeid : " << next->id << endl;
				visited.insert(next->id);
				st.push(next);
				st.push(curnode);
				break;
			}
		}
	}


}



#endif