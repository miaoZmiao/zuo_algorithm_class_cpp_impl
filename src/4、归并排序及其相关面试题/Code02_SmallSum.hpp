#pragma once
#include "utility_func.hpp"

namespace Code02_SmallSum {

	// 小和问题
// 给定数组，
// 一个数字的左边比他小的数字加起来
// 的小和数组

	int merge_sort_and_sum(vector<int> & arr, int left, int mid, int right) {

		vector<int> tmpvec(right - left + 1, 0);
		int leftindex = left;
		int rightindex = mid + 1;
		int ans = 0;
		int tmpindex = 0;
		while (leftindex <= mid && rightindex <= right)
		{
			if (arr[leftindex] < arr[rightindex])
			{
				ans += arr[leftindex] * (right - rightindex + 1);
				tmpvec[tmpindex] = arr[leftindex];
				leftindex++;
			}
			/*	else if (arr[leftindex] == arr[rightindex])
				{
					tmpvec[tmpindex] = arr[rightindex];
					rightindex++;
				}*/
			else // arr[leftindex] > arr[rightindex]
			{
				tmpvec[tmpindex] = arr[rightindex];
				rightindex++;
			}
			tmpindex++;
		}

		while (leftindex <= mid)
		{
			tmpvec[tmpindex++] = arr[leftindex];
			//ans += arr[leftindex] * (right - rightindex + 1);
			leftindex++;
		}
		while (rightindex <= right)
		{
			tmpvec[tmpindex++] = arr[rightindex];
			rightindex++;
		}

		for (int i = left, j = 0; i < right, j < tmpindex; i++, j++)
		{
			arr[i] = tmpvec[j];
		}
		return ans;
	}


	int minisum(vector<int> & arr, int left, int right)
	{
		if (left >= right)
		{
			return 0;
		}

		int mid = left + ((right - left) >> 1);

		int leftsum = minisum(arr, left, mid);
		int rightsum = minisum(arr, mid + 1, right);

		int cursum = merge_sort_and_sum(arr, left, mid, right);

		return leftsum + rightsum + cursum;
	}
}