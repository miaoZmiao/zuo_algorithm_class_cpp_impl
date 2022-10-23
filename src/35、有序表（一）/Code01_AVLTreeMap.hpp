#pragma once
#ifndef Code01_AVLTreeMap_HPP
#define Code01_AVLTreeMap_HPP
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

namespace Code01_AVLTreeMap {

	struct AVLTreeNode {
		int k;
		int v;
		int h;
		AVLTreeNode * left;
		AVLTreeNode * right;
		AVLTreeNode(int key, int value) {
			k = key;
			v = value;
			h = 1;
			left = nullptr;
			right = nullptr;
		}
		~AVLTreeNode() {
			if (left != nullptr)
			{
				delete left;
				left = nullptr;
			}
			if (right != nullptr)
			{
				delete right;
				right = nullptr;
			}
		}

	};

	class AVLTree {
		AVLTreeNode * m_root = nullptr;
		size_t m_size = 0;
	public:
		AVLTree() {
			m_root = nullptr;
			m_size = 0;
		}

		~AVLTree() {
			if (m_root != nullptr)
			{
				delete m_root;
				m_root = nullptr;
			}
		}

		AVLTreeNode * rightRotate(AVLTreeNode * cur)
		{
			AVLTreeNode * cur_left = cur->left;

			AVLTreeNode * cur_left_right = cur_left->right;
		
			cur_left->right = cur;

			cur->left = cur_left_right;

			// compute height
			int cur_left_height = (cur->left != nullptr ? cur->left->h : 0);
			int cur_right_height = (cur->right != nullptr ? cur->right->h : 0);
			cur->h = std::max(cur_left_height, cur_right_height) + 1;
			// cur->left height
			int cur_left_left_height =
				(cur_left->left!=nullptr? cur_left->left->h:0);
			int cur_left_right_height =
				(cur_left->right != nullptr ? cur_left->right->h : 0);
			
			cur_left->h = std::max(cur_left_left_height, cur_left_right_height) + 1;

			return cur_left;
		}

		AVLTreeNode * leftRotate(AVLTreeNode * cur)
		{
			AVLTreeNode * right = cur->right;
			cur->right = right->left;
			right->left = cur;
			// height
			int cur_left_h = (cur->left != nullptr ? cur->left->h : 0);
			int cur_right_h = (cur->right != nullptr ? cur->right->h : 0);
			cur->h = std::max(cur_left_h, cur_right_h) + 1;
			int right_left_h = (right->left != nullptr ? right->left->h : 0);
			int right_right_h = (right->right != nullptr ? right->right->h : 0);
			right->h = std::max(right_left_h, right_right_h) + 1;
			return right;
		}

		AVLTreeNode * maintain(AVLTreeNode * cur)
		{	
			if (cur == nullptr)
			{
				return nullptr;
			}
			int left_h = cur->left != nullptr ? cur->left->h : 0;
			int right_h = cur->right != nullptr ? cur->right->h : 0;
			if (std::abs(left_h - right_h) > 1)
			{
				AVLTreeNode * left = cur->left;
				AVLTreeNode * right = cur->right;
				if (left_h > right_h)
				{
					int left_left_h = (left != nullptr?
						(left->left != nullptr ? left->left->h:0)
						:
						0);
					int left_right_h = (left != nullptr ?
						(left->right != nullptr ? left->right->h : 0)
						:
						0);

					if (left_left_h >= left_right_h)
					{
						cur = rightRotate(cur);
					}
					else {
						
						cur->left = leftRotate(cur->left);
						cur = rightRotate(cur);
					}
				}
				else // right_h > left_h
				{
					int right_left_h = (right != nullptr ?
						(right->left != nullptr ? right->left->h : 0)
						:
						0);
					int right_right_h = (right != nullptr ?
						(right->right != nullptr ? right->right->h : 0)
						:
						0);

					if (right_right_h >= right_left_h)
					{
						cur = leftRotate(cur);
					}
					else // right_left_h > right_right_h 
					{

						cur->right = rightRotate(cur->right);
						cur = leftRotate(cur);
					}
				}

			}

			return cur;
		}

		AVLTreeNode * findLastIndex(int KEY)
		{
			AVLTreeNode * cur = m_root;
			AVLTreeNode * pre = m_root;
			while (cur != nullptr) {
				pre = cur;
				if (cur->k == KEY)
				{
					break;
				}
				else if (cur->k < KEY)
				{
					cur = cur->right;
				}
				else  // cur->k > KEY
				{
					cur = cur->left;
				}
			}
			return pre;
		}
		// find some node  k >= KEY 
		AVLTreeNode * findLastNoSmallIndex(int KEY)
		{
			AVLTreeNode * cur = nullptr;
			AVLTreeNode * ans = m_root;
			while (cur != nullptr)
			{
				if (cur->k == KEY)
				{
					ans = cur;
					break;
				}
				else if (cur->k > KEY)
				{
					ans = cur;
					cur = cur->left;
				}
				else // cur->k < KEY
				{
					cur = cur->right;
				}
			}
			return ans;
		}
		
		AVLTreeNode * findLastNoBigIndex(int KEY)
		{
			AVLTreeNode * cur = nullptr;
			AVLTreeNode * ans = m_root;
			while (cur != nullptr)
			{
				if (cur->k == KEY)
				{
					ans = cur;
					break;
				}
				else if (cur->k > KEY)
				{
					cur = cur->left;
				}
				else // cur->k < KEY
				{
					ans = cur;
					cur = cur->right;
				}
			}
			return ans;
		}
		
