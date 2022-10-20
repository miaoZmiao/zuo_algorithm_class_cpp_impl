#pragma once
#ifndef Code04_AvgLessEqualValueLongestSubarray_HPP
#define Code04_AvgLessEqualValueLongestSubarray_HPP

#include "utility_func.hpp"
#include <iostream>
#include <map>
#include <algorithm>
namespace Code04_AvgLessEqualValueLongestSubarray {


	int ways1(vector<int>& arr, int v) {
		int ans = 0;
		for (int L = 0; L < arr.size(); L++) {
			for (int R = L; R < arr.size(); R++) {
				int sum = 0;
				int k = R - L + 1;
				for (int i = L; i <= R; i++) {
					sum += arr[i];
				}
				double avg = (double)sum / (double)k;
				if (avg <= v) {
					ans = std::max(ans, k);
				}
			}
		}
		return ans;
	}
	int maxLengthAwesome(vector<int>& arr, int k);
	int ways3(vector<int> & arr, int v) {
		if (arr.size() == 0) {
			return 0;
		}
		vector<int> arr_i = arr;
		for (int i = 0; i < arr.size(); i++) {
			arr_i[i] -= v;
		}
		return maxLengthAwesome(arr_i, 0);
	}

	int maxLengthAwesome(vector<int>& arr, int k)
	{
		int N = arr.size();
		vector<int> minsum(N, 0);
		vector<int> minsumEnd(N, 0);
		minsum[N - 1] = arr[N - 1];
		minsumEnd[N - 1] = N - 1;
		for (int i = N - 2; i >= 0; i--)
		{
			if (minsum[i + 1] <= 0)
			{
				minsum[i] = arr[i] + minsum[i + 1];
				minsumEnd[i] = minsumEnd[i + 1];
			}
			else {
				minsum[i] = arr[i];
				minsumEnd[i] = i;
			}
		}
		int R = 0;
		int sum = 0;
		int ans = 0;
		for (int i = 0; i < N; i++)
		{
			while (R < N&&sum + minsum[R] <= k)
			{
				sum += minsum[R];
				R = minsumEnd[R] + 1;
			}
			ans = std::max(ans, R - i);
			if (R > i)
			{
				sum -= arr[i];
			}
			else {
				R = i + 1;
			}
		}
		return ans;
	}

}

void test_Code04_AvgLessEqualValueLongestSubarray() {

	int len = 10;
	int maxvalue = 20;
	int minvalue = 0;
	int testTime = 1000;
	int K = (maxvalue - minvalue) / 2 + minvalue;
	cout << "test_Code04_AvgLessEqualValueLongestSubarray begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(len, maxvalue, minvalue);
		int ans1 = Code04_AvgLessEqualValueLongestSubarray::ways1(arr, K);
		int ans2 = Code04_AvgLessEqualValueLongestSubarray::ways3(arr, K);
		if (ans1 != ans2)
		{
			print(arr);
			cout << ans1 << "," << ans2 << endl;
			break;
		}
	}
	cout << "test_Code04_AvgLessEqualValueLongestSubarray end" << endl;
	
}

#endif