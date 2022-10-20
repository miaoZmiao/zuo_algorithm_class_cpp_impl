#pragma once

#include "utility_func.hpp"


namespace Code01_SelectionSort {
	
	// —°‘Ò≈≈–Ú
	void selectsort(std::vector<int> & arr) {
		int veclen = arr.size();

		for (int i = 0; i < veclen; i++)
		{
			int minindex = i;
			for (int j = i + 1; j < veclen; j++)
			{
				if (arr[j] < arr[minindex])
				{
					minindex = j;
				}

			}
			swap(arr, i, minindex);
		}
	}

}

