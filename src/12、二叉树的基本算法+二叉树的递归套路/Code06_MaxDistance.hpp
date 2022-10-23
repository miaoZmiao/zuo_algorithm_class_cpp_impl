#pragma once
#include "treeNode.hpp"
#include "scope_guard.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
namespace Code06_MaxDistance {


	class MaxDistance {
	public:
		int maxDistance1(Node * head) {
			if (head == nullptr) {
				return 0;
			}
			vector<Node*> arr = getPrelist(head);
			unordered_map<Node*, Node*> parentMap = getParentMap(head);
			int max = 0;
			for (int i = 0; i < arr.size(); i++) {
				for (int j = i; j < arr.size(); j++) {
					max = std::max(max, distance(parentMap, arr[i], arr[j]));
				}
			}
			return max;
		}

		vector<Node*> getPrelist(Node * head) {
			vector<Node*> arr;
			fillPrelist(head, arr);
			return arr;
		}

		void fillPrelist(Node * head, vector<Node*> & arr) {
			if (head == nullptr) {
				return;
			}
			arr.push_back(head);
			fillPrelist(head->left, arr);
			fillPrelist(head->right, arr);
		}

		unordered_map<Node*, Node*> getParentMap(Node * head) {
			unordered_map<Node*, Node*> map;
			map.insert({head, nullptr });
			fillParentMap(head, map);
			return map;
		}

		void fillParentMap(Node * head, unordered_map<Node*, Node*> & parentMap) {
			if (head->left != nullptr) {
				parentMap.insert({ head->left, head });
				fillParentMap(head->left, parentMap);
			}
			if (head->right != nullptr) {
				parentMap.insert({ head->right, head });
				fillParentMap(head->right, parentMap);
			}
		}

		int distance(unordered_map<Node*, Node*> & parentMap, Node * o1, Node * o2) {
			unordered_set<Node*> o1Set ;
			Node * cur = o1;
			o1Set.insert(cur);
			while (parentMap[cur] != nullptr) {
				cur = parentMap[cur];
				o1Set.insert(cur);
			}
			cur = o2;
			while (!o1Set.count(cur)) {
				cur = parentMap[cur];
			}
			Node * lowestAncestor = cur;
			cur = o1;
			int distance1 = 1;
			while (cur != lowestAncestor) {
				cur = parentMap[cur];
				distance1++;
			}
			cur = o2;
			int distance2 = 1;
			while (cur != lowestAncestor) {
				cur = parentMap[cur];
				distance2++;
			}
			return distance1 + distance2 - 1;
		}

		struct Info {
			int maxDistance;
			int height;

			Info(int m, int h) {
				maxDistance = m;
				height = h;
			}

		};

		int maxDistance2(Node * head) {
			return process(head).maxDistance;
		}

	

		Info process(Node * x) {
			if (x == nullptr) {
				return Info(0, 0);
			}
			Info leftInfo = process(x->left);
			Info rightInfo = process(x->right);
			int height = std::max(leftInfo.height, rightInfo.height) + 1;
			int p1 = leftInfo.maxDistance;
			int p2 = rightInfo.maxDistance;
			int p3 = leftInfo.height + rightInfo.height + 1;
			int maxDistance = std::max(std::max(p1, p2), p3);
			return  Info(maxDistance, height);
		}

	};

	void test_main() {
		int maxLevel = 4;
		int maxValue = 100;
		int testTimes = 1000;
		MaxDistance md;
		for (int i = 0; i < testTimes; i++) {
			Node * head = generatetree(maxLevel);
			scope_guard sg([head]() {
				if (head != nullptr)
				{
					delete head;
				}
			});
			if (md.maxDistance1(head) != md.maxDistance2(head)) {
				cout << "Oops!" << endl;
				break;
			}
		}
	}

}


void test_Code06_MaxDistance() {

	cout << "test_Code06_MaxDistance begin" << endl;
	Code06_MaxDistance::test_main();
	cout << "test_Code06_MaxDistance end" << endl;
}