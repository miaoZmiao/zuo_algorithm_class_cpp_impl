#pragma once
#ifndef Code04_SplitArrayLargestSum_HPP
#define Code04_SplitArrayLargestSum_HPP
#include "utility_func.hpp"
#include "stop_watch.hpp"
namespace Code04_SplitArrayLargestSum {


	class Solution {
	public:
		
		int getsum(vector<int> & sum, int L, int R)
		{
			return sum[R + 1] - sum[L];
		}

		int splitArray1(vector<int> & nums, int K)
		{
			if (K <= 0)
			{
				return INT_MAX;
			}
			int N = nums.size();
			vector<int> sums(N + 1, 0);
			for (int i = 1; i <= N; i++)
			{
				sums[i] = sums[i - 1] + nums[i - 1];
			}
			if (K == 1)
			{
				return getsum(sums, 0, N - 1);
			}
			if (K > N)
			{
				return INT_MAX;
			}
			else if (K == N)
			{
				int ans = nums[0];
				for (int i = 1; i < N; i++)
				{
					ans = std::max(ans, nums[i]);
				}
				return ans;
			}
			// 0 < K < N
			return process1(sums, K, 0, 0);
		}

		// 先写了自己的暴力递归
		int process1(vector<int> & sums, int K, int number_index, int K_index)
		{
			if (number_index == sums.size()-1)
			{
				return 0;
			}
			if (K_index == K-1)
			{
				return getsum(sums, number_index, sums.size() - 2);
			}
			int ans = INT_MAX;
			// 第 K_index  不用来分
			int branch_ans = 0;
			branch_ans = std::max(process1(sums, K, number_index , K_index + 1), branch_ans);
			ans = std::min(ans, branch_ans);
			// 第 K_index 来分活
			for (int i = number_index; i< sums.size()-1;i++)
			{
				int left_sum = getsum(sums, number_index, i);
				int right_relative_max_sum = process1(sums, K, i + 1, K_index + 1);
				int temp_ans = std::max(left_sum, right_relative_max_sum);
				ans = std::min(ans, temp_ans);
			}
			return ans;
		}

		// 课程代码所用的 暴力递归

		int splitArray2(vector<int> & nums, int K)
		{
			int N = nums.size();
			vector<int> sums(N + 1, 0);
			for (int i = 1; i <= N; i++)
			{
				sums[i] = sums[i - 1] + nums[i - 1];
			}
			return process2(sums, N - 1, K);
		}

		// Kth = 0 属于无效值
		// index < 0 属于无效值
		int process2(vector<int> & sums, int index, int Kth)
		{
			if (index < 0 || Kth <= 0)
			{
				return 0;
			}
			if (index == 0 && Kth>=1)
			{
				return getsum(sums, 0, 0);
			}
			if (Kth == 1 && index>0)
			{
				return getsum(sums, 0, index);
			}
			int ans = INT_MAX;
			// 当前不用一个数字
			int current_sum = 0;
			current_sum = std::max(current_sum, process2(sums, index, Kth - 1));
			ans = std::min(ans, current_sum);
			for (int L = index; L >= 0; L--)
			{
				int rightsum = getsum(sums, L, index);
				int leftsum = process2(sums, L - 1, Kth - 1);
				current_sum = std::max(rightsum, leftsum);
				ans = std::min(ans, current_sum);
			}
			return ans;
		}


		int dpways1(vector<int> & nums, int K) {
			int N = nums.size();
			vector<int> sums(N + 1, 0);
			for (int i = 1; i <= N; i++)
			{
				sums[i] = sums[i - 1] + nums[i - 1];
			}
			
			vector<vector<int>> dp(N, vector<int>(K + 1, INT_MAX));
			// 第一行
			for (int i = 1; i <= K; i++)
			{
				dp[0][i] = getsum(sums, 0, 0);
			}
			// 第一列
			for (int i = 1; i < N; i++)
			{
				dp[i][1] = getsum(sums, 0, i);
			}
			
			for (int index = 1; index < N; index++)
			{
				for (int Kth = 2; Kth <= K; Kth++)
				{
					int ans = dp[index][Kth - 1];
					for (int L = index; L >= 1; L--)
					{
						int rightsum = getsum(sums, L, index);
						int leftsum = dp[L - 1][Kth - 1];
						int current_sum = std::max(rightsum, leftsum);
						ans = std::min(ans, current_sum);
					}
					dp[index][Kth] = ans;
				}
			}
			return dp[N - 1][K];
		}

