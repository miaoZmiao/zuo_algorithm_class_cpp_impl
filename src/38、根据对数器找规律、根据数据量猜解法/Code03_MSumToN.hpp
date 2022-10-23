#pragma once
#ifndef Code03_MSumToN_HPP
#define Code03_MSumToN_HPP

#include <iostream>
using namespace std;
namespace Code03_MSumToN {

	bool isMSum1(int n) {
	
		for (int start = 1; start <= n; start++)
		{
			int sum = start;
			for (int j = start + 1; j <= n; j++)
			{
				if (sum + j > n)
				{
					break;
				}
				if (sum + j == n)
				{
					return true;
				}
				sum += j;
			}
		}
		return false;
	}

	bool smartisMSum(int n)
	{
		int mostright = n & (~n + 1);
		if (mostright == n)
		{
			return false;
		}
		return true;
	}


}


void test_Code03_MSumToN() {
	cout << "test_Code03_MSumToN begin" << endl;
	for (int i = 1; i < 200; i++)
	{
		cout << i << "," << Code03_MSumToN::isMSum1(i)<<","<< Code03_MSumToN::smartisMSum(i) << endl;
	}
	cout << "test_Code03_MSumToN end" << endl;
}

#endif


