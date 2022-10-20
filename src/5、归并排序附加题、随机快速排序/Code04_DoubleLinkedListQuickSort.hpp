#pragma once
#include "utility_func.hpp"
#include <functional>
#include "scope_guard.h"
namespace Code04_DoubleLinkedListQuickSort {

	struct Node {
		int value;
		Node* last = nullptr;
		Node* next = nullptr;

		Node(int v = 0) {
			value = v;
		}
	};


	struct HeadTail {
		Node * h = nullptr;
		Node * t = nullptr;

		HeadTail(Node * head, Node * tail) {
			h = head;
			t = tail;
		}
	};

	struct Info {

		 Node *lh = nullptr;
		 Node* lt = nullptr;
		 int ls;
		 Node *rh = nullptr;
		 Node* rt = nullptr;
		 int rs;
		 Node *eh = nullptr;
		 Node *et = nullptr;
		 Info(Node * lH, Node * lT, int lS, Node * rH, Node * rT, int rS, Node * eH, Node * eT) {
			 lh = lH;
			 lt = lT;
			 ls = lS;
			 rh = rH;
			 rt = rT;
			 rs = rS;
			 eh = eH;
			 et = eT;
		 }

	};

	// (L....一直到空)，是一个双向链表
	// pivot是一个不在(L....一直到空)的独立节点，它作为划分值
	// 根据荷兰国旗问题的划分方式，把(L....一直到空)划分成:
	// <pivot 、 =pivot 、 >pivot 三个部分，然后把pivot融进=pivot的部分
	// 比如 4(L)->6->7->1->5->0->9->null pivot=5(这个5和链表中的5，是不同的节点)
	// 调整完成后:
	// 4->1->0 小于的部分
	// 5->5 等于的部分
	// 6->7->9 大于的部分
	// 三个部分是断开的
	// 然后返回Info：
	// 小于部分的头、尾、节点个数 : lh,lt,ls
	// 大于部分的头、尾、节点个数 : rh,rt,rs
	// 等于部分的头、尾 : eh,et
	Info partition(Node* L, Node *pivot)
	{
		Node *lh = nullptr;
		Node *lt = nullptr;
		int ls = 0;
		Node *rh = nullptr;
		Node* rt = nullptr;
		int rs = 0;
		Node *eh = pivot;
		Node* et = pivot;
		Node *tmp = nullptr;
		while (L != nullptr) {
			tmp = L->next;
			L->next = nullptr;
			L->last = nullptr;
			if (L->value < pivot->value) {
				ls++;
				if (lh == nullptr) {
					lh = L;
					lt = L;
				}
				else {
					lt->next = L;
					L->last = lt;
					lt = L;
				}
			}
			else if (L->value > pivot->value) {
				rs++;
				if (rh == nullptr) {
					rh = L;
					rt = L;
				}
				else {
					rt->next = L;
					L->last = rt;
					rt = L;
				}
			}
			else {
				et->next = L;
				L->last = et;
				et = L;
			}
			L = tmp;
		}
		return Info(lh, lt, ls, rh, rt, rs, eh, et);
	}

	HeadTail process(Node* L, Node* R, int N, 
		std::function<double()> getrandom_num) {
		if (L == nullptr) {
			return HeadTail(nullptr, nullptr);
		}
		if (L == R) {
			return  HeadTail(L, R);
		}
		// L..R上不只一个节点
		// 随机得到一个随机下标
		
		int randomIndex = (int)(getrandom_num() * N);
		// 根据随机下标得到随机节点
		Node* randomNode = L;
		while (randomIndex-- != 0) {
			randomNode = randomNode->next;
		}
		// 把随机节点从原来的环境里分离出来
		// 比如 a(L) -> b -> c -> d(R), 如果randomNode = c，那么调整之后
		// a(L) -> b -> d(R), c会被挖出来，randomNode = c
		if (randomNode == L || randomNode == R) {
			if (randomNode == L) {
				L = randomNode->next;
				L->last = nullptr;
			}
			else {
				randomNode->last->next = nullptr;
			}
		}
		else { // randomNode一定是中间的节点
			randomNode->last->next = randomNode->next;
			randomNode->next->last = randomNode->last;
		}
		randomNode->last = nullptr;
		randomNode->next = nullptr;
		Info info = partition(L, randomNode);
		// <randomNode的部分去排序
		HeadTail lht = process(info.lh, info.lt, info.ls, getrandom_num);
		// >randomNode的部分去排序
		HeadTail rht = process(info.rh, info.rt, info.rs, getrandom_num);
		// 左部分排好序、右部分排好序
		// 把它们串在一起
		if (lht.h != nullptr) {
			lht.t->next = info.eh;
			info.eh->last = lht.t;
		}
		if (rht.h != nullptr) {
			info.et->next = rht.h;
			rht.h->last = info.et;
		}
		// 返回排好序之后总的头和总的尾
		Node *h = lht.h != nullptr ? lht.h : info.eh;
		Node *t = rht.h != nullptr ? rht.t : info.et;
		return HeadTail(h, t);
	}

