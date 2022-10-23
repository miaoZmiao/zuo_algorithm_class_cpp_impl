#pragma once
#include "treeNode.hpp"
#include "scope_guard.h"

namespace Code02_MaxSubBSTHead {

	class MaxSubBSTHead {
	public:
		int getBSTSize(Node * head) {
			if (head == nullptr) {
				return 0;
			}
			vector<Node*> arr;
			in(head, arr);
			for (int i = 1; i < arr.size(); i++) {
				if (arr[i]->value <= arr[i - 1]->value) {
					return 0;
				}
			}
			return arr.size();
		}

		void in(Node * head, vector<Node*> & arr) {
			if (head == nullptr) {
				return;
			}
			in(head->left, arr);
			arr.push_back(head);
			in(head->right, arr);
		}

		Node * maxSubBSTHead1(Node * head) {
			if (head == nullptr) {
				return nullptr;
			}
			if (getBSTSize(head) != 0) {
				return head;
			}
			Node * leftAns = maxSubBSTHead1(head->left);
			Node * rightAns = maxSubBSTHead1(head->right);
			return getBSTSize(leftAns) >= getBSTSize(rightAns) ? leftAns : rightAns;
		}


		// Ã¿Ò»¿Ã×ÓÊ÷
		struct Info {
			Node * maxSubBSTHead;
			int maxSubBSTSize;
			int min;
			int max;

			Info(Node * h, int size, int mi, int ma) {
				maxSubBSTHead = h;
				maxSubBSTSize = size;
				min = mi;
				max = ma;
			}
		};


		Node * maxSubBSTHead2(Node * head) {
			if (head == nullptr) {
				return nullptr;
			}
			return process(head).maxSubBSTHead;
		}

		

		Info process(Node * X) {
			if (X == nullptr) {
				return Info(nullptr, 0, INT_MAX, INT_MIN);
			}
			Info leftInfo = process(X->left);
			Info rightInfo = process(X->right);
			int min = X->value;
			int max = X->value;
			Node * maxSubBSTHead = nullptr;
			int maxSubBSTSize = 0;

			min = std::min(min, leftInfo.min);
			max = std::max(max, leftInfo.max);
			maxSubBSTHead = leftInfo.maxSubBSTHead;
			maxSubBSTSize = leftInfo.maxSubBSTSize;

			min = std::min(min, rightInfo.min);
			max = std::max(max, rightInfo.max);
			if (rightInfo.maxSubBSTSize > maxSubBSTSize) {
				maxSubBSTHead = rightInfo.maxSubBSTHead;
				maxSubBSTSize = rightInfo.maxSubBSTSize;
			}
			
			if (((leftInfo.maxSubBSTHead == X->left && leftInfo.max < X->value))
				&& ((rightInfo.maxSubBSTHead == X->right && rightInfo.min > X->value))) {
				maxSubBSTHead = X;
				maxSubBSTSize = (leftInfo.maxSubBSTSize)
					+ (rightInfo.maxSubBSTSize) + 1;
			}
			return Info(maxSubBSTHead, maxSubBSTSize, min, max);
		}
	};

	void test_main() {
		int maxLevel = 4;
		int maxValue = 100;
		int testTimes = 1000;
		MaxSubBSTHead  msb;
		for (int i = 0; i < testTimes; i++) {
			Node * head = generatetree(maxLevel);
			scope_guard sg([head]() {
				if (head != nullptr)
				{
					delete head;
				}
			});
			if (msb.maxSubBSTHead1(head) != msb.maxSubBSTHead2(head)) {
				cout << "Oops!" << endl;
				break;
			}
		}
	
	}
}

void test_Code02_MaxSubBSTHead() {
	cout << "test_Code02_MaxSubBSTHead begin" << endl;
	Code02_MaxSubBSTHead::test_main();
	cout << "test_Code02_MaxSubBSTHead end" << endl;
}