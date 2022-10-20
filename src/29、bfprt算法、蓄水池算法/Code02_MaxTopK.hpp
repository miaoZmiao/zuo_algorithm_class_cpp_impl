#pragma once
#ifndef Code02_MaxTopK_HPP
#define Code02_MaxTopK_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include "utility_func.hpp"
#include "Code01_FindMinKth.hpp"
using namespace std;


namespace Code02_MaxTopK {

	class Solution {

	public:
		// N*logN   (+k??)
		vector<int> maxTopK1(vector<int>& arr, int k)
		{ 
			int N = arr.size();
			if (k == N)
			{
				return arr;
			}
			int retN = std::min(N, k);
			vector<int> ans(retN, 0);
			std::sort(arr.begin(), arr.end(), std::less<int>());
			for (int i = 0; i < retN; i++)
			{
				ans[i] = arr[N - 1 - i];
			}
			return ans;
		}
		// 方法二，时间复杂度O(N + K*logN)
		// 解释：堆
		vector<int> maxTopK2(vector<int>& arr, int k)
		{
			int N = arr.size();
			if (k == N)
			{
				return arr;
			}
			MyHeap mh(arr);
			mh.build_heap();
			k = std::min(k, N);
			vector<int> ans(k, 0);
			for (int i = 0; i < k; i++)
			{
				int num = mh.heap_pop();
				ans[i] = num;
			}
			return ans;
		}

		class MyHeap
		{
			int size_ = 0;
			vector<int> v_;
			int heap_valid_ = 0;
		public:
			MyHeap() {}
			MyHeap(int size) {
				size_ = size;
				v_.resize(size, 0);
				heap_valid_ = size;
			}
			MyHeap(vector<int>& arr) {
				size_ = arr.size();
				v_ = arr;
				heap_valid_ = size_;
			}
			// [L, R]
			void heapify(vector<int> & arr, int index, int Endindex)
			{
				int N = Endindex;
				int  cur = index;
				while (cur <= N-1)
				{
					int leftchild = 2 * cur + 1;
					int rightchild = leftchild + 1;
					int maxindex = cur;
					if (leftchild <N-1)
					{
						maxindex = arr[rightchild] > arr[leftchild] ? rightchild : leftchild;
					}
					else if(leftchild == N-1)
					{
						maxindex = leftchild;
					}
					else
					{
						break;
					}
					maxindex = arr[cur] > arr[maxindex] ? cur : maxindex;
					if (cur == maxindex)
					{
						break;
					}
					swap(arr, cur, maxindex);
					cur = maxindex;
				}

			}

			void swap(vector<int>& arr, int index1, int index2) {
				if (index1 == index2)
				{
					return;
				}
				arr[index1] = arr[index1] ^ arr[index2];
				arr[index2] = arr[index1] ^ arr[index2];
				arr[index1] = arr[index1] ^ arr[index2];
					  
			}


			// adjust insert
			void heap_insert(vector<int>& arr, int insertIndex)
			{
				while (arr[insertIndex] > arr[insertIndex / 2-1])
				{
					swap(arr, insertIndex, insertIndex / 2 - 1);
					insertIndex = insertIndex / 2 - 1;
				}
			}

			void build_heap()
			{
				int N = v_.size();
				for (int i = N - 1; i >= 0; i--)
				{
					heapify(v_, i, N);
				}
				
			}

			int heap_pop()
			{
				swap(v_, 0, --heap_valid_);
				heapify(v_, 0, heap_valid_);
				int ret = v_.back();
				v_.pop_back();
				return ret;
			}

			void push(int num)
			{
				v_.push_back(num);
				heap_insert(v_, heap_valid_++);
			}

			int top()
			{
				return v_[0];
			}

			bool empty()
			{
				return v_.size() == 0;
			}
		};

		// 借助FindMinKth
		vector<int> maxTopK3(vector<int>& arr, int k)
		{
			int N = arr.size();
			if (k == N)
			{
				return arr;
			}
			k = std::min(N, k);
			Code01_FindMinKth::Solution sln;
			// O(N)
			int num = sln.minKth2(arr, N - k);
			vector<int> ans(k, 0);
			int ki = 0;
			for (int i = 0; i < N; i++)
			{
				if (arr[i] > num)
				{
					ans[ki++] = arr[i];
				}
			}
			for (int i = ki; i < k; i++)
			{
				ans[i] = num;
			}

			std::sort(ans.begin(), ans.end(), std::greater<int>());
			return ans;
		
		}


	};

}

void test_Code02_MaxTopK() {

	Code02_MaxTopK::Solution sln;
	
	int maxLen = 10;
	int maxvalue = 10;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(1, maxLen);
	int testTime = 10;
	cout << "test Code02_MaxTopK begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(maxLen, maxvalue, 1);
		//vector<int> arr = { 5,2,8,4,6,6,17,11,14,3 };
		int K = dist(mt);
		//int K = 6;
		auto ans1 = sln.maxTopK1(arr, K);
		auto  ans2 = sln.maxTopK2(arr, K);
		auto ans3 = sln.maxTopK3(arr, K);
		if (!vector_equal(ans1, ans2) || !vector_equal(ans2, ans3))
		{
			print(arr);
			cout << "K:" << K << endl;
			cout << "ans1" << endl;
			print(ans1);
			cout << "ans2" << endl;
			print(ans2);
			cout << "ans3" << endl;
			print(ans3);
			break;
		}
	}
	cout << "test Code02_MaxTopK end" << endl;

}


#endif