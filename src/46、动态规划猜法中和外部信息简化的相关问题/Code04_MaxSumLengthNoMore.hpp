#pragma once
#ifndef Code04_MaxSumLengthNoMore_HPP
#define Code04_MaxSumLengthNoMore_HPP
#include <iostream>
#include "utility_func.hpp"
#include <algorithm>
#include <list>
using namespace std;
namespace Code04_MaxSumLengthNoMore {

	class Solution {
	public:
		int test(vector<int> & arr, int M) {
			if ( arr.size() == 0 ||  M < 1) {
				return 0;
			}
			int N = arr.size();
			int max = INT_MIN;
			for (int L = 0; L < N; L++) {
				int sum = 0;
				for (int R = L; R < N; R++) {
					if (R - L + 1 > M) {
						break;
					}
					sum += arr[R];
					max = std::max(max, sum);
				}
			}
			return max;
		}


		// O(N)的解法，最优解
		int maxSum(vector<int> & arr, int M) {
			if (arr.size() ==  0 || M < 1) {
				return 0;
			}
			int N = arr.size();
			vector<int> sum (N, 0);
			sum[0] = arr[0];
			for (int i = 1; i < N; i++) {
				sum[i] = sum[i - 1] + arr[i];
			}
			std::list<int> qmax;
			int i = 0;
			int end = std::min(N, M);
			for (; i < end; i++) {
				while (!qmax.empty() && sum[qmax.back()] <= sum[i]) {
					qmax.pop_back();
				}
				qmax.push_back(i);
			}
			int max = sum[qmax.front()];
			int L = 0;
			for (; i < N; L++, i++) {
				if (qmax.front() == L) {
					qmax.pop_front();
				}
				while (!qmax.empty() && sum[qmax.back()] <= sum[i]) {
					qmax.pop_back();
				}
				qmax.push_back(i);
				max = std::max(max, sum[qmax.front()] - sum[L]);
			}
			for (; L < N - 1; L++) {
				if (qmax.front() == L) {
					qmax.pop_front();
				}
				max = std::max(max, sum[qmax.front()] - sum[L]);
			}
			return max;
		}
	};
}

void test_Code04_MaxSumLengthNoMore() {

	int maxN = 50;
	int maxValue = 100;
	int testTime = 1000;
	cout << "test_Code04_MaxSumLengthNoMore begin" << endl;
	Code04_MaxSumLengthNoMore::Solution sln;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(1, maxN);

	for (int i = 0; i < testTime; i++) {
		int N = dist(mt);
		int M = dist(mt);
		vector<int> arr = generateRandomArray(N, 50, -50);
		int ans1 = sln.test(arr, M);
		int ans2 = sln.maxSum(arr, M);
		if (ans1 != ans2) {
			cout << "Oops!" << endl;
		}
	}
	cout << "test_Code04_MaxSumLengthNoMore end" << endl;

}


#endif