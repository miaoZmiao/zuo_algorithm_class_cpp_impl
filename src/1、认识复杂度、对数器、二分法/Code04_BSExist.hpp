#pragma once
#include "utility_func.hpp"

namespace Code04_BSExist {

	bool  findNumber(vector<int> & arr, int target) {
		if (arr.size() == 0)
		{
			return false;
		}

		int left = 0;
		int right = arr.size() - 1;
		int mid = 0;
		// 课程上讲了到底是要 < 还是<= 
		// 这属于边界条件的考虑，这是仁者见仁智者见智
		// 算法大的思想一样的前提下，小的边界条件如何设置
		// 这个没有套路
		while (left < right)
		{
			mid = left + ((right - left) >> 1);
			if (arr[mid] == target)
			{
				return true;
			}
			else if (arr[mid] > target)
			{
				right = mid - 1;
			}
			else if (arr[mid] < target)
			{
				left = mid + 1;
			}
		}

		return target == arr[left];

	}


	bool test(vector<int> & sortedArr, int num) {
		for (int cur : sortedArr) {
			if (cur == num) {
				return true;
			}
		}
		return false;
	}
}

void test_Code04_BSExist() {
	
	cout << "test_Code04_BSExist begin" << endl;
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
		if (Code04_BSExist::test(arr, value) != Code04_BSExist::findNumber(arr, value)) {
			succeed = false;
			break;
		}
	}
	cout << (succeed ? "Nice!" : "Fucking fucked!") << endl;
	cout << "test_Code04_BSExist end" << endl;

}