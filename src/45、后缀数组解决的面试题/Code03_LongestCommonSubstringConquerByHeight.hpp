#pragma once
#ifndef Code03_LongestCommonSubstringConquerByHeight_HPP
#define Code03_LongestCommonSubstringConquerByHeight_HPP
#include "utility_func.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include "stop_watch.hpp"
using namespace std;
// 最长公共子串问题是面试常见题目之一
// 假设str1长度N，str2长度M
// 因为最优解的难度所限，一般在面试场上回答出O(N*M)的解法已经是比较优秀了
// 因为得到O(N*M)的解法，就已经需要用到动态规划了
// 但其实这个问题的最优解是O(N+M)，为了达到这个复杂度可是不容易
// 首先需要用到DC3算法得到后缀数组(sa)
// 进而用sa数组去生成height数组
// 而且在生成的时候，还有一个不回退的优化，都非常不容易理解
// 这就是后缀数组在面试算法中的地位 : 德高望重的噩梦
namespace Code03_LongestCommonSubstringConquerByHeight {


	class DC3 {
	public:
		vector<int> sa_;
		vector<int> rank_;
		vector<int> height_;

		DC3() {

		}

		bool precheck(vector<int> & nums, int max)
		{
			// 
			auto iter = std::find_if(nums.begin(), nums.end(), [&](int num) {
				if (num < 1 || num > max)
				{
					return true;
				}
				return false;
			});

			// 不允许小于1的元素存在 或者大于 max的元素存在
			if (iter != nums.end())
			{
				return false;
			}

			return true;
		}

		void reset(vector<int> & nums, int max) {

			if (false == precheck(nums, max))
			{
				throw "get out!!!!";
			}
			sa_ = sa(nums, max);
			rank_ = rank();
			height_ = height(nums);
		}
		vector<int> sa(vector<int> & nums, int max) {
			int n = nums.size();
			vector<int> arr(n + 3, 0);
			for (int i = 0; i < n; i++) {
				arr[i] = nums[i];
			}
			return skew(arr, n, max);
		}
		vector<int> skew(vector<int> & nums, int n, int K)
		{
			int n0 = (n + 2) / 3, n1 = (n + 1) / 3, n2 = n / 3, n02 = n0 + n2;
			vector<int> s12(n02 + 3, 0);
			vector<int> sa12(n02 + 3, 0);
			for (int i = 0, j = 0; i < n + (n0 - n1); ++i) {
				if (0 != i % 3) {
					s12[j++] = i;
				}
			}
			radixPass(nums, s12, sa12, 2, n02, K);
			radixPass(nums, sa12, s12, 1, n02, K);
			radixPass(nums, s12, sa12, 0, n02, K);
			int name = 0, c0 = -1, c1 = -1, c2 = -1;
			for (int i = 0; i < n02; ++i) {
				if (c0 != nums[sa12[i]] || c1 != nums[sa12[i] + 1] || c2 != nums[sa12[i] + 2]) {
					name++;
					c0 = nums[sa12[i]];
					c1 = nums[sa12[i] + 1];
					c2 = nums[sa12[i] + 2];
				}
				if (1 == sa12[i] % 3) {
					s12[sa12[i] / 3] = name;
				}
				else {
					s12[sa12[i] / 3 + n0] = name;
				}
			}
			if (name < n02) {
				sa12 = skew(s12, n02, name);
				for (int i = 0; i < n02; i++) {
					s12[sa12[i]] = i + 1;
				}
			}
			else {
				for (int i = 0; i < n02; i++) {
					sa12[s12[i] - 1] = i;
				}
			}
			vector<int> s0(n0, 0);
			vector<int> sa0(n0, 0);
			for (int i = 0, j = 0; i < n02; i++) {
				if (sa12[i] < n0) {
					s0[j++] = 3 * sa12[i];
				}
			}
			radixPass(nums, s0, sa0, 0, n0, K);
			vector<int> sa(n, 0);
			for (int p = 0, t = n0 - n1, k = 0; k < n; k++) {
				int i = sa12[t] < n0 ? sa12[t] * 3 + 1 : (sa12[t] - n0) * 3 + 2;
				int j = sa0[p];
				if (sa12[t] < n0 ? leq(nums[i], s12[sa12[t] + n0], nums[j], s12[j / 3])
					: leq(nums[i], nums[i + 1], s12[sa12[t] - n0 + 1], nums[j], nums[j + 1], s12[j / 3 + n0])) {
					sa[k] = i;
					t++;
					if (t == n02) {
						for (k++; p < n0; p++, k++) {
							sa[k] = sa0[p];
						}
					}
				}
				else {
					sa[k] = j;
					p++;
					if (p == n0) {
						for (k++; t < n02; t++, k++) {
							sa[k] = sa12[t] < n0 ? sa12[t] * 3 + 1 : (sa12[t] - n0) * 3 + 2;
						}
					}
				}
			}
			return sa;
		}

		void radixPass(vector<int> & nums, vector<int> & input, vector<int> & output,
			int offset, int n, int k) {
			vector<int>  cnt(k + 1, 0);
			for (int i = 0; i < n; ++i) {
				cnt[nums[input[i] + offset]]++;
			}
			vector<int> sum(k + 1, 0);
			for (int i = 0, tmp_sum = 0; i < cnt.size(); ++i) {
				int t = cnt[i];
				sum[i] = tmp_sum;
				tmp_sum += t;
			}
			for (int i = 0; i < n; ++i) {
				output[sum[nums[input[i] + offset]]++] = input[i];
			}
		}

