#pragma once
#ifndef Code03_ZeroLeftOneStringNumber_HPP
#define Code03_ZeroLeftOneStringNumber_HPP
#include <vector>
#include <iostream>
using namespace std;


//	题目五
// 	给定一个数N，想象只由0和1两种字符，组成的所有长度为N的字符串
// 	如果某个字符串,任何0字符的左边都有1紧挨着,认为这个字符串达标
// 	返回有多少达标的字符串


namespace Code03_ZeroLeftOneStringNumber {

	class Solution {
	public:
		int getNum1(int n) {
			if (n < 1) {
				return 0;
			}
			return process1(1, n);
		}
		int process1(int i, int n) {
			if (i == n - 1) {
				return 2;
			}
			if (i == n) {
				return 1;
			}
			return process1(i + 1, n) + process1(i + 2, n);
		}

		int getNum2(int n)
		{
			if (n < 1) {
				return 0;
			}
			return process2(n);
		}
		int process2(int rest) {
			if (rest < 1)
			{	
				return 0;
			}
			if (rest == 1)
			{
				return 1;
			}
			if (rest == 2)
			{
				return 2;
			}
			return process2(rest - 1) + process2(rest - 2);
		}
		//	dp
		int getNum3(int n)
		{
			if (n < 1) {
				return 0;
			}
			if (n == 1)
			{
				return 1;
			}
			if (n == 2)
			{
				return 2;
			}
			int pre_pre = 1;
			int pre = 2;
			int cur = 0;
			for (int i = 2; i < n; i++)
			{
				cur = pre_pre + pre;
				pre_pre = pre;
				pre = cur;
			}
			return cur;
		}

		int getNum4(int n ) {
			if (n < 1) {
				return 0;
			}
			if (n == 1)
			{
				return 1;
			}
			if (n == 2)
			{
				return 2;
			}
			// fn = fn - 1 + fn - 2
			// fn        [1, 1] fn-1    f2 =2
			// fn-1   =  [1, 0] fn-2    f1 =1
		    // 
			vector<vector<int>> base{ {1, 1},{1, 0} };
			vector<vector<int>> res = matrixPow(base, n - 2);

			return res[0][0] * 2 + res[0][1];
		}

		vector<vector<int>> matrixPow(vector<vector<int>> &base, int pow)
		{
			vector<vector<int>> t = base;
			int N = base.size();
			vector<vector<int>> res(N, vector<int>(N, 0));
			for (int i = 0; i < N; i++)
			{
				res[i][i] = 1;
			}
			for (; pow != 0; pow >>= 1)
			{
				if (pow & 1 != 0)
				{
					res = matrixMult(res, t);
				}
				t = matrixMult(t, t);
			}
			return res;
		}

		vector<vector<int>> matrixMult(vector<vector<int>> &A, vector<vector<int>> &B)
		{
			int A_ROW = A.size();
			int A_COL = A[0].size();
			int B_ROW = B.size();
			int B_COL = B[0].size();
			vector<vector<int>> ans(A_ROW, vector<int>(B_COL, 0));
			for (int r = 0; r < A_ROW; r++)
			{
				for (int c = 0; c < B_COL; c++)
				{
					int sum = 0;
					for (int i = 0; i < A_COL; i++)
					{
						sum += A[r][i] * B[i][c];
					}
					ans[r][c] = sum;
				}
			}
			return ans;
		}



	};

}

void test_Code03_ZeroLeftOneStringNumber() {


	Code03_ZeroLeftOneStringNumber::Solution sln;
	int n = 1;
	int nmax = 10;
	while (n <= nmax)
	{
		int ans1 = sln.getNum1(n);
		int ans2 = sln.getNum2(n);
		int ans3 = sln.getNum3(n);
		int ans4 = sln.getNum4(n);
		cout << "====================" << endl;
		cout << n << "," << ans1 << ","<<ans2 <<","<<ans3
			<<","<<ans4<< endl;
		n++;
	}
	
	
}

#endif