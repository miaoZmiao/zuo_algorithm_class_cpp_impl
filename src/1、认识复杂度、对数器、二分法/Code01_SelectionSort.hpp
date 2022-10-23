#pragma once

#include "utility_func.hpp"


namespace Code01_SelectionSort {
	
	// —°‘Ò≈≈–Ú
	void selectsort(std::vector<int> & arr) {
		int veclen = arr.size();

		for (int i = 0; i < veclen; i++)
		{
			int minindex = i;
			for (int j = i + 1; j < veclen; j++)
			{
				if (arr[j] < arr[minindex])
				{
					minindex = j;
				}

			}
			swap(arr, i, minindex);
		}
	}

}

void test_Code01_SelectionSort() {
	cout << "test_Code01_SelectionSort begin" << endl;
	int testTime = 5000;
	int maxSize = 100;
	int maxValue = 100;
	bool succeed = true;
	for (int i = 0; i < testTime; i++) {
		vector<int> arr1 = generateRandomArray(maxSize, maxValue);
		vector<int> arr2 = arr1;
		Code01_SelectionSort::selectsort(arr1);
		std::sort(arr2.begin(), arr2.end());
		if (!vector_equal(arr1, arr2)) {
			succeed = false;
			print(arr1);
			print(arr2);
			break;
		}
	}
	cout<<(succeed ? "Nice!" : "Fucking fucked!")<<endl;
	cout << "test_Code01_SelectionSort end" << endl;

}
