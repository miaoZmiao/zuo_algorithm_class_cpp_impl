#pragma once


#include "utility_func.hpp"
#include "scope_guard.h"
#include <stack>
 
namespace Code01_ReverseList {
	struct LinkNode {
		LinkNode() {}
		LinkNode(int v) :val(v) {

		}
		int val;
		LinkNode * next = nullptr;

	};

	struct doubleLinkNode {

		int val;
		doubleLinkNode * next = nullptr;
		doubleLinkNode * pre = nullptr;
		doubleLinkNode(int value = 0) {
			val = value;
		}
	};


	//单链表，双链表
// 

// 反转链表
// 要求 空间复杂度 O(1)

	LinkNode * reverseLinkList(LinkNode * head)
	{
		if (head == nullptr)
		{
			return nullptr;
		}
		LinkNode * cur = head;
		LinkNode* pre = nullptr;

		while (cur != nullptr)
		{
			LinkNode * next = cur->next;
			cur->next = pre;
			pre = cur;
			cur = next;
		}
		return pre;
	}


	doubleLinkNode * reverseDoubleLinkList(doubleLinkNode * head) {
	    
		doubleLinkNode * rhead = head;

		doubleLinkNode * cur = head;
		doubleLinkNode * last = nullptr;
		while (cur != nullptr)
		{
			doubleLinkNode * next = cur->next;
			cur->next = last;
			cur->pre = next;
			last = cur;
			cur = next;
		}
		return last;
	}



	int random_number(int maxnum, int min_num)
	{
		if (maxnum < min_num)
		{
			return random_number(min_num, maxnum);
		}

		std::random_device rd;
		std::mt19937 rgen(rd());
		std::uniform_int_distribution<> disgene(min_num, maxnum);
		return disgene(rgen);

	}


	LinkNode * generate_link_list(int max_num, int min_num, size_t  len = 10) {

		std::random_device rd;
		std::mt19937 rgen(rd());
		std::uniform_int_distribution<> disgene(min_num, max_num);
		auto rg = [&]() {
			return disgene(rgen);
		};
		size_t size = len;
		LinkNode * head = new LinkNode(rg());
		size--;
		LinkNode * cur = head;
		while (size > 0)
		{
			cur->next = new LinkNode(rg());
			size--;
			cur = cur->next;
		}
		return head;
	}

	doubleLinkNode * generate_doublelink_list(int max_num, int min_num, size_t  len = 10) {
	
		std::random_device rd;
		std::mt19937 rgen(rd());
		std::uniform_int_distribution<> disgene(min_num, max_num);
		auto rg = [&]() {
			return disgene(rgen);
		};
		size_t size = len;
		doubleLinkNode * head = new doubleLinkNode(rg());
		size--;
		doubleLinkNode * cur = head;
		while (size > 0)
		{
			cur->next = new doubleLinkNode(rg());
			cur->next->pre = cur;
			size--;
			cur = cur->next;
		}
		return head;
	}
	template <class T>
	void destroy_link_list(T * head) {
		if (head == nullptr)
		{
			return;
		}
		T * cur = head;
		while (cur != nullptr)
		{
			T * nextnode = cur->next;
			delete cur;
			cur = nextnode;
		}
	}

	// print linklist
	template <class TList>
	void printlinklikst(TList * head)
	{
		if (head == nullptr)
		{
			return;
		}
		TList * cur = head;
		cout << "[";
		while (cur != nullptr)
		{
			cout << cur->val << " ";
			cur = cur->next;
		}
		cout << "]" << endl;
		return;
	}

	LinkNode * copyList(LinkNode * otherhead)
	{
		if (otherhead == nullptr)
		{
			return nullptr;
		}

		LinkNode * head = new LinkNode();
		head->val = otherhead->val;
		LinkNode* othercur = otherhead->next;
		LinkNode * cur = head;
		while (othercur != nullptr)
		{
			cur->next = new LinkNode(othercur->val);
			cur = cur->next;
			othercur = othercur->next;
		}
		return head;
	}

