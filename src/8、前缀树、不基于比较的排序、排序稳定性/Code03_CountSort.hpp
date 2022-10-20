#pragma once
#include "utility_func.hpp"
#include <algorithm>
namespace Code03_CountSort {

	// only for 0~200 value
	void countSort(vector<int> & arr) {
		if (arr.size() < 2) {
			return;
		}
		int max = INT_MIN;
		for (int i = 0; i < arr.size(); i++) {
			max = std::max(max, arr[i]);
		}
		vector<int> bucket(max + 1, 0);
		for (int i = 0; i < arr.size(); i++) {
			bucket[arr[i]]++;
		}
		int i = 0;
		for (int j = 0; j < bucket.size(); j++) {
			while (bucket[j]-- > 0) {
				arr[i++] = j;
			}
		}
	}


	void test_main() {
		int testTime = 5000;
		int maxSize = 100;
		int maxValue = 150;
		bool succeed = true;
		for (int i = 0; i < testTime; i++) {
			vector<int> arr1 = generateRandomArray(maxSize, maxValue, 0);
			vector<int> arr2 = arr1;
			countSort(arr1);
			std::sort(arr2.begin(), arr2.end());
			if (!vector_equal(arr1, arr2)) {
				succeed = false;
				print(arr1);
				print(arr2);
				break;
			}
		}
		cout << (succeed ? "Nice!" : "Fucking fucked!") << endl;

	}

}

void  test_Code03_CountSort() {


	cout << " test_Code03_CountSort begin" << endl;
	Code03_CountSort::test_main();
	cout << "test_Code03_CountSort end" << endl;

}