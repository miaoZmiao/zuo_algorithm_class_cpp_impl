#pragma once
#include "utility_func.hpp"


namespace Code05_BSNearLeft {

	int find_nearest_left_that_larger_than_target(vector<int> & arr, int target)
	{
		int retindex = -1;
		if (arr.size() == 0)
		{
			return retindex;
		}
		int left = 0;
		int right = arr.size() - 1;
		// 这里换成<= 了
		// 没有固定套路
		while (left <= right)
		{
			int mid = left + ((right - left) >> 1);
			if (arr[mid] >= target) {
				retindex = mid;
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}

		}
		return retindex;
	}

	int test(vector<int> & arr, int value) {
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i] >= value) {
				return i;
			}
		}
		return -1;
	}

}


void test_Code05_BSNearLeft() {
	cout << "test_Code05_BSNearLeft begin" << endl;
	int testTime = 5000;
	int maxSize = 10;
	int maxValue = 100;
	bool succeed = true;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<>  dist(0, maxValue);
	for (int i = 0; i < testTime; i++) {
		vector<int> arr = generateRandomArray(maxSize, maxValue);
		std::sort(arr.begin(), arr.end());
		int value = dist(mt);
		if (Code05_BSNearLeft::test(arr, value) != 
			Code05_BSNearLeft::find_nearest_left_that_larger_than_target(arr, value)) {
			succeed = false;
			break;
		}
	}
	cout << (succeed ? "Nice!" : "Fucking fucked!") << endl;
	cout << "test_Code05_BSNearLeft end" << endl;
}