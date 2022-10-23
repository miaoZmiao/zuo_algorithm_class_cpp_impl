#pragma once

#include "utility_func.hpp"
#include <queue>
namespace Code04_IPO {
	struct Program {
		int p;
		int c;
		Program(int pi =0, int ci=0) {
			p = pi;
			c = ci;
		}
	};

	struct MinCostComparator {

		bool operator()(const Program& o1, const Program& o2) const {
			return o1.c > o2.c;
		}
	};


	struct MaxProfitComparator {

		bool operator()(const Program& o1, const Program& o2) const {
			return o1.p > o2.p;
		}
	};

	// 最多K个项目
	// W是初始资金
	// Profits[] Capital[] 一定等长
	// 返回最终最大的资金
	int findMaximizedCapital(int K, int W, vector<int> & Profits, vector<int> & Capital) {
		priority_queue<Program, vector<Program>, MinCostComparator> minCostQ;
		priority_queue<Program, vector<Program>, MaxProfitComparator> maxProfitQ;
		for (int i = 0; i < Profits.size(); i++) {
			minCostQ.push(Program(Profits[i], Capital[i]));
		}
		for (int i = 0; i < K; i++) {
			while (!minCostQ.empty() && minCostQ.top().c <= W) {
				maxProfitQ.push(minCostQ.top());
				minCostQ.pop();
			}
			if (maxProfitQ.empty()) {
				return W;
			}
			W += maxProfitQ.top().p;
			maxProfitQ.pop();
		}
		return W;
	}

}

void test_Code04_IPO() {


}