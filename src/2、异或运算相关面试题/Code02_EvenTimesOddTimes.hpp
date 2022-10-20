#pragma once


#include "utility_func.hpp"

namespace Code02_EvenTimesOddTimes {

	int find_odd_number(vector<int> & arr)
	{
		int eor = 0;

		for (auto ele : arr)
		{
			eor = eor ^ ele;
		}
		return eor;
	}

	// 技巧： 把int类型数字最右侧的1提取出来（常用）

	int right_most_1(int num)
	{
		int ret = 0;
		ret = num & (~num + 1);
		return ret;
	}

	void printbinary(int num)
	{
		unsigned int tmp = num;
		stack<short> tmpst;
		while (tmp != 0)
		{
			if (tmp % 2)
			{
				tmpst.push(1);
			}
			else
			{
				tmpst.push(0);
			}
			tmp = tmp >> 1;
		}

		// print
		cout << endl;
		cout << "\t";
		int pop_num = 0;
		while (!tmpst.empty())
		{
			auto ele = tmpst.top();
			cout << ele;
			tmpst.pop();
			pop_num++;
			if (pop_num == 4)
			{
				cout << " ";
				pop_num = 0;
			}

		}
		cout << endl;
	}

	// 两个数字出现了奇数次，其他数出现了偶数次
	// 要求空间O(1), 时间O(N)

	int find_odd_a_b_number(vector<int>& arr)
	{
		int eor = 0;
		for (auto it : arr)
		{
			eor = eor ^ it;
		}

		int rightmost_1 = eor & (~eor + 1);

		int a_ = 0;

		for (auto it : arr)
		{
			if ((rightmost_1 & it) != 0)
			{
				a_ = a_ ^ it;
			}
		}

		cout << "a : " << a_ << endl;
		cout << "b : " << (a_ ^ eor) << endl;


		return 0;
	}

}