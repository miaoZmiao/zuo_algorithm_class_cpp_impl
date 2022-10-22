#pragma once

#include "utility_func.hpp"
#include <string>

namespace Code01_LinkedListMid {

	struct Node {
		int value;
		Node * next = nullptr;

		Node(int v) {
			value = v;
		}
	};
	// 链表问题，都是边界问题
	// 需要扣边界
	// 1、借助快慢指针找中点

	// 1、	输入链表头结点，奇数长度返回中点，偶数长度返回上中点
	Node * midOrUpMidNode(Node * head) {
		if (head == nullptr || head->next == nullptr)
		{
			return head;
		}
		Node * slow = head;
		Node * fast = head->next;
		while (fast->next != nullptr && fast->next->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	Node * midOrDownMidNode(Node * head) {
		if (head == nullptr || head->next == nullptr)
		{
			return head;
		}
		Node * slow = head->next;
		Node * fast = head->next;
		while (fast->next != nullptr && fast->next->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	Node * midOrUpMidPreNode(Node * head) {
		if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
			return nullptr;
		}
		Node * slow = head;
		Node * fast = head->next->next;
		while (fast->next != nullptr && fast->next->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	Node * midOrDownMidPreNode(Node * head) {
		if (head == nullptr || head->next == nullptr) {
			return nullptr;
		}
		if (head->next->next == nullptr) {
			return head;
		}
		Node * slow = head;
		Node * fast = head->next;
		while (fast->next != nullptr && fast->next->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	Node * right1(Node * head) {
		if (head == nullptr) {
			return nullptr;
		}
		Node * cur = head;
		vector<Node*> arr;
		while (cur != nullptr) {
			arr.push_back(cur);
			cur = cur->next;
		}
		return arr[(arr.size() - 1) / 2];
	}

	Node * right2(Node * head) {
		if (head == nullptr) {
			return nullptr;
		}
		Node * cur = head;
		vector<Node*> arr;
		while (cur != nullptr) {
			arr.push_back(cur);
			cur = cur->next;
		}
		return arr[(arr.size()) / 2];
	}

	Node * right3(Node * head) {
		if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
			return nullptr;
		}
		Node * cur = head;
		vector<Node*> arr;
		while (cur != nullptr) {
			arr.push_back(cur);
			cur = cur->next;
		}
		return arr[(arr.size()-3) / 2];
	}

	Node * right4(Node * head) {
		if (head == nullptr || head->next == nullptr) {
			return nullptr;
		}
		Node* cur = head;
		vector<Node*> arr;
		while (cur != nullptr) {
			arr.push_back(cur);
			cur = cur->next;
		}
		return arr[(arr.size() - 2) / 2];
	}

	void test_main() {
		Node * test = nullptr;
		test = new Node(0);
		test->next = new Node(1);
		test->next->next = new Node(2);
		test->next->next->next = new Node(3);
		test->next->next->next->next = new Node(4);
		test->next->next->next->next->next = new Node(5);
		test->next->next->next->next->next->next = new Node(6);
		test->next->next->next->next->next->next->next = new Node(7);
		test->next->next->next->next->next->next->next->next = new Node(8);

		Node * ans1 = nullptr;
		Node * ans2 = nullptr;
		ans1 = midOrUpMidNode(test);
		ans2 = right1(test);
		cout << (ans1 != nullptr ? std::to_string(ans1->value) : "无") << endl;
		cout << (ans2 != nullptr ? std::to_string(ans2->value) : "无") << endl;

		ans1 = midOrDownMidNode(test);
		ans2 = right2(test);
		cout << (ans1 != nullptr ? std::to_string(ans1->value) : "无") << endl;
		cout << (ans2 != nullptr ? std::to_string(ans2->value) : "无") << endl;

		ans1 = midOrUpMidPreNode(test);
		ans2 = right3(test);
		cout << (ans1 != nullptr ? std::to_string(ans1->value) : "无") << endl;
		cout << (ans2 != nullptr ? std::to_string(ans2->value) : "无") << endl;

		ans1 = midOrDownMidPreNode(test);
		ans2 = right4(test);
		cout << (ans1 != nullptr ? std::to_string(ans1->value) : "无") << endl;
		cout << (ans2 != nullptr ? std::to_string(ans2->value) : "无") << endl;

		Node * cur = test;
		while (cur != nullptr)
		{
			Node * tmp = cur->next;
			delete cur;
			cur = tmp;
		}
	}

}

void test_Code01_LinkedListMid() {

	cout << "test_Code01_LinkedListMid begin" << endl;
	Code01_LinkedListMid::test_main();
	cout << "test_Code01_LinkedListMid end" << endl;
}