#pragma once
#ifndef Code02_FibonacciProblem_HPP
#define Code02_FibonacciProblem_HPP
#include <vector>
#include <iostream>
using namespace std;
namespace Code02_FibonacciProblem {

	class Solution
	{
	public:
		// 暴力
		int f1(int n) {
			if (n < 1) {
				return 0;
			}
			if (n == 1 || n == 2) {
				return 1;
			}
			return f1(n - 1) + f1(n - 2);
		}
		// dp
		int f2(int n)
		{
			if (n < 1) {
				return 0;
			}
			if (n == 1 || n == 2) {
				return 1;
			}
			/*vector<int> dp(n+1, 0);
			dp[0] = 0;
			dp[1] = 1;
			dp[2] = 2;
			for (int i = 3; i < n; i++)
			{
				dp[i] = dp[i - 2] + dp[i - 1];
			}
			return dp[n];*/
			int dp_pre_pre = 1;
			int dp_pre = 1;
			int cur = 2;
			for (int i = 3; i <= n; i++)
			{
				cur = dp_pre_pre + dp_pre;
				dp_pre_pre = dp_pre;
				dp_pre = cur;
			}
			return cur;
		}

		int f3(int n)
		{
			if (n < 1) {
				return 0;
			}
			if (n == 1 || n == 2) {
				return 1;
			}
			// [ 1 ,1 ]
			// [ 1, 0 ]
			vector<vector<int>>  base{ {1,1},{1,0} };
			vector<vector<int>> res = matrixPow(base, n - 2);

			return res[0][0] + res[1][0];
		}

		vector<vector<int>> matrixPow(vector<vector<int>> &base, int pow) 
		{
		
			auto t = base;
			int N = base.size();
			vector<vector<int>>	ans(N, vector<int>(N, 0));
			// diag 
			for (int i = 0; i < N; i++)
			{
				ans[i][i] = 1;
			}
			for (; pow != 0; pow >>= 1)
			{
				if (pow & 1 != 0)
				{
					ans = matrixMult(ans, t);
				}
				t = matrixMult(t, t);
			}
			return ans;
		}

		vector<vector<int>> matrixMult(vector<vector<int>> &A, vector<vector<int>> &B)
		{
			
			int A_ROW = A.size();
			int A_COL = A[0].size();
			int B_ROW = B.size();
			int B_COL = B[0].size();
			vector<vector<int>> ans(A_ROW, vector<int>(B_COL, 0));
			for (int r = 0; r< A_ROW; r++)
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
		
		// 
		// 一个人可以一次往上迈1个台阶，也可以迈2个台阶
		// 返回这个人迈上N级台阶的方法数
		int s1(int n){
			if(n<1)
			{
				return 0;
			}
			if(n==1||n==2)
			{
				return n;
			}
			return s1(n - 1) + s1(n - 2);
		}
		// dp
		int s2(int n)
		{
			if (n < 1)
			{
				return 0;
			}
			if (n == 1 || n == 2)
			{
				return n;
			}
			int pre_pre = 1;
			int pre = 2;
			int cur = 3;
			for (int i = 3; i <= n; i++)
			{
				cur = pre_pre + pre;
				pre_pre = pre;
				pre = cur;
			}
			return cur;
		}

		int s3(int n)
		{
			if (n < 1)
			{
				return 0;
			}
			if (n == 1 || n == 2)
			{
				return n;
			}
			vector<vector<int>> base{ {1,1},{1,0} };
			vector<vector<int>> res = matrixPow(base, n - 2);
			return res[0][0] * 2 + res[1][0];
		}
		
		// 第一年农场有1只成熟的母牛A，往后的每年：

		// 1）每一只成熟的母牛都会生一只母牛
	
		// 2）每一只新出生的母牛都在出生的第三年成熟

		// 3）每一只母牛永远不会死

		// 返回N年后牛的数量
		int c1(int n)
		{
			if (n < 1)
			{
				return 0;
			}
			if (n == 1 || n == 2 || n == 3)
			{
				return n;
			}
			return c1(n - 1) + c1(n - 3);
		}

		int c2(int n)
		{
			if (n < 1)
			{
				return 0;
			}
			if (n == 1 || n == 2 || n == 3)
			{
				return n;
			}
			int fn_3 = 1;
			int fn_2 = 2;
			int fn_1 = 3;
			int fn = 5;
			for (int i = 4; i <= n; i++)
			{
				fn = fn_1 + fn_3;
				fn_3 = fn_2;
				fn_2 = fn_1;
				fn_1 = fn;
			}
			return fn;
		}

		int c3(int n)
		{
			if (n < 1)
			{
				return 0;
			}
			if (n == 1 || n == 2 || n == 3)
			{
				return n;
			}
			vector<vector<int>> base{ {1,0,1},{1,0,0},{0,1,0} };
			vector<vector<int>> res = matrixPow(base, n - 3);
			return res[0][0] * 3 + 2 * res[0][1] + res[0][2];
		}


	};
}

void test_Code02_FibonacciProblem() {

	Code02_FibonacciProblem::Solution sln;
	int n = 8;
	cout << "f1:" << sln.f1(n) << endl;
	cout << "f2:" << sln.f2(n) << endl;
	cout << "f3:" << sln.f3(n) << endl;

	cout << "s1:" << sln.s1(n) << endl;
	cout << "s2:" << sln.s2(n) << endl;
	cout << "s3:" << sln.s3(n) << endl;


	cout << "c1:" << sln.c1(n) << endl;
	cout << "c2:" << sln.c2(n) << endl;
	cout << "c3:" << sln.c3(n) << endl;

}

#endif