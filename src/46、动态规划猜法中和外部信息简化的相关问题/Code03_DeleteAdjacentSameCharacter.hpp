#pragma once
#ifndef Code03_DeleteAdjacentSameCharacter_HPP
#define Code03_DeleteAdjacentSameCharacter_HPP
#include "utility_func.hpp"
#include <iostream>
#include <algorithm>
#include <string>
// 如果一个字符相邻的位置没有相同字符，那么这个位置的字符出现不能被消掉
// 比如:"ab"，其中a和b都不能被消掉
// 如果一个字符相邻的位置有相同字符，就可以一起消掉
// 比如:"abbbc"，中间一串的b是可以被消掉的，消除之后剩下"ac"
// 某些字符如果消掉了，剩下的字符认为重新靠在一起
// 给定一个字符串，你可以决定每一步消除的顺序，目标是请尽可能多的消掉字符，返回最少的剩余字符数量
// 比如："aacca", 如果先消掉最左侧的"aa"，那么将剩下"cca"，然后把"cc"消掉，剩下的"a"将无法再消除，返回1
// 但是如果先消掉中间的"cc"，那么将剩下"aaa"，最后都消掉就一个字符也不剩了，返回0，这才是最优解。
// 再比如："baaccabb"，
// 如果先消除最左侧的两个a，剩下"bccabb"，
// 如果再消除最左侧的两个c，剩下"babb"，
// 最后消除最右侧的两个b，剩下"ba"无法再消除，返回2
// 而最优策略是：
// 如果先消除中间的两个c，剩下"baaabb"，
// 如果再消除中间的三个a，剩下"bbb"，
// 最后消除三个b，不留下任何字符，返回0，这才是最优解

namespace Code03_DeleteAdjacentSameCharacter {

	class Solution {
	public:
		// 暴力解
		 int restMin1(string s) {

			if (s.size() < 2) {
				return s.size();
			}
			int minLen = s.size();
			for (int L = 0; L < s.size(); L++) {
				for (int R = L + 1; R < s.size(); R++) {
					if (canDelete(s.substr(L, R-L+ 1))) {
						minLen = std::min(minLen, restMin1(s.substr(0, L) + s.substr(R + 1)));
					}
				}
			}
			return minLen;
		}

		 bool canDelete(string s) {
			 for (int i = 1; i < s.size(); i++) {
				 if (s[i - 1] != s[i]) {
					 return false;
				 }
			 }
			 return true;
		 }

		 // 优良尝试的暴力递归版本
		 int restMin2(string str) {
			 if (str.size() < 2) {
				 return str.size();
			 }
			 return process(str, 0, str.size()-1, false);
		 }



		 int process(string str, int L, int R, bool has) {
			 if (L > R) {
				 return 0;
			 }
			 if (L == R) {
				 return has ? 0 : 1;
			 }
			 int index = L;
			 int K = has ? 1 : 0;
			 while (index <= R && str[index] == str[L]) {
				 K++;
				 index++;
			 }
			 // index表示，第一个不是[L]字符的位置
			 int way1 = (K > 1 ? 0 : 1) + process(str, index, R, false);
			 int way2 = INT_MAX;
			 for (int split = index; split <= R; split++) {
				 if (str[split] == str[L] && str[split] != str[split - 1]) {
					 if (process(str, index, split - 1, false) == 0) {
						 way2 = std::min(way2, process(str, split, R, K != 0));
					 }
				 }
			 }
			 return std::min(way1, way2);
		 }

		 // 优良尝试的动态规划版本
		 int restMin3(string str) {

			 if (str.length() < 2) {
				 return str.length();
			 }
			 int N = str.size();
			 vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(2, -1)));
			 return dpProcess(str, 0, N - 1, false, dp);
		 }

		 int dpProcess(string str, int L, int R, bool has, vector<vector<vector<int>>>& dp) {
			 if (L > R) {
				 return 0;
			 }
			 int K = has ? 1 : 0;
			 if (dp[L][R][K] != -1) {
				 return dp[L][R][K];
			 }
			 int ans = 0;
			 if (L == R) {
				 ans = (K == 0 ? 1 : 0);
			 }
			 else {
				 int index = L;
				 int all = K;
				 while (index <= R && str[index] == str[L]) {
					 all++;
					 index++;
				 }
				 int way1 = (all > 1 ? 0 : 1) + dpProcess(str, index, R, false, dp);
				 int way2 = INT_MAX;
				 for (int split = index; split <= R; split++) {
					 if (str[split] == str[L] && str[split] != str[split - 1]) {
						 if (dpProcess(str, index, split - 1, false, dp) == 0) {
							 way2 = std::min(way2, dpProcess(str, split, R, all > 0, dp));
						 }
					 }
				 }
				 ans = std::min(way1, way2);
			 }
			 dp[L][R][K] = ans;
			 return ans;
		 }
	};

}


void test_Code03_DeleteAdjacentSameCharacter() {
	int maxLen = 16;
	int variety = 3;
	int testTime = 1000;

	cout << "test_Code03_DeleteAdjacentSameCharacter begin" << endl;
	Code03_DeleteAdjacentSameCharacter::Solution sln;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(1, maxLen);
	for (int i = 0; i < testTime; i++) {
		int len = dist(mt);
		string str = generatestr(len, 'a','h');
		int ans1 = sln.restMin1(str);
		int ans2 = sln.restMin2(str);
		int ans3 = sln.restMin3(str);
		if (ans1 != ans2 || ans1 != ans3) {
			cout << ans1 << "," << ans2 << "," << ans3 << endl;
			cout << "出错了！" << endl;
			break;
		}
	}
	cout << "test_Code03_DeleteAdjacentSameCharacter end" << endl;
}


#endif