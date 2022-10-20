#pragma once
#ifndef Code01_SubsquenceMaxModM_HPP
#define Code01_SubsquenceMaxModM_HPP
#include <vector>
#include <set>
#include "utility_func.hpp"
#include <algorithm>
using namespace std;
// 给定一个非负数组arr，和一个正数m。 返回arr的所有子序列中累加和%m之后的最大值。
namespace Code01_SubsquenceMaxModM {

	void process1(vector<int> &arr, int index, int sum, std::set<long> & set)
	{
		if (index == arr.size())
		{
			set.insert(sum);
			return ;
		}
		// index < arr.size();
		
		// 
		process1(arr, index + 1, sum, set);
		process1(arr, index + 1, sum + arr[index], set);
		return;
	}
	int max1(vector<int>& arr, int mod)
	{
		std::set<long> set;
		process1(arr, 0, 0, set);
		int ans = 0;
		for (auto e : set)
		{
			int tmp = e % mod;
			ans = std::max(ans, tmp);
		}
		return ans;
	}
	// dp 用dp 搞定 arr[0.....N-1] 累加和
	int dpmax1(vector<int>& arr, int mod)
	{
		long sum = 0;
		for (int i = 0; i < arr.size(); i++)
		{
			sum += arr[i];
		}
		int N = arr.size();
		vector<vector<bool>> dp(N, vector<bool>(sum + 1, false));

		for (int i = 0; i < N; i++)
		{
			dp[i][0] = true;
		}
		dp[0][arr[0]] = true;
		for (int i = 1; i < N; i++)
		{
			for (int j = 1; j <= sum; j++)
			{
				dp[i][j] = dp[i - 1][j];
				if (j - arr[i] >= 0)
				{
					dp[i][j] = dp[i][j] || dp[i - 1][j - arr[i]];
				}
			}
		}
		int ans = 0;
		for (int i = 0; i <= sum; i++)
		{
			if (dp[N - 1][i] == true)
			{
				ans = std::max(ans, i%mod);
			}
		}
		return ans;
	}

	// 
	int dpmax2(vector<int>& arr, int mod)
	{
		int N = arr.size();

		vector<vector<bool>> dp(N, vector<bool>(mod, false));

		for (int i = 0; i < N; i++)
		{
			dp[i][0] = true;
		}
		dp[0][arr[0] % mod] = true;
		for (int i = 1; i < N; i++)
		{
			int tmpm = arr[i] % mod;
			for (int m = 1; m < mod; m++)
			{
				dp[i][m] = dp[i - 1][m];
				if (tmpm <=m)
				{
					dp[i][m] = dp[i][m] || dp[i - 1][m - tmpm];
				}
				else // tmpm >m
				{
					dp[i][m] = dp[i][m] || dp[i - 1][mod + m - tmpm];
				}
			}
		}

		for (int i = mod - 1; i >= 0; i++)
		{
			if (dp[N - 1][i] == true)
			{
				return i;
			}
		}
		return 0;
	}
	// 如果arr的累加和很大，m也很大
	// 但是arr的长度相对不大
	void process4(vector<int>& arr, int index, int end, long sum, std::set<long> & set, int mod);
	int max4(vector<int>& arr, int mod)
	{
		int mid = arr.size() / 2;

		std::set<long> set1;
		std::set<long> set2;
		process4(arr, 0, mid, 0, set1, mod);
		process4(arr, mid + 1, arr.size() - 1, 0, set2, mod);

		long ans = 0;
		for (auto e : set1)
		{
			auto set2_i = set2.upper_bound(mod - e - 1);
			if (set2_i != set2.end() && set2_i != set2.begin())
			{
				set2_i--;
				int set2_e = *set2_i;
				ans = std::max(ans,
					e + set2_e
				);
			}
		}
		return ans;
	}

	void process4(vector<int>& arr, int index, int end, long sum, std::set<long> & set, int mod)
	{
		if (index == end + 1)
		{
			if (sum == 0)
			{
				return;
			}
			set.insert(sum%mod);
			return;
		}
		process4(arr, index + 1, end, sum, set, mod);
		process4(arr, index + 1, end, sum + arr[index], set, mod);
	}
}

void test_Code01_SubsquenceMaxModM() {
	
	int len = 10;
	int value = 100;
	int m = 76;
	int testTime = 100;
	cout << "test_Code01_SubsquenceMaxModM begin" << endl;
	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(len, value, 0);
		int ans1 = Code01_SubsquenceMaxModM::max1(arr, m);
		int ans2 = Code01_SubsquenceMaxModM::dpmax1(arr, m);
		int ans3 = Code01_SubsquenceMaxModM::dpmax2(arr, m);
		int ans4 = Code01_SubsquenceMaxModM::max4(arr,m);
		if (ans1 != ans2 || ans2 != ans3 || ans3 != ans4)
		{
			print(arr);
			cout << ans1 << "," << ans2 << "," << ans3 << "," << ans4 << "," << endl;
			break;
		}
	}
	cout << "test_Code01_SubsquenceMaxModM end" << endl;
}


#endif