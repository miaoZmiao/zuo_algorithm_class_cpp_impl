#pragma once
#ifndef FRUITS_TAOCAN_HPP
#define FRUITS_TAOCAN_HPP
#include <algorithm>
#include <random>
#include <map>
#include <vector>
#include <chrono>
//题目2：水果套餐问题
//有一个人小明要买水果，正好商家推出了水果套餐。小明要尽量花少的钱，凑足自己要的水果。
//参数从控制台流输入：
//第一行：需要买的水果的重量
//示例 : 3 2    （A水果需要3，B水果需要2）
//	第二行：水果的单价格
//	示例 : 2 5     （A水果单价2，B水果单价5）
//	后面若干行：水果的套餐
//	示例1：3, 1, 6  （表示如果买3个水果A，1个水果B，套餐花6块钱）
//	示例2：1, 2, 10  (表示如果买1个水果A，2个水果B，套餐花10元)
//	输出：
//	如果要满足小明的需求，最少花多少钱
//	输入输出示例：
//	输入：
//	3 2
//	2 5
//	3 1 6
//	1 2 10
//	输出：
//	11
//	限制：
//	1、不准买多了，小明要多少水果，只能凑多少水果
//	2、水果种类不超过10，套餐种类不超过10（记不清了，反正套餐种类和水果种类都不大）
//	3、水果价格不超过1000 （这个我也记不清了，描述信息反正没有大于1000的数字）
//	4、都是正数


using namespace  std;

//  计时器
class stop_watch
{
public:
	stop_watch() {}

	void start()
	{
		if (!running)
		{
			begin_time_ = std::chrono::steady_clock::now();
			running = true;
		}
	}

	void stop()
	{
		if (running)
		{
			end_time_ = std::chrono::steady_clock::now();
			elapsed_ = end_time_ - begin_time_;
			running = false;
		}
	}

	void restart()
	{
		elapsed_ = std::chrono::steady_clock::duration::zero();
		begin_time_ = std::chrono::steady_clock::now();
		running = true;
	}

	//秒
	double elapsed_second()
	{
		return ((double)std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_).count() / 1e3);
	}
	//毫秒
	double elapsed_ms()
	{
		return ((double)std::chrono::duration_cast<std::chrono::microseconds>(elapsed_).count() / 1e3);
	}

protected:
	std::chrono::steady_clock::duration elapsed_ = std::chrono::steady_clock::duration::zero();
	std::chrono::steady_clock::time_point begin_time_;
	std::chrono::steady_clock::time_point end_time_;
	bool running = false;
};



// 产生一个随机数组
vector<int> generateRandomArray(int maxsize, int maxvalue, int minvalue = 0) {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(minvalue, maxvalue);

	vector<int> result;
	for (int i = 0; i < maxsize; i++)
	{
		result.push_back(distrib(gen));
	}
	return result;
}
// 打印数组
template <class T >
void print(vector<T>& arr)
{
	//cout << "print array" << endl;
	cout << "[";
	for (size_t i = 0; i < arr.size(); i++)
	{
		if (i == arr.size() - 1)
		{
			cout << arr[i] << "]" << endl;
		}
		else
		{
			cout << arr[i] << ",";
		}
	}
	//cout << "print array end" << endl;
}

// 打印矩阵
template <class T >
void printMatrix(vector<vector<T>>& matrix)
{
	for (auto& vec : matrix)
	{
		print<T>(vec);
	}
}


namespace FRUITS_TAOCAN
{

	// 遇到小于0 的返回false
	// 都>=0 返回true
	bool check_available(vector<int> & fruit_w)
	{
		int N = fruit_w.size();
		for (int i = 0; i < N; i++)
		{
			if (fruit_w[i] < 0)
			{
				return false;
			}
		}
		return true;
	}

