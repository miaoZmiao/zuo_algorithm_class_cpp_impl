#pragma once

#include "utility_func.hpp"

namespace Code03_KM {

	// 
	// 一种数字出现K次，其他数出现了M次，
	//  M>1, K < M,
	// 要求找到出现K次的数字，要求额外空间复杂度O(1)，时间复杂度O(N)

	// arr中只有一种出现了K次,其余出现了M次
	// 

	int onlyKtimes(vector<int>& arr, int M, int K)
	{
		vector<int> alphabet(32, 0);
		for (auto it : arr)
		{
			for (int i = 0; i <= 31; i++)
			{
				if ((it&(1 << i)) != 0)
				{
					alphabet[i]++;
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < 32; i++)
		{
			if ((alphabet[i] % M) != 0)
			{
				ans = ans | (1 << i);
			}
		}
		return ans;
	}
}