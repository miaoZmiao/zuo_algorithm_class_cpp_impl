#pragma once
#include <vector>
#include <iostream>
#include <stack>
using namespace std;
namespace Code03_SmallerEqualBigger {

	struct Node {
		int value;
		Node * next = nullptr;

		Node(int data) {
			value = data;
		}
	};

	class ListPartition {
	public:

		Node * listPartition1(Node * head, int pivot)
		{
			if (head == nullptr) {
				return head;
			}
			Node * cur = head;
			int i = 0;
			while (cur != nullptr) {
				i++;
				cur = cur->next;
			}
			vector<Node*> nodeArr(i, nullptr);
			i = 0;
			cur = head;
			for (i = 0; i != nodeArr.size(); i++) {
				nodeArr[i] = cur;
				cur = cur->next;
			}
			arrPartition(nodeArr, pivot);
			for (i = 1; i != nodeArr.size(); i++) {
				nodeArr[i - 1]->next = nodeArr[i];
			}
			nodeArr[i - 1]->next = nullptr;
			return nodeArr[0];
		}

		void arrPartition(vector<Node*> & nodeArr, int pivot) {
			int small = -1;
			int big = nodeArr.size();
			int index = 0;
			while (index != big) {
				if (nodeArr[index]->value < pivot) {
					swap(nodeArr, ++small, index++);
				}
				else if (nodeArr[index]->value == pivot) {
					index++;
				}
				else {
					swap(nodeArr, --big, index);
				}
			}
		}

		void swap(vector<Node*> & nodeArr, int a, int b) {
			if (a == b)
			{
				return;
			}
			Node * tmp = nodeArr[a];
			nodeArr[a] = nodeArr[b];
			nodeArr[b] = tmp;
		}

		Node * listPartition2(Node * head, int pivot) {
			Node * sH = nullptr; // small head
			Node * sT = nullptr; // small tail
			Node * eH = nullptr; // equal head
			Node * eT = nullptr; // equal tail
			Node * mH = nullptr; // big head
			Node * mT = nullptr; // big tail
			Node * next = nullptr; // save next node
			// every node distributed to three lists
			while (head != nullptr) {
				next = head->next;
				head->next = nullptr;
				if (head->value < pivot) {
					if (sH == nullptr) {
						sH = head;
						sT = head;
					}
					else {
						sT->next = head;
						sT = head;
					}
				}
				else if (head->value == pivot) {
					if (eH == nullptr) {
						eH = head;
						eT = head;
					}
					else {
						eT->next = head;
						eT = head;
					}
				}
				else {
					if (mH == nullptr) {
						mH = head;
						mT = head;
					}
					else {
						mT->next = head;
						mT = head;
					}
				}
				head = next;
			}
			// 小于区域的尾巴，连等于区域的头，等于区域的尾巴连大于区域的头
			if (sT != nullptr) { // 如果有小于区域
				sT->next = eH;
				eT = eT == nullptr ? sT : eT; // 下一步，谁去连大于区域的头，谁就变成eT
			}
			// 下一步，一定是需要用eT 去接 大于区域的头
			// 有等于区域，eT -> 等于区域的尾结点
			// 无等于区域，eT -> 小于区域的尾结点
			// eT 尽量不为空的尾巴节点
			if (eT != nullptr) { // 如果小于区域和等于区域，不是都没有
				eT->next = mH;
			}
			return sH != nullptr ? sH : (eH != nullptr ? eH : mH);
		
		}
	};

	void printLinkedList(Node * node) {
		cout << "Linked List: " << endl;
		while (node != nullptr) {
			cout << node->value << " ";;
			node = node->next;
		}
		cout << endl;
	}
	void test_main() {
		
		Node * head1 = new Node(7);
		head1->next = new Node(9);
		head1->next->next = new Node(1);
		head1->next->next->next = new Node(8);
		head1->next->next->next->next = new Node(5);
		head1->next->next->next->next->next = new Node(2);
		head1->next->next->next->next->next->next = new Node(5);
		ListPartition lp;
		printLinkedList(head1);
		// head1 = listPartition1(head1, 4);
		head1 = lp.listPartition2(head1, 5);
		printLinkedList(head1);

		Node * cur = head1;
		while (cur != nullptr)
		{
			Node * tmp = cur->next;
			delete cur;
			cur = tmp;
		}

	}


}

void test_Code03_SmallerEqualBigger() {

	cout << "test_Code03_SmallerEqualBigger begin" << endl;
	Code03_SmallerEqualBigger::test_main();
	cout << "test_Code03_SmallerEqualBigger end" << endl;
}
