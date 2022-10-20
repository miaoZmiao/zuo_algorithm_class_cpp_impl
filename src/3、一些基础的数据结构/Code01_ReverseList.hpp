#pragma once


#include "utility_func.hpp"


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

		size_t size = len;
		LinkNode * head = new LinkNode(random_number(max_num, min_num));
		size--;
		LinkNode * cur = head;
		while (size > 0)
		{
			cur->next = new LinkNode(random_number(max_num, min_num));
			size--;
			cur = cur->next;
		}
		return head;
	}

	void destroy_link_list(LinkNode * head) {
		if (head == nullptr)
		{
			return;
		}
		LinkNode * cur = head;
		while (cur != nullptr)
		{
			LinkNode * nextnode = cur->next;
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


	bool is_two_list_equal(LinkNode * list1, LinkNode * list2) {
		if (list1 == list2)
		{
			return true;
		}
		LinkNode * cur1 = list1;
		LinkNode * cur2 = list2;

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

}