	int compute_remain_fruit_cost(vector<int> & fruit_p, vector<int> & fruit_w)
	{
		int N = fruit_w.size();
		int ans = 0;
		for (int i = 0; i < N; i++)
		{
			ans += fruit_p[i] * fruit_w[i];
		}
		return ans;
	}

	
	// 这里变成了两个可变参数，一个是 int 一个是vector<int>
	// 改DP基本不可能了
	// 比机考那个更弱鸡
	int cost_Force1(vector<int> & fruit_p, //  固定参数，水果价格
		vector<vector<int>> & taocans,	  //  固定参数，水果套餐的信息
		vector<int> & fruit_w,			// 可变参数，水果的当前重量,
										//  保证数组元素都不能小于0
		int taocan_index)				// 可变参数，当前套餐的index
										//  [0, taocans.size()-1]
	{
		//目标都小于0了，就是不可行的解
		if (false == check_available(fruit_w))
		{
			return INT_MAX;
		}
		// 套餐的索引到了最后了
		// 看有多少水果，按价格返回
		if (taocan_index == taocans.size())
		{
			return compute_remain_fruit_cost(fruit_p, fruit_w);
		}

		// 当前不使用任何套餐的cost
		int ans = compute_remain_fruit_cost(fruit_p, fruit_w);
		// 使用了多少个  taocans[taocan_index] 
		int current_use_taocan_cnt = 0;
		int N = fruit_w.size();
		while (true)
		{
			vector<int> next_fruit_w = fruit_w;
			for (int i = 0; i < N; i++)
			{
				next_fruit_w[i] -= (taocans[taocan_index][i] * current_use_taocan_cnt);
			}
			int next = cost_Force1(fruit_p, taocans, next_fruit_w, taocan_index + 1);
			if (next != INT_MAX)
			{
				ans = std::min(ans, next + taocans[taocan_index][N]* current_use_taocan_cnt);
			}
			else // 
			{
				break;
			}
			//  每一轮都把 taocans[taocan_index] 套餐的用量+1
			//  直到出现 不可行解，直接break;
			current_use_taocan_cnt++;
		}
		return ans;
	}

	// 算法群友提供了动态规划的思路
	// 因为不好状态压缩，直接上傻缓存
	// 用一个map缓存各个步骤的结果
	// 因为  target 是一个vector数组,要用有序map做为key
	// 首先定义比较方式
	struct v_compare
	{
		// 按照字典序比较吧
		bool operator()(const vector<int> & left, const vector<int> & right) const
		{
			int N1 = left.size();
			int N2 = right.size();
			if (N1 == 0 && N2 == 0)
			{
				return false;
			}
			if (N1 == 0)
			{
				return true;
			}
			if (N2 == 0)
			{
				return false;
			}
			int N = std::min(N1, N2);
			for (int i = 0; i < N; i++)
			{
				if (left[i] == right[i])
				{
					continue;
				}
				else if (left[i] < right[i])
				{
					return true;
				}
				else if (left[i] > right[i])
				{
					return false;
				}
			}
			if (N1 < N2)
			{
				return true;
			}
			return false;
		}
	};




	int dp_fruit_cost(vector<int> & fruit_p, //  固定参数，水果价格
		vector<vector<int>> & taocans,	  //  固定参数，水果套餐的信息
		vector<int> & fruit_w,			// 可变参数，水果的当前重量,
										//  保证水果重量都不能小于0
		std::map<vector<int>, int, decltype(v_compare())> & dp // 傻缓存
	)
	{
		//目标都小于0了，就是不可行的解
		if (false == check_available(fruit_w))
		{
			return INT_MAX;
		}
		auto iter = dp.find(fruit_w);
		if (iter != dp.end())
		{
			return iter->second;
		}
		// 看有多少水果，按价格返回
		// 当前不使用任何套餐的cost
		int ans = compute_remain_fruit_cost(fruit_p, fruit_w);
	
		int N = fruit_w.size();
		int N_taocan = taocans.size();
		for (int i = 0; i < N_taocan; i++)
		{
			vector<int> next_fruit_w = fruit_w;
			for (int fruit = 0; fruit < N; fruit++)
			{
				next_fruit_w[fruit] -= taocans[i][fruit];
			}
			int next = dp_fruit_cost(fruit_p, taocans, next_fruit_w, dp);
			if (next != INT_MAX)
			{
				ans = std::min(ans, next + taocans[i][N]);
			}
		}
		dp[fruit_w] = ans;
		return ans;
	}


	int  dp_main1(vector<int> & fruit_p, //  固定参数，水果价格
		vector<vector<int>> & taocans,	  //  固定参数，水果套餐的信息
		vector<int> & fruit_w)            // 需要搞定的水果的重量
	{
		std::map<vector<int>, int, decltype(v_compare())> dp;
		return dp_fruit_cost(fruit_p, taocans, fruit_w, dp);
	}




	// 机考时候的方法，已经通过机考的测试，可以用
	// 这里做对数器
	class duishuqi {

