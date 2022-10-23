#pragma once
#ifndef Code01_CountofRangeSum_HPP
#define Code01_CountofRangeSum_HPP
#include <iostream>
#include "utility_func.hpp"
using namespace std;

namespace Code01_CountofRangeSum {



	int countWhileMergeSort(vector<long>& sums, int start, int end, int lower, int upper)
	{
		if (end - start <= 1)
			return 0;
		int mid = (start + end) / 2;

		int count = countWhileMergeSort(sums, start, mid, lower, upper)
			+ countWhileMergeSort(sums, mid, end, lower, upper);
		int j = mid, k = mid, t = mid;

		vector<long> cache(end - start, 0);
		for (int i = start, r = 0; i < mid; ++i, ++r) {
			while (k < end && sums[k] - sums[i] < lower)
				k++;
			while (j < end && sums[j] - sums[i] <= upper)
				j++;
			while (t < end && sums[t] < sums[i])
				cache[r++] = sums[t++];
			cache[r] = sums[i];
			count += j - k;
		}
		for (int i = 0, sum_i=start; i < t - start; i++,sum_i++)
		{
			sums[sum_i] = cache[i];
		}
		return count;
	}

	int countRangeSum1(vector<int> nums, int lower, int upper) {
		int n = nums.size();
		vector<long> sums(n + 1, 0);
		for (int i = 0; i < n; ++i)
			sums[i + 1] = sums[i] + nums[i];
		return countWhileMergeSort(sums, 0, n + 1, lower, upper);
	}

	struct SBTreeNode {

		int key = 0;
		int value = 0;
		int size = 0;
		int all = 0;
		SBTreeNode * left = nullptr;
		SBTreeNode * right = nullptr;
		bool release_children = false;
		void release_child(bool release = false)
		{
			release_children = release;
		}

		SBTreeNode(int k, int v) {
			key = k;
			value = v;
			size = 1;
			all = 1;
		}
		~SBTreeNode() {
			if (release_children == true) {
				if (left == nullptr)
				{
					delete left;
					left = nullptr;
				}
				if(right == nullptr)
				{ 
					delete right;
					right = nullptr;
				}
			}
		}
	};

	class SBTree {

		SBTreeNode * m_root = nullptr;
		set<int> m_nums;
	public:
		SBTree() {}
		~SBTree() {
			if (m_root != nullptr)
			{
				delete m_root;
				m_root = nullptr;
			}
		}

		int size_recompute(SBTreeNode * cur)
		{
			int leftsize = (cur->left == nullptr ? 0 : cur->left->size);
			int rightsize = (cur->right == nullptr ? 0 : cur->right->size);
			return leftsize + rightsize + 1;
		}
		SBTreeNode * leftRotate(SBTreeNode * cur)
		{
			// count all 
			int left_all = cur->left == nullptr ? 0 : cur->left->all;
			int right_all = cur->right == nullptr ? 0 : cur->right->all;
			int same = cur->all - left_all - right_all;
			
			SBTreeNode * right = cur->right;
			cur->right = right->left;
			right->left = cur;
			cur->size = size_recompute(cur);
			right->size = size_recompute(right);

			right->all = cur->all;
			// count all
			left_all = cur->left == nullptr ? 0 : cur->left->all;
			right_all = cur->right == nullptr ? 0 : cur->right->all;
			cur->all = left_all + right_all + same;
			return right;
		}

		SBTreeNode * rightRotate(SBTreeNode * cur)
		{
			// count
			int left_all = cur->left == nullptr ? 0 : cur->left->all;
			int right_all = cur->right == nullptr ? 0 : cur->right->all;
			int same = cur->all - left_all - right_all;

			SBTreeNode * left = cur->left;
			cur->left = left->right;
			left->right = cur;
			cur->size = size_recompute(cur);
			left->size = size_recompute(left);

			left->all = cur->all;

			// count all 
			left_all = cur->left == nullptr ? 0 : cur->left->all;
			right_all = cur->right == nullptr ? 0 : cur->right->all;
			cur->all = left_all + right_all + same;
			return left;
		}

