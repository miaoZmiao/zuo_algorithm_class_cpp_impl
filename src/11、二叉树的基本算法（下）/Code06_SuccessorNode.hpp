#pragma once
#include "treeNode.hpp"
#include <string>

namespace Code06_SuccessorNode {

	struct NodeTP {
		int value;
		NodeTP * left = nullptr;
		NodeTP * right = nullptr;
		NodeTP * parent = nullptr;

		NodeTP(int data) {
			value = data;
		}
		~NodeTP() {
			if (left != nullptr)
			{
				delete left;
				left = nullptr;
			}
			if (right != nullptr)
			{
				delete right;
				right = nullptr;
			}
		}
	};

	NodeTP * getLeftMost(NodeTP * node) {
		if (node == nullptr) {
			return node;
		}
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}


	NodeTP * getSuccessorNode(NodeTP * node) {
		if (node == nullptr) {
			return node;
		}
		if (node->right != nullptr) {
			return getLeftMost(node->right);
		}
		else { // 无右子树
			NodeTP * parent = node->parent;
			while (parent != nullptr && parent->right == node) { // 当前节点是其父亲节点右孩子
				node = parent;
				parent = node->parent;
			}
			return parent;
		}
	}

	void test_main() {
		NodeTP * head = new NodeTP(6);
		head->parent = nullptr;
		head->left = new NodeTP(3);
		head->left->parent = head;
		head->left->left = new NodeTP(1);
		head->left->left->parent = head->left;
		head->left->left->right = new NodeTP(2);
		head->left->left->right->parent = head->left->left;
		head->left->right = new NodeTP(4);
		head->left->right->parent = head->left;
		head->left->right->right = new NodeTP(5);
		head->left->right->right->parent = head->left->right;
		head->right = new NodeTP(9);
		head->right->parent = head;
		head->right->left = new NodeTP(8);
		head->right->left->parent = head->right;
		head->right->left->left = new NodeTP(7);
		head->right->left->left->parent = head->right->left;
		head->right->right = new NodeTP(10);
		head->right->right->parent = head->right;

		NodeTP * test = head->left->left;
		NodeTP * suc = getSuccessorNode(test);
		cout<<test->value << " next: " << suc->value << endl;
		test = head->left->left->right;
		suc = getSuccessorNode(test);
		cout<<test->value << " next: " << (suc != nullptr ? std::to_string(suc->value) : "nullptr") << endl;
		test = head->left;
		suc = getSuccessorNode(test);
		cout<<test->value << " next: " << (suc != nullptr ? std::to_string(suc->value) : "nullptr") << endl;
		test = head->left->right;
		suc = getSuccessorNode(test);
		cout<<test->value << " next: " << (suc != nullptr ? std::to_string(suc->value) : "nullptr") << endl;
		test = head->left->right->right;
		suc = getSuccessorNode(test);
		cout<<test->value << " next: " << (suc != nullptr ? std::to_string(suc->value) : "nullptr") << endl;
		test = head;
		suc = getSuccessorNode(test);
		cout<<test->value << " next: " << (suc != nullptr ? std::to_string(suc->value) : "nullptr") << endl;
		test = head->right->left->left;
		suc = getSuccessorNode(test);
		cout<<test->value << " next: " << (suc != nullptr ? std::to_string(suc->value) : "nullptr") << endl;
		test = head->right->left;
		suc = getSuccessorNode(test);
		cout << test->value << " next: " << (suc != nullptr ? std::to_string(suc->value) : "nullptr") << endl;
		test = head->right;
		suc = getSuccessorNode(test);
		cout<<test->value << " next: " << (suc != nullptr ? std::to_string(suc->value) : "nullptr") << endl;
		test = head->right->right; // 10's next is null
		suc = getSuccessorNode(test);
		cout << test->value << " next: " << (suc != nullptr ? std::to_string(suc->value) : "nullptr") << endl;;
	
		delete head;
	}

}

void test_Code06_SuccessorNode() {

	cout << "test_Code06_SuccessorNode begin" << endl;
	Code06_SuccessorNode::test_main();
	cout << "test_Code06_SuccessorNode end" << endl;
}