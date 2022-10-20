#pragma once
#ifndef Code02_CardsInLine_HPP
#define Code02_CardsInLine_HPP
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
namespace Code02_CardsInLine {

	int f1(vector<int> &arr, int left, int right);
	int g1(vector<int> & arr, int left, int right);

	// 根据规则，返回获胜者的分数
	int win1(vector<int> &arr)
	{
		int f = f1(arr, 0, arr.size()- 1);
		int g = g1(arr, 0, arr.size() - 1);
		return std::max(f,g);
	}

	int f1(vector<int> &arr, int left, int right) {
		if (left == right)
		{
			return arr[left];
		}
		// choose left 
		int p1 = arr[left] + g1(arr, left+1, right);
		// choose left 
		int p2 = arr[right] + g1(arr, left, right - 1);
		return std::max(p1, p2);
	}

	int g1(vector<int> & arr, int left, int right)
	{
		if (left == right)
		{
			return 0;
		}
		// choose left 
		int p1 =  f1(arr, left + 1, right);
		// choose left 
		int p2 =  f1(arr, left, right - 1); 

		return std::min(p1, p2);
	}

	//  傻缓存 做法  
	int f2(vector<int> &arr, int left, int right, 
		vector<vector<int>> & fdp, vector<vector<int>> & gdp);
	int g2(vector<int> & arr, int left, int right,
		vector<vector<int>> & fdp, vector<vector<int>> & gdp);
	int win2(vector<int> & arr)
	{
		size_t  N = arr.size();
		vector<vector<int>> fdp(N, vector<int>(N, -1));
		vector<vector<int>> gdp(N, vector<int>(N, -1));
		int firsthand = f2(arr, 0, N-1, fdp, gdp);
		int secondhand = g2(arr, 0, N - 1, fdp, gdp);
		return std::max(firsthand, secondhand);
	}
	int f2(vector<int> &arr, int left, int right,
		vector<vector<int>> & fdp, vector<vector<int>> & gdp) {
		if (left == right)
		{
			fdp[left][left] = arr[left];
			return arr[left];
		}
		if (fdp[left][right] != -1)
		{
			return fdp[left][right];
		}

		int p1 = arr[left] + g2(arr, left + 1, right, fdp,gdp);
		// choose left 
		int p2 = arr[right] + g2(arr, left, right - 1, fdp, gdp);
		fdp[left][right] = std::max(p1, p2);

		return fdp[left][right];
	}

	int g2(vector<int> & arr, int left, int right,
		vector<vector<int>> & fdp, vector<vector<int>> & gdp) {
		if (left == right)
		{
			gdp[left][left] = 0;
			return 0;
		}
		if (gdp[left][right] != -1)
		{
			return gdp[left][right];
		}
		// choose left 
		int p1 = f2(arr, left + 1, right, fdp, gdp);
		// choose left 
		int p2 = f2(arr, left, right - 1, fdp, gdp);

		gdp[left][right] = std::min(p1, p2);
		return gdp[left][right];
	}

	// 完全动态规划
	int win3(vector<int> & arr)
	{
		size_t  N = arr.size();
		vector<vector<int>> fdp(N, vector<int>(N, 0));
		vector<vector<int>> gdp(N, vector<int>(N, 0));

		for (size_t i = 0; i < N; i++)
		{
			fdp[i][i] = arr[i];
		}

		for (int col = 1; col < N; col++)
		{
			int L = 0;
			int R = col;
			while (L < N && R < N)
			{
				// choose left 
				int first1 = arr[L] + gdp[L + 1][R];
				// choose left 
				int first2 = arr[R] + gdp[L][R - 1];
				fdp[L][R] = std::max(first1, first1);
				// choose left 
				int second1 = fdp[L + 1][R];
				// choose left 
				int second2 = fdp[L][R - 1];
				gdp[L][R]=std::min(second1, second2);
				L++;
				R++;
			}
		}
		
		return std::max(fdp[0][N-1], gdp[0][N-1]);

	}



}

void test_Code02_CardsInLine()
{
	cout << "test Code02_CardsInLine" << endl;
	vector<int> arr{ 5, 7, 4, 5, 8, 1, 6, 0, 3, 4, 6, 1, 7 };
	cout << "win1:" << Code02_CardsInLine::win1(arr) << endl;
	cout << "win2:" << Code02_CardsInLine::win2(arr) << endl;
	cout << "win3:" << Code02_CardsInLine::win2(arr) << endl;
}


#endif