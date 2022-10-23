#pragma once
#ifndef Code01_KMP_HPP
#define Code01_KMP_HPP
#include <vector>
#include <string>
#include "utility_func.hpp"
#include "stop_watch.hpp"
using namespace std;

// KMP算法
// 假设字符串str长度为N，字符串match长度为M，M <= N
// 想确定str中是否有某个子串是等于match的。
// 时间复杂度O(N)


namespace Code01_KMP {

	class Solution {

	public:
		int getIndexOf(const std::string & source, const std::string& match)
		{
			if (source.size() == 0 || match.size()<1 || source.size() < match.size()) {
				return -1;
			}
			vector<int> next = getNextArray(match);

			int N = source.size();
			int M = match.size();
			int i = 0;
			int j = 0;
			while (i < N && j<M)
			{
				if (source[i] == match[j])
				{
					i++;
					j++;
				}
				//  j = 0
				else if (next[j] == -1)
				{
					i++;
				}
				else
				{
					j = next[j];
				}
			}
			return j == M ? i - j : -1;
		}

		vector<int> getNextArray(const std::string & match)
		{
			if (match.size() == 1)
			{
				return { -1 };
			}
			vector<int> next(match.size(), 0);
			next[0] = -1;
			next[1] = 0;
			int cn = 0;
			int i = 2;
			int N = match.size();
			while (i < N)
			{
				if (match[i - 1] == match[cn])
				{
					next[i] = ++cn;
					i++;
				}
				else if (next[cn] != -1)
				{
					cn = next[cn];
				}
				else
				{
					next[i++] =0;
				}
			}
			return next;
		}

		int getIndexOf_1(const std::string & source, const std::string& match)
		{
			if (source.size() < 1 || source.size() < match.size() ||
				match.size() < 1)
			{
				return -1;
			}
			int S = source.size();
			int M = source.size();
			int i = 0;
			int j = 0;

			vector<int> next = getNextArray_1(match);

			while (i < S&&j < M)
			{
				if (source[i] == match[j])
				{
					i++;
					j++;
				}
				else if (next[j] == -1)
				{
					i++;
				}
				else {
				
					j = next[j];
				}
			}

			return j == M ? i - j : -1;

		}
		vector<int> getNextArray_1(const std::string & match)
		{
			if (match.size() == 1)
			{
				return { -1 };
			}
			int N = match.size();
			vector<int>  next(N, 0);
			next[0] = -1;
			next[1] = 1;
			int cn = 0;
			int i = 2;
			while (i < N)
			{
				// 
				if (match[i - 1] == match[cn])
				{
					next[i] = cn + 1;
					cn++;
					i++;
				}
				else if (next[cn] == -1)
				{
					next[i] = 0;
					i++;
				}
				else 
				{
					cn = next[cn];
				}
			}
			return next;

		}
	};

	




}

void test_Code01_KMP(){

	cout << "test_Code01_KMP begin" << endl;
	Code01_KMP::Solution sln;
	int maxlen = 10;
	int maxmatchlen = 2;
	int testTime = 10;
	for (int i = 0; i < testTime; i++)
	{
		/*string match = generatestr(maxmatchlen, 'a', 'g');
		string source = generatestr(maxlen, 'a', 'g');*/
		string match = "sdagasdafa";
		string source = "absafshasdagasdafaggfgasdas";
		int pos = sln.getIndexOf(source, match);
		if (1) {
			cout << "source:"<< source << endl;
			cout << "match:" << match << endl;
			cout << "pos:" << pos << endl;
		}
	}
	cout << "test_Code01_KMP end" << endl;

}

#endif