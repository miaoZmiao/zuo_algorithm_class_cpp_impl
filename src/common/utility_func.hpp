#pragma once
#ifndef __UTILITY_FUNC_HPP__
#define __UTILITY_FUNC_HPP__
#include <iostream>
#include <vector>
#include <random>
#include "anytype_hash_generate.hpp"
#include <unordered_set>
#include <set>
using namespace std;

// 随机序列生成器
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

// 随机序列生成器
vector<int> generateRandomNoRepeatArray(int maxsize, int maxvalue, int minvalue = 0) {
	if (maxsize > (maxvalue - minvalue + 1))
	{
		maxvalue = maxsize;
		minvalue = 1;
	}
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(minvalue, maxvalue);
	vector<int> result;
	set<int> s;
	for (int i = 0; i < maxsize; i++)
	{
		int gennum = distrib(gen);
		while (s.find(gennum) != s.end())
		{
			gennum = distrib(gen);
		}
		s.insert(gennum);
		result.push_back(gennum);
	}
	return result;
}




void swap(vector<int> & arr, int index1, int index2)
{
	if (index1 == index2)
	{
		return;
	}
	arr[index1] = arr[index1] ^ arr[index2];
	arr[index2] = arr[index1] ^ arr[index2];
	arr[index1] = arr[index1] ^ arr[index2];

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

// 判断两个vector是否相等
bool vector_equal(vector<int> & left, vector<int>& right)
{
	if (left.size() != right.size())
	{
		return false;
	}
	size_t veclen = left.size();

	for (int i = 0; i < veclen; i++)
	{
		if (left[i] != right[i])
		{
			return false;
		}
	}
	return true;
}



vector<vector<int>> generate_symmetric_matrix(
	int N, 
	int minvalue,
	int maxvalue,
	int diag)
{
	vector<vector<int>> ret(N, vector<int>(N, 0));
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(minvalue, maxvalue);
	for (int i = 0; i < N; i++)
	{
		ret[i][i] = diag;
		for (int j = i + 1; j < N; j++) {
		 	ret[i][j] = distrib(gen);
			ret[j][i] = ret[i][j];
		}
	}

	return ret;
}

vector<vector<char>> generate_char_matrix(
	int N,
	char minvalue,
	char maxvalue,
	int diag)
{
	vector<vector<char>> ret(N, vector<char>(N, 0));
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(minvalue, maxvalue);
	for (int i = 0; i < N; i++)
	{
		//ret[i][i] = diag;
		for (int j = 0; j < N; j++) {
			ret[i][j] = distrib(gen);
		}
	}

	return ret;
}


template <class T >
void printMatrix(vector<vector<T>> matrix)
{
	for (auto& vec : matrix)
	{
		print<T>(vec);
	}
}


vector<vector<int>> generate_M_N_matrix(
	int M,
	int N,
	int minvalue,
	int maxvalue
)
{
	vector<vector<int>> ret(M, vector<int>(N, 0));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(minvalue, maxvalue);

	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			ret[i][j] = dist(gen);
		}
	}
	return ret;
}

// 用于图的生成
vector<vector<int>> generate_N_3_matrix(int maxNodenumber, int minweight, int maxweight)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> weightdist(minweight, maxweight);
	std::uniform_int_distribution<> nodedist(0, maxNodenumber-1);
	// 计算边的数量  Cn2
	size_t edges_num = maxNodenumber * (maxNodenumber - 1) / 2;
	vector<vector<int>> ret(edges_num, vector<int>(3, 0));


	auto edge_compare = [](const std::pair<int ,int> & p1, const std::pair<int, int> & p2) {
		if (p1.first == p2.second)
		{
			return p1.second < p2.second;
		}
		return p1.first < p2.second;
	};

	set<std::pair<int, int>, decltype(edge_compare)> exists(edge_compare);



	for (size_t i = 0; i < edges_num; i++)
	{
		ret[i][0] = weightdist(gen);
		int node1;
		int node2;
		while (true)
		{
			node1 = nodedist(gen);
			node2 = nodedist(gen);
			if (exists.find(std::make_pair(node1, node2)) == exists.end())
			{
				exists.insert(std::make_pair(node1, node2));
				break;
			}
		}
		ret[i][1] = node1;
		ret[i][2] = node2;
	}

	return ret;
}

string generatestr(size_t N, char minchar, char maxchar)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(minchar, maxchar);

	string res(N, 0);

	for (int i = 0; i < N; i++)
	{
		res[i] = dist(gen);
	}
	return res;
}









#endif