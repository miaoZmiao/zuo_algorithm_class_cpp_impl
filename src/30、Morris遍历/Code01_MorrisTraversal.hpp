#pragma once
#ifndef Code01_MorrisTraversal_HPP
#define Code01_MorrisTraversal_HPP
#include <queue>
#include "treeNode.hpp"
namespace Code01_MorrisTraversal {

	

	class Solution
	{
	public:
		enum traversal_type : int{
			pre_order = 0,
			med_order = 1,
			pos_order
		};

		void normal_traversal(Node * node, int traversal_type_int)
		{
			switch (traversal_type_int)
			{
			case pre_order:
				cout << "print pre_order tree" << endl;
				break;
			case med_order:
				cout << "print med_order tree" << endl;
				break;
			case pos_order:
				cout << "print pos_order tree" << endl;
				break;
			default:
				break;
			}
			process1(node, traversal_type_int);
			cout  << endl;
		}

		void process1(Node * node, int traversal_type_int)
		{
			if (node == nullptr)
			{
				cout << "#,";
				return;
			}
			//
			if (traversal_type_int == pre_order)
			{
				cout << node->value << ",";
			}
			process1(node->left, traversal_type_int);
			//
			if (traversal_type_int == med_order)
			{
				cout<<node->value << ",";
			}
			process1(node->right, traversal_type_int);
			//
			if (traversal_type_int == pos_order)
			{
				cout << node->value << ",";
			}
		}
		void MorrisT_Traversal(Node * root, traversal_type type) {
			switch (type)
			{
			case pre_order:
				cout << "print MorrisT pre_order tree" << endl;
				break;
			case med_order:
				cout << "print MorrisT med_order tree" << endl;
				break;
			case pos_order:
				cout << "print MorrisT pos_order tree" << endl;
				break;
			default:
				break;
			}
			Node * cur = root;
			while (cur != nullptr)
			{
				// cur has left child
				if (cur->left != nullptr)
				{
					Node *  right_most = cur->left;
					while (right_most->right != nullptr && right_most->right != cur)
					{
						right_most = right_most->right;
					}
					// 第一次来到 cur
					if (right_most->right == nullptr)
					{
						right_most->right = cur;
						if (type == pre_order)
						{
							cout << cur->value << ",";
						}
						cur = cur->left;
						continue;
					}
					// 第二次来到cur
					if (right_most->right == cur)
					{
						right_most->right = nullptr;
						if (type == med_order)
						{
							cout << cur->value<<"," ;
						}
						if (type == pos_order)
						{
							printEdge(cur->left);
						}
						cur = cur->right;
						continue;
					}
				}
				else
				{
					
					if (type == pre_order /*|| med_order*/)
					{
						cout << cur->value << ","/*<<"#,"*/;
					}
					if (type == med_order)
					{
						cout << /*"#," <<*/ cur->value<<",";
					}
					cur = cur->right;
				}
			}
			if (type == pos_order)
			{
				printEdge(root);
			}
			cout << endl;
		}

		void printEdge(Node * node)
		{
			Node * tail = reverse(node);

			Node * cur = tail;
			while (cur != nullptr) {
				cout << cur->value << ",";
				cur = cur->right;
			}
			reverse(tail);
		}

		Node * reverse(Node * node)
		{
			Node * cur = node;
			Node * pre = nullptr;
			while (cur != nullptr)
			{
				Node * next = cur->right;
				cur->right = pre;
				pre = cur;
				cur = next;
			}
			return pre;
		}



	};

	

}

void test_Code01_MorrisTraversal() 
{
	Code01_MorrisTraversal::Solution sln;
	
	using traversal_type = Code01_MorrisTraversal::Solution::traversal_type;
	int testTime = 1;
	int treelevel = 4;
	cout << "test Code01_MorrisTraversal begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		Node * root =generatetree(treelevel);

		sln.normal_traversal(root, traversal_type::pre_order);
		sln.MorrisT_Traversal(root, traversal_type::pre_order);
		sln.normal_traversal(root, traversal_type::med_order);
		sln.MorrisT_Traversal(root, traversal_type::med_order);
		sln.normal_traversal(root, traversal_type::pos_order);
		sln.MorrisT_Traversal(root, traversal_type::pos_order);
		delete root;
	}
	cout << "test Code01_MorrisTraversal end" << endl;

}





#endif