#pragma once
#ifndef Code02_RemoveBoxes_HPP
#define Code02_RemoveBoxes_HPP
#include "utility_func.hpp"
#include <iostream>
#include <algorithm>
// 本题测试链接 : https://leetcode.com/problems/remove-boxes/
namespace Code02_RemoveBoxes {

	class Solution {
	public:
		int func1(vector<int>& arr, int L, int R, int K) {
			if (L > R) {
				return 0;
			}
			int ans = func1(arr, L + 1, R, 0) + (K + 1) * (K + 1);

			// 前面的K个X，和arr[L]数，合在一起了，现在有K+1个arr[L]位置的数
			for (int i = L + 1; i <= R; i++) {
				if (arr[i] == arr[L]) {
					ans = std::max(ans, func1(arr, L + 1, i - 1, 0) + func1(arr, i, R, K + 1));
				}
			}
			return ans;
		}

		int removeBoxes(vector<int>& boxes) {
			int N = boxes.size();
			vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(N, 0)));
			int ans = process1(boxes, 0, N - 1, 0, dp);
			return ans;
		}

		int process1(vector<int> boxes, int L, int R, int K,
			vector<vector<vector<int>>> & dp) 
		{
			if (L > R) {
				return 0;
			}
			if (dp[L][R][K] > 0) {
				return dp[L][R][K];
			}
			int ans = process1(boxes, L + 1, R, 0, dp) + (K + 1) * (K + 1);
			for (int i = L + 1; i <= R; i++) {
				if (boxes[i] == boxes[L]) {
					ans = std::max(ans, process1(boxes, L + 1, i - 1, 0, dp) + process1(boxes, i, R, K + 1, dp));
				}
			}
			dp[L][R][K] = ans;
			return ans;
		}

		int process2(vector<int> boxes, int L, int R, int K,
			vector<vector<vector<int>>> & dp) 
		{
			if (L > R) {
				return 0;
			}
			if (dp[L][R][K] > 0) {
				return dp[L][R][K];
			}
			int last = L;
			while (last + 1 <= R && boxes[last + 1] == boxes[L]) {
				last++;
			}
			// K个1     (K + last - L) last
			int pre = K + last - L;
			int ans = (pre + 1) * (pre + 1) + process2(boxes, last + 1, R, 0, dp);
			for (int i = last + 2; i <= R; i++) {
				if (boxes[i] == boxes[L] && boxes[i - 1] != boxes[L]) {
					ans = std::max(ans, process2(boxes, last + 1, i - 1, 0, dp) + process2(boxes, i, R, pre + 1, dp));
				}
			}
			dp[L][R][K] = ans;
			return ans;
		}


	};

}

void test_Code02_RemoveBoxes() {


}

#endif