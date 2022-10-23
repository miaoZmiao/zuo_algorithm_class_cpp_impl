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


void test_Code02_BubbleSort() {

	cout << "test_Code02_BubbleSort begin" << endl;
	int testTime = 5000;
	int maxSize = 100;
	int maxValue = 100;
	bool succeed = true;
	for (int i = 0; i < testTime; i++) {
		vector<int> arr1 = generateRandomArray(maxSize, maxValue);
		vector<int> arr2 = arr1;
		Code02_BubbleSort::bubblesort(arr1);
		std::sort(arr2.begin(), arr2.end());
		if (!vector_equal(arr1, arr2)) {
			succeed = false;
			print(arr1);
			print(arr2);
			break;
		}
	}
	cout << (succeed ? "Nice!" : "Fucking fucked!") << endl;
	cout << "test_Code02_BubbleSort end" << endl;
}