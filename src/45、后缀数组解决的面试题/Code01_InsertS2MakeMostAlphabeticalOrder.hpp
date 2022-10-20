#pragma once
#ifndef Code01_InsertS2MakeMostAlphabeticalOrder_HPP
#define Code01_InsertS2MakeMostAlphabeticalOrder_HPP
#include "utility_func.hpp"
#include <string>
#include <algorithm>

namespace Code01_InsertS2MakeMostAlphabeticalOrder {

	 class DC3 {
		
	 public:
		vector<int> sa_;

		vector<int> rank_;

		DC3() {}
		void reset(vector<int> & nums, int maxNum) {
			int N = nums.size();
			vector<int> arr(N + 3, 0);
			for (int i = 0; i < N; i++)
			{
				arr[i] = nums[i];
			}
			sa_ = skew(arr, N, maxNum);
			rank_ = rank();
		}

		vector<int> skew(vector<int> & nums, int n, int maxNum) {
			int n0 = (n + 2) / 3;
			int n1 = (n + 1) / 3;
			int n2 = (n) / 3;
			int n02 = n0 + n2;
			vector<int> s12(n02 + 3, 0);
			vector<int> sa12(n02 + 3, 0);
			for (int i = 0, j = 0; i < n + (n0 - n1); i++)
			{
				if (i % 3 != 0)
				{
					s12[j++] = i;
				}
			}
			radixsort(nums, s12, sa12, 2, n02, maxNum);
			radixsort(nums, sa12, s12, 1, n02, maxNum);
			radixsort(nums, s12, sa12, 0, n02, maxNum);
		
			//cout << "DC3 print sa12" << endl;
			//print(sa12);
			// 1,4,7..... 2,5,8,11......
			int name = 0;
			int c0 = -1;
			int c1 = -1;
			int c2 = -1;
			for (int i = 0; i < n02; i++)
			{
				int index = sa12[i];
				if (nums[index] != c0 ||
					nums[index + 1] != c1 ||
					nums[index + 2] != c2)
				{
					name++;
					c0 = nums[index];
					c1 = nums[index + 1];
					c2 = nums[index + 2];
				}
				if (index % 3 == 1)
				{
					s12[index / 3] = name;
				}
				else
				{
					s12[index / 3 + n0] = name;
				}
			}
			if (name < n02)
			{
				sa12 = skew(s12, n02, name);
				for (int i = 0; i < n02; i++)
				{
					s12[sa12[i]] = i + 1;
				}
			}
			else
			{
				for (int i = 0; i < n02; i++)
				{
					sa12[s12[i] - 1] = i;
				}
			}
			// s0
			vector<int> s0(n0, 0);
			vector<int> sa0(n0, 0);
			for (int i = 0, j = 0; i < n02; i++)
			{
				if (sa12[i] < n0)
				{
					s0[j++] = sa12[i] * 3;
				}
			}
			radixsort(nums, s0, sa0, 0, n0, maxNum);
			//cout << "DC3 print sa0" << endl;
			//print(sa0);

			// merge  s0 and s12
			vector<int> ans(n, 0);
			/*DC3 right sa[0] = 3
				DC3 right sa[1] = 0
				DC3 right sa[2] = 4
				DC3 right sa[3] = 5
				DC3 right sa[4] = 2
				DC3 right sa[5] = 6
				DC3 right sa[6] = 1*/
			for (int i = 0, j = n0 - n1, k = 0; k < n; k++)
			{
				int s12idx = sa12[j] < n0 ? sa12[j] * 3 + 1 : 3*(sa12[j]-n0) + 2;
				int s0idx = sa0[i];
				if (sa12[j] < n0 ?
					leq(nums[s12idx], s12[sa12[j] + n0], nums[s0idx], s12[s0idx / 3]) :
					leq(nums[s12idx], nums[s12idx + 1], s12[sa12[j]-n0+1],
						nums[s0idx], nums[s0idx + 1], s12[s0idx / 3 + n0])
					)
				{
					j++;
					ans[k] = s12idx;
					//cout << "DC3  sa[" << k << "]=" << ans[k] << endl;
					if (j == n02)
					{
						for (k++; k < n && i < n0; k++)
						{
							ans[k] = sa0[i++];
							///cout << "DC3  sa[" << k << "]=" << ans[k] << endl;
						}
					}
				}
				else
				{
					i++;
					ans[k] = s0idx;
					//cout << "DC3  sa[" << k << "]=" << ans[k] << endl;
					if (i == n0)
					{
						for (k++; k < n && j<n02; k++, j++)
						{
							if (sa12[j] < n0)
							{
								ans[k] = sa12[j] * 3 + 1;
								//cout << "DC3  sa[" << k << "]=" << ans[k] << endl;
							}
							else
							{
								ans[k] = (sa12[j]-n0) * 3 + 2;
								//cout << "DC3  sa[" << k << "]=" << ans[k] << endl;
							}
						}
					}
				}
				
			}
			return ans;
		}

