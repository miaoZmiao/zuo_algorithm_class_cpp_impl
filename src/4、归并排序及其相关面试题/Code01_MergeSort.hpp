#pragma once


#include "utility_func.hpp"

namespace Code01_MergeSort {

	// ¹é²¢ÅÅÐò
	void merge(vector<int> & arr, int left, int mid, int right)
	{
		vector<int> tmpv(right - left + 1, 0);
		int leftindex = left;
		int rightindex = mid + 1;

		int tmpindex = 0;
		while (leftindex <= mid && rightindex <= right)
		{
			if (arr[leftindex] < arr[rightindex])
			{
				tmpv[tmpindex] = arr[leftindex];
				leftindex++;
			}
			else
			{
				tmpv[tmpindex] = arr[rightindex];
				rightindex++;
			}
			tmpindex++;
		}

		while (leftindex <= mid)
		{
			tmpv[tmpindex++] = arr[leftindex];
			leftindex++;
		}

		while (rightindex <= right)
		{
			tmpv[tmpindex++] = arr[rightindex];
			rightindex++;
		}

		for (int i = left, j = 0; i <= right; i++, j++)
		{
			arr[i] = tmpv[j];
		}

	}


	void merge_sort(vector<int> & arr, int left, int right)
	{
		if (left >= right)
		{
			return;
		}
		int mid = left + ((right - left) >> 1);
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, mid, right);

	}


	// ·ÇµÝ¹éµÄ¹é²¢ÅÅÐò

	void mergesort_non_recursive(vector<int> & arr)
	{
		size_t arrlen = arr.size();

		int step = 1;

		while (step < arrlen) {

			int left = 0;
			while (left < arrlen)
			{
				int mid = left + step - 1;
				if (mid >= arrlen)
				{
					break;
				}
				// mid < arrlen 
				int right = std::min(size_t(mid + step), arrlen - 1);
				merge(arr, left, mid, right);
				left = right + 1;
			}

			if (step > arrlen / 2)
			{
				break;
			}
			step = step << 1;
		}
	}

}
