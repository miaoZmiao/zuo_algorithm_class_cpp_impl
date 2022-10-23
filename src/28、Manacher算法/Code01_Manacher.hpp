#pragma once
#ifndef Code01_Manacher_HPP
#define Code01_Manacher_HPP
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
namespace Code01_Manacher {

	class Solution
	{
	public:
		int manacher(std::string s)
		{
			string ms = makeManacherstr(s);

			int C = -1;
			int R = -1;
			int N = ms.size();
			vector<int> pArr(N, 0);
			for (int i = 0; i < N; i++)
			{
				pArr[i] = R > i ? std::min(pArr[2*C-i],R-i):1;
				while (i + pArr[i] < N&&i-pArr[i] >= 0)
				{
					if (ms[i + pArr[i]] == ms[i - pArr[i]])
					{
						pArr[i]++;
					}
					else {
						break;
					}
				}
				if(i + pArr[i] > R)
				{
					R = pArr[i];
					C = i;
				}
			}
			int maxLen = 0;
			for (int i = 0; i < N; i++)
			{
				maxLen = std::max(maxLen, pArr[i]);
			}
			//#a#b#a#
			return maxLen - 1;
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

void test_Code01_Manacher() {

	cout << "test_Code01_Manacher begin" << endl;
	std::string pali = "abcdcba";
	Code01_Manacher::Solution sln;
	int ans = sln.manacher(pali);
	cout << pali << endl;
	cout << ans << endl;
	cout << "test_Code01_Manacher end" << endl;
}


#endif