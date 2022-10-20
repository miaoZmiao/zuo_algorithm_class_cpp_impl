#pragma once
#ifndef Code04_AC2_HPP
#define Code04_AC2_HPP
#include <vector>
#include <iostream>
#include <queue>
#include "utility_func.hpp"
using namespace std;
namespace Code04_AC2 {
	
	struct Node {
		string end; 
		int endUse = false;
		Node* fail;
		vector<Node*> nexts;
		Node() {
			fail = nullptr;
			nexts.resize(26, nullptr);
			endUse = false;
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
	public:
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
		void insert(const string & s)
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
			cur->end = s;
		}

		void build(){
			Node * cur = nullptr;
			std::queue<Node *> q;
			q.push(root);
			Node * cfail = nullptr;
			while (!q.empty())
			{
				cur = q.front();
				q.pop();
				for (int i = 0; i < cur->nexts.size(); i++)
				{
					if (cur->nexts[i] != nullptr)
					{
						cur->nexts[i]->fail = root;
						cfail = cur->fail;
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

		vector<string> containWords(const string & content)
		{
			vector<string> ans;
			string s = content;
			Node * cur = root;
			Node * jump = nullptr;
			for (int i = 0; i < s.size(); i++)
			{
				int index = s[i] - 'a';
				while (cur->nexts[index] == nullptr && cur != root)
				{
					cur = cur->fail;
				}
				cur = cur->nexts[index] != nullptr ? cur->nexts[index] : root;
				jump = cur;
				while (jump != root)
				{
					if (jump->endUse == true)
					{
						break;
					}

					{
						if (jump->end.size() > 0)
						{
							ans.push_back(jump->end);
							jump->endUse = true;
						}
					}
					jump = jump->fail;
				}
			}
			return ans;
		}
	};
}


void test_Code04_AC2() {


	cout << "test Code04_AC2 begin" << endl;
	using ACAutomation = Code04_AC2::ACAutomation;

	ACAutomation * ac = new ACAutomation();
	ac->insert("dhe");
	ac->insert("he");
	ac->insert("abcdheks");
	// ÉèÖÃfailÖ¸Õë
	ac->build();
	vector<string> contains = ac->containWords("abcdhekskdjfafhasldkflskdjhwqaeruv");
	print(contains);
	delete ac;
	cout << "test Code04_AC2 end" << endl;
}

#endif