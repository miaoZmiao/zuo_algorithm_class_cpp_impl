#pragma once
#ifndef Code03_PavingTile_HPP
#define Code03_PavingTile_HPP
#include "utility_func.hpp"
#include <algorithm>
namespace Code03_PavingTile {


	class Solution {
	public:
		/*
		* 2*M铺地的问题非常简单，这个是解决N*M铺地的问题
		*/
		int ways1(int N, int M) {
			if (N < 1 || M < 1 || ((N * M) & 1) != 0) {
				return 0;
			}
			if (N == 1 || M == 1) {
				return 1;
			}
			vector<int> pre(M, 1); // pre代表-1行的状况
			return process(pre, 0, N);
		}

		int process(vector<int> & pre, int level, int N)
		{
			if (level == N)
			{
				for (int i = 0; i < pre.size(); i++)
				{
					if (pre[i] == 0)
					{
						return 0;
					}
				}
				return 1;
			}
			vector<int> nextOp = getOp(pre);
			return dfs(nextOp, 0, level, N);
		}


		vector<int> getOp(vector<int>& pre)
		{
			vector<int> s = pre;
			for (int i = 0; i < s.size(); i++)
			{
				s[i] = s[i] ^ 1;
			}
			return s;
		}


		int dfs(vector<int>& op, int col, int level, int N)
		{
			if (col == op.size())
			{
				return process(op, level + 1, N);
			}
			int ans = 0;
			// 不摆砖头
			ans += dfs(op, col + 1, level, N);
			// 摆横砖头
			if (col + 1 <= op.size() - 1 && op[col] == 0 && op[col + 1] == 0)
			{
				op[col] = 1;
				op[col + 1] = 1;
				ans += dfs(op, col + 2, level, N);
				op[col] = 0;
				op[col + 1] = 0;
			}
			return ans;
		}

		int ways2(int N, int M) {
			if (N < 1 || M < 1 || ((N * M) & 1) != 0) {
				return 0;
			}
			if (N == 1 || M == 1) {
				return 1;
			}

			int max_num = std::max(N, M);
			int min_num = std::min(N, M);

			int op = (1 << min_num) - 1;
			return process2(op, 0, max_num, min_num);
		}

		int process2(int pre, int level, int N, int M)
		{
			if (level == N)
			{
				if (pre == ((1 << M) - 1))
				{
					return 1;
				}
				return 0;
			}
			int nextOp = (~pre) & ((1 << M) - 1);

			return dfs2(nextOp, 0, level, N, M);
		}


		int dfs2(int pre, int col, int level, int N, int M)
		{
			if (col == M)
			{
				return process2(pre, level + 1, N, M);
			}
			int ans = 0;
			ans += dfs2(pre, col + 1, level, N, M);
			if (col + 1 <= M - 1 && ((1 << col)&pre) == 0 && ((1 << (col + 1))&pre) == 0)
			{
				int nextop = pre | (3 << col);
				ans += dfs2(nextop, col + 2, level, N, M);
			}
			return ans;
		}

		// 记忆化搜索
		int ways3(int N, int M) {
			if (N < 1 || M < 1 || ((N * M) & 1) != 0) {
				return 0;
			}
			if (N == 1 || M == 1) {
				return 1;
			}

			int max_num = std::max(N, M);
			int min_num = std::min(N, M);

			int op = (1 << min_num) - 1;
			vector<vector<int>> dp((1 << min_num), vector<int>(max_num+1, -1));

			return process3(op, 0, max_num, min_num, dp);
		}

		int process3(int pre, int level, int N, int M, vector<vector<int>> & dp)
		{
			if (dp[pre][level] != -1)
			{
				return dp[pre][level];
			}
			if (level == N)
			{
				if (pre == ((1 << M) - 1))
				{
					dp[pre][level] = 1;
					return dp[pre][level];
				}
				dp[pre][level] = 0;
				return dp[pre][level];
			}

			int nextOp = (~pre) & ((1 << M) - 1);

			int ans = dfs3(nextOp, 0, level, N, M, dp);
			dp[pre][level] = ans;
			return dp[pre][level];
		}

