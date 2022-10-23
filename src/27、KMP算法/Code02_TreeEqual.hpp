#pragma once
#ifndef Code02_TreeEqual_HPP
#define Code02_TreeEqual_HPP
#include <vector>
#include <string>
#include "utility_func.hpp"
#include "stop_watch.hpp"
using namespace std;

namespace Code02_TreeEqual {

	struct Node {
		int value;
		Node * left = nullptr;
		Node * right = nullptr;
		Node(int v = 0) {
			value = v;
		}
		~Node() {
			if (left != nullptr)
			{
				delete left;
				left = nullptr;
			}
			if (right != nullptr)
			{
				delete right;
				right = nullptr;
			}
		}
	};

	class Solution {
		std::random_device m_rd;
		std::mt19937 m_rgen;
		std::uniform_real_distribution<double> m_rdist;
		std::uniform_int_distribution<int> m_idist;
	public:
		Solution() {
			
			m_rgen.seed(m_rd());
			std::uniform_real_distribution<double> r1(0.0, 1.0);
			m_rdist.param(r1.param());
		}

		bool containsTree1(Node* big, Node * small)
		{
			if (small == nullptr)
			{
				return true;
			}
			if (big == nullptr)
			{
				return false;
			}
			if (isSameValueStructure(big, small))
			{
				return true;
			}
			return containsTree1(big->left, small) || containsTree1(big->right, small);

		}
		bool isSameValueStructure(Node *head1, Node *head2)
		{
			if (head1 == nullptr && head2 != nullptr)
			{
				return false;
			}
			if (head1 != nullptr && head2 == nullptr)
			{
				return false;
			}
			if (head1 == nullptr && head2 == nullptr)
			{
				return true;
			}
			if (head1->value != head2->value)
			{
				return false;
			}
			return isSameValueStructure(head1->left, head2->left) &&
				isSameValueStructure(head1->right, head2->right);
		}
		
		bool containsTree2(Node * big, Node * small)
		{
			if (small == nullptr)
			{
				return true;
			}
			if (big == nullptr)
			{
				return false;
			}
			vector<string> b = preSerial(big);
			vector<string> s = preSerial(small);
			string source;
			string match;
			for (int i = 0; i < b.size(); i++)
			{
				source += b[i];
				if (i != b.size() - 1)
				{
					source += "|";
				}
			}
			for (int i = 0; i < s.size(); i++)
			{
				match += s[i];
				if (i != s.size() - 1)
				{
					match += "|";
				}
			}
			//cout << "source:" << source << endl;
			//cout << "match:" << match << endl;
			int pos = GetIndexOf(source, match);
			if (pos != -1)
			{
				return true;
			}
			else {
				return false;
			}
		}

		string merge(vector<string> & vstr)
		{
			string res;
			for (int i = 0; i < vstr.size(); i++)
			{
				res += vstr[i];
				if (i != vstr.size() - 1)
				{
					res += "|";
				}
			}
			return res;
		}

		vector<string> preSerial(Node * node){
			vector<string> ans;
			pres(node, ans);
			return ans;
		}
		void pres(Node* node, vector<string> & ret)
		{
			if (node == nullptr)
			{
				ret.push_back("NULL");
				return;
			}
			ret.push_back(std::to_string(node->value));
			pres(node->left, ret);
			pres(node->right, ret);
		}

		int GetIndexOf(const string & source, const string & match) {
			if (source.size() < 1 || match.size() < 2 || source.size() < match.size())
			{
				return -1;
			}
			int S = source.size();
			int M = match.size();
			int i = 0;
			int j = 0;
			vector<int> next = getNextArray(match);
			while (i < S&&j < M)
			{
				if (source[i] == match[j])
				{
					i++;
					j++;
				}
				else if (next[j] != -1)
				{
					j = next[j];
				}
				else
				{
					i++;
				}
			}
			return j == M ? i - j : -1;
		}

		vector<int> getNextArray(const string & match)
		{
			if (match.size() == 1)
			{
				return { -1 };
			}
			int N = match.size();
			vector<int> next(N, 0);
			next[0] = -1;
			next[1] = next[0];
			int i = 2;
			int cn = 0;
			while (i < N)
			{
				if (match[i - 1] == match[cn])
				{
					next[i] = cn + 1;
					cn++;
					i++;
				}
				else if (next[cn] == -1)
				{
					next[i] = 0;
					i++;
				}
				else
				{
					cn = next[cn];
				}
			}
			return next;
		}


		Node* generateRandomBST(int maxLevel, int maxValue,int minValue = 1) {

			std::uniform_int_distribution<int> i1(minValue, maxValue);
			m_idist.param(i1.param());
			
			return generate(1, maxLevel);

		}

		Node * generate(int level, int maxLevel) {
			if (level > maxLevel || m_rdist(m_rgen) < 0.4)
			{
				return nullptr;
			}
			Node * head = new Node(m_idist(m_rgen));
			head->left = generate(level + 1, maxLevel);
			head->right = generate(level + 1, maxLevel);
			return head;
		}

		vector<double> generateRandomArray(size_t N)
		{
			if (N == 0)
			{
				return {};
			}
			vector<double> ans(N, 0.0);

			for (int i = 0; i < N; i++)
			{
				ans[i] = m_idist(m_rgen);
			}
			return ans;
		}


	};
}

void test_Code02_TreeEqual() {
	
	using namespace Code02_TreeEqual;
	Code02_TreeEqual::Solution sln;
	int N = 10;
	int bigTreeLevel = 7;
	int smallTreeLevel = 4;
	int nodeMaxValue = 5;
	int testTimes = 10;
	//vector<double> array = sln.generateRandomArray(N);
	//print(array);
	cout << "test_Code02_TreeEqual begin" << endl;
	for (int i = 0; i < testTimes; i++)
	{
		Node * bigtree = sln.generateRandomBST(bigTreeLevel, nodeMaxValue, 1);
		Node * smalltree = sln.generateRandomBST(smallTreeLevel, nodeMaxValue, 1);
		bool ans1 = sln.containsTree1(bigtree, smalltree);
		bool ans2 = sln.containsTree2(bigtree, smalltree);
		if (1/*ans1 != ans2*/)
		{
			auto vbstr = sln.preSerial(bigtree);
			string sbigtree = sln.merge(vbstr);
			auto vsstr = sln.preSerial(smalltree);
			string ssmalltree = sln.merge(vsstr);
			cout << "=================" << endl;
			cout << ans1 << "," << ans2 << endl;
			cout << "bigtree:	" << sbigtree << endl;
			cout << "smalltree:	"<< ssmalltree << endl;
		}
		if (bigtree != nullptr)
		{
			delete bigtree;
		}
		if (smalltree != nullptr)
		{
			delete smalltree;
		}
	}
	cout << "test_Code02_TreeEqual end" << endl;



}


#endif