		int dpways2(vector<int> & nums, int K)
		{
			int N = nums.size();
			vector<int> sums(N + 1, 0);
			for (int i = 1; i <= N; i++)
			{
				sums[i] = sums[i - 1] + nums[i - 1];
			}

			vector<vector<int>> dp(N, vector<int>(K + 1, INT_MAX));
			vector<vector<int>> dpbest(N, vector<int>(K + 1, INT_MAX));
			// 第一行
			for (int i = 1; i <= K; i++)
			{
				dp[0][i] = getsum(sums, 0, 0);
				dpbest[0][i] = -1;
			}
			// 第一列
			for (int i = 1; i < N; i++)
			{
				dp[i][1] = getsum(sums, 0, i);
				dpbest[i][1] = -1;
			}
			
			for (int Kth = 2; Kth <= K; Kth++)
			{
				for (int index = N - 1; index >= 1; index--)
				{
					int down = dpbest[index][Kth - 1];
					int up = index == N - 1 ? N - 1 : dpbest[index + 1][Kth];
					int ans = INT_MAX;
					int choose = -1;
					for (int LeftEnd = down; LeftEnd <= up; LeftEnd++)
					{
						int leftsum = LeftEnd == -1 ? 0 : dp[LeftEnd][Kth - 1];
						int rightsum = (LeftEnd == index ? 0 : getsum(sums, LeftEnd + 1, index));
						int cur = std::max(leftsum, rightsum);
						if (ans > cur)
						{
							ans = cur;
							choose = LeftEnd;
						}
					}
					dp[index][Kth] = ans;
					dpbest[index][Kth] = choose;
				}
			}
			return dp[N - 1][K];
		}
		
		// 方法 5 
		//  二分
		int splitArray5(vector<int> & nums, int K)
		{
			long sum = 0;
			for (int i = 0; i < nums.size(); i++)
			{
				sum += nums[i];
			}
			long L = 0;
			long R = sum;
			int ans = INT_MAX;
			while (L <= R)
			{
				long mid = L + ((R - L) >> 1);
				int split = getsplitNum(nums, mid);
				if (split <= K)
				{
					ans = mid;
					R = mid - 1;
				}
				else if (split > K)
				{
					L = mid + 1;
				}

			}
			return ans;
		}

		int getsplitNum(vector<int> & nums, long aim)
		{
			for (int i = 0; i < nums.size(); i++)
			{
				if (nums[i] > aim)
				{
					return INT_MAX;
				}
			}
			int batch = 1;
			long cur = nums[0];
			for (int i = 1; i < nums.size(); i++)
			{
				if (cur + nums[i] > aim)
				{
					batch++;
					cur = nums[i];
				}
				else {
					cur += nums[i];
				}
			}
			return batch;
		}


	};
}

void test_Code04_SplitArrayLargestSum() {
	
	int len = 15;
	int maxvalue = 50;
	int minvalue = 1;
	int testTime = 100;
	int K = 2;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);
	Code04_SplitArrayLargestSum::Solution sln;
	cout << "test_Code04_SplitArrayLargestSum begin" << endl;
	stop_watch st;
	double elapse1 = 0.0;
	double elapse2 = 0.0;
	double elapse3 = 0.0;
	double elapse4 = 0.0;
	double elapse5 = 0.0;
	for (int i = 0; i < testTime; i++)
	{
		vector<int> arr = generateRandomArray(len, maxvalue, minvalue);
		// vector<int> arr{ 7,2,5,10,8 };
		K = (int(dist(mt)*len) + 1);
		st.start();
		int ans1 = sln.splitArray1(arr, K);
		st.stop();
		elapse1 += st.elapsed_ms();
		st.start();
		int ans2 = sln.splitArray2(arr, K);
		st.stop();
		elapse2 += st.elapsed_ms();
		st.start();
		int ans3 = sln.dpways1(arr, K);
		st.stop();
		elapse3 += st.elapsed_ms();
		st.start();
		int ans4 = sln.dpways2(arr, K);
		st.stop();
		elapse4 += st.elapsed_ms();
		st.start();
		int ans5 = sln.splitArray5(arr, K);
		st.stop();
		elapse5 += st.elapsed_ms();
		if (ans1 != ans2 || ans1 != ans3 || ans4 != ans1 || ans5 != ans1)
		{
			print(arr);
			cout << "K:" << K << endl;
			cout << ans1 <<","<<ans2<< ","<<ans3<<","<<ans4<<","<<ans5<<endl;
			break;
		}
	}


	cout << "average elapse(ms)" << endl;
	cout << "force1:\t\t" << elapse1 / testTime << endl;
	cout << "force2:\t\t" << elapse2 / testTime << endl;
	cout << "dp1:\t\t" << elapse3 / testTime << endl;
	cout << "dp2:\t\t" << elapse4 / testTime << endl;
	cout << "split5:\t\t" << elapse5 / testTime << endl;
	cout << "test_Code04_SplitArrayLargestSum end" << endl;
	/*
		test_Code04_SplitArrayLargestSum begin
		test_Code04_SplitArrayLargestSum begin
		test_Code04_SplitArrayLargestSum end
		average elapse(ms)
		force1:         134.813
		force2:         174.124
		dp1:            0.02449
		dp2:            0.01654
		split5:         0.00311
	*/
}


#endif