#pragma once
#ifndef Code04_PrintAllPermutations_HPP
#define Code04_PrintAllPermutations_HPP
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace PrintAllPermutations {



	void process1(string & input, int index,
		vector<string> &ans);
	vector<string> permutation1(string & input) {

		vector<string> ans;
		process1(input, 0, ans);
		return ans;
	}

	void swap(string & input, int index1, int index2)
	{
		if (index1 == index2)
		{
			return;
		}
		char tmp = input[index1];
		input[index1] = input[index2];
		input[index2] = tmp;
	}


	void process1(string & input, int index, 
		vector<string> &ans)
	{
		if (index == input.size())
		{	
			ans.push_back(input);
			return;
		}
		for (int i = index; i < input.size(); i++)
		{
			swap(input, index, i);
			process1(input, index+1, ans);
			swap(input, index, i);
		}
	}

	// process2 属于去重版本
	void process2(string & input, int index,
		vector<string> &ans)
	{
		if (index == input.size())
		{
			ans.push_back(input);
			return;
		}
		bool visited[256] = { false };
		for (int i = index; i < input.size(); i++)
		{
			if (false == visited[input[i]])
			{
				visited[input[i]] = true;
				swap(input, index, i);
				process2(input, index + 1, ans);
				swap(input, index, i);
			}
		}
	}

	vector<string> permutation2(string & input)
	{
		vector<string> ans;
		process2(input, 0, ans);
		return ans;
	}




}



void test_permutation()
{
	cout << "test_permutation begin" << endl;
	string input = "aac";

	vector<string> ans = PrintAllPermutations::permutation1(input);
	cout << "=======================" << endl;
	for (auto & it : ans)
	{
		cout << it << endl;
	}
	cout << "=======================" << endl;
	ans = PrintAllPermutations::permutation2(input);
	for (auto & it : ans)
	{
		cout << it << endl;
	}
	cout << "=======================" << endl;
	cout << "test_permutation end" << endl;
}








#endif