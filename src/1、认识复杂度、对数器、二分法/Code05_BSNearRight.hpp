#pragma once
#include "utility_func.hpp"

namespace Code05_BSNearRight {
	//   Ñ°ÕÒÂú×ã <= value µÄ×îÓÒÎ»ÖÃ

	int find_nearest_right_that_less_than_target(vector<int> & arr, int target)
	{
		int retindex = -1;
		if (arr.size() == 0)
		{
			return retindex;
		}
		int left = 0;
		int right = arr.size() - 1;
		while (left <= right)
		{
			int mid = left + ((right - left) >> 1);
			if (arr[mid] <= target)
			{
				retindex = mid;
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}

		}

		return retindex;

	}

	int test(vector<int> & arr, int value) {
		for (int i = arr.size() -1; i >=0; i--) {
			if (arr[i] <= value) {
				return i;
			}
		}
		return -1;
	}
}

void test_Code05_BSNearRight() {

	cout << "test_Code05_BSNearRight begin" << endl;
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
		if (Code05_BSNearRight::test(arr, value) !=
			Code05_BSNearRight::find_nearest_right_that_less_than_target(arr, value)) {
			succeed = false;
			break;
		}
	}
	cout << (succeed ? "Nice!" : "Fucking fucked!") << endl;
	cout << "test_Code05_BSNearRight end" << endl;
}