	public:
		bool check_zero(vector<int>& fruit_cn)
		{
			int N = fruit_cn.size();
			for (int i = 0; i < N; i++)
			{
				if (fruit_cn[i] == 0)
				{
					return true;
				}
			}
			return false;
		}
		int usetaocancost(vector<int>& fruit_cnt, vector<int> & fruit_price, vector<vector<int>> & taocans)
		{
			{
				// 检查 fruit_cnt 如果是 全0
				// 直接返回0
				if (false == check_available(fruit_cnt))
				{
					return INT_MAX;
				}
				if (true == check_zero(fruit_cnt))
				{
					return compute_remain_fruit_cost(fruit_cnt, fruit_price);
				}
				int ans = INT_MAX;
				int N_taocan = taocans.size();
				int N = fruit_cnt.size();
				ans = compute_remain_fruit_cost(fruit_cnt, fruit_price);
				for (int i = 0; i < N_taocan; i++)
				{
					vector<int> oldcnt = fruit_cnt;
					for (int fruit = 0; fruit < N; fruit++)
					{
						fruit_cnt[fruit] -= taocans[i][fruit];
					}
					int next = usetaocancost(fruit_cnt, fruit_price, taocans);
					if (next != INT_MAX) {
						ans = std::min(ans, next + taocans[i][N]);
					}
					//恢复现场
					fruit_cnt = oldcnt;
				}
				return ans;
			}
		}

		int main_func(vector<int>& fruit_cnt, vector<int> & fruit_price, vector<vector<int>> & taocans)
		{
			if (fruit_cnt.size() != fruit_price.size())
			{
				// 数据就是错的，不处理
				return INT_MAX;
			}
			int N = fruit_cnt.size();
			// 不使用任何套餐的情况下的花费
			int cost_no_taocan = compute_remain_fruit_cost(fruit_cnt, fruit_price);
			int N_taocan = taocans.size();
			if (N_taocan == 0)
			{
				return cost_no_taocan;
			}
			// N_taocan >0
			// check all taocan 
			for (int i = 0; i < N_taocan; i++)
			{
				// 不合法的数据不处理
				if (taocans[i].size() != N + 1)
				{
					return INT_MAX;
				}
			}

			// 使用了套餐的cost
			int cost_use_taocan = usetaocancost(fruit_cnt, fruit_price, taocans);

			return std::min(cost_no_taocan, cost_use_taocan);
		}
	};
}

void test_FRUITS_TAOCAN() {

	int len = 60; // 水果种类 = 数组长度
	int maxw = 20;  // 水果的最大购买量
	int minw = 1;	// 水果的最小购买量 >0
	int maxp = 10;   // 水果的价格 最高
	int minp = 1;	 // 水果的价格 最低 >0
	int maxTaocan = 10; // 套餐的最大数量
	int taocan_max_p = 30;  // 套餐的最大价值
	int taocan_min_p = 10;   // 套餐的最小价值>0
	int testTime = 1000;	
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);
	FRUITS_TAOCAN::duishuqi dui;
	cout << "test begin" << endl;
	stop_watch st;
	double force1_elapse = 0.0;
	double force2_elapse = 0.0;
	double dp1_elapse = 0.0;
	for (int i = 0; i < testTime; i++)
	{
		vector<int> fruit_w = generateRandomArray(len, maxw, minw);
		vector<int> fruit_p = generateRandomArray(len, maxp, minp);
		int taocanNumber = 0;
		vector<vector<int>> taocans;
		while (taocanNumber < maxTaocan)
		{
			if (dist(mt) < 0.6)
			{
				vector<int> tmp_taocan = generateRandomArray(len + 1, taocan_max_p, taocan_min_p);
				taocans.push_back(tmp_taocan);
			}
			taocanNumber++;
		}
		st.start();
		int ans1 = dui.main_func(fruit_w, fruit_p, taocans);
		st.stop();
		force1_elapse += st.elapsed_ms();
		st.start();
		int ans2 = FRUITS_TAOCAN::cost_Force1(fruit_p, taocans, fruit_w, 0);
		st.stop();
		force2_elapse += st.elapsed_ms();
		st.start();
		int ans3 = FRUITS_TAOCAN::dp_main1(fruit_p, taocans, fruit_w);
		st.stop();
		dp1_elapse += st.elapsed_ms();
		if (ans1 != ans2 || ans1 != ans3)
		{
			cout << "fruit w" << endl;
			print(fruit_w);
			cout << "fruit p" << endl;
			print(fruit_p);
			cout << "fruit taocans" << endl;
			printMatrix(taocans);
			cout << ans1 << "," << ans2 <<","<<ans3 <<endl;
			break;
		}
	}
	cout << "test end" << endl;
	cout << "average elapse(ms)" << endl;
	cout << "duishuqi:\t" << force1_elapse / testTime << endl;
	cout << "force1:\t\t" << force2_elapse / testTime << endl;
	cout << "dp:\t\t" << dp1_elapse / testTime << endl;

	// 某次输出
	/*
		test begin
		test end
		average elapse(ms)
		duishuqi:       0.007814
		force1:         0.016993
		dp:             0.007021
	*/
}


#endif