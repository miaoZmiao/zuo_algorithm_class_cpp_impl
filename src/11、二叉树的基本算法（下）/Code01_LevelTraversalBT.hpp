#pragma once
#include "treeNode.hpp"
#include <queue>

namespace Code01_LevelTraversalBT {

	void level(Node * head) {
		if (head == nullptr) {
			return;
		}
		std::queue<Node*> queue;
		queue.push(head);
		while (!queue.empty()) {
			Node * cur = queue.front();
			queue.pop();
			cout<<cur->value<<"|";
			if (cur->left != nullptr) {
				queue.push(cur->left);
			}
			if (cur->right != nullptr) {
				queue.push(cur->right);
			}
		}
		cout << endl;
	}

	
}

void test_Code01_LevelTraversalBT() {

	Node * head = new Node(1);
	head->left = new Node(2);
	head->right = new Node(3);
	head->left->left = new Node(4);
	head->left->right = new Node(5);
	head->right->left = new Node(6);
	head->right->right = new Node(7);

	Code01_LevelTraversalBT::level(head);
	cout << "========" << endl;;
	delete head;

}