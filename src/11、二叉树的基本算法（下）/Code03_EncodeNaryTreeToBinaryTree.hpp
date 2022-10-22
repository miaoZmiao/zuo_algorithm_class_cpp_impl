#pragma once

#include "treeNode.hpp"

namespace Code03_EncodeNaryTreeToBinaryTree {


	// ±æÃ‚≤‚ ‘¡¥Ω”£∫https://leetcode.com/problems/encode-n-ary-tree-to-binary-tree

	struct MultiBranchTreeNode {

		int val;
		vector<MultiBranchTreeNode *> children;

		MultiBranchTreeNode() {
		}

		MultiBranchTreeNode(int _val) {
			val = _val;
		}

		MultiBranchTreeNode(int _val, const vector<MultiBranchTreeNode *> & _children) {
			val = _val;
			children = _children;
		}

		~MultiBranchTreeNode() {
			for (auto & c : children)
			{
				delete c;
				c = nullptr;
			}
		}

	};

	class Codec {
	public:
		// Encodes an n-ary tree to a binary tree.
		Node * encode(MultiBranchTreeNode * root) {
			if (root == nullptr) {
				return nullptr;
			}
			Node * head = new Node(root->val);
			head->left = en(root->children);
			return head;
		}

		Node* en(vector<MultiBranchTreeNode *> & children) {
			Node * head = nullptr;
			Node * cur = nullptr;
			for (MultiBranchTreeNode * child : children) {
				Node * tNode = new Node(child->val);
				if (head == nullptr) {
					head = tNode;
				}
				else {
					cur->right = tNode;
				}
				cur = tNode;
				cur->left = en(child->children);
			}
			return head;
		}

		MultiBranchTreeNode * decode(Node * root) {
			if (root == nullptr) {
				return nullptr;
			}
			return new MultiBranchTreeNode(root->value, de(root->left));
		}

		vector<MultiBranchTreeNode*> de(Node * root) {
			vector<MultiBranchTreeNode *> children;
			while (root != nullptr) {
				MultiBranchTreeNode * cur = new MultiBranchTreeNode(root->value, de(root->left));
				children.push_back(cur);
				root = root->right;
			}
			return children;
		}

	};

}


void test_Code03_EncodeNaryTreeToBinaryTree() {


}
