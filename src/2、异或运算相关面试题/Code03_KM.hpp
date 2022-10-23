#pragma once

#include "utility_func.hpp"
#include <unordered_map>
#include <unordered_set>
#include <functional>
namespace Code03_KM {

	// 
	// 一种数字出现K次，其他数出现了M次，
	//  M>1, K < M,
	// 要求找到出现K次的数字，要求额外空间复杂度O(1)，时间复杂度O(N)

	// arr中只有一种出现了K次,其余出现了M次
	int test(vector<int> & arr, int k, int m) {
		unordered_map<int, int> map;
		for (int num : arr) {
			if (map.count(num)) {
				map[num] = map[num] + 1;
			}
			else {
				map.insert({ num, 1 });
			}
		}
		for (auto & num : map) {
			if (num.second == k) {
				return num.first;
			}
		}
		return -1;
	}

	// 请保证arr中，只有一种数出现了K次，其他数都出现了M次
	int onlyKtimes(vector<int>& arr, int k, int m)
	{
		vector<int> alphabet(32, 0);
		for (auto it : arr)
		{
			for (int i = 0; i <= 31; i++)
			{
				if ((it&(1 << i)) != 0)
				{
					alphabet[i]++;
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < 32; i++)
		{
			if ((alphabet[i] % m) != 0)
			{
				ans = ans | (1 << i);
			}
		}
		return ans;
	}

	int randomNumber(int range, std::function<double()> rg) {
		return ((int)(rg() * range) + 1) - ((int)(rg() * range) + 1);
	}
	vector<int> randomArray(int maxKinds, int range, int k, int m, std::function<double()> rg) {
		int ktimeNum = randomNumber(range, rg);
		// 真命天子出现的次数
		int times = k;
		// 2
		int numKinds = (int)(rg() * maxKinds) + 2;
		// k * 1 + (numKinds - 1) * m
		vector<int> arr (times + (numKinds - 1) * m);
		int index = 0;
		for (; index < times; index++) {
			arr[index] = ktimeNum;
		}
		numKinds--;
		unordered_set<int> set;
		set.insert(ktimeNum);
		while (numKinds != 0) {
			int curNum = 0;
			do {
				curNum = randomNumber(range, rg);
			} while (set.count(curNum));
			set.insert(curNum);
			numKinds--;
			for (int i = 0; i < m; i++) {
				arr[index++] = curNum;
			}
		}
		// arr 填好了
		for (int i = 0; i < arr.size(); i++) {
			// i 位置的数，我想随机和j位置的数做交换
			int j = (int)(rg() * arr.size());// 0 ~ N-1
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		return arr;
	}


}

void test_Code03_KM() {
	cout << "test_Code03_KM begin" << endl;
	int kinds = 5;
	int range = 30;
	int testTime = 1000;
	int max = 9;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);
	std::function<double()> rg = [&]() {
		return dist(mt);
	};
	

	for (int i = 0; i < testTime; i++) {
		int a = (int)(rg() * max) + 1; // a 1 ~ 9
		int b = (int)(rg() * max) + 1; // b 1 ~ 9
		int k = std::min(a, b);
		int m = std::max(a, b);
		// k < m
		if (k == m) {
			m++;
		}
		vector<int> arr = Code03_KM::randomArray(kinds, range, k, m, rg);
		/*vector<int> arr{ -1,0,15,15,-1,15,15,0,15,15,0,0,0,0,-1 };
		int k = 3;
		int m = 6;*/
		int ans1 = Code03_KM::test(arr, k, m);
		int ans2 = Code03_KM::onlyKtimes(arr, k, m);
		if (ans1 != ans2) {
			cout << "k:" << k << endl;
			cout << "m:" << m << endl;
			print(arr);
			cout << (ans1) << "," << ans2 << endl;
			cout << "出错了！" << endl;
			break;
		}
	}
	cout << "test_Code03_KM end" << endl;
}