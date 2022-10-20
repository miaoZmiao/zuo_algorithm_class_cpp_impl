#pragma once
#ifndef Code03_ReservoirSampling_HPP
#define Code03_ReservoirSampling_HPP
#include <iostream>
#include <vector>
#include "utility_func.hpp"
using namespace std;

namespace Code03_ReservoirSampling {

	class Solution {
	public:
		class RandomBox
		{
			int box_count_ = 0;
			std::random_device rd_;
			std::mt19937 mt_;
			std::uniform_real_distribution<> dist_;
			vector<int> boxes_;

			int ball_count_ = 0;
		public:
			RandomBox(int count) {
				box_count_ = count;
				boxes_.resize(box_count_, 0);
				mt_.seed(rd_());
				std::uniform_real<> p(0.0, 1.0);
				dist_.param(p.param());
			}
			void add(int num) {
				
				ball_count_++;
				if (ball_count_ <= box_count_)
				{
					boxes_[ball_count_ - 1] = num;
				}
				else {
					// [1, box_count_]
					int loc = random(ball_count_);
					if (loc <= box_count_)
					{
						boxes_[random(box_count_) - 1] = num;
					}	
				}
			}
			vector<int> choices()
			{
				return boxes_;
			}

			int random(int M)
			{
				return dist_(mt_)*M + 1;
			}
		};

	};
}


void test_Code03_ReservoirSampling() {
	using RandomBox = Code03_ReservoirSampling::Solution::RandomBox;
	cout << "test Code03_ReservoirSampling begin" << endl;
	
	int test = 10000;
	int ballNum = 17;
	int boxcount = 10;
	vector<int> count = vector<int>(ballNum+1, 0);

	for (int i = 0; i < test; i++)
	{
		RandomBox rb(boxcount);
		for (int k= 1; k <= ballNum; k++)
		{
			rb.add(k);
		}
		vector<int> choices = rb.choices();
		for (int j = 0; j < choices.size(); j++)
		{
			count[choices[j]]++;
		}
	}
	auto printBoxOutput = [](vector<int> & count) {

		for (int i = 0; i < count.size(); i++)
		{
			cout << "ball[" << i << "]:" << count[i] << endl;
		}
	};
	printBoxOutput(count);

	cout << "test Code03_ReservoirSampling end" << endl;
}

#endif