		int dfs3(int op, int col, int level, int N, int M, 
			vector<vector<int>> & dp) 
		{
			if (col == M)
			{
				return process3(op, level + 1, N, M, dp);
			}
			int ans = 0;
			ans += dfs3(op, col + 1, level, N, M, dp);
			if (col + 1 <= M - 1 && ((1 << col)&op) == 0 && ((1 << (col + 1))&op) == 0)
			{
				int nextop = op | (3 << col);
				ans += dfs3(nextop, col + 2, level, N, M, dp);
			}
			return ans;
		}
		
		// 严格位置依赖动态规划
		int ways4(int N, int M) {
			if (N < 1 || M < 1 || ((N * M) & 1) != 0) {
				return 0;
			}
			if (N == 1 || M == 1) {
				return 1;
			}
			int max_num = std::max(N, M);
			int min_num = std::min(N, M);
			// 
			int op = (1 << min_num) - 1;
			vector<vector<int>> dp((1 << min_num), vector<int>(max_num + 1, 0));
			dp[op][max_num] = 1;


			for (int level = max_num - 1; level >= 0; level--)
			{
				for (int status = 0; status <= op; status++)
				{
					int nextOp = (~status) & ((1 << min_num) - 1);

					dp[status][level] = dfs4(nextOp, 0, level, max_num, min_num, dp);
				}
			}
			return dp[op][0];
		}

		int dfs4(int pre, int col, int level, int N, int M, 
			vector<vector<int>> & dp)
		{
			if (col == M)
			{
				return dp[pre][level + 1];
			}
			int ans = 0;
			ans += dfs4(pre, col + 1, level, N, M, dp);
			if (col + 1 <= M - 1 && ((1 << col)&pre) == 0 && ((1 << (col + 1))&pre) == 0)
			{
				int nextop = pre | (3 << col);
				ans += dfs4(nextop, col + 2, level, N, M, dp);
			}
			return ans;
		}
		

		// 严格位置依赖动态规划 +状态压缩
		int ways5(int N, int M) {
			if (N < 1 || M < 1 || ((N * M) & 1) != 0) {
				return 0;
			}
			if (N == 1 || M == 1) {
				return 1;
			}
			int max_num = std::max(N, M);
			int min_num = std::min(N, M);
			// 
			int op = (1 << min_num) - 1;
			vector<int> dp(1 << min_num, 0);
			dp[op] = 1;
			vector<int> tmpdp = dp;
			for (int level = max_num - 1; level >= 0; level--)
			{
				for (int status = 0; status <= op; status++)
				{
					int nextOp = (~status) & ((1 << min_num) - 1);

					tmpdp[status] = dfs5(nextOp, 0, level, max_num, min_num, dp);
				}
				dp = tmpdp;
			}
			return dp[op];
		}

		int dfs5(int pre, int col, int level, int N, int M,
			vector<int> & dp)
		{
			if (col == M)
			{
				return dp[pre];
			}
			int ans = 0;
			ans += dfs5(pre, col + 1, level, N, M, dp);
			if (col + 1 <= M - 1 && ((1 << col)&pre) == 0 && ((1 << (col + 1))&pre) == 0)
			{
				int nextop = pre | (3 << col);
				ans += dfs5(nextop, col + 2, level, N, M, dp);
			}
			return ans;
		}
	};
}


void test_Code03_PavingTile() {
	int N = 8;
	int M = 6;
	Code03_PavingTile::Solution sln;
	cout << "test_Code03_PavingTile begin" << endl;
	int ans1 = sln.ways1(M, N);
	int ans2 = sln.ways2(M, N);
	int ans3 = sln.ways3(M, N);
	int ans4 = sln.ways4(M, N);
	int ans5 = sln.ways5(M, N);
	cout << ans1 << "," << ans2 <<","<<ans3<<","<<ans4<<","<<ans5<<endl;
	cout << "test_Code03_PavingTile end" << endl;

}


#endif