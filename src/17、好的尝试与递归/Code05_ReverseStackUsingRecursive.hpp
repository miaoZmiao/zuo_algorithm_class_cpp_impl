#pragma once
#ifndef Code05_ReverseStackUsingRecursive_HPP
#define Code05_ReverseStackUsingRecursive_HPP
#include <stack>
#include <iostream>
using namespace  std;
namespace Code05_ReverseStackUsingRecursive
{
	int func_get_stack_bottom_element(std::stack<int> &stack)
	{
		int cur = stack.top();
		stack.pop();
		if (stack.empty())
		{
			return cur;
		}
		int last = func_get_stack_bottom_element(stack);
		stack.push(cur);
		return last;
	}

	void reverse(std::stack<int> &stack)
	{
		if (stack.empty())
		{
			return;
		}
		int element = func_get_stack_bottom_element(stack);
		reverse(stack);
		stack.push(element);
	}
}

void printStack_help(std::stack<int> & stack)
{
	if (stack.empty())
	{
		cout << "]" << endl;
		return;
	}
	int cur = stack.top();
	stack.pop();
	if (!stack.empty())
	{
		cout << cur << ",";
	}
	else
	{
		cout << cur;
	}
	printStack_help(stack);
	stack.push(cur);
	
}

void printStack(std::stack<int> & stack)
{
	cout << "stack : [";
	printStack_help(stack);
}



void test_Code05_ReverseStackUsingRecursive()
{
	int indexbegin = 1;
	int indexend = 5;
	std::stack<int> st;
	int index = indexbegin;
	
	while (index <= indexend)
	{
		st.push(index);
		index++;
	}
	printStack(st);
	cout << " reverse stack " << endl;
	Code05_ReverseStackUsingRecursive::reverse(st);
	printStack(st);
	

}


#endif