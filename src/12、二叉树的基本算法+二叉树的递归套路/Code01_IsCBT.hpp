#pragma once
#include "treeNode.hpp"
#include <queue>
#include <algorithm>
#include "scope_guard.h"
namespace Code01_IsCBT {

	class IsCBT {
	public:

		bool isCBT1(Node *  head) {
			if (head == nullptr) {
				return true;
			}
			queue<Node * > queue;
			// 是否遇到过左右两个孩子不双全的节点
			bool leaf = false;
			Node *  l = nullptr;
			Node *  r = nullptr;
			queue.push(head);
			while (!queue.empty()) {
				head = queue.front();
				queue.pop();
				l = head->left;
				r = head->right;
				if (
					// 如果遇到了不双全的节点之后，又发现当前节点不是叶节点
					(leaf && (l != nullptr || r != nullptr))
					||
					(l == nullptr && r != nullptr)

					) {
					return false;
				}
				if (l != nullptr) {
					queue.push(l);
				}
				if (r != nullptr) {
					queue.push(r);
				}
				if (l == nullptr || r == nullptr) {
					leaf = true;
				}
			}
			return true;
		}

		struct Info {
			bool isFull;
			bool isCBT;
			int height;

			Info(bool full, bool cbt, int h) {
				isFull = full;
				isCBT = cbt;
				height = h;
			}
		};

		Info process(Node * X) {
			if (X == nullptr) {
				return Info(true, true, 0);
			}
			Info leftInfo = process(X->left);
			Info rightInfo = process(X->right);
			int height = std::max(leftInfo.height, rightInfo.height) + 1;
			bool isFull = leftInfo.isFull
				&&
				rightInfo.isFull
				&& leftInfo.height == rightInfo.height;
			bool isCBT = false;
			if (isFull) {
				isCBT = true;
			}
			else { // 以x为头整棵树，不满
				if (leftInfo.isCBT && rightInfo.isCBT) {


					if (leftInfo.isCBT
						&& rightInfo.isFull
						&& leftInfo.height == rightInfo.height + 1) {
						isCBT = true;
					}
					if (leftInfo.isFull
						&&
						rightInfo.isFull
						&& leftInfo.height == rightInfo.height + 1) {
						isCBT = true;
					}
					if (leftInfo.isFull
						&& rightInfo.isCBT && leftInfo.height == rightInfo.height) {
						isCBT = true;
					}


				}
			}
			return Info(isFull, isCBT, height);
		}

		bool isCBT2(Node * head) {
			if (head == nullptr) {
				return true;
			}
			return process(head).isCBT;
		}

	};

	void test_main() {
		int maxLevel = 5;
		int maxValue = 100;
		int testTimes = 1000;
		IsCBT iscbt;
		for (int i = 0; i < testTimes; i++) {
			Node * head = generatetree(maxLevel);
			scope_guard sg([head]() {
				if (head != nullptr)
				{
					delete head;
				}
			});
			if (iscbt.isCBT1(head) != iscbt.isCBT2(head)) {
				cout<<"Oops!"<<endl;
				break;
			}
		}
	
	}


}

void test_Code01_IsCBT() {

	cout << "test_Code01_IsCBT begin" << endl;
	Code01_IsCBT::test_main();
	cout << "test_Code01_IsCBT end" << endl;

}