		AVLTreeNode * add(AVLTreeNode * cur, int KEY, int VALUE)
		{
			if (cur == nullptr)
			{
				AVLTreeNode * ans = new AVLTreeNode(KEY, VALUE);
				return ans;
			}
			else if (cur->k < KEY)
			{
				cur->right = add(cur->right, KEY, VALUE);
			}
			else if (cur->k > KEY)
			{
				cur->left = add(cur->left, KEY, VALUE);
			}
			int left_h = node_height(cur->left);
			int right_h = node_height(cur->right);
			cur->h = std::max(left_h, right_h) + 1;
			return maintain(cur);
		}
		
		int node_height(AVLTreeNode * node)
		{
			return node != nullptr ? node->h : 0;
		}

		AVLTreeNode * deleteNode(AVLTreeNode * cur, int KEY)
		{
			
			if (cur->k > KEY)
			{
				cur->left = deleteNode(cur->left, KEY);
			}
			else if (cur->k < KEY)
			{
				cur->right = deleteNode(cur->right, KEY);
			}
			else // cur->k == KEY
			{
				if (cur->left == nullptr && cur->right == nullptr)
				{
					delete cur;
					cur = nullptr;
				}
				else if (cur->left != nullptr && cur->right == nullptr)
				{
					AVLTreeNode * left = cur->left;
					cur->left = nullptr;
					delete cur;
					cur = left;
				}
				else if (cur->left == nullptr && cur->right != nullptr)
				{
					AVLTreeNode * right = cur->right;
					cur->right = nullptr;
					delete cur;
					cur = right;
				}
				else
				{
					AVLTreeNode * succ = cur->right;
					while (succ->left != nullptr)
					{
						succ = succ->left;
					}
					int succ_key = succ->k;
					cur->k = succ_key;
					cur->right = deleteNode(cur->right, succ->k);
				}
			}
			if(cur != nullptr)
			{
				cur->h = std::max(node_height(cur->left),
					node_height(cur->right)) + 1;
				cur = maintain(cur);
			}
			return cur;
		}
		int size() {
			return m_size;
		}

		bool containsKey(int KEY) {
			AVLTreeNode * node = findLastIndex(KEY);
			return node == nullptr ? false : (node->k == KEY?true:false);
		}
		void put(int key, int value)
		{
			AVLTreeNode * node = findLastIndex(key);
			bool is_node_exist = node == nullptr ? false : (node->k == key ? true : false);
			if (is_node_exist == false)
			{
				m_root = add(m_root, key, value);
				m_size++;
			}
			else
			{
				node->v = value;
			}
		}

		void remove(int key)
		{
			AVLTreeNode * node = findLastIndex(key);
			bool is_node_exist = node == nullptr ? false : (node->k == key ? true : false);
			if (true == is_node_exist)
			{
				m_root = deleteNode(m_root, key);
				m_size--;
			}
		}

		int get(int key)
		{
			AVLTreeNode * node = findLastIndex(key);
			bool is_node_exist = node == nullptr ? false : (node->k == key ? true : false);
			if (is_node_exist == true)
			{
				return node->v;
			}
			return int();
		}

		int firstKey()
		{
			AVLTreeNode * cur = m_root;
			while (cur->left != nullptr)
			{
				cur = cur->left;
			}
			return cur->k;
		}

		int lastKey()
		{
			AVLTreeNode * cur = m_root;
			while (cur->right != nullptr)
			{
				cur = cur->right;
			}
			return cur->k;
		}

		int floorKey(int key)
		{
			AVLTreeNode * node = findLastNoBigIndex(key);
			return node == nullptr ? int() : node->k;
		}

		int ceilKey(int key)
		{
			AVLTreeNode * node = findLastNoSmallIndex(key);
			return node == nullptr ? int() : node->k;
		}

		void printsingleNode(AVLTreeNode * node)
		{
			cout << "[ k:" << node->k << " v:" << node->v << " h:"<< node->h<<"] ";
		}

		void printLineEnd()
		{
			cout << endl;
		}


		void print()
		{
			std::queue<AVLTreeNode*> q;
			std::queue<AVLTreeNode*> next;
			q.push(m_root);
			while (!q.empty())
			{
				
				while (!q.empty())
				{
					AVLTreeNode * cur = q.front();
					q.pop();
					printsingleNode(cur);
					if (cur->left)
					{
						next.push(cur->left);
					}
					if (cur->right)
					{
						next.push(cur->right);
					}
				}
				printLineEnd();
				q.swap(next);
			}
			printLineEnd();
			printLineEnd();
		}

	};
}


void test_Code01_AVLTreeMap() {
	cout << "test_Code01_AVLTreeMap begin" << endl;
	using AVLTree = Code01_AVLTreeMap::AVLTree;
	AVLTree tree;

	tree.put(1, 1);
	tree.print();
	tree.put(2, 2);
	tree.print();
	tree.put(3, 3);
	tree.print();
	tree.put(4, 4);
	tree.print();
	tree.put(5, 5);
	tree.print();
	tree.put(6, 6);
	tree.print();
	tree.put(7, 7);
	tree.print();
	tree.put(8, 8);
	tree.print();
	tree.put(9, 9);
	tree.print();
	tree.put(10, 10);
	tree.print();

	tree.remove(1);
	tree.print();
	tree.remove(2);
	tree.print();
	tree.remove(3);
	tree.print();
	tree.remove(4);
	tree.print();
	tree.remove(5);
	tree.print();
	tree.remove(6);
	tree.print();
	cout << "test_Code01_AVLTreeMap end" << endl;

}


#endif