#pragma once
#include <stack>
#include <iostream>
using namespace std;
namespace Code02_IsPalindromeList {

	struct Node {
		int value;
		Node * next = nullptr;

		Node(int data) {
			value = data;
		}
	};

	// need n extra space
	bool isPalindrome1(Node * head) {
		if (head == nullptr || head->next == nullptr)
		{
			return true;
		}
		std::stack<Node*> st;
		Node * cur = head;
		while (cur != nullptr) {
			st.push(cur);
			cur = cur->next;
		}
		cur = head;
		while (cur != nullptr) {
			if (cur->value != st.top()->value) {
				return false;
			}
			st.pop();
			cur = cur->next;
		}
		return true;
	}

	// need n/2 extra space
	bool isPalindrome2(Node * head) {
		if (head == nullptr || head->next == nullptr) {
			return true;
		}
		Node * right = head->next;
		Node * cur = head;
		while (cur->next != nullptr && cur->next->next != nullptr) {
			right = right->next;
			cur = cur->next->next;
		}
		std::stack<Node*> stack;
		while (right != nullptr) {
			stack.push(right);
			right = right->next;
		}
		while (!stack.empty()) {
			if (head->value != stack.top()->value) {
				return false;
			}
			stack.pop();
			head = head->next;
		}
		return true;
	}

	bool isPalindrome3(Node * head) {
		if (head == nullptr || head->next == nullptr) {
			return true;
		}
		Node * n1 = head;
		Node * n2 = head;
		while (n2->next != nullptr && n2->next->next != nullptr) { // find mid node
			n1 = n1->next; // n1 -> mid
			n2 = n2->next->next; // n2 -> end
		}
		// n1 ÖÐµã


		n2 = n1->next; // n2 -> right part first node
		n1->next = nullptr; // mid.next -> null
		Node * n3 = nullptr;
		while (n2 != nullptr) { // right part convert
			n3 = n2->next; // n3 -> save next node
			n2->next = n1; // next of right node convert
			n1 = n2; // n1 move
			n2 = n3; // n2 move
		}
		n3 = n1; // n3 -> save last node
		n2 = head;// n2 -> left first node
		bool res = true;
		while (n1 != nullptr && n2 != nullptr) { // check palindrome
			if (n1->value != n2->value) {
				res = false;
				break;
			}
			n1 = n1->next; // left to mid
			n2 = n2->next; // right to mid
		}
		n1 = n3->next;
		n3->next = nullptr;
		while (n1 != nullptr) { // recover list
			n2 = n1->next;
			n1->next = n3;
			n3 = n1;
			n1 = n2;
		}
		return res;
	}

	void printLinkedList(Node * node) {
		cout << "Linked List: " << endl;
		while (node != nullptr) {
			cout << node->value << " ";;
			node = node->next;
		}
		cout << endl;
	}

	void test_main() {

		Node * head = nullptr;
		printLinkedList(head);
		cout << isPalindrome1(head) << " | " ;
		cout << isPalindrome2(head) << " | " ;
		cout << isPalindrome2(head) << " | " << endl;
		printLinkedList(head);
		cout << "=========================" << endl;
	
		head = new Node(1);
		printLinkedList(head);
		cout << isPalindrome1(head) << " | " ;
		cout << isPalindrome2(head) << " | " ;
		cout << isPalindrome2(head) << " | " << endl;
		printLinkedList(head);
		cout << "=========================" << endl;

		head->next = new Node(2);
		printLinkedList(head);
		cout << isPalindrome1(head) << " | " ;
		cout << isPalindrome2(head) << " | " ;
		cout << isPalindrome2(head) << " | " << endl;
		printLinkedList(head);
		cout << "=========================" << endl;

		head->next->value = 1;
		printLinkedList(head);
		cout << isPalindrome1(head) << " | " ;
		cout << isPalindrome2(head) << " | " ;
		cout << isPalindrome2(head) << " | " << endl;
		printLinkedList(head);
		cout << "=========================" << endl;
		head->next->value = 2;
		head->next->next = new Node(3);
		printLinkedList(head);
		cout << isPalindrome1(head) << " | " ;
		cout << isPalindrome2(head) << " | " ;
		cout << isPalindrome2(head) << " | " << endl;
		printLinkedList(head);
		cout << "=========================" << endl;
		head->next->next->value = 1;
		printLinkedList(head);
		cout << isPalindrome1(head) << " | ";
		cout << isPalindrome2(head) << " | ";
		cout << isPalindrome2(head) << " | " << endl;
		printLinkedList(head);
		cout << "=========================" << endl;
		head->next->next->value = 3;
		head->next->next->next = new Node(1);
		printLinkedList(head);
		cout << isPalindrome1(head) << " | ";
		cout << isPalindrome2(head) << " | ";
		cout << isPalindrome2(head) << " | " << endl;
		printLinkedList(head);
		cout << "=========================" << endl;
		head->next->next->value = 2;
		printLinkedList(head);
		cout << isPalindrome1(head) << " | ";
		cout << isPalindrome2(head) << " | ";
		cout << isPalindrome2(head) << " | " << endl;
		printLinkedList(head);
		cout << "=========================" << endl;
		head->next->next->value = 3;
		head->next->next->next->value = 2;
		head->next->next->next->next = new Node(1);
		printLinkedList(head);
		cout << isPalindrome1(head) << " | ";
		cout << isPalindrome2(head) << " | ";
		cout << isPalindrome2(head) << " | " << endl;
		printLinkedList(head);
		cout << "=========================" << endl;

		Node * cur = head;
		while (cur != nullptr)
		{
			Node * tmp = cur->next;
			delete cur;
			cur = tmp;
		}
	}


}


void test_Code02_IsPalindromeList() {

	cout << "test_Code02_IsPalindromeList begin" << endl;
	Code02_IsPalindromeList::test_main();
	cout << "test_Code02_IsPalindromeList end" << endl;
}