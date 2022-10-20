#pragma once
#ifndef Code01_LongestSumSubArrayLengthInPositiveArray_HPP
#define Code01_LongestSumSubArrayLengthInPositiveArray_HPP
#include <vector>
#include "utility_func.hpp"
#include <algorithm>
namespace Code01_LongestSumSubArrayLengthInPositiveArray {

	// 数组非负用窗口
	int getMaxLength(vector<int> & arr, int K)
	{
		int N = arr.size();
		int R = 0;
		int sum = 0;
		int ans = 0;
		for (int i = 0; i < N; i++)
		{
			while (R < N && sum  < K)
			{
				sum += arr[R];
				R++;
			}
			if (sum == K)
			{
				ans = std::max(ans, R - i);
			}
			if (R > i)
			{
				sum -= arr[i];
			}
			else // R == i
			{
				R = i + 1;
			}
		}
		return ans;
	}

	

	bool valid(vector<int> & arr, int L, int R, int K) {
		int sum = 0;
		for (int i = L; i <= R; i++) {
			sum += arr[i];
		}
		return sum == K;
	}

	int right(vector<int> & arr, int K) {
		int max = 0;
		for (int i = 0; i < arr.size(); i++) {
			for (int j = i; j < arr.size(); j++) {
				if (valid(arr, i, j, K)) {
					max = std::max(max, j - i + 1);
				}
			}
		}
		return max;
	}
}


void test_Code01_LongestSumSubArrayLengthInPositiveArray() {
	
	int len = 10;
	int value = 20;
	int K = len * (value) / 2;
	int testTime = 500000;
	cout << "test_Code01_LongestSumSubArrayLengthInPositiveArray begin" << endl;

	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(len, value, 1);
		int ans1 = Code01_LongestSumSubArrayLengthInPositiveArray::getMaxLength(arr, K);
		int ans2 = Code01_LongestSumSubArrayLengthInPositiveArray::right(arr, K);
		if (ans1 != ans2)
		{
			print(arr);
			cout << ans1 << "," << ans2 << endl;
			break;
		}
	}
	cout << "test_Code01_LongestSumSubArrayLengthInPositiveArray end" << endl;
}
#endif