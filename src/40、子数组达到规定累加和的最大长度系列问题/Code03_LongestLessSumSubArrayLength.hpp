#pragma once
#ifndef Code03_LongestLessSumSubArrayLength_HPP
#define Code03_LongestLessSumSubArrayLength_HPP
#include <vector>
#include <iostream>
#include <algorithm>
#include "utility_func.hpp"
using namespace std;

namespace Code03_LongestLessSumSubArrayLength {

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
		int ans = 0;
		int R = 0;
		int sum = 0;
		for (int i = 0; i < N; i++)
		{
			while (R < N&& sum + minsum[R] <= k)
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

	int getLessIndex(vector<int>& arr, int num) {
		int low = 0;
		int high = arr.size() - 1;
		int mid = 0;
		int res = -1;
		while (low <= high) {
			mid = (low + high) / 2;
			if (arr[mid] >= num) {
				res = mid;
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		return res;
	}
	int maxLength(vector<int>& arr, int k)
	{
		vector<int> h = vector<int>(arr.size() + 1, 0);
		int sum = 0;
		h[0] = sum;
		for (int i = 0; i != arr.size(); i++) {
			sum += arr[i];
			h[i + 1] = std::max(sum, h[i]);
		}
		sum = 0;
		int res = 0;
		int pre = 0;
		int len = 0;
		for (int i = 0; i != arr.size(); i++) {
			sum += arr[i];
			pre = getLessIndex(h, sum - k);
			len = pre == -1 ? 0 : i - pre + 1;
			res = std::max(res, len);
		}
		return res;
	}
}

void test_Code03_LongestLessSumSubArrayLength() {
	int len = 10;
	int maxValue = 20;
	int minValue = -20;
	int testTime = 100;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);
	cout << "test_Code03_LongestLessSumSubArrayLength begin" << endl;
	for (int i = 0; i < 500; i++) {
		vector<int>  arr = generateRandomArray(len, maxValue, minValue);
		int k = (int)(dist(mt) * maxValue) - 5;
		int ans1 = Code03_LongestLessSumSubArrayLength::maxLengthAwesome(arr, k);
		int ans2 = Code03_LongestLessSumSubArrayLength::maxLength(arr, k);
		if (ans1 != ans2) {
			print(arr);
			cout << ans1 << "," << ans2 << endl;
			break; 
		}
	}
	cout << "test_Code03_LongestLessSumSubArrayLength end" << endl;
}


#endif