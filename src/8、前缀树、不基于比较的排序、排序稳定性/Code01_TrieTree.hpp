#pragma once
#include <memory>
#include <vector>
#include <string>
#include "utility_func.hpp"
#include <unordered_map>
using namespace std;
namespace Code01_TrieTree {


	struct Node1 {
		int pass;
		int end;
		std::vector<Node1*> nexts;

		Node1() {
			pass = 0;
			end = 0;
			nexts.resize(26, nullptr);
			//std::memset(nexts, 0, 26 * sizeof(Node1));
		}
		~Node1() {
		
			for (int i = 0; i < 26; i++)
			{
				if (nexts[i] != nullptr)
				{
					delete nexts[i];
					nexts[i] = nullptr;
				}
			}

		}
	};

	class Trie1 {
		Node1  * root = nullptr;
	public:
		Trie1() {
			root = new Node1();
		}
		~Trie1() {
			if (root != nullptr)
			{
				delete root;
				root = nullptr;
			}
		}
		void insert(const std::string & word)
		{
			if (word.size() == 0)
			{
				return;
			}
			Node1 * cur = root;
			cur->pass++;
			int index = 0;
			for (int i = 0; i < word.size(); i++) { // 从左往右遍历字符
				index = word[i] - 'a'; // 由字符，对应成走向哪条路
				if (cur->nexts[index] == nullptr) {
					cur->nexts[index] = new Node1();
				}
				cur = cur->nexts[index];
				cur->pass++;
			}
			cur->end++;
		}

		int search(const std::string & word) {
			if (word.size() == 0)
			{
				return 0;
			}
			Node1 * cur = root;
			int index = 0;
			for (int i = 0; i < word.size(); i++) {
				index = word[i] - 'a';
				if (cur->nexts[index] == nullptr) {
					return 0;
				}
				cur = cur->nexts[index];
			}
			return cur->end;
		}

		void del(const std::string & word) {
			if (search(word) != 0) {
				Node1 * cur = root;
				cur->pass--;
				int index = 0;
				for (int i = 0; i < word.size(); i++) {
					index = word[i] - 'a';
					if (--(cur->nexts[index]->pass) == 0) {
						delete cur->nexts[index];
						cur->nexts[index] = nullptr;
						return;
					}
					cur = cur->nexts[index];
				}
				cur->end--;
			}
		}

		int prefixNumber(const std::string & word) {
			if (word.size() == 0) {
				return 0;
			}
			Node1* cur = root;
			int index = 0;
			for (int i = 0; i < word.size(); i++) {
				index = word[i] - 'a';
				if (cur->nexts[index] == nullptr) {
					return 0;
				}
				cur = cur->nexts[index];
			}
			return cur->pass;
		}
	};

	class Right {

		std::unordered_map<std::string, int> box;

	public:
		Right() {}

		void insert(const std::string & word) {
			if (!box.count(word)) {
				box.insert({ word, 1 });
			}
			else {
				box[word]++;
			}
		}

		void del(const std::string & word) {
			if (box.count(word)) {
				if (box[word] == 1) {
					box.erase(word);
				}
				else {
					box[word]--;
				}
			}
		}

		int search(const std::string & word) {
			if (!box.count(word)) {
				return 0;
			}
			else {
				return box[word];
			}
		}

		int prefixNumber(const std::string & word) {
			int count = 0;
			size_t wordsize = word.size();
			for (auto & cur : box) {
				string curs = cur.first;
				if (curs.substr(0, wordsize) == word) {
					count += cur.second;
				}
			}
			return count;
		}
	};

	vector<string> generateRandomStringArray(int arrLen, int strLen, 
		char minchar, char maxchar) 
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);
		vector<string> ans((size_t)(dist(mt)*arrLen) + 1);
		for (int i = 0; i < ans.size(); i++) {
			int slen = (int)(dist(mt) * strLen) + 1;
			ans[i] = generatestr(slen, minchar, maxchar);
		}
		return ans;
	}



	void test_main() {
	
		int arrLen = 100;
		int strLen = 20;
		int testTimes = 10000;
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);
		for (int i = 0; i < testTimes; i++) {
			vector<string> arr = generateRandomStringArray(arrLen, strLen, 'a', 'z');
			Trie1 trie1;
			//Trie2 trie2 = new Trie2();
			Right right;
			for (int j = 0; j < arr.size(); j++) {
				double decide = dist(mt);
				if (decide < 0.25) {
					trie1.insert(arr[j]);
					
					right.insert(arr[j]);
				}
				else if (decide < 0.5) {
					trie1.del(arr[j]);
				
					right.del(arr[j]);
				}
				else if (decide < 0.75) {
					int ans1 = trie1.search(arr[j]);
				
					int ans3 = right.search(arr[j]);
					if (ans1 != ans3) {
						cout << "Oops!" << endl;
					}
				}
				else {
					int ans1 = trie1.prefixNumber(arr[j]);
					int ans3 = right.prefixNumber(arr[j]);
					if (ans1 != ans3) {
						cout<<"Oops!"<<endl;
					}
				}
			}
		}
	}

}

void test_Code01_TrieTree() {
	
	cout << "test_Code01_TrieTree begin" << endl;
	Code01_TrieTree::test_main();
	cout << "test_Code01_TrieTree end" << endl;
}