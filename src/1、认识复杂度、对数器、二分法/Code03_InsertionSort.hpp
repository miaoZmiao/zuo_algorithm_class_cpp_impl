#pragma once
#include "utility_func.hpp"

namespace Code03_InsertionSort {
	// insert sort
	void insertsort(vector<int> & arr)
	{
		size_t arrlen = arr.size();

		for (int i = 1; i < arrlen; i++)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				if (arr[j] > arr[j + 1])
				{
					swap(arr, j, j + 1);
				}
				else
				{
					break;
				}
			}
		}
	}

}