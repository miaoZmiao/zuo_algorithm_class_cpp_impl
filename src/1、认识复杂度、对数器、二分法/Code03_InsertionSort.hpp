#pragma once
#include "utility_func.hpp"

namespace Code03_InsertionSort {
	// insert sort
	void insertsort(vector<int> & arr)
	{
		size_t arrlen = arr.size();

		for (int i = 1; i < arrlen; i++)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				if (arr[j] > arr[j + 1])
				{
					swap(arr, j, j + 1);
				}
				else
				{
					break;
				}
			}
		}
	}

}

void test_Code03_InsertionSort() {
	cout << "test_Code03_InsertionSort begin" << endl;
	int testTime = 5000;
	int maxSize = 100;
	int maxValue = 100;
	bool succeed = true;
	for (int i = 0; i < testTime; i++) {
		vector<int> arr1 = generateRandomArray(maxSize, maxValue);
		vector<int> arr2 = arr1;
		Code03_InsertionSort::insertsort(arr1);
		std::sort(arr2.begin(), arr2.end());
		if (!vector_equal(arr1, arr2)) {
			succeed = false;
			print(arr1);
			print(arr2);
			break;
		}
	}
	cout << "test_Code03_InsertionSort end" << endl;
}