#pragma once
#include <stack>
#include <iostream>
using namespace std;
namespace Code05_GetMinStack {

	class MyStack1 {
		stack<int> stackData;
		stack<int> stackMin;
	public:
		MyStack1() {
		}

		void push(int newNum) {
			if (stackMin.empty()) {
				stackMin.push(newNum);
			}
			else if (newNum <= getmin()) {
				stackMin.push(newNum);
			}
			stackData.push(newNum);
		}

		int pop() {
			if (stackData.empty()) {
				throw std::runtime_error("Your stack is empty.");
			}
			int value = stackData.top(); stackData.pop();
			if (value == getmin()) {
				stackMin.pop();
			}
			return value;
		}

		int getmin() {
			if (stackMin.empty()) {
				throw std::runtime_error("Your stack is empty.");
			}
			return stackMin.top();
		}
	};

	class MyStack2 {
		stack<int> stackData;
		stack<int> stackMin;
	public:
		MyStack2() {

		}

		void push(int newNum) {
			if (stackMin.empty()) {
				stackMin.push(newNum);
			}
			else if (newNum < getmin()) {
				stackMin.push(newNum);
			}
			else {
				int newMin = stackMin.top();
				stackMin.push(newMin);
			}
			stackData.push(newNum);
		}

		int pop() {
			if (stackData.empty()) {
				throw std::runtime_error("Your stack is empty.");
			}
			stackMin.pop();
			int ret = stackData.top(); stackData.pop();
			return ret;
		}

		int getmin() {
			if (stackMin.empty()) {
				throw std::runtime_error("Your stack is empty.");
			}
			return stackMin.top();
		}
	};

	void test_main() {
		MyStack1 stack1;
		stack1.push(3);
		cout<<(stack1.getmin())<<endl;
		stack1.push(4);
		cout<<(stack1.getmin()) << endl;
		stack1.push(1);
		cout<<(stack1.getmin()) << endl;
		cout<<(stack1.pop()) << endl;
		cout<<(stack1.getmin()) << endl;

		cout<<("=============");

		MyStack1 stack2;
		stack2.push(3);
		cout<<(stack2.getmin()) << endl;
		stack2.push(4);
		cout<<(stack2.getmin()) << endl;
		stack2.push(1);
		cout<<(stack2.getmin()) << endl;
		cout<<(stack2.pop());
		cout<<(stack2.getmin()) << endl;

	}

}

void test_Code05_GetMinStack() {

	cout << "test_Code05_GetMinStack begin" << endl;
	Code05_GetMinStack::test_main();
	cout << "test_Code05_GetMinStack end" << endl;
}