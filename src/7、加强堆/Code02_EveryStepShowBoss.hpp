#pragma once
#include "utility_func.hpp"

#include "HeapGreater.hpp"
using namespace std;
struct  Customer {
	int id;
	int buy;
	int enterTime;

	Customer(int v=0, int b=0, int o=0) {
		id = v;
		buy = b;
		enterTime = 0;
	}
};

struct CandidateComparator {

	bool  operator()(const Customer& o1, const Customer& o2) {
		if (o1.buy != o2.buy)
		{
			return o1.buy > o2.buy;
		}
		return o1.enterTime < o2.enterTime;

	}
};

struct DaddyComparator {

	bool  operator()(const Customer& o1, const Customer& o2) const {

		if (o1.buy != o2.buy)
		{
			return o1.buy < o2.buy;
		}
		return o1.enterTime < o2.enterTime;

	}
};



template <>
struct std::hash<Customer> {
	std::size_t operator()(const Customer & A) const noexcept
	{
		return A.id;
	}
};
namespace Code02_EveryStepShowBoss {

	class WhosYourDaddy {
		unordered_map<int, Customer> customers;
		HeapGreater<Customer, CandidateComparator> candHeap;
		HeapGreater<Customer, DaddyComparator> daddyHeap;
		int daddyLimit;
	public:
		WhosYourDaddy(int limit) {
			daddyLimit = limit;
		}

		void operate(int time, int id, bool buyOrRefund) {
			if (!buyOrRefund && !customers.count(id)) {
				return;
			}
			if (!customers.count(id)) {
				customers.insert({ id,  Customer(id, 0, 0) });
			}
			Customer  c = customers[id];
			if (buyOrRefund) {
				c.buy++;
			}
			else {
				c.buy--;
			}
			customers[id] = c;
			if (c.buy == 0) {
				customers.erase(id);
			}
			if (!candHeap.contains(c) && !daddyHeap.contains(c)) {
				if (daddyHeap.size() < daddyLimit) {
					c.enterTime = time;
					customers[id] = c;
					daddyHeap.push(c);
				}
				else {
					c.enterTime = time;
					customers[id] = c;
					candHeap.push(c);
				}
			}
			else if (candHeap.contains(c)) {
				if (c.buy == 0) {
					candHeap.remove(c);
				}
				else {
					candHeap.resign(c, [&c](Customer & target) {
						target.buy = c.buy;
					});
				}
			}
			else {
				if (c.buy == 0) {
					daddyHeap.remove(c);
				}
				else {
					daddyHeap.resign(c, [&c](Customer & target) {
						target.buy = c.buy;
					});
				}
			}
			daddyMove(time);
		}

		vector<int> getDaddies() {
			vector<Customer> cli = daddyHeap.getAllElements();
			vector<int> ans;
			for (auto& c : cli) {
				ans.push_back(c.id);
			}
			return ans;
		}


	private:

		void daddyMove(int time) {
			if (candHeap.isEmpty()) {
				return;
			}
			if (daddyHeap.size() < daddyLimit) {
				Customer p = candHeap.pop();
				p.enterTime = time;
				daddyHeap.push(p);
			}
			else {
				if (candHeap.peek().buy > daddyHeap.peek().buy) {
					Customer oldDaddy = daddyHeap.pop();
					Customer newDaddy = candHeap.pop();
					oldDaddy.enterTime = time;
					newDaddy.enterTime = time;
					daddyHeap.push(newDaddy);
					candHeap.push(oldDaddy);
				}
			}
		}
	};

	vector<vector<int>> topK(const vector<int> & arr, const vector<bool>& op, int k) {
		vector<vector<int>> ans;
		WhosYourDaddy whoDaddies(k);
		for (int i = 0; i < arr.size(); i++) {
			whoDaddies.operate(i, arr[i], op[i]);
			ans.push_back(whoDaddies.getDaddies());
		}
		return ans;
	}


	vector<int> getCurAns(vector<Customer>& daddy) {
		vector<int> ans ;
		for (auto &c : daddy) {
			ans.push_back(c.id);
		}
		return ans;
	}
	void cleanZeroBuy(vector<Customer>& arr, unordered_set<int> & id_set) {
		vector<Customer> noZero ;
		for (auto & c : arr) {
			if (c.buy != 0) {
				noZero.push_back(c);
			}
			else
			{
				id_set.erase(c.id);
			}
		}
		arr.clear();
		for (auto & c : noZero) {
			arr.push_back(c);
		}
	}

