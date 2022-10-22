#pragma once
#include "treeNode.hpp"
#include <stack>

namespace Code03_UnRecursiveTraversalBT {

	void pre(Node * head) {
		
		if (head == nullptr) {
			return;
		}
		Node * cur = head;
		std::stack<Node *> st;
		st.push(head);
		while (!st.empty()) {
			cur = st.top();
			st.pop();
			cout << cur->value << "|";
			if (cur->right != nullptr)
			{
				st.push(cur->right);
			}
			if (cur->left != nullptr)
			{
				st.push(cur->left);
			}
		}
		cout << endl;
		return;
	}

	void in(Node * head) {
		if (head == nullptr)
		{
			return;
		}
		std::stack<Node *> st;
		Node * cur = head;
		while (!st.empty() || cur != nullptr)
		{
			if (cur != nullptr)
			{
				st.push(cur);
				cur = cur->left;
			}
			else {
				cur = st.top();
				st.pop();
				cout << cur->value << "|";
				cur = cur->right;
			}
		}
		cout << endl;
		return;
	}

	void pos1(Node * head) {
	
		if (head == nullptr)
		{
			return;
		}
		std::stack<Node *> st1;
		std::stack<Node *> st2;
		Node * cur = head;
		st1.push(head);
		while (!st1.empty())
		{
			cur = st1.top();
			st1.pop();
			st2.push(cur);
			// 中 右 左
			if (cur->left != nullptr)
			{
				st1.push(cur->left);
			}
			if (cur->right != nullptr)
			{
				st1.push(cur->right);
			}

		}
		// 左 右 中 
		while (!st2.empty())
		{
			cur = st2.top();
			st2.pop();
			cout << cur->value << "|";
		}
		cout << endl;
		return;
	}


	void pos2(Node * head) {

		if (head == nullptr)
		{
			return;
		}
		std::stack<Node*> st;
		Node * cur = head;
		Node * last = nullptr;
		st.push(head);
		while (!st.empty())
		{
			cur = st.top();
			// 第一次经过cur 要到到 cur->left 
			// last 点既不是 cur 的左子 也不是 cur 的右子
			if (cur->left != nullptr && last != cur->left && last != cur->right)
			{
				st.push(cur->left);
			}
			// 第二次 经过 cur，要到 cur->right
			// last 点是 cur的左子 但是 last 不是cur的右子
			else if (cur->right != nullptr && last == cur->left && last != cur->right)
			{
				st.push(cur->right);
			}
			else
			{
				cur = st.top();
				st.pop();
				last = cur;
				cout << cur->value << "|";
			}
		}
		cout << endl;
		return;
	}

	void test_main() {
	
		Node * head = new Node(1);
		head->left = new Node(2);
		head->right = new Node(3);
		head->left->left = new Node(4);
		head->left->right = new Node(5);
		head->right->left = new Node(6);
		head->right->right = new Node(7);

		pre(head);
		cout << "========" << endl;
		in(head);
		cout << "========" << endl;
		pos1(head);
		cout << "========" << endl;
		pos2(head);
		cout << "========" << endl;
	
		delete head;
	}
}


void test_Code03_UnRecursiveTraversalBT() {

	cout << "test_Code03_UnRecursiveTraversalBT begin" << endl;
	Code03_UnRecursiveTraversalBT::test_main();
	cout << "test_Code03_UnRecursiveTraversalBT end" << endl;
	
}