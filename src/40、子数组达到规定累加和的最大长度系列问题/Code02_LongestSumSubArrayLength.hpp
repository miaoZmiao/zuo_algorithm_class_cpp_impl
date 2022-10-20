#pragma once
#ifndef Code02_LongestSumSubArrayLength_HPP
#define Code02_LongestSumSubArrayLength_HPP
#include <vector>
#include <algorithm>
#include <map>
#include "utility_func.hpp"
namespace Code02_LongestSumSubArrayLength {

	int maxLength(vector<int> & arr, int k)
	{
		std::map<int, int> mp;
		mp.insert(std::make_pair(0, -1));
		int sum = 0;
		int N = arr.size();
		int ans = 0;
		for (int i = 0; i < N; i++)
		{
			sum += arr[i];
			int rest = sum - k;
			auto it_find = mp.find(rest);
			if (it_find != mp.end())
			{
				ans = std::max(ans, i - it_find->second);
			}
			if (mp.end() == mp.find(sum))
			{
				mp[sum] = i;
			}
		}
		return ans;
	}

	bool valid(vector<int> & arr, int L, int R, int K) {
		int sum = 0;
		for (int i = L; i <= R; i++) {
			sum += arr[i];
		}
		return sum == K;
	}

	int right(vector<int> & arr, int K) {
		int max = 0;
		for (int i = 0; i < arr.size(); i++) {
			for (int j = i; j < arr.size(); j++) {
				if (valid(arr, i, j, K)) {
					max = std::max(max, j - i + 1);
				}
			}
		}
		return max;
	}
}

void test_Code02_LongestSumSubArrayLength() {

	int len = 10;
	int maxvalue = 20;
	int minvalue = -20;
	int testTime = 500000;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);
	cout << "test_Code02_LongestSumSubArrayLength begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(len, maxvalue, minvalue);
		int K = (int)(dist(mt)* maxvalue) - (int)(dist(mt)* maxvalue * maxvalue);
		int ans1 = Code02_LongestSumSubArrayLength::maxLength(arr, K);
		int ans2 = Code02_LongestSumSubArrayLength::right(arr, K);
		if (ans1 != ans2)
		{
			print(arr);
			cout << ans1 << "," << ans2 << endl;
			break;
		}
	}
	cout << "test_Code02_LongestSumSubArrayLength end" << endl;
}

#endif