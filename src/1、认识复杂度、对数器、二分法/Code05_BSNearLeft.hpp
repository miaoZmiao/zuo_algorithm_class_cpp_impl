#pragma once
#include "utility_func.hpp"


namespace Code05_BSNearLeft {

	int find_nearest_left_that_larger_than_target(vector<int> & arr, int target)
	{
		int retindex = -1;
		if (arr.size() == 0)
		{
			return retindex;
		}
		int left = 0;
		int right = arr.size() - 1;
		// 这里换成<= 了
		// 没有固定套路
		while (left <= right)
		{
			int mid = left + ((right - left) >> 1);
			if (arr[mid] <= target)
			{
				retindex = mid;
				left = mid + 1;
			}
			else // arr[mid] > target
			{
				right = mid - 1;
			}

		}
		return retindex;
	}


}