#pragma once
#ifndef Code02_SmallSum_HPP
#define Code02_SmallSum_HPP
#include "utility_func.hpp"
namespace Code02_PartitionAndQuickSort {



	int partition(vector<int>& arr, int L, int R) {
		if (L > R) {
			return -1;
		}
		if (L == R) {
			return L;
		}
		int lessEqual = L - 1;
		int index = L;
		while (index < R) {
			if (arr[index] <= arr[R]) {
				swap(arr, index, ++lessEqual);
			}
			index++;
		}
		swap(arr, ++lessEqual, R);
		return lessEqual;
	}
	// arr[L...R] 玩荷兰国旗问题的划分，以arr[R]做划分值
	// <arr[R] ==arr[R] > arr[R]
	vector<int> netherlandsFlag(vector<int>& arr, int L, int R) {
		if (L > R) { // L...R L>R
			return { -1, -1 };
		}
		if (L == R) {
			return  { L, R };
		}
		int less = L - 1; // < 区 右边界
		int more = R; // > 区 左边界
		int index = L;
		while (index < more) { // 当前位置，不能和 >区的左边界撞上
			if (arr[index] == arr[R]) {
				index++;
			}
			else if (arr[index] < arr[R]) {
				//				swap(arr, less + 1, index);
				//				less++;
				//				index++;						
				swap(arr, index++, ++less);
			}
			else { // >
				swap(arr, index, --more);
			}
		}
		swap(arr, more, R); // <[R]   =[R]   >[R]
		return { less + 1, more };
	}

	void process1(vector<int>& arr, int L, int R) {
		if (L >= R) {
			return;
		}
		// L..R partition arr[R] [ <=arr[R] arr[R] >arr[R] ]
		int M = partition(arr, L, R);
		process1(arr, L, M - 1);
		process1(arr, M + 1, R);
	}


	void quickSort1(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
		process1(arr, 0, arr.size() - 1);
	}


	void process2(vector<int>& arr, int L, int R) {
		if (L >= R) {
			return;
		}
		// [ equalArea[0]  ,  equalArea[0]]
		vector<int> equalArea = netherlandsFlag(arr, L, R);
		process2(arr, L, equalArea[0] - 1);
		process2(arr, equalArea[1] + 1, R);
	}


	void quickSort2(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
		process2(arr, 0, arr.size() - 1);
	}

	void process3(vector<int>& arr, int L, int R) {
		if (L >= R) {
			return;
		}
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<> dist(L, R);
 
		swap(arr, L , dist(mt));
		vector<int> equalArea = netherlandsFlag(arr, L, R);
		process3(arr, L, equalArea[0] - 1);
		process3(arr, equalArea[1] + 1, R);
	}

	void quickSort3(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}

		process3(arr, 0, arr.size() - 1);
	}

}

void test_Code02_PartitionAndQuickSort() {
	int testTime = 1000;
	int maxSize = 100;
	int maxValue = 100;
	cout << "Code02_PartitionAndQuickSort begin" << endl;
	for (int i = 0; i < testTime; i++) {
		vector<int> arr = generateRandomArray(maxSize, maxValue);
		vector<int> arr1 = arr;
		vector<int> arr2 = arr;
		vector<int> arr3 = arr;
 		Code02_PartitionAndQuickSort::quickSort1(arr1);
		Code02_PartitionAndQuickSort::quickSort2(arr2);
		Code02_PartitionAndQuickSort::quickSort3(arr3);
		
		if (!vector_equal(arr1, arr2) || !vector_equal(arr2, arr3))
		{
			print(arr);
			print(arr1);
			print(arr2);
			print(arr3);
			break;
		}


	}
	cout << "Code02_PartitionAndQuickSort end" << endl;
}



#endif