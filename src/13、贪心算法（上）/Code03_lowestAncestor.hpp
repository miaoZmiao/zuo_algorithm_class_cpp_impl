#pragma once
#include "treeNode.hpp"
#include "scope_guard.h"
#include <unordered_map>
#include <unordered_set>
namespace Code03_lowestAncestor {

	class lowestAncestorA {
	public:
		Node * lowestAncestor1(Node * head, Node * o1, Node * o2) {
			if (head == nullptr) {
				return nullptr;
			}
			// key的父节点是value
			unordered_map<Node*, Node*> parentMap ;
			parentMap.insert({ head, nullptr });
			fillParentMap(head, parentMap);
			unordered_set<Node*> o1Set;
			Node * cur = o1;
			o1Set.insert(cur);
			while (parentMap[cur] != nullptr) {
				cur = parentMap[cur];
				o1Set.insert(cur);
			}
			cur = o2;
			while (!o1Set.count(cur)) {
				cur = parentMap[cur];
			}
			return cur;
		}

		void fillParentMap(Node * head, unordered_map<Node*, Node*> & parentMap) {
			if (head->left != nullptr) {
				parentMap.insert({ head->left, head });
				fillParentMap(head->left, parentMap);
			}
			if (head->right != nullptr) {
				parentMap.insert({ head->right, head });
				fillParentMap(head->right, parentMap);
			}
		}

		struct Info {
			bool findA;
			bool findB;
			Node * ans;

			Info(bool fA, bool fB, Node * an) {
				findA = fA;
				findB = fB;
				ans = an;
			}
		};

		Node * lowestAncestor2(Node * head, Node * a, Node * b) {
			return process(head, a, b).ans;
		}

	

		Info process(Node * x, Node * a, Node * b) {
			if (x == nullptr) {
				return  Info(false, false, nullptr);
			}
			Info leftInfo = process(x->left, a, b);
			Info rightInfo = process(x->right, a, b);
			bool findA = (x == a) || leftInfo.findA || rightInfo.findA;
			bool findB = (x == b) || leftInfo.findB || rightInfo.findB;
			Node * ans = nullptr;
			if (leftInfo.ans != nullptr) {
				ans = leftInfo.ans;
			}
			else if (rightInfo.ans != nullptr) {
				ans = rightInfo.ans;
			}
			else {
				if (findA && findB) {
					ans = x;
				}
			}
			return Info(findA, findB, ans);
		}

		// for test
		Node * pickRandomOne(Node * head) {
			if (head == nullptr) {
				return nullptr;
			}
			vector<Node*> arr;
			fillPrelist(head, arr);
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<> dist(0, arr.size()-1);
			int randomIndex = dist(mt);
			return arr[randomIndex];
		}

		// for test
		void fillPrelist(Node * head, vector<Node*>& arr) {
			if (head == nullptr) {
				return;
			}
			arr.push_back(head);
			fillPrelist(head->left, arr);
			fillPrelist(head->right, arr);
		}
	};

	void test_main() {
		int maxLevel = 4;
		int maxValue = 100;
		int testTimes = 1000;
		lowestAncestorA  laa;
		for (int i = 0; i < testTimes; i++) {
			Node * head = generatetree(maxLevel);
			Node * o1 = laa.pickRandomOne(head);
			Node * o2 = laa. pickRandomOne(head);
			scope_guard sg([head]() {
				if (head != nullptr)
				{
					delete head;
				}
			});
			if (laa.lowestAncestor1(head, o1, o2) != laa.lowestAncestor1(head, o1, o2)) {
				cout << "Oops!" << endl;
				break;
			}
		}
	}
}

void test_Code03_lowestAncestor() {

	cout << "test_Code03_lowestAncestor begin" << endl;
	Code03_lowestAncestor::test_main();
	cout << "test_Code03_lowestAncestor end" << endl;
}