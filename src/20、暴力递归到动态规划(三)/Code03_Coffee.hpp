#pragma once
#ifndef Code03_Coffee_HPP
#define Code03_Coffee_HPP
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include "utility_func.hpp"
using namespace std;


namespace Code03_Coffee {
// 题目
// 数组arr代表每一个咖啡机冲一杯咖啡的时间，
// 每个咖啡机只能串行的制造咖啡。
// 现在有n个人需要喝咖啡，只能用咖啡机来制造咖啡。
// 认为每个人喝咖啡的时间非常短，冲好的时间即是喝完的时间。
// 每个人喝完之后咖啡杯可以选择洗或者自然挥发干净，
//	只有一台洗咖啡杯的机器，只能串行的洗咖啡杯。
// 洗杯子的机器洗完一个杯子时间为a，
//	任何一个杯子自然挥发干净的时间为b。
// 四个参数：arr, n, a, b
// 假设时间点从0开始，返回所有人喝完咖啡
// 并洗完咖啡杯的全部过程结束后，至少来到什么时间点。




	class Solution
	{
	public:
		// 验证的方法
		// 彻底的暴力
		// 很慢但是绝对正确
		int right(vector<int> & arr, int n, int a, int b) {
			vector<int> times(arr.size(), 0);
			vector<int> drinks(n, 0);
			return forceMake(arr, drinks, times, 0, a, b);
		}
		// 暴力做咖啡
		// 第 index 人喝咖啡(第 index 个被子 的时间)
		// 需要填充drinks数组(杯子什么时候喝完咖啡了)
		// 需要填充 times 数组 (咖啡机啥时候可用)
		int forceMake(vector<int> & arr, vector<int> & drinks,
			vector<int> & times, 
			int index, int a, int b) 
		{
			if (index == drinks.size())
			{
				auto sorteddrinks = drinks;
				std::sort(sorteddrinks.begin(), sorteddrinks.end());
				return forceWash(sorteddrinks, 0, 0, a, b);
			}
			// 第 index 个人(杯子) 用 第 i 号咖啡机磨咖啡
			int min_time = INT_MAX;
			for (int i = 0; i < arr.size(); i++)
			{
				int addtime = arr[i];
				int pre = times[i];
				times[i] = times[i] + addtime;
				drinks[index] = times[i];
				int tmp_mintime = forceMake(arr, drinks,
					times, index+1, a, b);
				min_time = std::min(min_time, tmp_mintime);
				drinks[index] = 0;
				times[i] = pre;
			}
			return min_time;
			
		}

		// 杯子的可用时间 drinks
		// a 洗一个杯子的时间
		// b 自然干燥杯子的时间
		// 从index 杯开始
		int forceWash(vector<int> & drinks, int index,
			int washavailable, int a, int b)
		{
			if(index == drinks.size())
			{
				return 0;
			}
			int min_time = INT_MAX;
			// 第 index 个杯子 如果我们决定洗一下
			// 花了 washtime 时间
			int washovertime = std::max(washavailable, 
				drinks[index]) + a;
			// 剩下的杯子需要处理这么多时间
			int restime1 = forceWash(drinks, index+1, 
				washovertime,a,b);
			// 两个时间取 max，在洗第index个杯子的情况下
			// 用的最短时间
			int p1 = std::max(washovertime, restime1);

			// 第index个杯子，决定自然风干
			int drytime = drinks[index] + b;
			int restime2 = forceWash(drinks, index + 1,
				washavailable, a, b);
			int p2 = std::max(drytime, restime2);

			return std::min(p1, p2);
		}

		struct Machine
		{
			int makecoffeetime = 0;
			int cur = 0;
		};

		

		int minTime1(vector<int> & arr, int n, int a, int b)
		{
			auto compare_machine = []
			(const Machine & A, const Machine & B)->bool {
				return (A.makecoffeetime + A.cur) >
					(B.makecoffeetime + B.cur);
			};

			priority_queue<Machine, vector<Machine>,
				decltype(compare_machine)> pq(compare_machine);

			vector<int> drinks(n, 0);
			for (auto & makecoffeetime : arr)
			{
				Machine m;
				m.cur = 0;
				m.makecoffeetime = makecoffeetime;
				pq.push(m);
			}

			for (int i = 0; i < n; i++)
			{
				Machine m = pq.top();
				pq.pop();
				m.cur += m.makecoffeetime;
				drinks[i] = m.cur;
				pq.push(m);
			}
			return bestTime(drinks, 0 ,0 ,a,b);
		}

