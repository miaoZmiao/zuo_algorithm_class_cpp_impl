#pragma once
#ifndef Code02_AddShortestEnd_HPP
#define Code02_AddShortestEnd_HPP
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
namespace Code02_AddShortestEnd {

	class Solution
	{
	public:
		std::string shortestEnd(std::string s)
		{
			string ms = makeManacherstr(s);
			int N = ms.size();
			vector<int> pArr(N, 0);
			int R = -1;
			int C = -1;
			int maxRadius = 0;
			for (int i = 0; i < N; i++)
			{
				pArr[i] = R > i ? std::min(pArr[2 * C - i], R - i) : 1;
				while (i + pArr[i] < N&& i - pArr[i] >= 0)
				{
					if (ms[i + pArr[i]] == ms[i - pArr[i]])
					{
						pArr[i]++;
					}
					else
					{
						break;
					}
				}
				if (i + pArr[i] > R)
				{
					R = i + pArr[i];
					C = i;
				}
				if (R == N)
				{
					maxRadius = pArr[i] - 1;
					break;
				}
			}
			string ans;
			int ON = s.size();
			int left = ON - maxRadius;
			for (int i = left-1; i>=0; i--)
			{
				ans.push_back(s[i]);
			}
			return ans;
		}

		std::string makeManacherstr(std::string s)
		{
			int N = s.size();
			string sret;
			for (int i = 0; i < N; i++)
			{
				sret.push_back('#');
				sret.push_back(s[i]);
			}
			sret.push_back('#');
			return sret;
		}
	};
}

void test_Code02_AddShortestEnd() {

	string s = "aabbccddcc";
	Code02_AddShortestEnd::Solution sln;
	string ans = sln.shortestEnd(s);
	cout << ans << endl;
}

#endif