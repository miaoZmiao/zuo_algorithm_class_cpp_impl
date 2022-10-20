#pragma once
#ifndef __BFS__
#define __BFS__
#include "node.h"
#include <queue>
#include <unordered_map>
#include <iostream>
// 从node出发，进行宽度优先遍历

void BFS(Node* root)
{
	if (root == nullptr)
	{
		return;
	}
	std::queue<Node*>  q;
	unordered_map<int, Node*> visited;
	q.push(root);
	visited.insert(std::make_pair(root->value, root));
	while (!q.empty())
	{	
		auto curnode = q.front();
		cout << "id:" << curnode->id<<" value:"<<curnode->value << endl;
		q.pop();
		for (auto & next : curnode->nexts)
		{
			if (visited.end() == visited.find(next->value))
			{
				visited.insert(std::make_pair(next->value, next));
			}
		}
	
	}



}





#endif