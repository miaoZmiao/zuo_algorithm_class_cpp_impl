#pragma once

#include "utility_func.hpp"
namespace Code02_BubbleSort {
	// ц╟ещеепР
	void bubblesort(vector<int>& vec) {

		size_t veclen = vec.size();

		for (size_t j = veclen - 1; j >= 1; j--)
		{
			for (size_t i = 0; i < j; i++)
			{
				if (vec[i] > vec[i + 1])
				{
					swap(vec, i, i + 1);
				}
			}
		}

	}

}