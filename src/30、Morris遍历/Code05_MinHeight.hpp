#pragma once
#ifndef Code05_MinHeight_HPP
#define Code05_MinHeight_HPP
#include <iostream>
#include <queue>
#include <algorithm>
#include "treeNode.hpp"
#include "Code01_MorrisTraversal.hpp"
using namespace std;
namespace Code05_MinHeight {
	class Solution {
	public:
		int minHeight1(Node* head) {
			if (head == nullptr) {
				return 0;
			}
			return p(head);
		}
		// 返回以node 为头的树的最小深度
		int p(Node* node)
		{
			if (node->left == nullptr && node->right == nullptr)
			{
				return 1;
			}

			int leftH = INT_MAX;
			if (node->left != nullptr)
			{
				leftH = p(node->left);
			}
			int rightH = INT_MAX;
			if (node->right != nullptr)
			{
				rightH = p(node->right);
			}
			return 1 + std::min(leftH, rightH);
		}

		
		int MorrisT_MinH(Node* head)
		{
			if (head == nullptr) {
				return 0;
			}
			Node * cur = head;
			Node * c_right_most = nullptr;
			int MinHeight = INT_MAX;
			int curlevel = 1;
			while (cur != nullptr)
			{
				c_right_most = cur->left;
				if (c_right_most != nullptr)
				{
					int rightBoard = 1;
					while (c_right_most->right != nullptr && c_right_most->right != cur)
					{
						rightBoard++;
						c_right_most = c_right_most->right;
					}
					// 第一次来到cur
					if (c_right_most->right == nullptr)
					{
						c_right_most->right = cur;
						// 
						curlevel++;

						cur = cur->left;
						continue;
					}
					// 第二次来到 cur
					// 能够第二次来到cur 说明，他一定有左子
					if (c_right_most->right == cur)
					{
						if (c_right_most->left == nullptr)
						{
							MinHeight = std::min(curlevel, MinHeight);
						}
						curlevel -= rightBoard;
						c_right_most->right = nullptr;
						cur = cur->right;
						continue;
					}
				}
				else
				{
					curlevel++;
					cur = cur->right;
				}
			}

			cur = head;
			int rightEdgeLevel = 1;
			while (cur->right!= nullptr)
			{
				rightEdgeLevel++;
				cur = cur->right;
			}
			if (cur->right == nullptr && cur->left == nullptr)
			{
				MinHeight = std::min(MinHeight, rightEdgeLevel);
			}
			return MinHeight;
		}
	};
}

Node * for_test_tree()
{
	
	int curlevel = 1;
	std::queue<Node*> q;
	int vindex = 1;
	Node * root = new Node(vindex++);
	//q.push(root);
	root->left = new Node(vindex++);
	root->right = new Node(vindex++);

	root->left->left = new Node(vindex++);
	root->left->right = new Node(vindex++);
	root->right->right = new Node(vindex++);

	return root;
}

void test_Code05_MinHeight() {

	int testTime = 10;
	int treeLevel = 4;
	Code05_MinHeight::Solution sln;
	Code01_MorrisTraversal::Solution sln1;
	cout << "test Code05_MinHeight begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		
		/*Node * root =generatetree(treeLevel);*/
		Node * root = for_test_tree();

		/*cout << "========" << endl;
		printTree(root);*/
		int ans1 = sln.minHeight1(root);
		/*cout << "========" << endl;
		printTree(root);*/
		int ans2 = sln.MorrisT_MinH(root);
		/*cout << "========" << endl;
		printTree(root);*/

		if (ans1 != ans2)
		{
			printTree(root);
			cout << ans1 << "," << ans2 << endl;
		}
		delete root;
	}
	cout << "test Code05_MinHeight end" << endl;
}

#endif