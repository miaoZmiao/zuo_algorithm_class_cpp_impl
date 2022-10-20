#pragma once
#ifndef Code02_AllLessNumSubArray_HPP
#define Code02_AllLessNumSubArray_HPP
#include <vector>
#include <algorithm>
#include <deque>
#include "utility_func.hpp"
#include "stop_watch.hpp"
using namespace std;

// 题目二// 给定一个整形数组 arr 和一个数字sum
// 某个arr 的子数组 需要满足
// 子数组最大值- 子数组最小值<= sum
// 返回arr中满足条件的子数组数量

namespace Code02_AllLessNumSubArray {

	class Solution {
	public:
		int right(vector<int> & arr, int sum) {
			if (arr.size()==0 || sum < 0) {
				return 0;
			}
			int N = arr.size();
			int count = 0;
			for (int L = 0; L < N; L++) {
				for (int R = L; R < N; R++) {
					int max = arr[L];
					int min = arr[L];
					for (int i = L + 1; i <= R; i++) {
						max = std::max(max, arr[i]);
						min = std::min(min, arr[i]);
					}
					if (max - min <= sum) {
						count++;
					}
				}
			}
			return count;
		}

		int num(vector<int> & arr, int sum) {
			if (arr.size() == 0 || sum < 0) {
				return 0;
			}
			int N = arr.size();
			int count = 0;
			deque<int> maxq;
			deque<int> minq;
			int R = 0;
			for (int L = 0; L < N; L++)
			{
				while (R < N)
				{
					while (!maxq.empty() && arr[maxq.back()] <= arr[R])
					{
						maxq.pop_back();
					}
					maxq.push_back(R);
					while (!minq.empty() && arr[minq.back()] >= arr[R])
					{
						minq.pop_back();
					}
					minq.push_back(R);
					if (arr[maxq.front()] - arr[minq.front()] > sum)
					{
						break;
					}
					else
					{
						
						R++;
					}
				}
				count += R - L;
				if (maxq.front() == L)
				{
					maxq.pop_front();
				}
				if (minq.front() == L)
				{
					minq.pop_front();
				}
			}
			return count;
		}
	};
}
void test_Code02_AllLessNumSubArray()
{
	int maxlen = 1000;
	int maxval = 100;
	int testLoop = 10;
	stop_watch st;
	double elapse_force = 0.0;
	double elapse_slidewindow = 0.0;
	Code02_AllLessNumSubArray::Solution sln;
	int sum = maxval/2 * maxlen;
	cout << "test begin" << endl;
	for (int i = 0; i < testLoop; i++)
	{
		vector<int> arr = generateRandomArray(maxlen, maxval, 1);
		st.start();
		int ans1 = sln.right(arr, sum);
		st.stop();
		elapse_force += st.elapsed_ms();
		st.start();
		int ans2 = sln.num(arr, sum);
		st.stop();
		elapse_slidewindow += st.elapsed_ms();
		
		if (ans1 != ans2)
		{
			print(arr);
			cout << ans1 << "," << ans2 << endl;
			break;
		}
	}
	cout << "test end" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force / testLoop << endl;
	cout << "slidewindow:" << elapse_slidewindow / testLoop << endl;
	//	test begin
	//	test end
	//	average elapse(ms)
	//	force:1891.6
	//	slidewindow : 0.4968



}


#endif