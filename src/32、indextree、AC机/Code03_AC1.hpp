#pragma once
#ifndef Code03_AC1_HPP
#define Code03_AC1_HPP
#include <vector>
#include <string>
#include <iostream>
#include <queue>
using namespace std;
namespace Code03_AC1 {
	// 
	struct Node {
		int end; // 有多少个字符串以该节点结尾
		Node* fail;
		vector<Node*> nexts;
		Node() {
			fail = nullptr;
			nexts.resize(26, nullptr);
			end = 0;
		}
		~Node() {
			for (int i = 0; i < nexts.size(); i++)
			{
				if (nexts[i] != nullptr)
				{
					delete nexts[i]; 
					nexts[i] = nullptr;
				}
			}
		}
	};

	class ACAutomation {
		Node* root = nullptr;
	public:
		ACAutomation() {
			root = new Node();
		}
		~ACAutomation() {
			if (root != nullptr)
			{
				delete root;
				root = nullptr;
			}
		}
		void insert(string s)
		{
			Node * cur = root;
			for (int i = 0; i < s.size(); i++)
			{
				int index = s[i] - 'a';
				if (cur->nexts[index] == nullptr)
				{
					cur->nexts[index] = new Node();
				}
				cur = cur->nexts[index];
			}
			cur->end++;
		}
		void build() {
		
			std::queue<Node*> q;
			q.push(root);
			while (!q.empty())
			{
				Node* cur = q.front();
				q.pop();
				
				for (int i = 0; i < cur->nexts.size(); i++)
				{
					if (cur->nexts[i] != nullptr)
					{
						Node * cfail = cur->fail;
						cur->nexts[i]->fail = root;
						while (cfail != nullptr)
						{
							if (cfail->nexts[i] != nullptr)
							{
								cur->nexts[i]->fail = cfail->nexts[i];
								break;
							}
							cfail = cfail->fail;
						}
						q.push(cur->nexts[i]);
					}
				}
			}
		}


		int containNum(const string & content) {
			string s = content;
			Node * cur = root;
			Node * jump = nullptr;
			int ans = 0;
			for (int i = 0; i < s.size(); i++)
			{
				int index = s[i] - 'a';
				while (cur->nexts[i] == nullptr && cur != root)
				{
					cur = cur->fail;
				}
				cur = cur->nexts[index] != nullptr ? cur->nexts[index] :
					root;
				jump = cur;
				while (jump != root)
				{
					if (jump->end == -1)
					{
						break;
					}
					{
						ans += jump->end;
						jump->end = -1;
					}
					jump = jump->fail;
				}
			}
			return ans;
		}
	};

}

void test_Code03_AC1() {

	cout << "test Code03_AC1 begin" << endl;
	using ACAutomation = Code03_AC1::ACAutomation;
	ACAutomation * ac = new ACAutomation();
	ac->insert("dhe");
	ac->insert("he");
	ac->insert("c");
	ac->build();
	cout << ac->containNum("cdhe") << endl;;
	cout << "test Code03_AC1 end" << endl;
	delete ac;

}

#endif