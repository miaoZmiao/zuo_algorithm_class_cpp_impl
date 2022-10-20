#pragma once
#include "utility_func.hpp"


namespace Code04_BiggerThanRightTwice {


	int merge(vector<int>& arr, int L, int m, int r)
	{
		int ans = 0;
		int windowR = m + 1;
		for (int i = L; i <= m; i++)
		{
			while (windowR <= r && arr[i] > arr[windowR] * 2)
			{
				windowR++;
			}
			ans += windowR - m - 1;
		}
		
		vector<int> help(r-L+1);
		int p1 = L;
		int p2 = m + 1;
		int ih = 0;
		while (p1 <= m && p2 <= r)
		{
			if (arr[p1] <= arr[p2])
			{
				help[ih++] = arr[p1++];
			}
			else if (arr[p1] > arr[p2])
			{
				help[ih++] = arr[p2++];
			}
		}

		while (p1 <= m) {
			help[ih++] = arr[p1++];
		}
		while (p2 <= r) {
			help[ih++] = arr[p2++];
		}
		for (int i = 0; i < help.size(); i++) {
			arr[L + i] = help[i];
		}
		return ans;
	}


	int process(vector<int>& arr, int l, int r)
	{
		if (l == r) {
			return 0;
		}
		// l < r
		int mid = l + ((r - l) >> 1);
		return process(arr, l, mid) + process(arr, mid + 1, r) + merge(arr, l, mid, r);
	}

	int biggerTwice(vector<int>& arr)
	{
		if (arr.size() < 2)
		{
			return 0;
		}

		return process(arr, 0, arr.size() - 1);
	}
	
	int comparator(vector<int> & arr) {
		int ans = 0;
		for (int i = 0; i < arr.size(); i++) {
			for (int j = i + 1; j < arr.size(); j++) {
				if (arr[i] > (arr[j] << 1)) {
					ans++;
				}
			}
		}
		return ans;
	}

}


void test_Code04_BiggerThanRightTwice() {

	int testTime = 1000;
	int maxSize = 100;
	int maxValue = 100;

	cout << "test_Code04_BiggerThanRightTwice begin" << endl;

	for (int i = 0; i < testTime; i++)
	{
		vector<int> input1 = generateRandomArray(maxSize, maxValue, 0);
		vector<int> input2 = input1;
 		int ans1 = Code04_BiggerThanRightTwice::comparator(input1);
		int ans2 = Code04_BiggerThanRightTwice::biggerTwice(input2);
		if (ans1 != ans2)
		{
			cout << "Oops" << endl;
			cout << ans1 << "," << ans2 << endl;
			print(input1);
			break;
		}
	}

	cout << "test_Code04_BiggerThanRightTwice end" << endl;
}