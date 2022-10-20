#pragma once

#include "utility_func.hpp"
#include <algorithm>
#include <cmath>
namespace Code04_RadixSort {

	int maxbits(const vector<int> & arr) {
		int max = INT_MIN;
		for (int i = 0; i < arr.size(); i++) {
			max = std::max(max, arr[i]);
		}
		int res = 0;
		while (max != 0) {
			res++;
			max /= 10;
		}
		return res;
	}


	int getDigit(int x, int d) {
		return ((x / ((int)std::pow(10, d - 1))) % 10);
	}


	void radixSort(vector<int> & arr, int L, int R, int digit) {
		const int radix = 10;
		int i = 0, j = 0;
		// 有多少个数准备多少个辅助空间
		vector<int> help(R - L + 1, 0);
		for (int d = 1; d <= digit; d++) { // 有多少位就进出几次
			// 10个空间
			// count[0] 当前位(d位)是0的数字有多少个
			// count[1] 当前位(d位)是(0和1)的数字有多少个
			// count[2] 当前位(d位)是(0、1和2)的数字有多少个
			// count[i] 当前位(d位)是(0~i)的数字有多少个
			vector<int> count(radix, 0); // count[0..9]
			for (i = L; i <= R; i++) {
				// 103  1   3
				// 209  1   9
				j = getDigit(arr[i], d);
				count[j]++;
			}
			for (i = 1; i < radix; i++) {
				count[i] = count[i] + count[i - 1];
			}
			for (i = R; i >= L; i--) {
				j = getDigit(arr[i], d);
				help[count[j] - 1] = arr[i];
				count[j]--;
			}
			for (i = L, j = 0; i <= R; i++, j++) {
				arr[i] = help[j];
			}
		}
	}

	// only for no-negative value
	void radixSort(vector<int> & arr) {
		if (arr.size() < 2) {
			return;
		}
		radixSort(arr, 0, arr.size() - 1, maxbits(arr));
	}

	void test_main() {
		
		int testTime = 5000;
		int maxSize = 100;
		int maxValue = 1000;
		bool succeed = true;
		for (int i = 0; i < testTime; i++) {
			vector<int> arr1 = generateRandomArray(maxSize, maxValue);
			vector<int> arr2 = arr1;
			radixSort(arr1);
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




void test_Code04_RadixSort() {

	cout << "test_Code04_RadixSort begin" << endl;
	Code04_RadixSort::test_main();
	cout << "test_Code04_RadixSort end" << endl;
}