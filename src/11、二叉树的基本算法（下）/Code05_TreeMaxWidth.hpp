#pragma once
#include "treeNode.hpp"
#include <unordered_map>
#include <queue>
#include <algorithm>
#include "scope_guard.h"
namespace Code05_TreeMaxWidth {
	int maxWidthUseMap(Node * head) {
		if (head == nullptr) {
			return 0;
		}
		queue<Node *> queue;
		queue.push(head);
		// key 在 哪一层，value
		unordered_map<Node*, int> levelMap;
		levelMap.insert({ head, 1 });
		int curLevel = 1; // 当前你正在统计哪一层的宽度
		int curLevelNodes = 0; // 当前层curLevel层，宽度目前是多少
		int max = 0;
		while (!queue.empty()) {
			Node * cur = queue.front();
			queue.pop();
			int curNodeLevel = levelMap[(cur)];
			if (cur->left != nullptr) {
				levelMap.insert({ cur->left, curNodeLevel + 1 });
				queue.push(cur->left);
			}
			if (cur->right != nullptr) {
				levelMap.insert({ cur->right, curNodeLevel + 1 });
				queue.push(cur->right);
			}
			if (curNodeLevel == curLevel) {
				curLevelNodes++;
			}
			else {
				max = std::max(max, curLevelNodes);
				curLevel++;
				curLevelNodes = 1;
			}
		}
		max = std::max(max, curLevelNodes);
		return max;
	}


	int maxWidthNoMap(Node * head) {
		if (head == nullptr) {
			return 0;
		}
		queue<Node*> queue;
		queue.push(head);
		Node * curEnd = head; // 当前层，最右节点是谁
		Node * nextEnd = nullptr; // 下一层，最右节点是谁
		int max = 0;
		int curLevelNodes = 0; // 当前层的节点数
		while (!queue.empty()) {
			Node * cur = queue.front();
			queue.pop();
			if (cur->left != nullptr) {
				queue.push(cur->left);
				nextEnd = cur->left;
			}
			if (cur->right != nullptr) {
				queue.push(cur->right);
				nextEnd = cur->right;
			}
			curLevelNodes++;
			if (cur == curEnd) {
				max = std::max(max, curLevelNodes);
				curLevelNodes = 0;
				curEnd = nextEnd;
			}
		}
		return max;
	}

	void test_main() {
		int maxLevel = 10;
		int maxValue = 100;
		int testTimes = 1000;
		for (int i = 0; i < testTimes; i++) {
			Node * head = generatetree(maxLevel);
			scope_guard sg([head]() {
				if (head != nullptr)
				{
					delete head;
				}
			});
			if (maxWidthUseMap(head) != maxWidthNoMap(head)) {
				cout << "Oops" << endl;
				break;
			}
		}
	}
}

void test_Code05_TreeMaxWidth() {

	cout << "test_Code05_TreeMaxWidth begin" << endl;
	Code05_TreeMaxWidth::test_main();
	cout << "test_Code05_TreeMaxWidth end" << endl;
}