	void move(vector<Customer>& cands, vector<Customer>& daddy, 
		unordered_set<int> & candsmap, unordered_set<int> & daddymap,
		int k, int time) {
		if (cands.empty()) {
			return;
		}
		// 候选区不为空
		if (daddy.size() < k) {
			Customer c = cands[0];
			auto iter = cands.begin();
			c.enterTime = time;
			daddy.push_back(c);
			daddymap.insert(c.id);
			cands.erase(iter);
			candsmap.erase(c.id);
		}
		else { // 等奖区满了，候选区有东西
			if (cands[0].buy > daddy[0].buy) {
				Customer oldDaddy = daddy[0];
				auto iterdaddy = daddy.begin();
				daddy.erase(iterdaddy);
				daddymap.erase(oldDaddy.id);
				Customer newDaddy = cands[0];
				auto itercands = cands.begin();
				cands.erase(itercands);
				candsmap.erase(newDaddy.id);
				newDaddy.enterTime = time;
				oldDaddy.enterTime = time;
				daddy.push_back(newDaddy);
				daddymap.insert(newDaddy.id);
				cands.push_back(oldDaddy);
				candsmap.insert(oldDaddy.id);
			}
		}
	}
	vector<vector<int>> compare(const vector<int> & arr, const vector<bool> &op, int k) {
		unordered_map<int, Customer> map;
		vector<Customer> cands ;
		unordered_set<int> candsmap;
		vector<Customer> daddy ;
		unordered_set<int> daddymap;
		vector<vector<int>> ans; 
		for (int i = 0; i < arr.size(); i++) {
			int id = arr[i];
			bool buyOrRefund = op[i];
			if (!buyOrRefund && !map.count(id)) {
				ans.push_back(getCurAns(daddy));
				continue;
			}
			// 没有发生：用户购买数为0并且又退货了
			// 用户之前购买数是0，此时买货事件
			// 用户之前购买数>0， 此时买货
			// 用户之前购买数>0, 此时退货
			if (!map.count(id)) {
				map.insert({ id , Customer(id, 0, 0) });
			}
			// 买、卖
			Customer c = map[id];
			if (buyOrRefund) {
				c.buy++;
			}
			else {
				c.buy--;
			}
			map[id] = c;
			if (c.buy == 0) {
				map.erase(id);
			}
			// c
			// 下面做
			if (!candsmap.count(c.id) && !daddymap.count(c.id)) {
				if (daddy.size() < k) {
					c.enterTime = i;
					map[id] = c;
					daddy.push_back(c);
					daddymap.insert(c.id);
				}
				else {
					c.enterTime = i;
					map[id] = c;
					cands.push_back(c);
					candsmap.insert(c.id);
				}
			}
			else if (candsmap.count(c.id)) {
				/*if (c.buy == 0) {
					cands.erase(std::remove_if(cands.begin(), cands.end(), [&c](const Customer & vc) {
						return vc.id == c.id;
					}));
					candsmap.erase(c.id);
				}
				else {*/
				auto iter_find = std::find_if(cands.begin(), cands.end(), [&c](const Customer & vc) {
					return vc.id == c.id;
				});
				if (iter_find != cands.end())
					iter_find->buy = c.buy;
				/*}*/
			}
			else {
				/*if (c.buy == 0) {
					daddy.erase(std::remove_if(daddy.begin(), daddy.end(), [&c](Customer & vc) {
						return vc.id == c.id;
					}));
					daddymap.erase(c.id);
				}
				else {*/
				auto iter_find = std::find_if(daddy.begin(), daddy.end(), [&c](Customer & vc) {
					return vc.id == c.id;
				});
				if (iter_find != daddy.end())
					iter_find->buy = c.buy;
				/*}*/
			}
			cleanZeroBuy(cands, candsmap);
			cleanZeroBuy(daddy, daddymap);
			std::sort(cands.begin(), cands.end(), CandidateComparator());
			std::sort(daddy.begin(), daddy.end(), DaddyComparator());
			move(cands, daddy, candsmap, daddymap, k, i);
			ans.push_back(getCurAns(daddy));
		}
		return ans;
	}
	
	struct Data {
		vector<int> arr;
		vector<bool>  op;

		Data(vector<int>& a, vector<bool>& o) {
			arr = a;
			op = o;
		}

	};

	Data randomData(int maxValue, int maxLen) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);
		int len = (int)(dist(mt) * maxLen) + 1;
		vector<int> arr(len, 0);
		vector<bool>  op(len, false);
		for (int i = 0; i < len; i++) {
			arr[i] = (int)(dist(mt) * maxValue);
			op[i] = dist(mt) < 0.5 ? true : false;
		}
		return  Data(arr, op);
	}

	bool sameAnswer(vector<vector<int> > & ans1, vector<vector<int> > & ans2) {
		if (ans1.size() != ans2.size()) {
			return false;
		}
		for (int i = 0; i < ans1.size(); i++) {
			vector<int> & cur1 = ans1[i];
			vector<int> & cur2 = ans2[i];
			if (cur1.size() != cur2.size()) {
				return false;
			}
			std::sort(cur1.begin(), cur1.end());
			std::sort(cur2.begin(), cur2.end());
			for (int j = 0; j < cur1.size(); j++) {
				if (cur1[j] != cur2[j])
				{
					return false;
				}
			}
		}
		return true;
	}
	void test_main() {
		int maxValue = 10;
		int maxLen = 20;
		int maxK = 6;
		int testTimes = 1000;
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);
		for (int i = 0; i < testTimes; i++) {
			Data testData = randomData(maxValue, maxLen);
			int k = (int)(dist(mt) * maxK) + 1;
			vector<int > arr = testData.arr;
			vector<bool> op = testData.op;
			vector<vector<int> >  ans1 = topK(arr, op, k);
			vector<vector<int> >  ans2 = compare(arr, op, k);
			if (!sameAnswer(ans1, ans2)) {
				cout << "k:" << k << endl;
				cout << "arr:" << endl;
				print(arr);
				cout << "op:" << endl;
				print(op);
				cout << "wrong!!!" << endl;
				break;
			}
		}
	
	}


}

void test_Code02_EveryStepShowBoss() {

	cout << "test_Code02_EveryStepShowBoss b" << endl;
	Code02_EveryStepShowBoss::test_main();
	cout << "test_Code02_EveryStepShowBoss e" << endl;
}