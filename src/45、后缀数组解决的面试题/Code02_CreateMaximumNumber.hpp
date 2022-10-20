#pragma once
#ifndef Code02_CreateMaximumNumber_HPP
#define Code02_CreateMaximumNumber_HPP
#include "utility_func.hpp"
namespace Code02_CreateMaximumNumber {

	class DC3 {
	public:
		vector<int> sa_;
		vector<int> rank_;
		vector<int> height_;

		DC3() {

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

	// ²âÊÔÁ´½Ó: https://leetcode.com/problems/create-maximum-number/
	class Solution {

	public:

		// force
		vector<int> maxNumber1(vector<int>& nums1, vector<int>& nums2, int k)
		{
			int len1 = nums1.size();
			int len2 = nums2.size();
			if (k <= 0 || k > len1 + len2)
			{
				return { };
			}
			vector<int> ans(k, 0);

			vector<vector<int>> dp1 = getdp(nums1);

			vector<vector<int>> dp2 = getdp(nums2);

			for (int get1 = std::max(0, k - len2); get1 <= std::min(k, len1); get1++)
			{
				vector<int> pick1 = maxPick(nums1, dp1, get1);
				vector<int> pick2 = maxPick(nums2, dp2, k - get1);
				vector<int> mg = merge(pick1, pick2);
				if (!preMoreThanLast(ans, 0, mg, 0))
				{
					ans.swap(mg);
				}				
			}
			return ans;
		}

		vector<int> merge(vector<int>& nums1, vector<int>& nums2)
		{
			int k = nums1.size() + nums2.size();
			vector<int> ans(k, 0);
			for (int i = 0, j = 0, r = 0; r < k; ++r) {
				ans[r] = preMoreThanLast(nums1, i, nums2, j) ? nums1[i++] : nums2[j++];
			}
			return ans;
		}


		bool preMoreThanLast(vector<int>& nums1, int i, vector<int>& nums2, int j)
		{
			while (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j])
			{
				i++;
				j++;
			}
			if (j == nums2.size())
			{
				return true;
			}
			if (i < nums1.size() && nums1[i] > nums2[j])
			{
				return true;
			}
			return false;
		}


		// dc3
		vector<int> maxNumber2(vector<int>& nums1, vector<int>& nums2, int k)
		{
			int len1 = nums1.size();
			int len2 = nums2.size();
			if (k <= 0 || k > len1 + len2)
			{
				return { };
			}
			vector<int> ans(k, 0);

			vector<vector<int>> dp1 = getdp(nums1);
			vector<vector<int>> dp2 = getdp(nums2);

			for (int get1 = std::max(0, k - len2); get1 <= std::min(k, len1); get1++)
			{
				vector<int> pick1 = maxPick(nums1, dp1, get1);
				vector<int> pick2 = maxPick(nums2, dp2, k - get1);

				vector<int> mg = mergeBySuffixArray(pick1, pick2);
				
				if (!moreThan(ans, mg))
				{
					ans.swap(mg);
				}
			}
			return ans;
		}

		vector<int> mergeBySuffixArray(vector<int> & nums1, vector<int> & nums2) {
			int s1 = nums1.size();
			int s2 = nums2.size();
			vector<int> nums(s1 + 1 +s2);
			for (int i = 0; i < s1; i++) {
				nums[i] = nums1[i] + 2;
			}
			nums[s1] = 1;
			for (int j = 0; j < s2; j++) {
				nums[j + s1 + 1] = nums2[j] + 2;
			}
			DC3 dc3;
			dc3.reset(nums, 11);
			vector<int> & rank = dc3.rank_;
			int i = 0;
			int j = 0;
			int r = 0;

			vector<int> ans(s1 + s2);
			while (i < s1 && j < s2) {
				ans[r++] = rank[i] > rank[j + s1 + 1] ? nums1[i++] : nums2[j++];
			}
			while (i < s1) {
				ans[r++] = nums1[i++];
			}
			while (j < s2) {
				ans[r++] = nums2[j++];
			}
			return ans;
		}



		bool moreThan(vector<int>& pre, vector<int>& last)
		{
			int i = 0;
			int j = 0;
			while (i < pre.size() && j < last.size() && pre[i] == last[j])
			{
				i++;
				j++;
			}
			if (j == last.size())
			{
				return true;
			}
			if (i < pre.size() && pre[i] > last[j])
			{
				return true;
			}
			return false;
		}

		vector<vector<int>> getdp(vector<int>& arr)
		{
			int N = arr.size();
			
			vector<vector<int>> dp(N, vector<int>(N + 1, 0));

			for (int get = 1; get <= N; get++)
			{
				int maxIndex = N - get;
				for (int index = maxIndex; index >= 0; index--)
				{
					if (arr[index] >= arr[maxIndex])
					{
						maxIndex = index;
					}
					dp[index][get] = maxIndex;
				}
			}
			return dp;
		}

		vector<int> maxPick(vector<int>& arr, vector<vector<int>>& dp, int pick)
		{
			vector<int> ans(pick, 0);
			int pos = 0;
			for (int i = pick, resindex = 0; i >=1; i--, resindex++)
			{
				ans[resindex] = arr[dp[pos][i]];
				pos = dp[pos][i] + 1;
			}
			return ans;
		}
	};
}

void test_Code02_CreateMaximumNumber() {

	/*[3, 4, 6, 5]
	[9, 1, 2, 5, 8, 3]
	5*/
	vector<int> nums1{ 3, 4, 6, 5 };
	vector<int> nums2{ 9, 1, 2, 5, 8, 3 };
	int k = 5;
	Code02_CreateMaximumNumber::Solution sln;
	cout << "test_Code02_CreateMaximumNumber begin" << endl;
	vector<int> ans = sln.maxNumber2(nums1, nums2, k);
	print(ans);
	cout << "test_Code02_CreateMaximumNumber end" << endl;

}


#endif