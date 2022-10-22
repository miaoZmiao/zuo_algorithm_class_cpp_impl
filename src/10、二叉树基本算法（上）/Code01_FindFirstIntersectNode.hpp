#pragma once
#include "utility_func.hpp"
#include <algorithm>
#include <string>
namespace Code01_FindFirstIntersectNode {

	struct Node {
		int value;
		Node * next = nullptr;
		Node(int v) {
			value = v;
		}
	};

	class FindFirstIntersectNode {

	public:
		Node * getIntersectNode(Node * head1, Node * head2) {
			if (head1 == nullptr || head2 == nullptr) {
				return nullptr;
			}
			Node * loop1 = getLoopNode(head1);
			Node * loop2 = getLoopNode(head2);
			if (loop1 == nullptr && loop2 == nullptr) {
				return noLoop(head1, head2);
			}
			if (loop1 != nullptr && loop2 != nullptr) {
				return bothLoop(head1, loop1, head2, loop2);
			}
			return nullptr;
		}
		// 找到链表第一个入环节点，如果无环，返回null
		Node * getLoopNode(Node * head) {
			if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
				return nullptr;
			}
			// n1 慢  n2 快
			Node * slow = head->next; // n1 -> slow
			Node * fast = head->next->next; // n2 -> fast
			while (slow != fast) {
				if (fast->next == nullptr || fast->next->next == nullptr) {
					return nullptr;
				}
				fast = fast->next->next;
				slow = slow->next;
			}

			// slow fast  相遇
			fast = head; // n2 -> walk again from head
			while (slow != fast) {
				slow = slow->next;
				fast = fast->next;
			}
			// 解释
			// L = 非环部分的长度，
			// 单点从起点走需要先走L的长度，才能走到环上，假设该点为环的0刻度点
			// C = 环本身的长度
			// 从环的零刻度点开始走，需要走C长度，才能再次回到环的0刻度点
			// slow 和 fast 同时从起点开始走
			// 假设同时开始走，在环上的c刻度相遇
			// slow 走的长度为 L + c
			// fast 走的长度为 L + c + C
			// 有关系: L+c+C = 2*(L+c)
			// 展开: L + c + C = 2L + 2c
			// 化简之后:
			// C = L + c
			// 此时 Fast 从 0开始走 需要走 L，走到环的0点
			// slow 在环上的c点，也需要走L，也会走到环上的0点(因为 L = C - c)
			return slow;
		}
		// 如果两个链表都无环，返回第一个相交节点，如果不想交，返回null
		Node * noLoop(Node * head1, Node * head2) {
			if (head1 == nullptr || head2 == nullptr) {
				return nullptr;
			}
			Node * cur1 = head1;
			Node * cur2 = head2;
			int n = 0;
			while (cur1->next != nullptr) {
				n++;
				cur1 = cur1->next;
			}
			while (cur2->next != nullptr) {
				n--;
				cur2 = cur2->next;
			}
			if (cur1 != cur2) {
				return nullptr;
			}
			// n  :  链表1长度减去链表2长度的值
			cur1 = n > 0 ? head1 : head2; // 谁长，谁的头变成cur1
			cur2 = cur1 == head1 ? head2 : head1; // 谁短，谁的头变成cur2
			n = std::abs(n);
			while (n != 0) {
				n--;
				cur1 = cur1->next;
			}
			while (cur1 != cur2) {
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
			return cur1;
		}
		// 如果两个链表都无环，返回第一个相交节点，如果不相交，返回null
		Node * bothLoop(Node * head1, Node * loop1, Node * head2, Node * loop2) {
		
			Node * cur1 =  nullptr;
			Node * cur2 = nullptr;
			if (loop1 == loop2) {
				cur1 = head1;
				cur2 = head2;
				int n = 0;
				while (cur1 != loop1) {
					n++;
					cur1 = cur1->next;
				}
				while (cur2 != loop2) {
					n--;
					cur2 = cur2->next;
				}
				cur1 = n > 0 ? head1 : head2;
				cur2 = cur1 == head1 ? head2 : head1;
				n = std::abs(n);
				while (n != 0) {
					n--;
					cur1 = cur1->next;
				}
				while (cur1 != cur2) {
					cur1 = cur1->next;
					cur2 = cur2->next;
				}
				return cur1;
			}
			else {
				cur1 = loop1->next;
				while (cur1 != loop1) {
					if (cur1 == loop2) {
						return loop1;
					}
					cur1 = cur1->next;
				}
				return nullptr;
			}
		}

	};

	void destroyList(Node * head) {
		while (head != nullptr)
		{
			Node * tmp = head->next;
			delete head;
			head = tmp;
		}
		return;
	}

	void test_main() {
		FindFirstIntersectNode ff;
		// 1->2->3->4->5->6->7->null
		Node * head1 = new Node(1);
		head1->next = new Node(2);
		head1->next->next = new Node(3);
		head1->next->next->next = new Node(4);
		head1->next->next->next->next = new Node(5);
		head1->next->next->next->next->next = new Node(6);
		head1->next->next->next->next->next->next = new Node(7);

		// 0->9->8->6->7->null
		Node * head2 = new Node(0);
		head2->next = new Node(9);
		head2->next->next = new Node(8);
		head2->next->next->next = head1->next->next->next->next->next; // 8->6
		Node * intersect = ff.getIntersectNode(head1, head2);
		cout << (intersect!=nullptr? std::to_string(intersect->value):"null") << endl;
		head2->next->next->next = nullptr;
		destroyList(head1); head1 = nullptr;
		destroyList(head2); head2 = nullptr;
		// 1->2->3->4->5->6->7->4...
		head1 = new Node(1);
		head1->next = new Node(2);
		head1->next->next = new Node(3);
		head1->next->next->next = new Node(4);
		head1->next->next->next->next = new Node(5);
		head1->next->next->next->next->next = new Node(6);
		head1->next->next->next->next->next->next = new Node(7);
		head1->next->next->next->next->next->next = head1->next->next->next; // 7->4
		
		// 0->9->8->2...
		head2 = new Node(0);
		head2->next = new Node(9);
		head2->next->next = new Node(8);
		head2->next->next->next = head1->next; // 8->2
		intersect = ff.getIntersectNode(head1, head2);
		cout << (intersect != nullptr ? std::to_string(intersect->value) : "null") << endl;
		head2->next->next->next = nullptr;
		destroyList(head2); head2 = nullptr;
		// 0->9->8->6->4->5->6..
		head2 = new Node(0);
		head2->next = new Node(9);
		head2->next->next = new Node(8);
		head2->next->next->next = head1->next->next->next->next->next; // 8->6
		intersect = ff.getIntersectNode(head1, head2);
		cout << (intersect != nullptr ? std::to_string(intersect->value) : "null") << endl;
		head2->next->next->next = nullptr;
		destroyList(head2); head2 = nullptr;
		head1->next->next->next->next->next->next = nullptr;
		destroyList(head1); head1 = nullptr;
	}

}


void test_Code01_FindFirstIntersectNode() {

	cout << "test_Code01_FindFirstIntersectNode begin" << endl;
	Code01_FindFirstIntersectNode::test_main();
	cout << "test_Code01_FindFirstIntersectNode end" << endl;
}