		bool leq(int a1, int a2, int b1, int b2) {
			return a1 < b1 || (a1 == b1 && a2 <= b2);
		}
		bool leq(int a1, int a2, int a3, int b1, int b2, int b3) {
			return a1 < b1 || (a1 == b1 && leq(a2, a3, b2, b3));
		}

		vector<int> rank() {
			int n = sa_.size();
			vector<int> ans(n, 0);
			for (int i = 0; i < n; i++) {
				ans[sa_[i]] = i;
			}
			return ans;
		}

		vector<int> height(vector<int> & s) {
			int n = s.size();
			vector<int> ans(n, 0);
			for (int i = 0, k = 0; i < n; ++i) {
				if (rank_[i] != 0) {
					if (k > 0) {
						--k;
					}
					int j = sa_[rank_[i] - 1];
					while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
						++k;
					}
					ans[rank_[i]] = k;
				}
			}
			return ans;
		}
	};

	class Solution {

	public:
		int process(const string & s1, int index1, const string & s2, int index2)
		{
			if (index1 == 0 || index2 == 0)
			{
				if (s1[index1] == s2[index2])
				{
					return 1;
				}
				return 0;
			}
			int ans = INT_MIN;
			if (s1[index1] == s2[index2])
			{
				ans = std::max(ans, process(s1, index1 - 1, s2, index2 - 1) + 1);
			}
			ans = std::max(ans, process(s1, index1, s2, index2 - 1));
			ans = std::max(ans, process(s1, index1-1, s2, index2));
			return ans;
			// 错的
			// 这是最长公共子序列，不是最长公共子串
		}


		int lcs1(const string & s1, const string & s2)
		{
			if (s1.size() == 0 || s2.size()== 0 ) {
				return 0;
			}
			int row = 0;
			int col = s2.size() - 1;
			int max = 0;
			while (row < s1.size()) {
				int i = row;
				int j = col;
				int len = 0;
				while (i < s1.size() && j < s2.size()) {
					if (s1[i] != s2[j]) {
						len = 0;
					}
					else {
						len++;
					}
					if (len > max) {
						max = len;
					}
					i++;
					j++;
				}
				if (col > 0) {
					col--;
				}
				else {
					row++;
				}
			}
			return max;
		}
		
		int lcs2(const string & s1, const string & s2)
		{
			if (s1.size() == 0 || s2.size() == 0) {
				return 0;
			}
			int len1 = s1.size();
			int len2 = s2.size();
			int min_num = s1[0];
			int max_num = s1[0];
			for (int i = 1; i < len1; i++)
			{
				int c = s1[i];
				min_num = std::min(min_num, c);
				max_num = std::max(max_num, c);
			}
			for (int i = 0; i < len2; i++)
			{
				int c = s2[i];
				min_num = std::min(min_num, c);
				max_num = std::max(max_num, c);
			}
			vector<int> arr(len1 + len2 + 1);
			for (int i = 0; i < len1; i++)
			{
				int c = s1[i];
				arr[i] = c - min_num + 2;
			}
			arr[len1] = 1;
			for (int i = 0; i < len2; i++)
			{
				int c = s2[i];
				arr[i+len1+1] = c - min_num + 2;
			}

			DC3 dc3;
			dc3.reset(arr, max_num - min_num + 2);
			vector<int> & sa = dc3.sa_;
			vector<int> & height = dc3.height_;
			int ans = INT_MIN;
			for (int i = 1; i < arr.size(); i++)
			{
				int X = sa[i];
				int Y = sa[i - 1];
				if (std::min(X, Y) < len1 && std::max(X, Y) > len1) {
					ans = std::max(ans, height[i]);
				}
			}
			return ans;
		}




	};

}

void test_Code03_LongestCommonSubstringConquerByHeight() {
	int len = 30;
	int range = 5;
	int testTime = 1000;	
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(1, len);
	Code03_LongestCommonSubstringConquerByHeight::Solution sln;
	cout << "test_Code03_LongestCommonSubstringConquerByHeight begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		int N1 = dist(mt);
		int N2 = dist(mt);
		string str1 = generatestr(N1, 'a', 'l');
		string str2 = generatestr(N2, 'a', 'l');
		int ans1 = sln.lcs1(str1, str2);
		int ans2 = sln. lcs2(str1, str2);
		if (ans1 != ans2) {
			cout << str1 << endl;
			cout << str2 << endl;
			cout << ans1 << "," << ans2 << endl;
			break;
		}
	}

	cout << "performance test" << endl;
	len = 80000;
	range = 26;
	long start;
	long end;
	string str1 = generatestr(len, 'a', 'z');
	string str2 = generatestr(len, 'a', 'z');

	stop_watch st;
	st.start();
	int ans1 = sln.lcs1(str1, str2);
	st.stop();
	cout << "lcs1: ans1:" << ans1 << "  cost:" << st.elapsed_ms() << "ms" << endl;
	st.start();
	int ans2 = sln.lcs2(str1, str2);
	st.stop();
	cout << "lcs1: ans2:" << ans1 << "  cost:" << st.elapsed_ms() << "ms" << endl;
	cout << "test_Code03_LongestCommonSubstringConquerByHeight end" << endl;

	//// 某次输出
	/*	test_Code03_LongestCommonSubstringConquerByHeight begin
		performance test
		lcs1 : ans1:7  cost : 126098ms
		lcs1 : ans2:7  cost : 78.174ms
		test_Code03_LongestCommonSubstringConquerByHeight end*/


}

#endif