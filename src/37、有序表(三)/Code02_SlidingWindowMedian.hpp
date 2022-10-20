#pragma once
#ifndef Code02_SlidingWindowMedian_HPP
#define Code02_SlidingWindowMedian_HPP
#include <iostream>
#include <map>
#include "utility_func.hpp"
using namespace std;

namespace Code02_SlidingWindowMedian {

	struct SBTreeNode {

		int key = 0;
		int size = 0; // sb tree 调节平衡用
		
		int all = 0;  //路径上的总数
		SBTreeNode * left = nullptr;
		SBTreeNode * right = nullptr;
		bool release_child = false;
		SBTreeNode(int k) {
			key = k;
			size = 1;
			all = 1;
		}
		void release_child_after_delete(bool release)
		{
			release_child = release;
		}
		~SBTreeNode() {
			if (release_child == true)
			{
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
		}
	};
	// 目标是中位数
	class SBTreeSet {
		SBTreeNode* m_root = nullptr;
		// 记录数字有多少个
		map<int, int> m_nums;
		int m_size = 0;
	public:
		SBTreeSet() {}
		~SBTreeSet() {
			if (m_root != nullptr)
			{
				m_root->release_child_after_delete(true);
				delete m_root;
				m_root = nullptr;
			}
		}

		
		int node_size_from_child(SBTreeNode * cur) {
			if (cur == nullptr)
			{
				return 0;
			}
			int leftsize = cur->left != nullptr ? cur->left->size : 0;
			int rightsize = cur->right != nullptr ? cur->right->size : 0;
			// 注意 这里没有 +1
			return leftsize + rightsize;
		}

		int node_size_except_child(SBTreeNode * cur)
		{
			if (cur == nullptr)
			{
				return 0;
			}
			return cur->size - node_size_from_child(cur);
		}


		int node_all_from_child(SBTreeNode * cur)
		{
			if (cur == nullptr)
			{
				return 0;
			}
			int leftsize = cur->left != nullptr ? cur->left->all : 0;
			int rightsize = cur->right != nullptr ? cur->right->all : 0;
			// 注意 这里没有 +1
			return leftsize + rightsize;
		}

		int node_all_except_child(SBTreeNode * cur)
		{
			if (cur == nullptr)
			{
				return 0;
			}
			return cur->all - node_all_from_child(cur);
		}

		SBTreeNode * leftRotate(SBTreeNode * cur)
		{
			// compute all
			//int cur_all = cur->all;
			int cur_same = node_all_except_child(cur);

			SBTreeNode * right = cur->right;
			cur->right = right->left;
			right->left = cur;

			right->all = cur->all;
			cur->all = cur_same + node_all_from_child(cur);

			cur->size = node_size_from_child(cur) + 1;
			right->size = node_size_from_child(right) + 1;

			return right;
		}

		SBTreeNode * rightRotate(SBTreeNode * cur)
		{
			// compute all
			//int cur_all = cur->all;
			int cur_same = node_all_except_child(cur);

			SBTreeNode * left = cur->left;
			cur->left = left->right;
			left->right = cur;

			left->all = cur->all;
			cur->all = cur_same + node_all_from_child(cur);

			cur->size = node_size_from_child(cur) + 1;
			left->size = node_size_from_child(left) + 1;

			return left;
		}

		int pure_node_size(SBTreeNode * node)
		{
			if (node == nullptr)
			{
				return 0;
			}
			return node->size;
		}

		SBTreeNode * maintain(SBTreeNode * cur) {

			if (cur == nullptr)
			{
				return nullptr;
			}
			int leftsize = pure_node_size(cur->left);
			int leftleftsize = cur->left == nullptr ? 0 : pure_node_size(cur->left->left);
			int leftrightsize = cur->left == nullptr ? 0 : pure_node_size(cur->left->right);
			int rightsize = pure_node_size(cur->right);
			int rightleftsize = cur->right == nullptr ? 0 : pure_node_size(cur->right->left);
			int rightrightsize = cur->right == nullptr ? 0 : pure_node_size(cur->right->right);
			// LL violation
			if (leftleftsize > rightsize)
			{
				cur = rightRotate(cur);
				cur->right = maintain(cur->right);
				cur = maintain(cur);
			}
			else if (leftrightsize > rightsize)
			{
				cur->left = leftRotate(cur->left);
				cur = rightRotate(cur);
				cur->left = maintain(cur->left);
				cur->right = maintain(cur->right);
				cur = maintain(cur);
			}
			else if (rightleftsize > leftsize)
			{
				cur->right = rightRotate(cur->right);
				cur = leftRotate(cur);
				cur->right = maintain(cur->right);
				cur->left = maintain(cur->left);
				cur = maintain(cur);
			}
			else if (rightrightsize > leftsize)
			{
				cur = leftRotate(cur);
				cur->left = maintain(cur->left);
				cur = maintain(cur);
			}
			return cur;
		}


		SBTreeNode * add(SBTreeNode * cur, int key, bool contains)
		{
			if (cur == nullptr)
			{
				return new SBTreeNode(key);
			}
			// cur ！= nullptr
			cur->all++;
			if (contains == false)
			{
				cur->size++;
			}
			if (cur->key < key)
			{
				cur->right = add(cur->right, key, contains);
			}
			else if (cur->key > key)
			{
				cur->left = add(cur->left, key, contains);
			}
			else // cur->key == key
			{
				
			}
			return  maintain(cur);
		}