		int bestTime(vector<int> & drinks, int index,
			int washavailable, int a, int b)
		{
			if (index == drinks.size())
			{
				return 0;
			}
			int min_time = INT_MAX;
			// 第 index 个杯子 如果我们决定洗一下
			// 花了 washtime 时间
			int washovertime = std::max(washavailable,
				drinks[index]) + a;
			// 剩下的杯子需要处理这么多时间
			int restime1 = bestTime(drinks, index + 1,
				washovertime, a, b);
			// 两个时间取 max，在洗第index个杯子的情况下
			// 用的最短时间
			int p1 = std::max(washovertime, restime1);
			// 第index个杯子，决定自然风干
			int drytime = drinks[index] + b;
			int restime2 = bestTime(drinks, index + 1,
				washavailable, a, b);
			int p2 = std::max(drytime, restime2);
			return std::min(p1, p2);
		}

		int bestTimedp(vector<int> & drinks,int a, int b)
		{
			int maxAvailable = 0;
			int N = drinks.size();
			for (int i = 0; i < N; i++)
			{
				maxAvailable = std::max(maxAvailable, drinks[i]) 
					+ a;
			}
			vector<vector<int>> dp
			(N+1, vector<int>(maxAvailable +1, 0));
			
			for (int index = N - 1; index >= 0; index--)
			{
				for (int washavailable = maxAvailable; 
					washavailable >= 0; 
					washavailable--)
				{
					int min_time = INT_MAX;
					// 第 index 个杯子 如果我们决定洗一下
					// 花了 washtime 时间
					int washovertime = std::max(washavailable,
						drinks[index]) + a;
					// 剩下的杯子需要处理这么多时间
					int restime1 = 0;
					if (washovertime <= maxAvailable)
					{
						restime1 = dp[index + 1][washovertime];
					}
					// 两个时间取 max，在洗第index个杯子的情况下
					// 用的最短时间
					int p1 = std::max(washovertime, restime1);
					// 第index个杯子，决定自然风干
					int drytime = drinks[index] + b;
					int restime2 = dp[index + 1][washavailable];
					int p2 = std::max(drytime, restime2);
					dp[index][washavailable] = std::min(p1, p2);
				}
			}
			return dp[0][0];
		}


		int minTime2(vector<int> & arr, int n, int a, int b)
		{
			auto compare_machine = []
			(const Machine & A, const Machine & B)->bool {
				return (A.makecoffeetime + A.cur) >
					(B.makecoffeetime + B.cur);
			};

			priority_queue<Machine, vector<Machine>,
				decltype(compare_machine)> pq(compare_machine);

			vector<int> drinks(n, 0);
			for (auto & makecoffeetime : arr)
			{
				Machine m;
				m.cur = 0;
				m.makecoffeetime = makecoffeetime;
				pq.push(m);
			}

			for (int i = 0; i < n; i++)
			{
				Machine m = pq.top();
				pq.pop();
				m.cur += m.makecoffeetime;
				drinks[i] = m.cur;
				pq.push(m);
			}
			return bestTimedp(drinks, a, b);
		}
	};

}

void test_Code03_Coffee() {
	int len = 10;
	int max = 10;
	int testTime = 10;
	cout << "测试开始" << endl;
	Code03_Coffee::Solution sln;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);

	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(len, max, 1);
		//vector<int> arr = { 6,2,7,7,7 };
		int n = (int)(dist(gen) * 7) + 1;
		int a = (int)(dist(gen) * 7) + 1;
		int b = (int)(dist(gen) * 10) + 1;
		/*int n = 3;
		int a = 3;
		int b = 4;*/
		int ans1 = sln.right(arr, n, a, b);
		int ans2 = sln.minTime1(arr, n, a, b);
		int ans3 = sln.minTime2(arr, n, a, b);
		if (ans1 != ans2 || ans2 != ans3) {
			print(arr);
			cout << "n : " << n << endl;
			cout << "a : " << a << endl;
			cout << "b : " << b << endl;
			cout << ans1 << " , " << ans2 << " , " << ans3 << endl;
			cout << "===============" << endl;
			break;
		}
	}
	cout << "测试结束" << endl;
}




#endif 