		int get_size(SBTreeNode * node)
		{
			return node == nullptr ? 0 : node->size;
		}

		SBTreeNode * maintain(SBTreeNode * cur)
		{
			if (cur == nullptr)
			{
				return cur;
			}
			int leftsize = get_size(cur->left);
			int leftleftsize = cur->left == nullptr ? 0 : get_size(cur->left->left);
			int leftrightsize = cur->left == nullptr ? 0 : get_size(cur->left->right);
			int rightsize = get_size(cur->right);
			int rightleftsize = cur->right == nullptr ? 0 : get_size(cur->right->left);
			int rightrightsize = cur->right == nullptr ? 0 : get_size(cur->right->right);
			// LL violation
			if (leftleftsize > rightsize)
			{
				cur = rightRotate(cur);
				cur->right = maintain(cur->right);
				cur = maintain(cur);
			}
			// LR violation
			else if (leftrightsize > rightsize)
			{
				cur->left = leftRotate(cur->left);
				cur = rightRotate(cur);
				cur->left = maintain(cur->left);
				cur->right = maintain(cur->right);
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
			// RR violation
			else if(rightrightsize > leftsize)
			{
				cur = leftRotate(cur);
				cur->left = maintain(cur->left);
				cur = maintain(cur);
			}
			return cur;
		}

		SBTreeNode * add(SBTreeNode * cur, int key, int value, bool contains)
		{
			if (nullptr == cur)
			{
				return new SBTreeNode(key, value);
			}
			else {
				
				cur->all++;
				if (contains == false)
				{
					cur->size++;
				}
				if (cur->key < key)
				{
					cur->right = add(cur->right, key, value, contains);
				}
				else if (cur->key > key)
				{
					cur->left = add(cur->left, key, value, contains);
				}
				else // cur->key == key
				{

				}
				return maintain(cur);
			}
			
		}
		void add(long sum) {
			bool sum_is_exist = false;
			if (m_nums.find(sum) != m_nums.end())
			{
				sum_is_exist = true;
			}
			m_root = add(m_root, sum, sum, sum_is_exist);
			m_nums.insert(sum);
		}
		long lessKeySize(long key) {
			
			int ans = 0;
			SBTreeNode * cur = m_root;
			while (cur != nullptr)
			{
				if (cur->key > key)
				{
					cur = cur->left;
				}
				else if (cur->key < key)
				{
					int right_all = cur->right == nullptr ? 0 : cur->right->all;
					ans += cur->all - right_all;
					cur = cur->right;
				}
				else // cur->key == key
				{
					//int right_all = cur->right == nullptr ? 0 : cur->right->all;
					int left_all = cur->left == nullptr ? 0 : cur->left->all;
					ans += left_all;
					break;
				}
			}
			return ans;
		}
		// if key = 7
		// find the number count that bigger than 7
		long moreKeySize(long key) {
			if (m_root == nullptr)
			{
				return 0;
			}
			int less_than_key_plus_1 = lessKeySize(key + 1);
			return m_root->all - less_than_key_plus_1;
		}
	};


	int countRangeSum2(vector<int>& nums, int lower, int upper)
	{
		SBTree sbt;
		sbt.add(0);
		long sum = 0;
		int count = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			sum += nums[i];
			long up = sum - lower+1;
			long low = sum - upper;
			int a = sbt.lessKeySize(up);
			int b = sbt.lessKeySize(low);
			count += a - b;
			sbt.add(sum);
		}
		return count;
	}


}

void test_Code01_CountofRangeSum() {

	cout << "test_Code01_CountofRangeSum begin" << endl;
	vector<int> arr{-2,5,-1};
	int lo = -2;
	int up = 2;
	int ans = Code01_CountofRangeSum::countRangeSum2(arr, lo, up);
	cout << "test_Code01_CountofRangeSum end" << endl;

}

#endif