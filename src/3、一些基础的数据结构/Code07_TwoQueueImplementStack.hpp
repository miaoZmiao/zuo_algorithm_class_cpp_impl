#pragma once
#include <queue>
#include <iostream>
#include <stack>
#include "utility_func.hpp"
using namespace std;
namespace Code07_TwoQueueImplementStack {

	template <class T > 
	class TwoQueueStack {
		std::queue<T> queue;
		std::queue<T> help;
	public:
		TwoQueueStack() {

		}

		void push(T value) {
			queue.push(value);
		}

		T poll() {
			while (queue.size() > 1) {
				help.push(queue.front()); 
				queue.pop();
			}
			T ans = queue.front(); queue.pop();
			queue.swap(help);
			return ans;
		}

		T peek() {
			while (queue.size() > 1) {
				help.push(queue.front());
				queue.pop();
			}
			T ans = queue.front(); queue.pop();
			help.push(ans);
			queue.swap(help);
			return ans;
		}

		bool isEmpty() {
			return queue.empty();
		}

	};

	void test_main() {
		
		TwoQueueStack<int> myStack;
		stack<int> test;
		int testTime = 1000;
		int max = 1000;
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);
		for (int i = 0; i < testTime; i++) {
			if (myStack.isEmpty()) {
				if (!test.empty()) {
					cout << ("Oops") << endl;
					break;
				}
				int num = (int)(dist(mt) * max);
				myStack.push(num);
				test.push(num);
			}
			else {
				if (dist(mt) < 0.25) {
					int num = (int)(dist(mt) * max);
					myStack.push(num);
					test.push(num);
				}
				else if (dist(mt) < 0.5) {
					if (!myStack.peek()== (test.top())) {
						cout << ("Oops") << endl;
						break;
					}
				}
				else if (dist(mt) < 0.75) {
					if (!myStack.peek() == (test.top())) {
						myStack.poll();
						test.pop();
						cout << ("Oops") << endl;
					}
				}
				else {
					if (myStack.isEmpty() != test.empty()) {
						cout << ("Oops") << endl;
					}
				}
			}
		}
	}

}

void test_Code07_TwoQueueImplementStack() {
	
	cout << "test_Code07_TwoQueueImplementStack begin" << endl;
	Code07_TwoQueueImplementStack::test_main();
	cout << "test_Code07_TwoQueueImplementStack end" << endl;

}