#pragma once
#ifndef Code01_CountOfRangeSum_HPP
#define Code01_CountOfRangeSum_HPP
#include "utility_func.hpp"
// 这道题直接在leetcode测评：
// https://leetcode.com/problems/count-of-range-sum/
namespace Code01_CountOfRangeSum {

	int merge(vector<long> &arr, int L, int M, int R, int lower, int upper) {
		int ans = 0;
		int windowL = L;
		int windowR = L;
		// [windowL, windowR)
		for (int i = M + 1; i <= R; i++) {
			long min = arr[i] - upper;
			long max = arr[i] - lower;
			while (windowR <= M && arr[windowR] <= max) {
				windowR++;
			}
			while (windowL <= M && arr[windowL] < min) {
				windowL++;
			}
			ans += windowR - windowL;
		}
		vector<long> help(R - L + 1);
		int i = 0;
		int p1 = L;
		int p2 = M + 1;
		while (p1 <= M && p2 <= R) {
			help[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
		}
		while (p1 <= M) {
			help[i++] = arr[p1++];
		}
		while (p2 <= R) {
			help[i++] = arr[p2++];
		}
		for (i = 0; i < help.size(); i++) {
			arr[L + i] = help[i];
		}
		return ans;
	}



	int process(vector<long> &sum, int L, int R, int lower, int upper) {
		if (L == R) {
			return sum[L] >= lower && sum[L] <= upper ? 1 : 0;
		}
		int M = L + ((R - L) >> 1);
		return process(sum, L, M, lower, upper) + process(sum, M + 1, R, lower, upper)
			+ merge(sum, L, M, R, lower, upper);
	}



	int countRangeSum(vector<int>& nums, int lower, int upper) {
		if ( nums.size() == 0) {
			return 0;
		}
		vector<long> sum(nums.size());
		
		sum[0] = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			sum[i] = sum[i - 1] + nums[i];
		}
		return process(sum, 0, sum.size() - 1, lower, upper);
	}
}


#endif