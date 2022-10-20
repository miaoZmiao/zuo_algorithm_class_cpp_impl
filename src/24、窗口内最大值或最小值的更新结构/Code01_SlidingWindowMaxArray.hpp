#pragma once
#ifndef Code01_SlidingWindowMaxArray_HPP
#define Code01_SlidingWindowMaxArray_HPP
#include "utility_func.hpp"
#include "stop_watch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
//题目一//
//假设一个固定大小为W的窗口，依次划过arr，//返回每一次滑出状况的最大值//例如，arr = [4, 3, 5, 4, 3, 3, 6, 7], W = 3//返回：[5, 5, 5, 4, 6, 7]
namespace Code01_SlidingWindowMaxArray {

	class Solution
	{
	public:
		//暴力对数器
		vector<int> right(vector<int> & arr, int w) {
			if (arr.size() < 1 || arr.size() < w) {
				return{};
			}
			int N = arr.size();
			vector<int> ans(N - w + 1, 0);
			int L = 0;
			int R = w - 1;
			int index = 0;
			while (R < N)
			{
				int max_num = arr[L];
				int tmp_i = L+1;
				while (tmp_i <= R)
				{
					max_num = std::max(arr[tmp_i], max_num);
					tmp_i++;
				}
				ans[index] = max_num;
				index++;
				L++;
				R++;
			}
			return ans;
		}

		vector<int> getMaxWindow(vector<int> & arr, int w) {
			if (arr.size() < 1 || arr.size() < w) {
				return{};
			}
			int N = arr.size();
			vector<int> ans(N - w + 1, 0);
			int L = 0;
			int R = w - 1;
			int index = 0;
			std::deque<int> dq;
			for (int R = 0; R < N; R++)
			{
				while (!dq.empty() && arr[dq.back()] <= arr[R])
				{
					dq.pop_back();
				}
				dq.push_back(R);
				if (dq.front()==R-w)
				{
					dq.pop_front();
				}
				if (R >= w - 1)
				{
					ans[index] = arr[dq.front()];
					index++;
				}
			}
			return ans;
		}

	};

}


bool outputequal(vector<vector<int>> & output1, vector<vector<int>> & output2)
{
	int N1 = output1.size();
	int N2 = output2.size();
	if (N1 != N2)
	{
		return false;
	}
	for (int i = 0; i < N1; i++)
	{
		if (false == vector_equal(output1[i], output2[i])) {
			return false;
		}
	}
	return true;
}



void test_Code01_SlidingWindowMaxArray()
 {
	int maxlen = 100000;
	int maxval = 1000;
	int testLoop = 50;
	stop_watch st;
	double elapse_force = 0.0;
	double elapse_slidewindow = 0.0;
	Code01_SlidingWindowMaxArray::Solution sln;
	cout << "test begin" << endl;
	int window = 3;
	for (int i = 0; i < testLoop; i++)
	{
		vector<int > arr = generateRandomArray(maxlen, maxval, 1);
		//vector<int > arr = { 5, 2, 3, 5, 3 };
		
		st.start();
		vector<int> ans1 = sln.right(arr, window);
		st.stop();
		elapse_force += st.elapsed_ms();

		st.start();
		vector<int> ans2 = sln.getMaxWindow(arr, window);
		st.stop();
		elapse_slidewindow += st.elapsed_ms();
		if (false == vector_equal(ans1, ans2))
		{
			print(arr);
			cout << "ans1" << endl;
			print(ans1);
			cout << "ans2" << endl;
			print(ans2);
			break;
		}
	}
	cout << "test end" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force/ testLoop << endl;
	cout << "slidewindow:" << elapse_slidewindow /testLoop << endl;

	/*	test begin
		test end
		average elapse(ms)
		force:2.8389
		slidewindow : 21.7451*/

}

#endif