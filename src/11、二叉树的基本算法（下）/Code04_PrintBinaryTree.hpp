#pragma once
#include "treeNode.hpp"
#include <string>

namespace Code04_PrintBinaryTree {

	class PBTree {
	public:
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
			cout << (getSpace(height * len) + val)<<endl;
			printInOrder(head->left, height + 1, "^", len);
		}

		string getSpace(int num) {
			string space = " ";
			string buf;
			for (int i = 0; i < num; i++) {
				buf += (space);
			}
			return buf;
		}
		void printTree(Node * head) {
			cout << "Binary Tree:" << endl;
			printInOrder(head, 0, "H", 17);
			cout << endl;
		}

	};

	void test_main() {
		
		Node * root = generatetree();

		PBTree pbt;

		pbt.printTree(root);

		printTree(root);

		delete root;
		root = nullptr;
	}

}

void test_Code04_PrintBinaryTree() {

	cout << "test_Code04_PrintBinaryTree begin" << endl;
	Code04_PrintBinaryTree::test_main();
	cout << "test_Code04_PrintBinaryTree end" << endl;
}