		SBTreeNode * del(SBTreeNode * cur, int key, bool need_drop_node_from_tree)
		{
			if (cur == nullptr)
			{
				return nullptr;
			}
			//  cur != nullptr
			cur->all--;
			if (need_drop_node_from_tree == true)
			{
				cur->size--;
			}
			if (cur->key < key)
			{
				cur->right = del(cur->right, key, need_drop_node_from_tree);
			}
			else if (cur->key > key)
			{
				cur->left = del(cur->left, key, need_drop_node_from_tree);
			}
			else // cur->key == key
			{
				if (need_drop_node_from_tree == true)
				{

					if (cur->left == nullptr && cur->right == nullptr)
					{
						delete cur;
						cur = nullptr;
					}
					else if (cur->left != nullptr && cur->right == nullptr)
					{
						SBTreeNode * left = cur->left;
						delete cur;
						cur = cur->left;
					}
					else if (cur->left == nullptr && cur->right != nullptr)
					{
						SBTreeNode * right = cur->right;
						delete cur;
						cur = cur->right;
					}
					else {
						// find succesor
						SBTreeNode * suc = cur->right;
						SBTreeNode * pre = cur;
						suc->size--;
						suc->all--;
						while (suc->left != nullptr)
						{
							pre = suc;
							suc = suc->left;
							suc->size--;
							suc->all--;
						}
						// give suc right child to pre
						if (pre != cur)
						{
							pre->left = suc->right;
							suc->right = cur->right;
						}
						suc->left = cur->left;
						//int suc_self = suc->all - node_all_from_child(suc);
						suc->size = node_size_from_child(suc) + 1;
						suc->all = cur->all;

						delete cur;
						cur = suc;
					}
				}
			}
			// cur = maintain(cur);
			return cur;
		}

		bool contain(int key)
		{
			if (m_root == nullptr)
			{
				return false;
			}
			SBTreeNode * cur = m_root;
			while (cur != nullptr)
			{
				if (cur->key == key)
				{
					return true;
				}
				else if (cur->key < key)
				{
					cur = cur->right;
				}
				else if (cur->key > key)
				{
					cur = cur->left;
				}
			}
			return false;
		}


		void put(int key)
		{
			bool node_is_exist = contain(key);
			m_root = add(m_root, key, node_is_exist);
			m_nums[key]++;
		}

		void remove(int key)
		{
			bool node_is_exist = false;
			bool need_drop_node_from_tree = false;
			auto find = m_nums.find(key);
			if (find != m_nums.end())
			{
				node_is_exist = true;
				if (find->second <= 1)
				{
					need_drop_node_from_tree = true;
					m_nums.erase(key);
				}
				else
				{
					find->second--;
				}
			}
			m_root = del(m_root, key, need_drop_node_from_tree);
		}

		int getIndex(SBTreeNode* cur, int index)
		{
			int leftall_count = cur->left == nullptr ? 0 : cur->left->all;
			int rightall_count = cur->right == nullptr ? 0 : cur->right->all;
			int cur_all_count = cur->all - leftall_count - rightall_count;
			if (index + 1 <= leftall_count)
			{
				return getIndex(cur->left, index);
			}
			// 
			else if (index + 1 > leftall_count && index + 1 <= leftall_count + cur_all_count)
			{
				return cur->key;
			}
			else if (index + 1 > leftall_count+cur_all_count)
			{
				return getIndex(cur->right, index - leftall_count - cur_all_count);
			}
				
		}

		int getIndexKey(int index)
		{
			if (index < 0 || index >= all_node_count())
			{
				return 0;
			}
			return getIndex(m_root, index);
		}

		int all_node_count()
		{
			if (m_root != nullptr)
			{
				return m_root->all;
			}
			return 0;
		}
	};

	vector<double> medianSlidingWindow(vector<int> & nums, int k) {
		SBTreeSet sbt;
		for (int i = 0; i < k-1; i++)
		{
			sbt.put(nums[i]);
		}
		int N = nums.size();
		vector<double> ans(N - k + 1);
		for (int i = k-1,j=0; i < N; i++,j++)
		{
			sbt.put(nums[i]);
			if (k % 2 == 0)
			{
				int midloindex = k / 2 - 1;
				int midhiindex = k / 2;

				int midlo = sbt.getIndexKey(midloindex);
				int midhi = sbt.getIndexKey(midhiindex);
				ans[j] = (double)(midlo + midhi) / 2;

			}
			else
			{
				int midindex = k / 2;
				int mid = sbt.getIndexKey(midindex);
				ans[j] = mid;
			}
			sbt.remove(nums[j]);
		}
		return ans;
	}


}

void test_Code02_SlidingWindowMedian() {

	vector<int> nums{2,3,3,3,4,4,6,4,5,5,5};
	int k = 4;
	vector<double> ans = Code02_SlidingWindowMedian::medianSlidingWindow(nums, k);
	print(ans);
}

#endif