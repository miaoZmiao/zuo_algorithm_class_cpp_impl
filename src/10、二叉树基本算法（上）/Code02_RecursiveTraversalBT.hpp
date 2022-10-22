#pragma once
#include "treeNode.hpp"
#include <functional>
namespace Code02_RecursiveTraversalBT {

	/*struct Node {
		int value;
		Node * left = nullptr;
		Node * right = nullptr;

		Node(int v) {
			value = v;
		}
	};*/

	struct OP {

		enum OP_TYPE : int {
			OP_PRE = 0,
			OP_IN,
			OP_POS
		};
		OP_TYPE optype;
		std::function<void(Node*)> opfunc;

	};


	void func(Node * root, const OP & op) {
		if (root == nullptr)
		{	
			return;
		}
		if (op.optype == OP::OP_PRE)
		{
			op.opfunc(root);
		}
		func(root->left, op);
		if (op.optype == OP::OP_IN)
		{
			op.opfunc(root);
		}
		func(root->right, op);
		if (op.optype == OP::OP_POS)
		{
			op.opfunc(root);
		}
	}

	void test_main() {
		
		Node * head = new Node(1);
		head->left = new Node(2);
		head->right = new Node(3);
		head->left->left = new Node(4);
		head->left->right = new Node(5);
		head->right->left = new Node(6);
		head->right->right = new Node(7);
		OP op;
		op.optype = OP::OP_PRE;
		op.opfunc = [](Node * node) {
			cout << node->value<<"|";
		};
		printTree(head);
		func(head, op);
		cout << endl << "========" << endl;
		op.optype = OP::OP_IN;
		func(head, op);
		cout << endl << "========" << endl;
		op.optype = OP::OP_POS;
		func(head, op);
		cout << endl << "========" << endl;
		delete head;
		head = nullptr;
	}

}

void test_Code02_RecursiveTraversalBT() {

	cout << "test_Code02_RecursiveTraversalBT begin" << endl;
	Code02_RecursiveTraversalBT::test_main();
	cout << "test_Code02_RecursiveTraversalBT end" << endl;
}