#pragma once
#include "treeNode.hpp"
#include "scope_guard.h"

namespace Code05_MaxSubBSTSize {

	class MaxSubBSTSize {

	public:
		int getBSTSize(Node *head) {
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

		void in(Node *head, vector<Node*> & arr) {
			if (head == nullptr) {
				return;
			}
			in(head->left, arr);
			arr.push_back(head);
			in(head->right, arr);
		}

		int maxSubBSTSize1(Node *head) {
			if (head == nullptr) {
				return 0;
			}
			int h = getBSTSize(head);
			if (h != 0) {
				return h;
			}
			return std::max(maxSubBSTSize1(head->left), maxSubBSTSize1(head->right));
		}

		struct Info {
			int maxBSTSubtreeSize;
			int allSize;
			int max;
			int min;

			Info(int m, int a, int ma, int mi) {
				maxBSTSubtreeSize = m;
				allSize = a;
				max = ma;
				min = mi;
			}
		};

		int maxSubBSTSize2(Node *head) {
			if (head == nullptr) {
				return 0;
			}
			return process(head).maxBSTSubtreeSize;
		}

		

		Info process(Node *x) {
			if (x == nullptr) {
				return Info(0, 0, INT_MIN, INT_MAX);
			}
			Info leftInfo = process(x->left);
			Info rightInfo = process(x->right);
			int max = x->value;
			int min = x->value;
			int allSize = 1;

			max = std::max(leftInfo.max, max);
			min = std::min(leftInfo.min, min);
			allSize += leftInfo.allSize;


			max = std::max(rightInfo.max, max);
			min = std::min(rightInfo.min, min);
			allSize += rightInfo.allSize;

			int p1 = -1;

			p1 = leftInfo.maxBSTSubtreeSize;

			int p2 = -1;

			p2 = rightInfo.maxBSTSubtreeSize;

			int p3 = -1;
			bool leftBST = (leftInfo.maxBSTSubtreeSize == leftInfo.allSize);
			bool rightBST = (rightInfo.maxBSTSubtreeSize == rightInfo.allSize);
			if (leftBST && rightBST) {
				bool leftMaxLessX = (leftInfo.max < x->value);
				bool rightMinMoreX = (x->value < rightInfo.min);
				if (leftMaxLessX && rightMinMoreX) {
					int leftSize = leftInfo.allSize;
					int rightSize = rightInfo.allSize;
					p3 = leftSize + rightSize + 1;
				}
			}
			return Info(std::max(p1, std::max(p2, p3)), allSize, max, min);
		}
	};

	void test_main() {
		int maxLevel = 5;
		int maxValue = 100;
		int testTimes = 1000;
		MaxSubBSTSize mbst;
		for (int i = 0; i < testTimes; i++) {
			Node * head = generatetree(maxLevel);
			scope_guard sg([head]() {
				if (head != nullptr)
				{
					delete head;
				}
			});
			if (mbst.maxSubBSTSize1(head) != mbst.maxSubBSTSize2(head)) {
				cout << "Oops!" << endl;
				break;
			}
		}
	
	}

}

void test_Code05_MaxSubBSTSize() {
	
	cout << "test_Code05_MaxSubBSTSize begin" << endl;
	Code05_MaxSubBSTSize::test_main();
	cout << "test_Code05_MaxSubBSTSize end" << endl;
}