		void radixsort(vector<int> & nums,
			vector<int>& input,
			vector<int> & output,
			int offset, int N, int maxnum
		)
		{
			vector<int> count(maxnum + 1, 0);
			for (int i = 0; i < N; i++)
			{
				count[nums[input[i] + offset]]++;
			}

			// accumulate count array
			for (int i = 0, sum = 0; i < maxnum + 1; i++)
			{
				int tmpsum = count[i];
				count[i] = sum;
				sum += tmpsum;
			}

			for (int i = 0; i < N; i++)
			{
				output[count[nums[input[i] + offset]]++] = input[i];
			}
		}

		bool leq(int a1, int a2, int b1, int b2)
		{
			if (a1 == b1)
			{
				return a2 <= b2;
			}
			return a1 < b1;
		}

		bool leq(int a1, int a2, int a3, int b1, int b2, int b3)
		{
			if (a1 == b1)
			{
				return leq(a2, a3, b2, b3);
			}
			return a1 < b1;
		}

		vector<int> rank() {

			int N = sa_.size();
			vector<int> ans(N, 0);
			for (int i = 0; i < N; i++)
			{
				ans[sa_[i]] = i;
			}
			return ans;
		}
	};

	class DC3_right {
public:
	vector<int> sa_;
	vector<int> rank_;
	vector<int> height_;

	DC3_right() {

	}

