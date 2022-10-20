#pragma once
#ifndef Code01_FindMinKth_HPP
#define Code01_FindMinKth_HPP
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include "utility_func.hpp"
using namespace std;
namespace Code01_FindMinKth {

	class Solution {

		std::random_device rd_;
		std::mt19937 mt_;
		std::uniform_real_distribution<> dist_;

	public:
		Solution() {
			mt_.seed(rd_());
			std::uniform_real<> p(0.0, 1.0);
			dist_.param(p.param());
			/*vector<double> v(10, 0.0);
			for (int i = 0; i < 10; i++)
			{
				v[i] = dist_(mt_);
			}
			print(v);*/
		}

		// O(N*logk)
		int minKth1(vector<int>& arr, int k)
		{
			std::priority_queue<int, vector<int>, std::less<int>> pq;
			for (int i = 0; i < k; i++)
			{
				pq.push(arr[i]);
			}
			int N = arr.size();
			for (int i = k; i < N; i++)
			{
				if (arr[i] < pq.top())
				{
					pq.push(arr[i]);
					pq.pop();
				}
			}
			return pq.top();
		}
		// 方法2 借助快排
		// pivot 的获取方法
		int minKth2(vector<int>& arr, int k)
		{
			vector<int> input = arr;
			int N = arr.size();
			int ans = process2(input, 0, N - 1, k - 1);
			return ans;
		}

		int process2(vector<int>& arr, int L, int R, int index)
		{
			if (L == R)
			{
				return arr[L];
			}
			int ip = L + ((int)(R - L)*dist_(mt_));
			int pivot = arr[ip];

			vector<int> p = partition(arr, L, R, pivot);

			if (index >= p[0] && index <= p[1])
			{
				return arr[index];
			}
			else if(index < p[0])
			{
				return process2(arr, L, p[0] - 1, index);
			}
			else {
				return process2(arr, p[1] + 1, R, index);
			}
		
		}

		vector<int> partition(vector<int>& arr, int L, int R, int pivot) 
		{
			int left = L - 1;
			int right = R + 1;
			int cur = L;
			while (cur < right)
			{
				if (arr[cur] > pivot)
				{
					swap(arr, cur, --right);
				}
				else if (arr[cur] < pivot)
				{
					swap(arr, cur++, ++left);
				}
				else
				{
					cur++;
				}
			}
			return { left + 1, right - 1 };
		}

		void swap(vector<int>& arr, int index1, int index2)
		{
			if (index1 == index2)
			{
				return;
			}
			arr[index1] = arr[index1] ^ arr[index2];
			arr[index2] = arr[index1] ^ arr[index2];
			arr[index1] = arr[index1] ^ arr[index2];
		}
		//  bfptr 算法
		int minKth3(vector<int>& arr, int k) 
		{
			int N = arr.size();
			vector<int> input = arr;
			int ans = bfprt(input, 0, N - 1, k - 1);
			return ans;
		}

		int bfprt(vector<int> & arr, int L, int R, int index) {
			if (L == R)
			{
				return arr[L];
			}
			int pivot = getMedianOfMedian(arr, L, R);
			vector<int> p = partition(arr, L, R, pivot);
			if (index >= p[0] && index <= p[1])
			{
				return arr[index];
			}
			else if (index < p[0])
			{
				return bfprt(arr, L, p[0] - 1, index);
			}
			else
			{
				return bfprt(arr, p[1] + 1, R, index);
			}
		}

		int getMedianOfMedian(vector<int> & arr, int L, int R)
		{
			int size = R - L + 1;
			int offset = size % 5 == 0 ? 0 : 1;
			vector<int> med(size / 5 + offset, 0);
			for (int i = 0; i < med.size(); i++)
			{
				int left = L + i * 5;
				int right = std::min(left+4, R);
				med[i] = getMedian(arr, left, right);
			}
			int MK = med.size();
			int me = bfprt(med, 0, MK - 1, MK / 2);
			return me;
		}

		int getMedian(vector<int> & arr, int L, int R)
		{
			for (int i = L+1; i <= R; i++)
			{
				for (int j = i-1; j >= L; j--)
				{
					if (arr[j+1] < arr[j])
					{
						swap(arr, j+1, j);
					}
					else // arr[j+1]>=arr[j]
					{
						break;
					}
				}
			}
			return arr[L + (R - L) / 2];
		}

	};
}

void test_Code01_FindMinKth() {

	Code01_FindMinKth::Solution sln;
	vector<int> arr = { 9,4,2,7,5,3,8,6,1 };
	int maxLen = 10;
	int maxvalue = 10;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(1, maxLen);
	int testTime = 100;
	cout << "test Code01_FindMinKth begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(maxLen, maxvalue, 1);
		//vector<int> arr = { 5,2,8,4,6,6,17,11,14,3 };
		int K = dist(mt);
		//int K = 6;
		int ans1 = sln.minKth1(arr, K);
		int ans2 = sln.minKth2(arr, K);
		int ans3 = sln.minKth3(arr, K);
		if (ans1 != ans2 || ans2 != ans3)
		{
			print(arr);
			cout << "K:" << K << endl;
			cout <<ans1<< "," << ans2 <<","<<ans3<< endl;
			break;
		}
	}
	cout << "test Code01_FindMinKth end" << endl;

}

#endif