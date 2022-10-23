#pragma once
#include "utility_func.hpp"
#include <string>
#include <set>
namespace Code05_LowestLexicography {


	class LowestLexicography {

	public:
		string loweststring1(vector<string> & strs) {
			if (strs.size() == 0) {
				return "";
			}
			set<string> ans = process(strs);
			return ans.size() == 0 ? "" : *ans.begin();
		}

		// strs中所有字符串全排列，返回所有可能的结果
		set<string> process(vector<string> & strs) {
			set<string> ans;
			if (strs.size() == 0) {
				ans.insert("");
				return ans;
			}
			for (int i = 0; i < strs.size(); i++) {
				string first = strs[i];
				vector<string>  nexts = removeIndexstring(strs, i);
				set<string> next = process(nexts);
				for (string cur : next) {
					ans.insert(first + cur);
				}
			}
			return ans;
		}

		// {"abc", "cks", "bct"}
		// 0 1 2
		// removeIndexstring(arr , 1) -> {"abc", "bct"}
		vector<string>  removeIndexstring(vector<string> & arr, int index) {
			int N = arr.size();
			vector<string> ans (N-1);
			int ansIndex = 0;
			for (int i = 0; i < N; i++) {
				if (i != index) {
					ans[ansIndex++] = arr[i];
				}
			}
			return ans;
		}


		struct MyComparator  {

			bool operator()(const string & a, const string & b) const {
				return (a + b)<(b + a);
			}
		};

		string loweststring2(vector<string> & strs) {
			if (strs.size() == 0) {
				return "";
			}
			std::sort(strs.begin(),strs.end(), MyComparator());
			string res = "";
			for (int i = 0; i < strs.size(); i++) {
				res += strs[i];
			}
			return res;
		}
	};

	vector<string> generateRandomStringArray(int arrLen, int strLen) {
		
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);
		vector<string> ans((int)(dist(mt) * arrLen) + 1);
		for (int i = 0; i < ans.size(); i++) {
			ans[i] = generatestr(strLen, 'a', 'z');
		}
		return ans;
	}

	void test_main() {
		int arrLen = 6;
		int strLen = 5;
		int testTimes = 1000;
		LowestLexicography llg;
		for (int i = 0; i < testTimes; i++) {
			vector<string> arr1 = generateRandomStringArray(arrLen, strLen);
			vector<string> arr2 = arr1;
			if (llg.loweststring1(arr1) != (llg.loweststring2(arr2))) {
				for (auto & str : arr1) {
					cout<<str + ",";
				}
				cout<<endl;
				cout << "Oops!" << endl;
				break;
			}
		}
	}
}

void test_Code05_LowestLexicography() {

	cout << "test_Code05_LowestLexicography begin" << endl;
	Code05_LowestLexicography::test_main();
	cout << "test_Code05_LowestLexicography end" << endl;
}
