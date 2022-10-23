#pragma once
#ifndef Code03_IsRotation_HPP
#define Code03_IsRotation_HPP
#include <vector>
#include <iostream>
#include <string>
using namespace std;
namespace Code03_IsRotation {

	class Solution
	{
	public:
		bool isRotation(const string & s1, const string &s2)
		{
			if (s1.size() == 0 || s2.size() == 0 || s1.size() != s2.size())
			{
				return false;
			}
			if (s1.size() == 1 && s2.size() == 1)
			{
				return s1 == s2;
			}
			string source = s2 + s2;
			string match = s1;
			int pos = GetIndexOf(source, match);
			if (pos != -1)
			{
				return true;
			}
			return false;
		}

		int GetIndexOf(const string & source, const string & match)
		{
			if (source.size() < match.size() || source.size() < 1 ||
				match.size() < 1)
			{
				return -1;
			}
			int S = source.size();
			int M = match.size();
			int i = 0;
			int j = 0;
			vector<int> next = getNextArray(match);
			while (i < S&& j < M)
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
				else
				{
					j = next[j];
				}
			}
			return j == M ? i - j : -1;
		}

		vector<int> getNextArray(const string & match) {
			
			if (match.size() == 1)
			{
				return { -1 };
			}
			int N = match.size();
			vector<int> next(N, 0);
			next[0] = -1;
			next[1] = 0;
			int cn = 0;
			int i = 2;
			while (i < N)
			{
				if (match[i - 1] == match[cn])
				{
					next[i] = cn + 1;
					cn++;
					i++;
				}
				else if(next[cn] == -1)
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

void test_Code03_IsRotation() {
	cout << "test_Code03_IsRotation begin" << endl;
	Code03_IsRotation::Solution sln;

	string s1 = "amfaingasidniagfnasd";
	string s2 = "sidniagfnasdamfainga";
	string s3 = "mfaingasidniagfnasdb";
	bool ans1 = sln.isRotation(s1, s2);
	cout << "ans1:" << ans1 << endl;
	bool ans2 = sln.isRotation(s2, s3);
	cout << "ans2:" << ans2 << endl;
	cout << "test_Code03_IsRotation end" << endl;
}

#endif