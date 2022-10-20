#pragma once
#ifndef Code01_MonotonousStack_HPP
#define Code01_MonotonousStack_HPP
#include "utility_func.hpp"
#include "stop_watch.hpp"
#include <vector>
#include <stack>

using namespace std;

// 单调栈
namespace Code01_MonotonousStack {

	class Solution
	{
	public:
		// arr = [ 3, 1, 2, 3]
		//         0  1  2  3
		//  [
		//     0 : [-1,  1]
		//     1 : [-1, -1]
		//     2 : [ 1, -1]
		//     3 : [ 2, -1]
		//  ]
		//  arr无重复数字
		vector<vector<int>> getNearLessNoRepeat(vector<int> & arr) {
			size_t N = arr.size();
			if (N == 1)
			{
				return { {-1,-1} };
			}
			if (N == 0)
			{
				return { {} };
			}
			vector<vector<int>> ans(N, vector<int>(2, -1));
			stack<int> st;

			for (int i = 0; i < N; i++)
			{
				while (!st.empty() && arr[st.top()] > arr[i])
				{
					int topindex = st.top();
					st.pop();
					ans[topindex][1] = i;
					{
						ans[topindex][0] = st.empty() ? -1 : st.top();
					}
				}
				ans[i][0] = st.empty() ? -1 : st.top();

				st.push(i);
			}

			while (!st.empty())
			{
				int topindex = st.top();
				st.pop();
				ans[topindex][1] = -1;
			}
			return ans;
		}

		// 有重复数字
		vector<vector<int>> getNearLess(vector<int> & arr)
		{
			size_t N = arr.size();
			if (N == 1)
			{
				return { {-1,-1} };
			}
			if (N == 0)
			{
				return { {} };
			}
			vector<vector<int>> ans(N, vector<int>(2, -1));
			stack<vector<int>> st;

			for (int i = 0; i < N; i++)
			{
				while (!st.empty() && arr[st.top().back()] > arr[i])
				{
					vector<int> ti = st.top();
					st.pop();
					int leftindex = st.empty() ? -1 : st.top().back();
					for (auto & it : ti)
					{
						ans[it][1] = i;
						ans[it][0] = leftindex;
					}
				}
				if (st.empty())
				{
					st.push({ i });
				}
				else if (arr[st.top().back()] == arr[i])
				{
					st.top().push_back(i);
				}
				else // arr[st.top().back()] < arr[i]
				{
					st.push({ i });
				}
			}

			while (!st.empty())
			{
				vector<int> ti = st.top();
				st.pop();
				int leftindex = st.empty() ? -1 : st.top().back();
				for (auto it : ti)
				{
					ans[it][1] = -1;
					ans[it][0] = leftindex;
				}
			}
			return ans;
		}


		vector<vector<int>> rightway(vector<int> & arr)
		{
			size_t N = arr.size();
			if (N == 1)
			{
				return { {-1,-1} };
			}
			if (N == 0)
			{
				return { {} };
			}
			vector<vector<int>> ans(N, vector<int>(2, -1));

			for (int i = 0; i < N; i++)
			{
				int leftindex = -1;
				int rightindex = -1;
				int cur = i - 1;
				while (cur >= 0)
				{
					if (arr[i] > arr[cur])
					{
						leftindex = cur;
						break;
					}
					cur--;
				}
				cur = i + 1;
				while (cur < N)
				{
					if (arr[i] > arr[cur])
					{
						rightindex = cur;
						break;
					}
					cur++;
				}
				ans[i][0] = leftindex;
				ans[i][1] = rightindex;
			}
			return ans;
		}


	};

}

void printOutput(vector<int>&arr, vector<vector<int>> & output) {

	print(arr);
	printMatrix(output);
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



void test_Code01_MonotonousStack()
{
	int maxlen = 1000;

	int maxval = 50;

	int testLoop = 50;
	stop_watch st;
	double elapse_force = 0.0;
	double elapse_monostack = 0.0;
	Code01_MonotonousStack::Solution sln;
	cout << "test begin" << endl;
	for (int i = 0; i < testLoop; i++)
	{
		vector<int > arr = generateRandomArray(maxlen, maxval, 1);
		st.start();
		vector<vector<int>> ans1 = sln.rightway(arr);
		st.stop();
		elapse_force += st.elapsed_ms();
		/*vector<int> arr2 = generateRandomNoRepeatArray(maxlen, maxval, 1);
		vector<vector<int>> ans2 = sln.getNearLessNoRepeat(arr2);*/
		//vector<int > arr3 = generateRandomArray(maxlen, maxval, 1);
		st.start();
		vector<vector<int>> ans2 = sln.getNearLess(arr);
		st.stop();
		elapse_monostack += st.elapsed_ms();
		if (false == outputequal(ans1, ans2))
		{
			print(arr);
			cout << "ans1" << endl;
			printMatrix(ans1);
			cout << "ans2" << endl;
			printMatrix(ans2);
			break;
		}
	}
	cout << "test end" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force:" << elapse_force / testLoop << endl;
	cout << "monostack:" << elapse_monostack / testLoop << endl;

	//printOutput(arr1, ans1);
	//	test begin
	//	test end
	//	average elapse(ms)
	//	force:0.41332
	//	monostack : 0.92298
}

#endif