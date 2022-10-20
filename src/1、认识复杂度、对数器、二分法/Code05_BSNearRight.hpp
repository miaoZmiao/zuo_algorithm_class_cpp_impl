#pragma once
#include "utility_func.hpp"

namespace Code05_BSNearRight {
	//   Ñ°ÕÒÂú×ã <= value µÄ×îÓÒÎ»ÖÃ

	int find_nearest_right_that_less_than_target(vector<int> & arr, int target)
	{
		int retindex = -1;
		if (arr.size() == 0)
		{
			return retindex;
		}
		int left = 0;
		int right = arr.size() - 1;
		while (left <= right)
		{
			int mid = left + ((right - left) >> 1);
			if (target <= arr[mid])
			{
				retindex = mid;
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}

		}

		return retindex;

	}


}