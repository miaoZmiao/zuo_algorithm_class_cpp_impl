#pragma once
#include "treeNode.hpp"
#include "scope_guard.h"

namespace Code03_IsBalanced {

	class IsBalanced {
	public:
		bool isBalanced1(Node *  head) {
			vector<bool> ans(1, true);
			ans[0] = true;
			process1(head, ans);
			return ans[0];
		}

		int process1(Node *  head, vector<bool> & ans) {
			if (!ans[0] || head == nullptr) {
				return -1;
			}
			int leftHeight = process1(head->left, ans);
			int rightHeight = process1(head->right, ans);
			if (std::abs(leftHeight - rightHeight) > 1) {
				ans[0] = false;
			}
			return std::max(leftHeight, rightHeight) + 1;
		}

		bool isBalanced2(Node *  head) {
			return process(head).isBalanced;
		}

		struct Info {
			bool isBalanced;
			int height;

			Info(bool i, int h) {
				isBalanced = i;
				height = h;
			}
		};

		Info process(Node *  x) {
			if (x == nullptr) {
				return  Info(true, 0);
			}
			Info leftInfo = process(x->left);
			Info rightInfo = process(x->right);
			int height = std::max(leftInfo.height, rightInfo.height) + 1;
			bool isBalanced = true;
			if (!leftInfo.isBalanced) {
				isBalanced = false;
			}
			if (!rightInfo.isBalanced) {
				isBalanced = false;
			}
			if (std::abs(leftInfo.height - rightInfo.height) > 1) {
				isBalanced = false;
			}
			return  Info(isBalanced, height);
		}
	};

	void test_main() {
		int maxLevel = 5;
		int maxValue = 100;
		int testTimes = 1000;
		IsBalanced ib;
		for (int i = 0; i < testTimes; i++) {
			Node * head = generatetree(maxLevel);
			scope_guard sg([head]() {
				if (head != nullptr)
				{
					delete head;
				}
			});
			if (ib.isBalanced1(head) != ib.isBalanced2(head)) {
				cout << "Oops!" << endl;
				break;
			}
		}
	}
}

void test_Code03_IsBalanced() {

	cout << "Code03_IsBalanced begin" << endl;
	Code03_IsBalanced::test_main();
	cout << "Code03_IsBalanced end" << endl;
}