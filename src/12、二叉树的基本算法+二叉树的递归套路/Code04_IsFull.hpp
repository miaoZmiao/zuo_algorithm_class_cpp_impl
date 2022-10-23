#pragma once
#include "treeNode.hpp"
#include "scope_guard.h"


namespace Code04_IsFull {

	class IsFull {
	public:
		bool isFull1(Node * head) {
			if (head == nullptr) {
				return true;
			}
			int height = h(head);
			int nodes = n(head);
			return (1 << height) - 1 == nodes;
		}

		int h(Node *head) {
			if (head == nullptr) {
				return 0;
			}
			return std::max(h(head->left), h(head->right)) + 1;
		}

		int n(Node *head) {
			if (head == nullptr) {
				return 0;
			}
			return n(head->left) + n(head->right) + 1;
		}

		

		struct Info {
			int height;
			int nodes;

			Info(int h, int n) {
				height = h;
				nodes = n;
			}
		};

		bool isFull2(Node *head) {
			if (head == nullptr) {
				return true;
			}
			Info all = process(head);
			return (1 << all.height) - 1 == all.nodes;
		}

		Info process(Node *head) {
			if (head == nullptr) {
				return  Info(0, 0);
			}
			Info leftInfo = process(head->left);
			Info rightInfo = process(head->right);
			int height = std::max(leftInfo.height, rightInfo.height) + 1;
			int nodes = leftInfo.nodes + rightInfo.nodes + 1;
			return  Info(height, nodes);
		}

	};


	void test_main() {
		int maxLevel = 5;
		int maxValue = 100;
		int testTimes = 1000;
		IsFull isfull;
		for (int i = 0; i < testTimes; i++) {
			Node * head = generatetree(maxLevel);
			scope_guard sg([head]() {
				if (head != nullptr)
				{
					delete head;
				}
			});
			if (isfull.isFull1(head) != isfull.isFull2(head)) {
				cout << "Oops!" << endl;
				break;
			}
		}

	}
}

void test_Code04_IsFull() {
	cout << "test_Code04_IsFull begin" << endl;
	Code04_IsFull::test_main();
	cout << "test_Code04_IsFull end" << endl;
}
