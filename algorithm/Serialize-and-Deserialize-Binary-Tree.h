#pragma once
//���л��ǽ�һ�����ݽṹ���߶���ת��Ϊ�����ı���λ�Ĳ������������Խ�ת��������ݴ洢��һ���ļ������ڴ��У�ͬʱҲ����ͨ�����紫�䵽��һ���������������ȡ�෴��ʽ�ع��õ�ԭ���ݡ�
//
//�����һ���㷨��ʵ�ֶ����������л��뷴���л������ﲻ�޶�������� / �����л��㷨ִ���߼�����ֻ��Ҫ��֤һ�����������Ա����л�Ϊһ���ַ������ҽ�����ַ��������л�Ϊԭʼ�����ṹ��
//ʾ��:
//
//����Խ����¶�������
//
//   1
//  / \
//  2  3
// /   \
// 4    5
//
//���л�Ϊ "[1,2,3,null,null,4,5]"



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


class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {

		if (!root)
			return "[null]";

		string ret = "[";
		dfs(root, ret);
		ret.pop_back();
		return ret + "]";
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		vector<string> vec = get_vector(data);

		if (vec.size() == 0 || (vec.size() == 1 && vec[0] == "null"))
			return NULL;

		//        for(const string& s: vec)
		//            cout << s << " ";
		//        cout << endl;

		int index = 0;
		return dfs(vec, index);
	}

private:
	TreeNode* dfs(const vector<string>& vec, int& index) {

		if (index == vec.size() || vec[index] == "null")
			return NULL;

		TreeNode* node = new TreeNode(atoi(vec[index].c_str()));
		index++;
		node->left = dfs(vec, index);

		index++;
		node->right = dfs(vec, index);

		return node;
	}

	void dfs(TreeNode* node, string& ret) {

		ret += to_string(node->val) + ",";

		if (node->left)
			dfs(node->left, ret);
		else
			ret += "null,";

		if (node->right)
			dfs(node->right, ret);
		else
			ret += "null,";
	}

	vector<string> get_vector(const string& data) {

		string s = data.substr(1, data.size() - 2) + ",";

		vector<string> res;
		int i = 0;
		while (i < s.size()) {
			int comma = s.find(',', i);
			res.push_back(s.substr(i, comma - i));
			i = comma + 1;
		}
		return res;
	}
};

// @lc code=end

