#pragma once
#include <vector>
#include <string>
#include "utility_func.hpp"
#include <unordered_set>
#include <algorithm>
namespace Code01_Light {

	class Light {
	public:
		int minLight1(string road) {
			if (road.size() == 0) {
				return 0;
			}
			set<int> lights;
			return process(road, 0, lights);
		}

		// str[index....]位置，自由选择放灯还是不放灯
		// str[0..index-1]位置呢？已经做完决定了，那些放了灯的位置，存在lights里
		// 要求选出能照亮所有.的方案，并且在这些有效的方案中，返回最少需要几个灯
		int process(const string & str, int index, set<int> & lights) {
			if (index == str.size()) { // 结束的时候
				for (int i = 0; i < str.size(); i++) {
					if (str[i] != 'X') { // 当前位置是点的话
						if (!lights.count(i - 1) && !lights.count(i) && !lights.count(i + 1)) {
							return INT_MAX;
						}
					}
				}
				return lights.size();
			}
			else { // str还没结束
			 // i X .
				int no = process(str, index + 1, lights);
				int yes = INT_MAX;
				if (str[index] == '.') {
					lights.insert(index);
					yes = process(str, index + 1, lights);
					lights.erase(index);
				}
				return std::min(no, yes);
			}
		}

		int minLight2(string road) {
			string  str = road;
			int i = 0;
			int light = 0;
			while (i < str.size()) {
				if (str[i] == 'X') {
					i++;
				}
				else {
					light++;
					if (i + 1 == str.size()) {
						break;
					}
					else { // 有i位置  i+ 1   X  .
						if (str[i + 1] == 'X') {
							i = i + 2;
						}
						else {
							i = i + 3;
						}
					}
				}
			}
			return light;
		}
	};


	// for test
	string randomstring(int len) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<>  dist(0.0, 1.0);

		string res((int)(dist(mt) * len) + 1, '\0');
		for (int i = 0; i < res.size(); i++) {
			res[i] = dist(mt) < 0.5 ? 'X' : '.';
		}
		return res;
	}

	void test_main() {
		int len = 20;
		int testTime = 1000;
		Light lt;
		for (int i = 0; i < testTime; i++) {
			string test = randomstring(len);
			int ans1 = lt.minLight1(test);
			int ans2 = lt.minLight2(test);
			if (ans1 != ans2) {
				cout << "oops!" << endl;
				break;
			}
		}
	
	}

}

void test_Code01_Light() {
	
	cout << "test_Code01_Light begin" << endl;
	Code01_Light::test_main();
	cout << "test_Code01_Light end" << endl;

}