#pragma once
#include <stack>
#include <iostream>
using namespace std;
namespace Code06_TwoStacksImplementQueue {
	class TwoStacksQueue {
		stack<int> stackPush;
		stack<int> stackPop;
	public:
		TwoStacksQueue() {

		}

		// push栈向pop栈倒入数据
		void pushToPop() {
			if (stackPop.empty()) {
				while (!stackPush.empty()) {
					stackPop.push(stackPush.top());
					stackPush.pop();
				}
			}
		}

		void add(int pushInt) {
			stackPush.push(pushInt);
			pushToPop();
		}

		int poll() {
			if (stackPop.empty() && stackPush.empty()) {
				throw std::runtime_error("Queue is empty!");
			}
			pushToPop();
			int ret = stackPop.top(); stackPop.pop();
			return ret;
		}

		int peek() {
			if (stackPop.empty() && stackPush.empty()) {
				throw std::runtime_error("Queue is empty!");
			}
			pushToPop();
			return stackPop.top();
		}
	};

	void test_main() {
		TwoStacksQueue test;
		test.add(1);
		test.add(2);
		test.add(3);
		cout << (test.peek()) << endl;
		cout<<(test.poll()) << endl;
		cout<<(test.peek()) << endl;
		cout<<(test.poll()) << endl;
		cout<<(test.peek()) << endl;
		cout<<(test.poll()) << endl;
	}
	
}

void test_Code06_TwoStacksImplementQueue() {

	cout << "test_Code06_TwoStacksImplementQueue begin" << endl;
	Code06_TwoStacksImplementQueue::test_main();
	cout << "test_Code06_TwoStacksImplementQueue end" << endl;
}