#pragma once
#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP
#include "utility_func.hpp"
#include <queue>
struct Node {

	Node(int va) {
		value = va;
	}
	~Node() {
		if (nullptr != left)
		{
			delete left;
			left = nullptr;;
		}
		if (nullptr != right)
		{
			delete right;
			right = nullptr;;
		}
	}

	int value;
	Node * left = nullptr;
	Node * right = nullptr;
};

Node * generatetree(int maxlevel = 5)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);
	int curlevel = 1;
	std::queue<Node*> q;
	int vindex = 1;
	Node * root = new Node(vindex++);

	q.push(root);
	while (curlevel < maxlevel)
	{
		std::queue<Node*> next;
		while (!q.empty())
		{
			auto cur = q.front();
			q.pop();
			// 70%的概率产生下一个子节点
			if (dist(mt) < 0.7)
			{
				cur->left = new Node(vindex++);
				next.push(cur->left);
			}
			if (dist(mt) < 0.7)
			{
				cur->right = new Node(vindex++);
				next.push(cur->right);
			}

		}
		q.swap(next);
		curlevel++;
	}
	return root;
}

void printTree(Node * root)
{
	if (root == nullptr)
	{
		cout << "#" << endl;
	}
	std::queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		std::queue<Node*> next;

		while (!q.empty())
		{
			Node * cur = q.front();
			q.pop();
			if (cur == nullptr)
			{
				cout << "#,";
			}
			else
			{
				cout << cur->value << ",";
				next.push(cur->left);
				next.push(cur->right);
			}
		}
		cout << endl;
		q.swap(next);
	}
	

}



#endif