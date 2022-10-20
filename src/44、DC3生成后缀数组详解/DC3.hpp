#pragma once
#ifndef DC3_HPP
#define DC3_HPP
#include "utility_func.hpp"
#include <algorithm>
namespace DC3 {

	class Solution {
	public:
		vector<int> sa_;
		vector<int> rank_;
		vector<int> height_;

		Solution() {

		}

		bool precheck(vector<int> & nums, int max)
		{
			// 
			auto iter = std::find_if(nums.begin(), nums.end(), [&](int num) {
				if (num < 1 || num > max)
				{
					return true;
				}
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


}

template <class T>
T get_max(vector<T> & nums) {
	int N = nums.size();
	int r_max = INT_MIN;
	for (int i = 0; i < N; i++)
	{
		if (r_max < nums[i])
		{
			r_max = nums[i];
		}
	}
	return r_max;
}


void test_DC3() {

	int N = 20;
	int maxValue = 20;
	int minValue = 1;
	int testTime = 100;

	DC3::Solution sln;

	cout << "test_DC3 begin" << endl;

	for (int i = 0; i < testTime; i++)
	{
		//vector<int> nums = generateRandomArray(N, maxValue, minValue);
		vector<int> nums{ 0,1,2,3,4,5,6,7,8/*,9 */};
		int max = get_max(nums);
		sln.reset(nums, max);
		vector<int> rank = sln.rank();
		print(rank);
	}

	cout << "test_DC3 end" << endl;



}


#endif