	Node* quickSort(Node* h) {
		if (h == nullptr) {
			return nullptr;
		}
		int N = 0;
		Node* c = h;
		Node *e = nullptr;
		while (c != nullptr) {
			N++;
			e = c;
			c = c->next;
		}
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);
		auto getrandom = [&]()->double {
			return dist(mt);
		};
		return process(h, e, N, getrandom).h;
	}

	struct NodeCmp {

		bool operator()(Node * left , Node * right) const {
			return left->value < right->value;
		}
	};


	Node  * normalsort(Node * head)
	{
		if (head == nullptr)
		{
			return nullptr;
		}
		vector<Node *> arr;
		while (head != nullptr)
		{
			arr.push_back(head);
			head = head->next;
		}
		std::sort(arr.begin(), arr.end(), NodeCmp());
		Node* h = arr[0];
		h->last = nullptr;
		Node * pre = h;
		for (int i = 1; i < arr.size(); i++)
		{
			Node * cur = arr[i];
			pre->next = cur;
			cur->last = pre;
			cur->next = nullptr;
			pre = cur;
		}
		return h;
	}

	Node * generateRandomDoubleLinkedList(int n, int v) {
		if (n == 0) {
			return nullptr;
		}
		Node* head = nullptr;
		Node * pre  = nullptr;
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);
		for (int i = 0; i < n; i++) {
			if (head == nullptr)
			{
				head = new Node((int)(dist(mt) * v));
				head->last = nullptr;
				head->next = nullptr;
				pre = head;
			}
			else {
				pre->next = new Node((int)(dist(mt) * v));
				pre->next->last = pre;
				pre->next->next = nullptr;
				pre = pre->next;
			}

		}
		return head;
	}

	Node * cloneDoubleLinkedList(Node * head) {
		if (head == nullptr) {
			return nullptr;
		}
		Node* h = new Node(head->value);
		Node* p = h;
		head = head->next;
		while (head != nullptr) {
			Node *c = new Node(head->value);
			p->next = c;
			c->last = p;
			c->next = nullptr;
			p = c;
			head = head->next;
		}
		return h;
	}

	bool isDoubleLinkListEqual(Node * h1, Node* h2) {
		if (h1 == nullptr && h2 == nullptr)
		{
			return true;
		}
		else if (h1 == nullptr || h2 == nullptr)
		{
			return false;
		}
		
		while (h1 != nullptr && h2 != nullptr)
		{
			if (h1->value != h2->value)
			{
				return false;
			}
			h1 = h1->next;
			h2 = h2->next;
		}
		return isDoubleLinkListEqual(h1, h2);
	}

	void freeDoubleLinkList(Node * h) {
		while (h != nullptr)
		{
			Node* tmp = h->next;
			delete h;
			h = tmp;
		}
	}

	void test_() {
	
		int N = 500;
		int V = 500;
		int testTime = 5000;
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);

		for (int i = 0; i < testTime; i++) {
			int size = int(N*dist(mt)) + 1;
			Node * head1 = generateRandomDoubleLinkedList(size, V);
			Node * head2 = cloneDoubleLinkedList(head1);
		
			Node * ans1 = quickSort(head1);
			Node * ans2 = normalsort(head2);
			scope_guard sg([&]() {
				if (ans1 != nullptr)
				{
					freeDoubleLinkList(ans1);
				}
				if (ans2 != nullptr)
				{
					freeDoubleLinkList(ans2);
				}
			});
			if (!isDoubleLinkListEqual(ans1, ans2)) {
				cout << "wrong" << endl;
				break;
			}
			
		}
	}
}


void test_Code04_DoubleLinkedListQuickSort() {
	

	cout << "test_Code04_DoubleLinkedListQuickSort begin" << endl;

	Code04_DoubleLinkedListQuickSort::test_();

	cout << "test_Code04_DoubleLinkedListQuickSort end" << endl;
}