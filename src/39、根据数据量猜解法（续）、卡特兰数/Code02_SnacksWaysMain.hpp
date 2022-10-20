#pragma once
#ifndef Code02_SnacksWaysMain_HPP
#define Code02_SnacksWaysMain_HPP

//本文件是Code02_SnacksWays问题的牛客题目解答
//但是用的分治的方法
//这是牛客的测试链接：
//https://www.nowcoder.com/questionTerminal/d94bb2fa461d42bcb4c0f2b94f5d4281

#include <vector>
#include <iostream>
#include <set>
#include <map>
using namespace std;

namespace Code02_SnacksWaysMain {

	long process1(vector<int> & arr, int index, int e, long w, long bag, std::map<long, long> & mp);

	long ways(vector<int> & arr,  long bag) {
		
		int mid = arr.size() >> 1;
		map<long, long> lmp;
		map<long, long >rmp;
		long ways = 0;
		ways += process1(arr, 0, mid, 0, bag, lmp);
		ways += process1(arr, mid + 1, arr.size() - 1, 0, bag, rmp);
		long presum = 0;
		for (auto it = rmp.begin(); it != rmp.end(); it++)
		{
			it->second += presum;
			presum = it->second;
		}
		for (auto left : lmp)
		{
			long rest = bag - left.first;
			auto it = rmp.upper_bound(rest);
			if (it == rmp.end())
			{
				ways += left.second * presum;
			}
			else if (it == rmp.begin())
			{
				continue;
			}
			else {
				it--;
				ways += left.second * (it->second);
			}
		}
		return ways + 1;
	}


	long process1(vector<int> & arr, int index, int e, long w, long bag, std::map<long, long> & mp)
	{
		if (w > bag)
		{
			return 0;
		}
		if (index > e)
		{
			if (w != 0)
			{
				mp[w] ++;
				return 1;
			}
			else  // w ==0
			{
				return 0;
			}
		}

		long ways = process1(arr, index + 1, e, w, bag, mp);
		ways += process1(arr, index + 1, e, w + arr[index], bag, mp);
		return ways;
	
	}


}


void test_Code02_SnacksWaysMain() {
	
	//输入包括两行
	//第一行为两个正整数n和w(1 <= n <= 30, 1 <= w <= 2 * 10 ^ 9), 表示零食的数量和背包的容量。
	//第二行n个正整数v[i](0 <= v[i] <= 10 ^ 9), 表示每袋零食的体积。
	int n = 30;
	int w = 1;
	cin >> n;
	cin >> w;
	vector<int> arr(n, 0);
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	long ways = Code02_SnacksWaysMain::ways(arr, w);

	cout << ways << endl;


	// 牛客测试已经通过
}


#endif