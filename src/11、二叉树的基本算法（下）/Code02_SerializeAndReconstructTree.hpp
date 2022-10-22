#pragma once
#include "treeNode.hpp"
#include <string>
#include <queue>
#include <stack>
#include "scope_guard.h"
namespace Code02_SerializeAndReconstructTree {
	/*
	 * 二叉树可以通过先序、后序或者按层遍历的方式序列化和反序列化，
	 * 以下代码全部实现了。
	 * 但是，二叉树无法通过中序遍历的方式实现序列化和反序列化
	 * 因为不同的两棵树，可能得到同样的中序序列，即便补了空位置也可能一样。
	 * 比如如下两棵树
	 *         __2
	 *        /
	 *       1
	 *       和
	 *       1__
	 *          \
	 *           2
	 * 补足空位置的中序遍历结果都是{ null, 1, null, 2, null}
	 *
	 * */

	class TreeSerialize {
	public:

		queue<string> preSerial(Node * head) {
			queue<string> ans;
			pres(head, ans);
			return ans;
		}

		void pres(Node * head, queue<string>& ans) {
			if (head == nullptr) {
				ans.push("#");
			}
			else {
				ans.push(std::to_string(head->value));
				pres(head->left, ans);
				pres(head->right, ans);
			}
		}

		queue<string> inSerial(Node * head) {
			queue<string> ans;
			ins(head, ans);
			return ans;
		}

		void ins(Node * head, queue<string>& ans) {
			if (head == nullptr) {
				ans.push("#");
			}
			else {
				pres(head->left, ans);
				ans.push(std::to_string(head->value));
				pres(head->right, ans);
			}
		}

		queue<string> posSerial(Node * head) {
			queue<string> ans;
			poss(head, ans);
			return ans;
		}

		void poss(Node * head, queue<string>& ans) {
			if (head == nullptr) {
				ans.push("#");
			}
			else {
				poss(head->left, ans);
				poss(head->right, ans);
				ans.push(std::to_string(head->value));
			}
		}

		Node * buildByPreQueue(queue<string> & prelist) {
			if (prelist.size() == 0 ) {
				return nullptr;
			}
			return preb(prelist);
		}

		Node * preb(queue<string> & prelist) {
			string value = prelist.front();
			prelist.pop();
			if (value == "#") {
				return nullptr;
			}
			Node * head = new Node(std::atoi(value.c_str()));
			head->left = preb(prelist);
			head->right = preb(prelist);
			return head;
		}

		Node * buildByPosQueue(queue<string> & poslist) {
			if (poslist.size() == 0) {
				return nullptr;
			}
			// 左右中  ->  stack(中右左)
			stack<string> st;
			while (!poslist.empty()) {
				st.push(poslist.front());
				poslist.pop();
			}
			return posb(st);
		}

		Node * posb(stack<string> & posstack) {
			string value = posstack.top();
			posstack.pop();
			if (value == "#") {
				return nullptr;
			}
			Node * head = new Node(std::atoi(value.c_str()));
			head->right = posb(posstack);
			head->left = posb(posstack);
			return head;
		}

		queue<string> levelSerial(Node * head) {
			
			queue<string> ans;
			if (head == nullptr) {
				ans.push("#");
			}
			else {
				ans.push(std::to_string(head->value));
				queue<Node *> queue;
				queue.push(head);
				while (!queue.empty()) {
					head = queue.front(); // head 父   子
					queue.pop();
					if (head->left != nullptr) {
						ans.push(std::to_string(head->left->value));
						queue.push(head->left);
					}
					else {
						ans.push("#");
					}
					if (head->right != nullptr) {
						ans.push(std::to_string(head->right->value));
						queue.push(head->right);
					}
					else {
						ans.push("#");
					}
				}
			}
			return ans;
		}

		Node * buildByLevelQueue(queue<string> & levelList) {
			if (levelList.size() == 0) {
				return nullptr;
			}
			Node * head = generateNode(levelList.front());
			levelList.pop();
			queue<Node*> queue;
			if (head != nullptr) {
				queue.push(head);
			}
			Node * node = nullptr;
			while (!queue.empty()) {
				node = queue.front();
				queue.pop();
				node->left = generateNode(levelList.front());
				levelList.pop();
				node->right = generateNode(levelList.front());
				levelList.pop();
				if (node->left != nullptr) {
					queue.push(node->left);
				}
				if (node->right != nullptr) {
					queue.push(node->right);
				}
			}
			return head;
		}

		Node * generateNode(string val) {
			if (val == "#") {
				return nullptr;
			}
			return new Node(std::atoi(val.c_str()));
		}

		void printInOrder(Node * head, int height, string to, int len) {
			if (head == nullptr) {
				return;
			}
			printInOrder(head->right, height + 1, "v", len);
			string val = to + std::to_string(head->value) + to;
			int lenM = val.length();
			int lenL = (len - lenM) / 2;
			int lenR = len - lenM - lenL;
			val = getSpace(lenL) + val + getSpace(lenR);
			cout << (getSpace(height * len) + val) << endl;
			printInOrder(head->left, height + 1, "^", len);
		}

		string getSpace(int num) {
			string space = " ";
			string buf;
			for (int i = 0; i < num; i++) {
				buf+=(space);
			}
			return buf;
		}
		void printTree(Node * head) {
			cout << "Binary Tree:" << endl;
			printInOrder(head, 0, "H", 17);
			cout << endl;
		}

	};

	bool isSameValueStructure(Node * head1, Node * head2) {
		if (head1 == nullptr && head2 != nullptr) {
			return false;
		}
		if (head1 != nullptr && head2 == nullptr) {
			return false;
		}
		if (head1 == nullptr && head2 == nullptr) {
			return true;
		}
		if (head1->value != head2->value) {
			return false;
		}
		return isSameValueStructure(head1->left, head2->left) && isSameValueStructure(head1->right, head2->right);
	}

	void test_main() {
		int maxLevel = 5;
		int maxValue = 100;
		int testTimes = 1000;

		TreeSerialize ts;
		for (int i = 0; i < testTimes; i++) {
			Node * head = generatetree(maxLevel);
			queue<string> pre = ts.preSerial(head);
			queue<string> pos = ts.posSerial(head);
			queue<string> level = ts.levelSerial(head);
			Node * preBuild = ts.buildByPreQueue(pre);
			Node * posBuild = ts.buildByPosQueue(pos);
			Node * levelBuild = ts.buildByLevelQueue(level);
			scope_guard sg([&]() {
				if (preBuild)
				{
					delete preBuild;
				}
				if (posBuild)
				{
					delete posBuild;
				}
				if (levelBuild)
				{
					delete levelBuild;
				}
				if (head)
				{
					delete head;
				}
			});
			if (!isSameValueStructure(preBuild, posBuild) || !isSameValueStructure(posBuild, levelBuild)) {
				cout<<"Oops!"<<endl;
				cout << "origin tree" << endl;
				printTree(head);
				cout << "origin preBuild" << endl;
				printTree(preBuild);
				cout << "origin posBuild" << endl;
				printTree(posBuild);
				cout << "origin levelBuild" << endl;
				printTree(levelBuild);
				break;
			}
			
		}

	}

}


void test_Code02_SerializeAndReconstructTree() {

	cout << "test_Code02_SerializeAndReconstructTree begin" << endl;
	Code02_SerializeAndReconstructTree::test_main();
	cout << "test_Code02_SerializeAndReconstructTree end" << endl;
}