	void reset(vector<int> & nums, int max) {
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
		//cout << "DC3_right print sa12" << endl;
		//print(sa12);
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
		//cout << "DC3_right print sa0" << endl;
		//print(sa0);
		vector<int> sa(n, 0);
		for (int p = 0, t = n0 - n1, k = 0; k < n; k++) {
			int i = sa12[t] < n0 ? sa12[t] * 3 + 1 : (sa12[t] - n0) * 3 + 2;
			int j = sa0[p];
			if (sa12[t] < n0 ? leq(nums[i], s12[sa12[t] + n0], nums[j], s12[j / 3])
				: leq(nums[i], nums[i + 1], s12[sa12[t] - n0 + 1], nums[j], nums[j + 1], s12[j / 3 + n0])) {
				sa[k] = i;
				//cout << "DC3 right sa[" << k << "]=" << sa[k] << endl;
				t++;
				if (t == n02) {
					for (k++; p < n0; p++, k++) {
						sa[k] = sa0[p];
						//cout << "DC3 right sa[" << k << "]=" << sa[k] << endl;
					}
				}
			}
			else {
				sa[k] = j;
				//cout << "DC3 right sa[" << k << "]=" << sa[k] << endl;
				p++;
				if (p == n0) {
					for (k++; t < n02; t++, k++) {
						sa[k] = sa12[t] < n0 ? sa12[t] * 3 + 1 : (sa12[t] - n0) * 3 + 2;
						//cout << "DC3 right sa[" << k << "]=" << sa[k] << endl;
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
		// 暴力方法
		std::string right(std::string s1, std::string s2)
		{
			if (s1.size() == 0) {
				return s2;
			}
			if (s2.size() == 0) {
				return s1;
			}
			string p1 = s1 + s2;
			string p2 = s2 + s1;
			string ans = p1 > p2 ? p1 : p2;

			for (int i = 1; i < s1.size(); i++)
			{
				string cur = s1.substr(0, i) + s2 + s1.substr(i);
				if (cur > ans)
				{
					ans = cur;
				}
			}
			return ans;
		}
		// 正式方法 O(N+M) + O(M^2)
		// N : s1长度
		// M : s2长度
		string maxCombine(string s1, string s2)
		{
			if (s1.size() == 0) {
				return s2;
			}
			if (s2.size() == 0) {
				return s1;
			}
			int N = s1.size();
			int M = s2.size();
			int minNum = s1[0];
			int maxNum = s1[0];
			for (int i = 1; i < N; i++)
			{
				int c = s1[i];
				minNum = std::min(c, minNum);
				maxNum = std::max(c, maxNum);
			}
			for (int i = 0; i < M; i++)
			{
				int c = s2[i];
				minNum = std::min(c, minNum);
				maxNum = std::max(c, maxNum);
			}
			vector<int> arr(M + N + 1, 0);
			for (int i = 0; i < N; i++)
			{
				int c = s1[i];
				arr[i] = c - minNum + 2;
			}

			for (int i = 0; i < M; i++)
			{
				int c = s2[i];
				arr[i + N + 1] = c - minNum + 2;
			}
			arr[N] = 1;

			DC3_right  dc;
			dc.reset(arr, maxNum - minNum + 2);
			vector<int> & rank = dc.rank_;
			//cout << "DC3 rank" << endl;
			//print(rank);
			string ans;
			int comp_idx = N + 1;
			for (int i = 0; i < N; i++)
			{
				if (rank[i] < rank[comp_idx])
				{
					int best = bestSplit(s1, s2, i);
					return s1.substr(0, best) + s2 + s1.substr(best);
				}
			}
			return s1 + s2;
		}

		int	bestSplit(const string & s1, const string &s2, int from_where) {
			int best = from_where;
			int N = s1.size();
			int M = s2.size();
			int end = N;
			for (int i = from_where,j= 0;i<N&&j<M;i++,j++)
			{
				if (s1[i] < s2[j])
				{
					end = i;
					break;
				}
			}
			string bestPrefix = s2;
			int ans = from_where;
			for (int i = from_where +1,j = M; i <= end ; i++,j--)
			{
				string scmp = s1.substr(from_where, i - from_where) + s2.substr(0,j);
				if (scmp > bestPrefix)
				{
					bestPrefix = scmp;
					ans = i;
				}
			}
			return ans;
		}


		string rightDC3Combine(const string & s1, const string &s2) {
			if (s1.size() == 0) {
				return s2;
			}
			if (s2.size() == 0) {
				return s1;
			}
			int N = s1.size();
			int M = s2.size();
			int minNum = s1[0];
			int maxNum = s1[0];
			for (int i = 1; i < N; i++)
			{
				int c = s1[i];
				minNum = std::min(c, minNum);
				maxNum = std::max(c, maxNum);
			}
			for (int i = 0; i < M; i++)
			{
				int c = s2[i];
				minNum = std::min(c, minNum);
				maxNum = std::max(c, maxNum);
			}
			vector<int> arr(M + N + 1, 0);
			for (int i = 0; i < N; i++)
			{
				int c = s1[i];
				arr[i] = c - minNum + 2;
			}

			for (int i = 0; i < M; i++)
			{
				int c = s2[i];
				arr[i + N + 1] = c - minNum + 2;
			}
			arr[N] = 1;

			DC3  dc;
			dc.reset(arr, maxNum - minNum + 2);
			vector<int> & rank = dc.rank_;
			/*cout << "DC3 right rank" << endl;
			print(rank);*/
			string ans;
			int comp_idx = N + 1;
			for (int i = 0; i < N; i++)
			{
				if (rank[i] < rank[comp_idx])
				{
					int best = bestSplit(s1, s2, i);
					return s1.substr(0, best) + s2 + s1.substr(best);
				}
			}
			return s1 + s2;
		}


		vector<int> make_arr(const string & s1, const string &s2) {
			int N = s1.size();
			int M = s2.size();
			int minNum = s1[0];
			int maxNum = s1[0];
			for (int i = 1; i < N; i++)
			{
				int c = s1[i];
				minNum = std::min(c, minNum);
				maxNum = std::max(c, maxNum);
			}
			for (int i = 0; i < M; i++)
			{
				int c = s2[i];
				minNum = std::min(c, minNum);
				maxNum = std::max(c, maxNum);
			}
			vector<int> arr(M + N + 1, 0);
			for (int i = 0; i < N; i++)
			{
				int c = s1[i];
				arr[i] = c - minNum + 2;
			}

			for (int i = 0; i < M; i++)
			{
				int c = s2[i];
				arr[i + N + 1] = c - minNum + 2;
			}
			arr[N] = 1;
			return arr;
		}

		int getMax(vector<int> & arr) {
			int ans = arr[0];
			for (int i = 0; i < arr.size(); i++)
			{
				ans = std::max(ans, arr[i]);
			}
			return ans;
		}

	};
}

void test_Code01_InsertS2MakeMostAlphabeticalOrder() {
	
	int range = 10;
	int len = 6;
	int testTime = 100;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(1, len);
	Code01_InsertS2MakeMostAlphabeticalOrder::Solution  sln;
	Code01_InsertS2MakeMostAlphabeticalOrder::DC3  dc3;
	Code01_InsertS2MakeMostAlphabeticalOrder::DC3_right dc3right;
	cout << "test_Code01_InsertS2MakeMostAlphabeticalOrder begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		int len1 = dist(mt);
		int len2 = dist(mt);
		string s1 = generatestr(len1, 'a', 'j');
		string s2 = generatestr(len2, 'a', 'j');
		/*s1 = "c";
		s2 = "cb";*/
		/*	c
			cb
			ccb
			cbc*/
		/*vector<int> arr = sln.make_arr(s1, s2);
		int max = sln.getMax(arr);
		dc3.reset(arr, max);
		dc3right.reset(arr, max);
		
		if (!vector_equal(dc3.rank_, dc3right.rank_))
		{
			print(dc3.rank_);
			print(dc3right.rank_);
			break;
		}*/


		string ans1 = sln.right(s1, s2);
		string ans2 = sln.maxCombine(s1, s2);
		//string ans3 = sln.rightDC3Combine(s1, s2);
		if (ans1 != ans2)
		{
			cout << s1 << endl;
			cout << s2 << endl;
			cout << ans1 << endl;
			cout << ans2 << endl;
			break;
		}
	}
	cout << "test_Code01_InsertS2MakeMostAlphabeticalOrder end" << endl;

}

#endif