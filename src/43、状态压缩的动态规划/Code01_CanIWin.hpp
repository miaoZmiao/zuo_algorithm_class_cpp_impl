#pragma once
#include "utility_func.hpp"
#include <map>
namespace Code01_CanIWin {

	class Solution {
	public:
		// leetcode 464题
		// 1~choose 拥有的数字
		// total 一开始的剩余
		// 返回先手会不会赢
		/*1 <= maxChoosableInteger <= 20
			0 <= desiredTotal <= 300*/
		bool canIWin0(int choose, int total)
		{
			if (total == 0)
			{
				return true;
			}
			if ((((choose + 1)*choose )>> 1) < total)
			{
				return false;
			}

			vector<int> used(choose, 0);
			for (int i = 0; i < choose; i++)
			{
				used[i] = i + 1;
			}
			return process(used, total);
			
		}

		bool process(vector<int>& arr, int rest)
		{
			if (rest <= 0)
			{
				return false;
			}
			int N = arr.size();
			for (int i = 0; i < N; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				int cur = arr[i];
				arr[i] = -1;
				bool next = process(arr, rest - cur);
				arr[i] = cur;
				if (false == next) {
					return true;
				}
			}
			return false;
		}
		bool canIWin1(int choose, int total)
		{
			if (total == 0)
			{
				return true;
			}
			if ((((choose + 1)*choose) >> 1) < total)
			{
				return false;
			}
			return process1(choose, 0, total);
		}

		bool process1(int choose, int status, int rest)
		{
			if (rest <= 0)
			{
				return false;
			}
			for (int i = 1; i <= choose; i++)
			{
				if ((status & (1 << i)) != 0)
				{
					continue;
				}
				bool next = process1(choose, status | (1 << i), rest - i);
				if (false == next) {
					return true;
				}
			}
			return false;
		}
		// 暴力尝试改动态规划而已
		bool canIWin2(int choose, int total)
		{
			if (total == 0)
			{
				return true;
			}
			if ((((choose + 1)*choose) >> 1) < total)
			{
				return false;
			}
			std::map<int, bool> buffer;
			return process2(choose, 0, total, buffer);

		}


		bool process2(int choose, int status, int rest, std::map<int, bool> & buffer)
		{
			auto iter = buffer.find(status);
			if (iter != buffer.end())
			{
				return iter->second;
			}
			if (rest <= 0)
			{
				buffer[status] = false;
				return false;
			}
			for (int i = 1; i <= choose; i++)
			{
				if ((status & (1 << i)) != 0)
				{
					continue;
				}
				bool next = process2(choose, (status | (1 << i)), rest - i, buffer);
				if (false == next) {
					buffer[status] = true;
					return true;
				}
			}
			buffer[status] = false;
			return false;
		}
	};

	

}

void test_Code01_CanIWin() {

	int choose = 10;
	int total = 40;

	Code01_CanIWin::Solution sln;

	cout << "test_Code01_CanIWin begin" << endl;
	bool ans1 = sln.canIWin0(choose, total);
	bool ans2 = sln.canIWin1(choose, total);
	bool ans3 = sln.canIWin2(choose, total);
	if (ans1 != ans2 || ans2 != ans3)
	{
		cout << ans1 << "," << ans2 << "," << ans3 << endl;
	}
	cout << "test_Code01_CanIWin end" << endl;

}