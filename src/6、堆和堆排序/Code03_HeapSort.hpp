#pragma once
#include "utility_func.hpp"
#include <algorithm>

namespace Code03_HeapSort {



	void heapify(vector<int> & arr, int index, int heapSize) {

		int left = 2 * index + 1;
		while (left < heapSize)
		{
			int largestindex = (left + 1) < heapSize && arr[left + 1] > arr[left] ?
				left + 1 : left;

			largestindex = arr[index] > arr[largestindex] ? index : largestindex;
			if (largestindex == index)
			{
				break;
			}
			swap(arr, largestindex, index);
			index = largestindex;
			left = 2 * index + 1;
		}

	}

	void heapInsert(vector<int> & arr, int index)
	{
		while (arr[index] > arr[(index - 1) / 2])
		{
			swap(arr, index, (index - 1) / 2);
			index = (index - 1) / 2;
		}
	}


	void heapSort(vector<int> &arr) {
	
		if (arr.size() < 2) {
			return;
		}
		for (int i = arr.size() - 1; i >= 0;i--)
		{
			heapify(arr, i, arr.size());
		}
		int heapSize = arr.size();
		
		while (heapSize > 0)
		{
			swap(arr, 0, --heapSize);
			heapify(arr, 0, heapSize);
		}
	}


}


void test_Code03_HeapSort() {

	int testTime = 5000;
	int maxSize = 100;
	int maxValue = 100;
	bool succeed = true;
	cout << "test_Code03_HeapSort begin" << endl;
	for (int i = 0; i < testTime; i++) {
	
		vector<int> arr1 = generateRandomArray(maxSize, maxValue);
		vector<int> arr2 = arr1;

		Code03_HeapSort::heapSort(arr1);
		std::sort(arr2.begin(), arr2.end());
		if (!vector_equal(arr1, arr2))
		{
			cout << "Oops!" << endl;
			print(arr1);
			print(arr2);
			break;
		}

	}

	cout << "test_Code03_HeapSort end" << endl;


}