#pragma once
#include "utility_func.hpp"

namespace Code08_GetMax {

	// arr[L..R]范围上求最大值  L ... R   N
	int process(vector<int> & arr, int L, int R) {
		// arr[L..R]范围上只有一个数，直接返回，base case
		if (L == R) {
			return arr[L];
		}
		// L...R 不只一个数
		// mid = (L + R) / 2
		int mid = L + ((R - L) >> 1); // 中点   	1
		int leftMax = process(arr, L, mid);
		int rightMax = process(arr, mid + 1, R);
		return std::max(leftMax, rightMax);
	}


	// 求arr中的最大值
	int getMax(vector<int> & arr) {
		return process(arr, 0, arr.size() - 1);
	}

	
}