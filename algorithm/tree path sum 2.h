//����һ��������������ÿ����㶼�����һ������ֵ��
//
//�ҳ�·���͵��ڸ�����ֵ��·��������
//
//·������Ҫ�Ӹ��ڵ㿪ʼ��Ҳ����Ҫ��Ҷ�ӽڵ����������·��������������µģ�ֻ�ܴӸ��ڵ㵽�ӽڵ㣩��
//
//������������1000���ڵ㣬�ҽڵ���ֵ��Χ��[-1000000, 1000000] ��������
#include<bits/stdc++.h>
#include"TraversalHelper(������).h"
using namespace std;
class Solution {

public:
	int pathSum(TreeNode* root, int sum) {

		if (root == NULL)
			return 0;

		return findPath(root, sum)
			+ pathSum(root->left, sum)
			+ pathSum(root->right, sum);
	}

private:
	int findPath(TreeNode* node, int num) {

		if (node == NULL)
			return 0;

		int res = 0;
		if (node->val == num)
			res += 1;

		res += findPath(node->left, num - node->val);
		res += findPath(node->right, num - node->val);

		return res;
	}
};
// @lc code=end
