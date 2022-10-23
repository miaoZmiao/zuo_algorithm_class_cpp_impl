#pragma once
#ifndef Code02_HorseJump_HPP
#define Code02_HorseJump_HPP
#include <iostream>
#include "stop_watch.hpp"
#include <vector>
using namespace std;

namespace Code02_HorseJump {
	
	class Solution
	{
	public:
		// 当前来到的位置是（x,y）
		// 还剩下rest步需要跳
		// 跳完rest步，正好跳到a，b的方法数是多少？
		// 10 * 9
		int jump(int a, int b, int k) {
			return process1(0, 0, k, a, b);
		}

		int process1(int x, int y, int rest, int targetx, int targety) {
			if (x < 0 || x> 9 || y < 0 || y > 8)
			{
				return 0;
			}
			if (rest == 0)
			{
				if (x == targetx && y == targety)
				{
					return 1;
				}
				return 0;
			}
			int ways = 0;
			//  
			ways += process1(x - 2, y - 1, rest - 1, 
				targetx, targety);
			ways += process1(x - 2, y + 1, rest - 1,
				targetx, targety);
			ways += process1(x - 1, y + 2, rest - 1,
				targetx, targety);
			ways += process1(x + 1, y + 2, rest - 1,
				targetx, targety);
			ways += process1(x + 2, y + 1, rest - 1,
				targetx, targety);
			ways += process1(x + 2, y - 1, rest - 1,
				targetx, targety);
			ways += process1(x + 1, y - 2, rest - 1,
				targetx, targety);
			ways += process1(x - 1, y - 2, rest - 1,
				targetx, targety);
			return ways;
		}


		int jumpdp(int a, int b, int k)
		{
			vector<vector<int>> chesstable(10, vector<int>(9, 0));
			chesstable[a][b] = 1;

			for (int loop = 0; loop < k; loop++)
			{
				vector<vector<int>> tmpchesstable = chesstable;
				for (int x = 0; x < 10; x++)
				{
					for (int y = 0; y < 9; y++)
					{
						int ways = 0;
						if (x >=2 && y>=1)
						{
							ways += chesstable[x - 2][y - 1];
						}
						if ((x >= 2) && (y <= 7))
						{
							ways += chesstable[x - 2][y + 1];
						}
						if ((x >= 1) && (y <= 6))
						{
							ways += chesstable[x - 1][y + 2];
						}
						if ((x <= 8) && (y <= 6))
						{
							ways += chesstable[x + 1][y + 2];
						}
						if ((x <= 7) && (y <= 7))
						{
							ways += chesstable[x + 2][y + 1];
						}
						if ((x <= 7) && (y >=1 ))
						{
							ways += chesstable[x + 2][y - 1];
						}
						if ((x <= 8) && (y >= 2))
						{
							ways += chesstable[x + 1][y - 2];
						}
						if ((x >= 1) && (y >= 2))
						{
							ways += chesstable[x - 1][y - 2];
						}
						tmpchesstable[x][y] = ways;
					}
				}
				chesstable.swap(tmpchesstable);
			}
			return chesstable[0][0];
		}


	};

}

void test_Code02_HorseJump() {
	
	cout << "test_Code02_HorseJump begin" << endl;
	int x = 7;
	int y = 7;
	int step = 10;
	Code02_HorseJump::Solution sln;
	stop_watch st;
	st.start();
	int ret1 = sln.jump(x, y, 10);
	st.stop();
	cout << "ret1:" << ret1 << endl;
	cout << "force : " << st.elapsed_ms() << "ms" << endl;
	st.start();
	int ret2 = sln.jumpdp(x, y, 10);
	st.stop();
	cout << "ret2:" << ret2 << endl;
	cout << "dp : " << st.elapsed_ms() << "ms" << endl;

	cout << "test_Code02_HorseJump end" << endl;
	//  amazing result on my computer
	//	ret1:515813
	//	force : 124.714ms
	//	ret2 : 515813
	//	dp : 0.073ms


}



#endif