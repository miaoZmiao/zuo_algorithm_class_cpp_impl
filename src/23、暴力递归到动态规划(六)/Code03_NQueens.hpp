#pragma once
#ifndef Code03_NQueens_HPP
#define Code03_NQueens_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "stop_watch.hpp"
using namespace std;
namespace Code03_NQueens {

	class Solution
	{
	public:
		int num1(int n) {
			if (n < 1) {
				return 0;
			}
			vector<int> record(n, 0);
			return process1(0, record, n);
		}

		int process1(int row, vector<int> & record, int N)
		{
			if (row == N)
			{
				return 1;
			}
			int ways = 0;
			for (int col = 0; col < N; col++)
			{
				if (judge(record, col, row))
				{
					record[row] = col;
					ways += process1(row + 1, record, N);
				}
			}
			return ways;
		}

		bool judge(vector<int> & record, int col , int row)
		{
			for (int i = 0; i < row; i++)
			{
				if (record[i]== col)
				{
					return false;
				}
				if (std::abs(i - row) == std::abs(record[i] - col))
				{
					return false;
				}
			}
			return true;
		}

		// 请不要超过32皇后问题
		int num2(int n) {
			if (n < 1 || n > 32) {
				return 0;
			}
			int limit = (n == 32 ? -1 : ((1 << n) - 1));
			return process2(limit, 0, 0, 0);

		}
		int process2(int limit, int colLim, int leftDiaLim, int rightDiaLim)
		{
			if (limit == colLim)
			{
				return 1;
			}
			
			int currentLim = limit & (~(colLim | leftDiaLim | rightDiaLim));
			int ways = 0;
			while (currentLim != 0)
			{
				int rightmost1 = currentLim &(~currentLim+1);
				currentLim = currentLim ^ rightmost1;
				ways += process2(limit, colLim | rightmost1, ((leftDiaLim | rightmost1) << 1), ((rightDiaLim | rightmost1) >> 1));
			}
			return ways;
		}

	};
}

void test_Code03_NQueens() {

	int n = 10;
	Code03_NQueens::Solution sln;
	cout << "test begin" << endl;
	stop_watch st;
	st.start();
	int ans1 = sln.num1(n);
	st.stop();
	double elapse_force1 = st.elapsed_ms();
	st.start();
	int ans2 = sln.num2(n);
	st.stop();
	double elapse_force2 = st.elapsed_ms();
	cout << "n:" << n << endl;
	cout << "ans1:" << ans1 << endl;
	cout << "ans2:" << ans2 << endl;
	cout << "test end" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "force1:" << elapse_force1 << endl;
	cout << "force2:" << elapse_force2 << endl;

	//	test begin
	//	n : 15
	//	ans1 : 2279184
	//	ans2 : 2279184
	//	test end
	//	average elapse(ms)
	//	force1 : 132303
	//	force2 : 1302.86
}

#endif