#pragma once
#ifndef Code03_AddRemoveGetIndexGreat_HPP
#define Code03_AddRemoveGetIndexGreat_HPP
#include <vector>
#include "utility_func.hpp"
#include "stop_watch.hpp"
namespace Code03_AddRemoveGetIndexGreat {

	struct SBTNode {
		// int key
		int value;
		int size;
		SBTNode* left = nullptr;
		SBTNode* right = nullptr;
		bool release_child_after_delete = true;
		void release_child(bool option)
		{
			release_child_after_delete = option;
		}
		SBTNode(int v) {
			value = v;
			size = 1;
		}
		~SBTNode() {
			if (true == release_child_after_delete)
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

	class SbtList {
		SBTNode* m_root;
	public:
		SbtList() {}
		~SbtList()
		{
			if (m_root != nullptr)
			{
				delete m_root;
				m_root = nullptr;
			}
		}

		void reset() {
			if (m_root != nullptr)
			{
				delete m_root;
				m_root = nullptr;
			}
		}


		int node_size_from_child(SBTNode * cur)
		{
			if (cur == nullptr)
			{
				return 0;
			}
			int leftsize = cur->left == nullptr ? 0 : cur->left->size;
			int rightsize = cur->right == nullptr ? 0 : cur->right->size;
			return leftsize + rightsize;
		}


		SBTNode * leftRotate(SBTNode * cur)
		{
			SBTNode * right = cur->right;
			cur->right = right->left;
			right->left = cur;

			// recompute size
			cur->size = node_size_from_child(cur) + 1;
			right->size = node_size_from_child(right) + 1;

			return right;
		}

		SBTNode * rightRotate(SBTNode * cur)
		{
			SBTNode * left = cur->left;
			cur->left = left->right;
			left->right = cur;

			// recompute size
			cur->size = node_size_from_child(cur) + 1;
			left->size = node_size_from_child(left) + 1;

			return left;
		}

		int get_pure_node_size(SBTNode * cur) {
			if (cur == nullptr)
			{
				return 0;
			}
			return cur->size;
		}

		SBTNode * maintain(SBTNode * cur)
		{
			if (cur == nullptr)
			{
				return cur;
			}
			int leftsize = get_pure_node_size(cur->left);
			int leftleftsize = (cur->left == nullptr ? 0 : get_pure_node_size(cur->left->left));
			int leftrightsize = (cur->left == nullptr ? 0 : get_pure_node_size(cur->left->right));
			int rightsize = get_pure_node_size(cur->right);
			int rightleftsize = (cur->right == nullptr ? 0 : get_pure_node_size(cur->right->left));
			int rightrightsize = (cur->right == nullptr ? 0 : get_pure_node_size(cur->right->right));
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


		SBTNode* add(SBTNode* cur, int index, SBTNode * newNode)
		{
			if (cur == nullptr)
			{
				return newNode;
			}
			// cur != nullptr;
			cur->size++;
			int leftAndHead = get_pure_node_size(cur->left) + 1;
			if (index < leftAndHead)
			{
				cur->left = add(cur->left, index, newNode);
			}
			else if (index >= leftAndHead)
			{
				cur->right = add(cur->right, index - leftAndHead, newNode);
			}
			return maintain(cur);
		}

		SBTNode* remove(SBTNode* cur, int index)
		{
			if (cur == nullptr)
			{
				return nullptr;
			}
			cur->size--;
			int rootIndex = get_pure_node_size(cur->left);
			if (index != rootIndex)
			{
				if (index < rootIndex)
				{
					cur->left = remove(cur->left, index);
				}
				else // index >rootindex
				{
					cur->right = remove(cur->right, index - rootIndex - 1);
				}
				return cur;
			}
			// index == rootindex
			if (cur->left == nullptr && cur->right == nullptr)
			{
				cur->release_child(false);
				delete cur;
				cur = nullptr;
			}
			else if (cur->left != nullptr && cur->right == nullptr)
			{
				SBTNode* left = cur->left;
				cur->release_child(false);
				delete cur;
				cur = left;
			}
			else if (cur->left == nullptr && cur->right != nullptr)
			{
				SBTNode * right = cur->right;
				cur->release_child(false);
				delete cur;
				cur = right;
			}
			else {
				SBTNode * suc = cur->right;
				SBTNode * pre = cur;
				suc->size--;
				while (suc->left != nullptr)
				{
					pre = suc;
					suc = suc->left;
					suc->size--;
				}
				if (pre != cur)
				{
					pre->left = suc->right;
					suc->right = cur->right;
				}
				suc->left = cur->left;

				suc->size = cur->size;
				cur->release_child(false);
				delete cur;
				cur = suc;
			}
			return cur;
		}

		SBTNode * get(SBTNode * cur, int index)
		{
			if (cur == nullptr)
			{
				return cur;
			}
			int leftsize = get_pure_node_size(cur->left);
			int curIndex = leftsize;
			if (index == curIndex)
			{
				return cur;
			}
			else if (index < curIndex)
			{
				return get(cur->left, index);
			}
			else if (index > curIndex)
			{
				return get(cur->right, index - curIndex - 1);
			}

		}

		void add(int index, int value)
		{
			SBTNode * newNode = new SBTNode(value);
			if (m_root == nullptr)
			{
				m_root = newNode;
			}
			else if(index <= m_root->size && index >=0)
			{
				m_root = add(m_root, index, newNode);
			}
		}

		int get(int index)
		{
			SBTNode * ans = get(m_root, index);
			if (ans == nullptr)
			{
				return 0;
			}
			return ans->value;
		}

		void remove(int index)
		{
			if (index >= 0 && index < total_size()) {
				m_root = remove(m_root, index);
			}
		}

		int total_size() {
			if (m_root == nullptr)
			{
				return 0;
			}
			return m_root->size;
		}

	};
}

void test_Code03_AddRemoveGetIndexGreat() {
	
	int test = 100;
	int max = 20;
	bool pass = true;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);

	vector<int> arr;
	Code03_AddRemoveGetIndexGreat::SbtList sbt;
	cout << "test_Code03_AddRemoveGetIndexGreat begin" << endl;
	for (int i = 0; i < test; i++)
	{
		if (arr.size() != sbt.total_size())
		{
			pass = false;
			break;
		}
		if (arr.size() > 1 && dist(mt) < 0.5)
		{
			int removeIndex = (int)(dist(mt) * arr.size());
			arr.erase(arr.begin() + removeIndex);
			sbt.remove(removeIndex);
		}
		else {
			int randomIndex = (int)(dist(mt) * (arr.size() + 1));
			int randomValue = (int)(dist(mt) * (max + 1));
			arr.insert(arr.begin() + randomIndex, randomValue);
			sbt.add(randomIndex, randomValue);
		}
		
	}
	for (int i = 0; i < arr.size(); i++) {
		int num1 = arr[i];
		int num2 = sbt.get(i);
		if (num1 != num2)
		{
			cout << "arr[" << i << "] = " << num1 << endl;
			cout << "sbt.get(" << i << ") = " << num2 << endl;
			pass = false;
			break;
		}
	}
	
	// perf test
	stop_watch st;
	test = 500000;
	arr.clear();
	sbt.reset();
	st.start();
	for (int i = 0; i < test; i++) {
		int randomIndex = (int)(dist(mt) * (arr.size() + 1));
		int randomValue = (int)(dist(mt) * (max + 1));
		arr.insert(arr.begin() + randomIndex, randomValue);
	}
	st.stop();
	cout << "std::vector insert elapse:" << st.elapsed_ms() <<"ms"<< endl;
	st.start();
	for (int i = 0; i < test; i++) {
		int randomIndex = (int)(dist(mt) * (i + 1));
		arr[i];
	}
	st.stop();
	cout << "std::vector read elapse:" << st.elapsed_ms() << "ms" << endl;
	st.start();
	for (int i = 0; i < test; i++) {
		int randomIndex = (int)(dist(mt) * arr.size());
		arr.erase(arr.begin() + randomIndex);
	}
	st.stop();
	cout << "std::vector erase elapse:" << st.elapsed_ms() << "ms" << endl;
	st.start();
	for (int i = 0; i < test; i++) {
		int randomIndex = (int)(dist(mt) * (sbt.total_size() + 1));
		int randomValue = (int)(dist(mt) * (max + 1));
		sbt.add(randomIndex, randomValue);
	}
	st.stop();
	cout << "sbtlist insert elapse:" << st.elapsed_ms() << "ms" << endl;

	st.start();
	for (int i = 0; i < test; i++) {
		int randomIndex = (int)(dist(mt) * (sbt.total_size() + 1));
		sbt.get(randomIndex);
	}
	st.stop();
	cout << "sbtlist get elapse:" << st.elapsed_ms() << "ms" << endl;

	st.start();
	for (int i = 0; i < test; i++) {
		int randomIndex = (int)(dist(mt) * sbt.total_size());
		sbt.remove(randomIndex);
	}
	st.stop();
	cout << "sbtlist erase elapse:" << st.elapsed_ms() << "ms" << endl;

	cout << "test_Code03_AddRemoveGetIndexGreat end" << endl;
}
/*   // Ä³´ÎÊä³ö
	test_Code03_AddRemoveGetIndexGreat begin
	std::vector insert elapse : 4268.26ms
	std::vector read elapse : 25.016ms
	std::vector erase elapse : 4555.64ms
	sbtlist insert elapse : 522.507ms
	sbtlist get elapse : 310.743ms
	sbtlist erase elapse : 301.387ms
	test_Code03_AddRemoveGetIndexGreat end
*/
#endif