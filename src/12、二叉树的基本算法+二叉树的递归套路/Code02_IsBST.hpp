#pragma once

#include "treeNode.hpp"
#include "scope_guard.h"

namespace Code02_IsBST {

	class IsBST {
	public:
		bool isBST1(Node *  head) {
			if (head == nullptr) {
				return true;
			}
			vector<Node * > arr ;
			in(head, arr);
			for (int i = 1; i < arr.size(); i++) {
				if (arr[i]->value <= arr[i-1]->value) {
					return false;
				}
			}
			return true;
		}

		void in(Node *  head, vector<Node * >& arr) {
			if (head == nullptr) {
				return;
			}
			in(head->left, arr);
			arr.push_back(head);
			in(head->right, arr);
		}

		bool isBST2(Node *  head) {
			if (head == nullptr) {
				return true;
			}
			return process(head).isBST;
		}

		struct Info {
			bool isBST;
			int max;
			int min;

			Info(bool i, int ma, int mi) {
				isBST = i;
				max = ma;
				min = mi;
			}

		};

		Info process(Node *  x) {
			if (x == nullptr) {
				return Info(true, INT_MIN, INT_MAX);
			}
			Info leftInfo = process(x->left);
			Info rightInfo = process(x->right);
			int max = x->value;

			max = std::max(max, leftInfo.max);

			max = std::max(max, rightInfo.max);

			int min = x->value;

			min = std::min(min, leftInfo.min);

			min = std::min(min, rightInfo.min);

			bool isBST = true;
			if (!leftInfo.isBST) {
				isBST = false;
			}
			if (!rightInfo.isBST) {
				isBST = false;
			}
			if (leftInfo.max >= x->value) {
				isBST = false;
			}
			if (rightInfo.min <= x->value) {
				isBST = false;
			}
			return Info(isBST, max, min);
		}

	};

	void test_main() {
		int maxLevel = 4;
		int maxValue = 100;
		int testTimes = 1000;
		IsBST isbst;
		for (int i = 0; i < testTimes; i++) {
			Node * head = generatetree(maxLevel);
			scope_guard sg([head]() {
				if (head != nullptr)
				{
					delete head;
				}
			});
			if (isbst.isBST1(head) != isbst.isBST2(head)) {
				cout << "Oops!" << endl;
				break;
			}
		}
	}

}

void test_Code02_IsBST() {
	cout << "test_Code02_IsBST begin" << endl;
	Code02_IsBST::test_main();
	cout << "test_Code02_IsBST end" << endl;
}