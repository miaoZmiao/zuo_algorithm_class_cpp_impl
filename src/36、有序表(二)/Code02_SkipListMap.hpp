#pragma once
#ifndef Code02_SkipListMap_HPP
#define Code02_SkipListMap_HPP
#include <iostream>
#include <vector>
#include "utility_func.hpp"
using namespace std;
namespace Code02_SkipListMap {

	struct SkipListNode {

		int key;
		int value;
		vector<SkipListNode*> nexts;

		SkipListNode(int k,int v) {
			key = k;
			value = v;
		}

		bool operator==(const SkipListNode & other) const {
			return key == other.key;
		}

		bool operator < (const SkipListNode& other) const {
			return key < other.key;
		}
		bool operator>(const SkipListNode& other) const {
			return key > other.key;
		}
	};

	class SkipListMap {

		double m_probability = 0.5;
		SkipListNode* m_head = nullptr;
		size_t m_size = 0;
		int m_maxlevel = 0;

		std::random_device m_rd;
		std::mt19937 m_mt;
		std::uniform_real_distribution<> m_dist;

	public:
		SkipListMap() {
			//m_head;
			m_head = new SkipListNode(0,0);
			m_head->nexts.push_back(nullptr);
			
			m_mt.seed(m_rd());

			std::uniform_real_distribution<>::param_type p(0.0, 1.0);
			m_dist.param(p);
			vector<double> v;
			/*for (int i = 0; i < 10; i++)
			{
				v.push_back(m_dist(m_mt));
			}
			print(v);*/
		}

		~SkipListMap() {
			if (m_head->nexts[0] != nullptr)
			{
				SkipListNode * cur = m_head;
				SkipListNode* next = nullptr;

				while (cur->nexts[0] != nullptr)
				{
					next = cur->nexts[0];
					delete cur;
					cur = next;
				}
			}
			delete m_head;
			m_head = nullptr;
		}

		double get_random()
		{
			return  m_dist(m_mt);
		}


		SkipListNode * mostRightLessNodeInTree(int key)
		{
			int level = m_maxlevel;
			SkipListNode * cur = m_head;
			while (level >= 0)
			{
				cur = mostRightLessNodeInLevel(cur, key, level);
				level--;
			}
			return cur;
		}

		SkipListNode * mostRightLessNodeInLevel(SkipListNode * cur, int key, int level)
		{
			SkipListNode * next = cur->nexts[level];
			while (next != nullptr && next->key < key)
			{
				cur = next;
				next = next->nexts[level];
			}
			return cur;
		}

		bool containsKey(int key)
		{
			SkipListNode*  find = mostRightLessNodeInTree(key);
			SkipListNode* next = find->nexts[0];
			if (next == nullptr)
			{
				return false;
			}
			return next->key == key;
		}

		void put(int key, int value)
		{
			SkipListNode*  find = mostRightLessNodeInTree(key);
			SkipListNode * next = find;
			bool node_is_exist = false;
			if (next == nullptr)
			{
				node_is_exist = false;
			}
			else if(next->key == key)
			{
				node_is_exist = true;
			}
			if (true == node_is_exist)
			{
				next->value = value;
			}
			else // node does not exist
			{
				m_size++;
				int newLevel = 0;
				while (get_random() < m_probability)
				{
					newLevel++;
				}
				// newNodeLevel
				while (newLevel > m_maxlevel) {
					m_head->nexts.push_back(nullptr);
					m_maxlevel++;
				}
				SkipListNode * newNode = new SkipListNode(key, value);
				for (int i = 0; i <= newLevel; i++)
				{
					newNode->nexts.push_back(nullptr);
				}
				int level = m_maxlevel;
				SkipListNode* pre = m_head;
				while (level >= 0)
				{
					pre = mostRightLessNodeInLevel(pre, key, level);
					if (level <= newLevel)
					{
						newNode->nexts[level] = pre->nexts[level];
						pre->nexts[level] = newNode;
					}
					level--;
				}
			}
		}

		int get(int key)
		{
			SkipListNode * find = mostRightLessNodeInTree(key);
			SkipListNode * next = find->nexts[0];
			if (next == nullptr)
			{
				return 0;
			}
			if (next->key != key)
			{
				return 0;
			}
			return next->value;
		}
		void remove(int key)
		{
			if (true == containsKey(key))
			{
				m_size--;
				int level = m_maxlevel;
				SkipListNode * pre = m_head;
				while (level >= 0)
				{
					pre = mostRightLessNodeInLevel(pre, key, level);
					SkipListNode * next = pre->nexts[level];
					if (next != nullptr && next->key == key)
					{
						pre->nexts[level] = next->nexts[level];
					}

					if (level != 0 && pre == m_head && pre->nexts[level] == nullptr)
					{
						m_head->nexts.pop_back();
						m_maxlevel--;
					}
					level--;
				}
			}
		}

		int firstKey() {

			SkipListNode * first = m_head->nexts[0];
			if (nullptr != first)
			{
				return 0;
			}
			return first->key;
		}

		int lastKey() {
			SkipListNode * cur = m_head;
			int level = m_maxlevel;
			while (level >= 0)
			{
				while (cur->nexts[level] != nullptr)
				{
					cur = cur->nexts[level];
				}
				level--;
			}
			if (cur == m_head)
			{
				return 0;
			}
			return cur->key;
		}
		int ceilingKey(int key)
		{
			SkipListNode * pre = mostRightLessNodeInTree(key);
			SkipListNode * next = pre->nexts[0];
			if (next == nullptr)
			{
				return 0;
			}

			return next->key;
		}

		int floorKey(int key)
		{
			SkipListNode * pre = mostRightLessNodeInTree(key);
			SkipListNode * next = pre->nexts[0];
			if (next == nullptr)
			{
				return pre->key;
			}
			else {

				if (next->key == key)
				{
					return key;
				}
				else if (next->key > key)
				{
					return pre->key;
				}
			}
		}

		int size() {
			return m_size;
		}

		void printAll() {
			//int level = m_maxlevel;
			for (int level = m_maxlevel; level >= 0; level--)
			{
				SkipListNode * cur = m_head->nexts[level];
				while (cur != nullptr)
				{
					cout << "[k:" << cur->key << " v:" << cur->value << " ]";
					cur = cur->nexts[level];
				}
				cout << endl;
			}
			cout << endl<<endl;
		}
	};
}



void test_Code02_SkipListMap() {
	using SKL = Code02_SkipListMap::SkipListMap;
	SKL skl;
	cout << "test_Code02_SkipListMap begin" << endl;
	skl.put(1, 1);
	skl.printAll();
	skl.put(2, 2);
	skl.put(3, 3);
	skl.put(4, 4);
	skl.put(5, 5);
	skl.printAll();
	skl.put(6, 6);
	skl.put(7, 7);
	skl.put(8, 8);
	skl.put(9, 9);
	skl.put(10, 10);
	skl.printAll();
	
	skl.remove(6);
	skl.printAll();
	skl.remove(8);
	skl.printAll();
	skl.remove(4);
	skl.printAll();
	skl.remove(3);
	skl.printAll();

	cout << "test_Code02_SkipListMap end" << endl;
}
#endif