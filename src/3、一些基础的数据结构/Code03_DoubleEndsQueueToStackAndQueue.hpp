#pragma once

#include "utility_func.hpp"
#include "scope_guard.h"
#include <queue>
#include <stack>
namespace Code03_DoubleEndsQueueToStackAndQueue {

	template <class T>
	struct Node {
		T value;
		Node * last = nullptr;
		Node * next = nullptr;

		Node(T data) {
			value = data;
		}
	};

	template <class T>
	class DoubleEndsQueue {
		Node<T> * head = nullptr;
		Node<T> * tail = nullptr;
	public:
		DoubleEndsQueue() {}

		~DoubleEndsQueue() {
			Node<T> * cur = head;
			while (cur != nullptr)
			{
				Node<T>  * next = cur->next;
				delete cur;
				cur = next;
			}
			head = nullptr;
			tail = nullptr;
		}

		void addFromHead(T value) {
			Node<T> * cur = new Node<T>(value);
			if (head == nullptr) {
				head = cur;
				tail = cur;
			}
			else {
				cur->next = head;
				head->last = cur;
				head = cur;
			}
		}

		 void addFromBottom(T value) {
			 Node<T> * cur = new Node<T>(value);
			 if (head == nullptr) {
				 head = cur;
				 tail = cur;
			 }
			 else {
				 cur->last = tail;
				 tail->next = cur;
				 tail = cur;
			 }
		 }

		 T popFromHead() {
			 if (head == nullptr) {
				 return T();
			 }
			 Node<T> * cur = head;
			 scope_guard sg([cur]() {
				 delete cur;
			 });
			 if (head == tail) {
				 head = nullptr;
				 tail = nullptr;
			 }
			 else {
				 head = head->next;
				 cur->next = nullptr;
				 head->last = nullptr;
			 }
			 return cur->value;
		 }

		 T popFromBottom() {
			 if (head == nullptr) {
				 return T();
			 }
			 Node<T> * cur = tail;
			 scope_guard sg([cur]() {
				 delete cur;
			 });
			 if (head == tail) {
				 head = nullptr;
				 tail = nullptr;
			 }
			 else {
				 tail = tail->last;
				 tail->next = nullptr;
				 cur->last = nullptr;
			 }
			 return cur->value;
		 }

		 bool isEmpty() {
			 return head == nullptr;
		 }

	};

	template <class T>
	class MyStack {
		 DoubleEndsQueue<T> queue;
	public:
		MyStack() {
			
		}
		~MyStack() {}
		void push(T value) {
			queue.addFromHead(value);
		}

		T pop() {
			return queue.popFromHead();
		}

		bool isEmpty() {
			return queue.isEmpty();
		}

	};
	template <class T>
	class MyQueue {
		DoubleEndsQueue<T> queue;
	public:
		MyQueue() {

		}
		~MyQueue() {}
		void push(T value) {
			queue.addFromHead(value);
		}

		T poll() {
			return queue.popFromBottom();
		}

		bool isEmpty() {
			return queue.isEmpty();
		}

	};

	void test_main() {
		int oneTestDataNum = 100;
		int value = 10000;
		int testTimes = 1000;
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);
		for (int i = 0; i < testTimes; i++) {
			MyStack<int> myStack;
			MyQueue<int> myQueue;
			stack<int> stack;
			queue<int> queue;
			for (int j = 0; j < oneTestDataNum; j++) {
				int nums = (int)(dist(mt) * value);
				if (stack.empty()) {
					myStack.push(nums);
					stack.push(nums);
				}
				else {
					if (dist(mt) < 0.5) {
						myStack.push(nums);
						stack.push(nums);
					}
					else {
						int v1 = myStack.pop();
						int v2 = stack.top(); stack.pop();
						if (v1 != v2) {
							cout << "stack oops!" << endl;
						}
					}
				}
				int numq = (int)(dist(mt) * value);
				if (queue.empty()) {
					myQueue.push(numq);
					queue.push(numq);
				}
				else {
					if (dist(mt) < 0.5) {
						myQueue.push(numq);
						queue.push(numq);
					}
					else {
						int val1 = myQueue.poll();
						int val2 = queue.front(); queue.pop();
						if (val1 != val2) {
							cout<<"queue oops!"<<endl;
						}
					}
				}
			}
		}
	}
}

void test_Code03_DoubleEndsQueueToStackAndQueue() {
	cout << "test_Code03_DoubleEndsQueueToStackAndQueue begin" << endl;
	Code03_DoubleEndsQueueToStackAndQueue::test_main();
	cout << "test_Code03_DoubleEndsQueueToStackAndQueue end" << endl;

}