#pragma once
#ifndef Code01_SizeBalancedTreeMap_HPP
#define Code01_SizeBalancedTreeMap_HPP
#include <iostream>
#include <queue>
using namespace std;

namespace Code01_SizeBalancedTreeMap {

	struct SBTNode {
		int key;
		int value;
		int size;
		SBTNode * left;
		SBTNode * right;
		SBTNode(int key, int value) {
			this->key = key;
			this->value = value;
			size = 1;
			left = nullptr;
			right = nullptr;
		}
		~SBTNode() {
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

	class SizeBalancedTree {
		SBTNode* m_root = nullptr;
		int m_size = 0;
	public:
		SizeBalancedTree() {
			m_size = 0;
		}
		~SizeBalancedTree() {
			if (m_root != nullptr)
			{
				delete m_root;
				m_root = nullptr;
			}
		}

		int nodeSizeFromChild(SBTNode * node)
		{
			if (node == nullptr)
			{	
				return 0;
			}
			int leftsize = nodeSize(node->left);
			int rightsize = nodeSize(node->right);
			return leftsize + rightsize + 1;
		}


		int nodeSize(SBTNode * node)
		{
			if (node == nullptr)
			{
				return 0;
			}
			return node->size;
		}

		SBTNode * leftRotate(SBTNode * cur)
		{
			SBTNode * right = cur->right;
			cur->right = right->left;
			right->left = cur;
			cur->size = nodeSizeFromChild(cur);
			right->size = nodeSizeFromChild(right);
			return right;
		}

		SBTNode * rightRotate(SBTNode * cur)
		{
			SBTNode * left = cur->left;
			cur->left = left->right;
			left->right = cur;
			cur->size = nodeSizeFromChild(cur);
			left->size = nodeSizeFromChild(left);
			return left;
		}

		SBTNode * maintain(SBTNode * cur) {
			if (cur == nullptr)
			{
				return cur;
			}
			int leftsize = nodeSize(cur->left);
			int leftleftsize = (cur->left != nullptr ? nodeSize(cur->left->left) : 0);
			int leftrightsize = (cur->left != nullptr ? nodeSize(cur->left->right) : 0);

			int rightsize = nodeSize(cur->right);
			int rightleftsize = (cur->right != nullptr ? nodeSize(cur->right->left) : 0);
			int rightrightsize = (cur->right != nullptr ? nodeSize(cur->right->right) : 0);
			// LL  violation
			if (leftleftsize > rightsize)
			{
				cur = rightRotate(cur);
				cur->right = maintain(cur->right);
				cur = maintain(cur);
			}
			// LR  violation
			else if (leftrightsize > rightsize)
			{
				cur->left = leftRotate(cur->left);
				cur = rightRotate(cur);
				cur->left = maintain(cur->left);
				cur->right = maintain(cur->right);
				cur = maintain(cur);
			}
			// RR violation 
			else if (rightrightsize > leftsize)
			{
				cur = leftRotate(cur);
				cur->left = maintain(cur->left);
				cur = maintain(cur);
			}
			// RL violation
			else if (rightleftsize > leftsize)
			{
	
				cur->right = rightRotate(cur->right);
				cur = leftRotate(cur);
				cur->right = maintain(cur->right);
				cur->left = maintain(cur->left);
				cur = maintain(cur);
			}
			return cur;
		}

		SBTNode *findLastIndex(int key)
		{
			SBTNode * pre = m_root;
			SBTNode * cur = m_root;
			while (cur != nullptr)
			{
				pre = cur;
				if (cur->key == key)
				{
					break;
				}
				else if (cur->key > key)
				{
					cur = cur->left;
				}
				else// cur->key< key
				{
					cur = cur->right;
				}
			}
			return pre;
		}
		// find some node->key >= key
		SBTNode * findLastNoSmallIndex(int key)
		{
			SBTNode * ans = nullptr;
			SBTNode * cur = m_root;
			while (cur != nullptr)
			{	
				if (cur->key == key)
				{
					ans = cur;
					break;
				}
				else if (cur->key > key)
				{
					ans = cur;
					cur = cur->left;
				}
				else // cur->key < key
				{
					cur = cur->right;
				}
			}
			return ans;
		}	
		//find some node->key <= key
		SBTNode * findLastNoBigIndex(int key)
		{
			SBTNode * ans = nullptr;
			SBTNode * cur = m_root;
			while (cur != nullptr)
			{
				if (cur->key == key)
				{
					ans = cur;
					break;
				}
				else if (cur->key > key)
				{
					cur = cur->left;
				}
				else // cur->key < key
				{
					ans = cur;
					cur = cur->right;
				}
			}
			return ans;
		}

		SBTNode * add(SBTNode * cur, int K, int V)
		{
			if (cur == nullptr)
			{
				return new SBTNode(K, V);
			}
			cur->size++;
			if (cur->key > K)
			{
				cur->left = add(cur->left, K, V);
			}
			else if (cur->key < K)
			{
				cur->right = add(cur->right, K, V);
			}
			cur = maintain(cur);
			return cur;
		}

		SBTNode * deleteNode(SBTNode * cur, int K)
		{
			if (cur == nullptr)
			{
				return nullptr;
			}
			cur->size--;
			if (cur->key < K)
			{
				cur->right = deleteNode(cur->right, K);
			}
			else if (cur->key > K)
			{
				cur->left = deleteNode(cur->left, K);
			}
			else // cur->key == K
			{
				if (cur->left == nullptr && cur->right == nullptr)
				{
					delete cur;
					cur = nullptr;
				}
				else if (cur->left == nullptr && cur->right != nullptr)
				{
					SBTNode * right = cur->right;
					cur->right = nullptr;
					delete cur;
					cur = right;
				}
				else if (cur->left != nullptr && cur->right == nullptr)
				{
					SBTNode * left = cur->left;
					cur->left = nullptr;
					delete cur;
					cur = left;
				}
				else // cur->left != nullptr && 
					//	cur->right != nullptr
				{
					SBTNode * succ = cur->right;
					SBTNode * pre = nullptr;
					succ->size--;
					while (succ->left != nullptr)
					{
						pre = succ;
						succ = succ->left;
						succ->size--;
					}
					if (pre != nullptr)
					{
						pre->left = succ->right;
					}
					else
					{
						cur->right = succ->right;
					}
					cur->key = succ->key;
					cur->value = succ->value;
					succ->right = nullptr;
					delete succ;
				}
				
			}
			cur = maintain(cur);
			return cur;
		}

		SBTNode* getIndex(SBTNode* cur, int kth) {
			if (cur == nullptr)
			{	
				return nullptr;
			}
			if (kth == nodeSize(cur->left) + 1)
			{
				return cur;
			}
			else if (kth <= nodeSize(cur->left))
			{
				return getIndex(cur->left, kth);
			}
			else 
			{
				return getIndex(cur->right, kth - nodeSize(cur->left) - 1);
			}
		}

		int size() {
			return m_root == nullptr ? 0 : m_root->size;
		}

		bool containsKey(int key)
		{
			SBTNode* find = findLastIndex(key);
			if (find == nullptr) {
				return false;
			}
			return find->key == key;
		}

		void put(int key, int value)
		{
			SBTNode* find = findLastIndex(key);
			bool node_is_exist;
			if (find == nullptr)
			{
				node_is_exist = false;
			}
			else
			{
				node_is_exist = (find->key == key);
			}
			if (true == node_is_exist)
			{
				find->value = value;
			}
			else
			{
				m_root = add(m_root, key, value);
			}
		}

		void remove(int key)
		{
			SBTNode* find = findLastIndex(key);
			bool node_is_exist;
			if (find == nullptr)
			{
				node_is_exist = false;
			}
			else
			{
				node_is_exist = (find->key == key);
			}
			if (node_is_exist == true)
			{
				m_root = deleteNode(m_root, key);
			}
		}
		int getIndexKey(int index)
		{
			SBTNode * node = getIndex(m_root, index + 1);
			if (node == nullptr)
			{
				return 0;
			}
			return node->key;
		}

		int getIndexValue(int index)
		{
			SBTNode * node = getIndex(m_root, index + 1);
			if (node == nullptr)
			{
				return 0;
			}
			return node->value;
		}

		int get(int key)
		{
			SBTNode* find = findLastIndex(key);
			bool node_is_exist;
			if (find == nullptr)
			{
				node_is_exist = false;
			}
			else
			{
				node_is_exist = (find->key == key);
			}
			if (false == node_is_exist)
			{
				return 0;
			}
			return find->value;
		}

		int firstKey() {
			SBTNode* cur = m_root;
			SBTNode* ans = nullptr;
			while (cur != nullptr)
			{
				ans = cur;
				cur = cur->left;
			}
			if (ans == nullptr)
			{
				return 0;
			}
			return ans->key;
		}

		int lastKey() {
			if (m_root == nullptr)
			{
				return 0;
			}
			SBTNode* cur = m_root;
			while (cur->right != nullptr)
			{
				cur = cur->right;
			}
			return cur->key;
		}

		int floorKey(int key)
		{
			SBTNode * find = findLastNoBigIndex(key);
			if (find == nullptr)
			{
				return 0;
			}
			return find->key;
		}
		// 
		int ceilingKey(int key)
		{
			SBTNode * find = findLastNoSmallIndex(key);
			if (find == nullptr)
			{
				return 0;
			}
			return find->key;
		}


		void printsingleNode(SBTNode * node)
		{
			cout << "[ k:" << node->key << " v:" << node->value << " s:" << node->size << "] ";
		}

		void printLineEnd()
		{
			cout << endl;
		}


		void print()
		{
			std::queue<SBTNode*> q;
			std::queue<SBTNode*> next;
			q.push(m_root);
			while (!q.empty())
			{

				while (!q.empty())
				{
					SBTNode * cur = q.front();
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


void test_Code01_SizeBalancedTreeMap(){
	using SizeBalancedTree = Code01_SizeBalancedTreeMap::SizeBalancedTree;
	SizeBalancedTree sbt;
	cout << "test_Code01_SizeBalancedTreeMap begin" << endl;
	sbt.put(1, 1);
	sbt.print();
	sbt.put(2, 2);
	sbt.print();
	sbt.put(3, 3);
	sbt.print();
	sbt.put(4, 4);
	sbt.print();
	sbt.put(5, 5);
	sbt.print();
	sbt.put(6, 6);
	sbt.print();
	sbt.put(7, 7);
	sbt.print();
	sbt.put(8, 8);
	sbt.print();
	sbt.put(9, 9);
	sbt.print();
	sbt.put(10, 10);
	sbt.print();
	sbt.remove(5);
	sbt.print();
	sbt.remove(8);
	sbt.print();
	sbt.remove(3);
	sbt.print();
	sbt.remove(6);
	sbt.print();

	for (int i = 0; i < sbt.size(); i++) {
		cout << sbt.getIndexKey(i) << "," << sbt.getIndexValue(i) << endl;;
	}
	cout << "test_Code01_SizeBalancedTreeMap end" << endl;
}

#endif 