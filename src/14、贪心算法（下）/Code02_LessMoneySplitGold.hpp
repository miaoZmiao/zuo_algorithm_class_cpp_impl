#pragma once

#include "utility_func.hpp"
#include <queue>

namespace Code02_LessMoneySplitGold {

	class LessMoneySplitGold {

	public:
		// 纯暴力！
		int lessMoney1(vector<int> & arr) {
			if (arr.size() == 0) {
				return 0;
			}
			return process(arr, 0);
		}

		// 等待合并的数都在arr里，pre之前的合并行为产生了多少总代价
		// arr中只剩一个数字的时候，停止合并，返回最小的总代价
		int process(const vector<int> & arr, int pre) {
			if (arr.size() == 1) {
				return pre;
			}
			int ans = INT_MAX;
			for (int i = 0; i < arr.size(); i++) {
				for (int j = i + 1; j < arr.size(); j++) {
					ans = std::min(ans, process(copyAndMergeTwo(arr, i, j), pre + arr[i] + arr[j]));
				}
			}
			return ans;
		}

		vector<int> copyAndMergeTwo(const vector<int> & arr, int i, int j) {
			vector<int>  ans (arr.size() - 1);
			int ansi = 0;
			for (int arri = 0; arri < arr.size(); arri++) {
				if (arri != i && arri != j) {
					ans[ansi++] = arr[arri];
				}
			}
			ans[ansi] = arr[i] + arr[j];
			return ans;
		}

		int lessMoney2(vector<int> & arr) {
			std::priority_queue<int, vector<int>, std::greater<int>> pQ;
			for (int i = 0; i < arr.size(); i++) {
				pQ.push(arr[i]);
			}
			int sum = 0;
			int cur = 0;
			while (pQ.size() > 1) {
				int add1 = pQ.top(); pQ.pop();
				int add2 = pQ.top(); pQ.pop();
				cur = add1 + add2;
				sum += cur;
				pQ.push(cur);
			}
			return sum;
		}
	};

	void test_main() {
		int testTime = 1000;
		int maxSize = 6;
		int maxValue = 1000;
		LessMoneySplitGold lmsg;
		for (int i = 0; i < testTime; i++) {
			vector<int> arr = generateRandomArray(maxSize, maxValue);
			if (lmsg.lessMoney1(arr) != lmsg.lessMoney2(arr)) {
				cout << "Oops!" << endl;
			}
		}
	
	}

}

void test_Code02_LessMoneySplitGold() {

	cout << "test_Code02_LessMoneySplitGold begin" << endl;
	Code02_LessMoneySplitGold::test_main();
	cout << "test_Code02_LessMoneySplitGold end" << endl;


}