#pragma once
//��תһ�ö�����
//ʾ����
//
//���룺
//
//	4
//	/ \
//	2     7
//	/ \ / \
//	1   3 6   9
//�����
//
//	4
//	/ \
//	7     2
//	/ \ / \
//	9   6 3   1


 // @lc code=start
#include<bits/stdc++.h>
using namespace std;

//* Definition for a binary tree node.
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr)
			return nullptr;
		invertTree(root->left);
		invertTree(root->right);
		swap(root->left, root->right);
		return root;
	}
};
// @lc code=end