	template < class TList>
	bool is_two_list_equal(TList * list1, TList * list2) {
		if (list1 == list2)
		{
			return true;
		}
		TList * cur1 = list1;
		TList * cur2 = list2;

		while ((cur1 != nullptr  && cur2 != nullptr))
		{
			if (cur1->val == cur2->val)
			{
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
			else
			{
				return false;
			}
		}

		if (cur1 == nullptr && cur2 == nullptr)
		{
			return true;
		}
		return false;

	}

	LinkNode * reverseLinkList_use_stack(LinkNode * list)
	{
		if (list == nullptr)
		{
			return nullptr;
		}
		LinkNode* cur = list;
		std::stack<LinkNode* > stk;
		while (cur != nullptr)
		{
			stk.push(cur);
			cur = cur->next;
		}

		LinkNode* pre = nullptr;
		LinkNode * reverseHead = stk.top();
		while (!stk.empty())
		{
			LinkNode * node = stk.top();
			if (pre != nullptr)
			{
				pre->next = node;
			}
			stk.pop();
			pre = node;
		}
		if (pre != nullptr)
		{
			pre->next = nullptr;
		}
		return reverseHead;
	}


	// for test
	vector<int> getLinkedListOriginOrder(LinkNode* head) {
		vector<int > ans;
		while (head != nullptr) {
			ans.push_back(head->val);
			head = head->next;
		}
		return ans;
	}

	// for test
	vector<int> getDoubleListOriginOrder(doubleLinkNode * head) {
		vector<int> ans;
		while (head != nullptr) {
			ans.push_back(head->val);
			head = head->next;
		}
		return ans;
	}

	bool checkLinkedListReverse(vector<int> & origin, LinkNode * head) {
		for (int i = origin.size() - 1; i >= 0; i--) {
			if (!origin[i]== (head->val)) {
				return false;
			}
			head = head->next;
		}
		return true;
	}

	bool checkDoubleListReverse(vector<int> & origin, doubleLinkNode * head) {
		doubleLinkNode * end = nullptr;
		for (int i = origin.size() - 1; i >= 0; i--) {
			if (!origin[i] == (head->val)) {
				return false;
			}
			end = head;
			head = head->next;
		}
		for (int i = 0; i < origin.size(); i++) {
			if (!origin[i]==(end->val)) {
				return false;
			}
			end = end->pre;
		}
		return true;
	}


	void test_main() {
	
		int len = 50;
		int value = 100;
		int testTime = 1000;

		for (int i = 0; i < testTime; i++) {
			LinkNode * node1 = generate_link_list(value, 0, len);
			scope_guard sg1([node1]() {
				if (node1 != nullptr)
				{
					destroy_link_list(node1);
				}
			});
			vector<int> list1 = getLinkedListOriginOrder(node1);
			node1 = reverseLinkList(node1);
			if (!checkLinkedListReverse(list1, node1)) {
				cout << "Oops1!" << endl;
				break;
			}

			LinkNode * node2 = generate_link_list(value, 0, len);
			scope_guard sg2([node2]() {
				if (node2 != nullptr)
				{
					destroy_link_list(node2);
				}
			});
			vector<int> list2 = getLinkedListOriginOrder(node2);
			node2 = reverseLinkList(node2);
			if (!checkLinkedListReverse(list2, node2)) {
				cout << "Oops2!" << endl;
				break;
			}

			doubleLinkNode * node3 = generate_doublelink_list(value, 0, len);
			scope_guard sg3([node3]() {
				if (node3 != nullptr)
				{
					destroy_link_list(node3);
				}
			});
			vector<int> list3 = getDoubleListOriginOrder(node3);
			node3 = reverseDoubleLinkList(node3);
			if (!checkDoubleListReverse(list3, node3)) {
				cout << "Oops3!" << endl;
				break;
			}

			doubleLinkNode * node4 = generate_doublelink_list(value, 0, len);
			scope_guard sg4([node4]() {
				if (node4 != nullptr)
				{
					destroy_link_list(node4);
				}
			});
			vector<int> list4 = getDoubleListOriginOrder(node4);
			node4 = reverseDoubleLinkList(node4);
			if (!checkDoubleListReverse(list4, node4)) {
				cout << "Oops3!" << endl;
				break;
			}

		}
	
	
	}
}


void test_Code01_ReverseList() {
	cout << "test_Code01_ReverseList begin" << endl;
	Code01_ReverseList::test_main();
	cout << "test_Code01_ReverseList end" << endl;
}