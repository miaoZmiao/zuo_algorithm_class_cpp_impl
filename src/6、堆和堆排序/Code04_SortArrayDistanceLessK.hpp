#pragma once
#include "utility_func.hpp"
#include <queue>
#include <algorithm>
namespace Code04_SortArrayDistanceLessK {
	
	void sortedArrDistanceLessK(vector<int>& arr, int k) {
		if (k == 0) {
			return;
		}
		// 默认小根堆
		std::priority_queue<int, vector<int>, std::greater<int>> heap;
		int index = 0;
		// 0...K-1
		for (; index <= std::min(arr.size() - 1, (size_t)k - 1); index++) {
			heap.push(arr[index]);
		}
		int i = 0;
		for (; index < arr.size(); i++, index++) {
			heap.push(arr[index]);
			arr[i] = heap.top();
			heap.pop();
		}
		while (!heap.empty()) {
			arr[i++] = heap.top();
			heap.pop();
		}
	}


	vector<int> randomArrayNoMoveMoreK(int maxSize, int maxValue, int K) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);

		int N = (int)(maxSize)*dist(mt) + 1;
		vector<int> arr(N);

		for (int i = 0; i < arr.size(); i++) {
			arr[i] = (int)((maxValue + 1) * dist(mt)) - (int)(maxValue * dist(mt));
		}
		// 先排个序
		std::sort(arr.begin(), arr.end());
		// 然后开始随意交换，但是保证每个数距离不超过K
		// swap[i] == true, 表示i位置已经参与过交换
		// swap[i] == false, 表示i位置没有参与过交换
		vector<bool> isSwap(arr.size());
		for (int i = 0; i < arr.size(); i++) {
			int j = std::min((size_t)i + (int)(dist(mt) * (K + 1)), arr.size() - 1);
			if (!isSwap[i] && !isSwap[j]) {
				isSwap[i] = true;
				isSwap[j] = true;
				int tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
		return arr;
	}


}


void test_Code04_SortArrayDistanceLessK() {
	int testTime = 5000;
	int maxSize = 100;
	int maxValue = 100;
	bool succeed = true;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);
	cout << "test_Code04_SortArrayDistanceLessK begin" << endl;
	for (int i = 0; i < testTime; i++) {
		int k = (int)(dist(mt) * maxSize) + 1;
		vector<int> arr = Code04_SortArrayDistanceLessK::randomArrayNoMoveMoreK(maxSize, maxValue, k);
		vector<int> arr1 = arr;
		vector<int> arr2 = arr;
		Code04_SortArrayDistanceLessK::sortedArrDistanceLessK(arr1, k);
		std::sort(arr2.begin(), arr2.end());
		if (!vector_equal(arr1, arr2)) {
			succeed = false;
			cout << "K : " << k << endl;;
			print(arr);
			print(arr1);
			print(arr2);
			break;
		}
	}
	cout << "test_Code04_SortArrayDistanceLessK end" << endl;
}