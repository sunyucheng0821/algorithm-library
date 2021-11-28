#include <iostream>
#include <queue>
#include <cassert>
using namespace std;

// ����������
template <typename Key, typename Value>
class BST {

private:
	// ���еĽڵ�Ϊ˽�еĽṹ��, ��粻��Ҫ�˽�����������ڵ�ľ���ʵ��
	struct Node {
		Key key;
		Value value;
		Node* left;
		Node* right;

		Node(Key key, Value value) {
			this->key = key;
			this->value = value;
			this->left = this->right = NULL;
		}

		Node(Node* node) {
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
		}
	};

	Node* root; // ���ڵ�
	int count;  // ���еĽڵ����

public:
	// ���캯��, Ĭ�Ϲ���һ�ÿն���������
	BST() {
		root = NULL;
		count = 0;
	}

	// ��������, �ͷŶ��������������пռ�
	~BST() {
		destroy(root);
	}

	// ���ض����������Ľڵ����
	int size() {
		return count;
	}

	// ���ض����������Ƿ�Ϊ��
	bool isEmpty() {
		return count == 0;
	}

	// ������������в���һ���µ�(key, value)���ݶ�
	void insert(Key key, Value value) {
		root = insert(root, key, value);
	}

	// �鿴�������������Ƿ���ڼ�key
	bool contain(Key key) {
		return contain(root, key);
	}

	// �ڶ�����������������key����Ӧ��ֵ��������ֵ������, �򷵻�NULL
	Value* search(Key key) {
		Node* node = search(root, key);
		if (node == NULL)
			return NULL;
		return &(node->value);
	}

	// ������������ǰ�����
	void preOrder() {
		preOrder(root);
	}

	// �������������������
	void inOrder() {
		inOrder(root);
	}

	// �����������ĺ������
	void postOrder() {
		postOrder(root);
	}

	// �����������Ĳ������
	void levelOrder() {

		if (root == NULL) return;

		queue<Node*> q;
		q.push(root);
		while (!q.empty()) {

			Node* node = q.front();
			q.pop();

			cout << node->key << endl;

			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}
	}

	// Ѱ�Ҷ�������������С�ļ�ֵ
	Key minimum() {
		assert(count != 0);
		Node* minNode = minimum(root);
		return minNode->key;
	}

	// Ѱ�Ҷ��������������ļ�ֵ
	Key maximum() {
		assert(count != 0);
		Node* maxNode = maximum(root);
		return maxNode->key;
	}

	// �Ӷ�����������ɾ����Сֵ���ڽڵ�
	void removeMin() {
		if (root)
			root = removeMin(root);
	}

	// �Ӷ�����������ɾ�����ֵ���ڽڵ�
	void removeMax() {
		if (root)
			root = removeMax(root);
	}

	// �Ӷ�����������ɾ����ֵΪkey�Ľڵ�
	void remove(Key key) {
		root = remove(root, key);
	}

	// Ѱ��key��floorֵ, �ݹ��㷨
	// ���������key��floorֵ(key��BST�е���Сֵ��С), ����NULL
	Key* floor(Key key) {

		if (count == 0 || key < minimum())
			return NULL;

		Node* floorNode = floor(root, key);
		return &(floorNode->key);
	}

	// Ѱ��key��ceilֵ, �ݹ��㷨
	// ���������key��ceilֵ(key��BST�е����ֵ����), ����NULL
	Key* ceil(Key key) {

		if (count == 0 || key > maximum())
			return NULL;

		Node* ceilNode = ceil(root, key);
		return &(ceilNode->key);
	}

	// ����key��ǰ��
	// ���������key��ǰ��(key������, ����key�����ö������е���Сֵ), �򷵻�NULL
	Key* predecessor(Key key) {

		Node* node = search(root, key);
		// ���key���ڵĽڵ㲻����, ��keyû��ǰ��, ����NULL
		if (node == NULL)
			return NULL;

		// ���key���ڵĽڵ���������Ϊ��,���������������ֵΪkey��ǰ��
		if (node->left != NULL)
			return &(maximum(node->left)->key);

		// ����, key��ǰ���ڴӸ��ڵ㵽key��·����, �����·����Ѱ�ҵ���keyС�����ֵ, ��Ϊkey��ǰ��
		Node* preNode = predecessorFromAncestor(root, key);
		return preNode == NULL ? NULL : &(preNode->key);
	}

	// ����key�ĺ��, �ݹ��㷨
	// ���������key�ĺ��(key������, ����key�����ö������е����ֵ), �򷵻�NULL
	Key* successor(Key key) {

		Node* node = search(root, key);
		// ���key���ڵĽڵ㲻����, ��keyû��ǰ��, ����NULL
		if (node == NULL)
			return NULL;

		// ���key���ڵĽڵ���������Ϊ��,��������������СֵΪkey�ĺ��
		if (node->right != NULL)
			return &(minimum(node->right)->key);

		// ����, key�ĺ���ڴӸ��ڵ㵽key��·����, �����·����Ѱ�ҵ���key�����Сֵ, ��Ϊkey�ĺ��
		Node* sucNode = successorFromAncestor(root, key);
		return sucNode == NULL ? NULL : &(sucNode->key);
	}

private:
	// ����nodeΪ���Ķ�����������, ����ڵ�(key, value), ʹ�õݹ��㷨
	// ���ز����½ڵ��Ķ����������ĸ�
	Node* insert(Node* node, Key key, Value value) {

		if (node == NULL) {
			count++;
			return new Node(key, value);
		}

		if (key == node->key)
			node->value = value;
		else if (key < node->key)
			node->left = insert(node->left, key, value);
		else    // key > node->key
			node->right = insert(node->right, key, value);

		return node;
	}

	// �鿴��nodeΪ���Ķ������������Ƿ������ֵΪkey�Ľڵ�, ʹ�õݹ��㷨
	bool contain(Node* node, Key key) {

		if (node == NULL)
			return false;

		if (key == node->key)
			return true;
		else if (key < node->key)
			return contain(node->left, key);
		else // key > node->key
			return contain(node->right, key);
	}

	// ����nodeΪ���Ķ����������в���key����Ӧ��node, �ݹ��㷨
	// ��key������, �򷵻�NULL
	Node* search(Node* node, Key key) {

		if (node == NULL)
			return NULL;

		if (key == node->key)
			return node;
		else if (key < node->key)
			return search(node->left, key);
		else // key > node->key
			return search(node->right, key);
	}

	// ����nodeΪ���Ķ�������������ǰ�����, �ݹ��㷨
	void preOrder(Node* node) {

		if (node != NULL) {
			cout << node->key << endl;
			preOrder(node->left);
			preOrder(node->right);
		}
	}

	// ����nodeΪ���Ķ��������������������, �ݹ��㷨
	void inOrder(Node* node) {

		if (node != NULL) {
			inOrder(node->left);
			cout << node->key << endl;
			inOrder(node->right);
		}
	}

	// ����nodeΪ���Ķ������������к������, �ݹ��㷨
	void postOrder(Node* node) {

		if (node != NULL) {
			postOrder(node->left);
			postOrder(node->right);
			cout << node->key << endl;
		}
	}

	// �ͷ���nodeΪ���Ķ��������������нڵ�
	// ���ú��������ĵݹ��㷨
	void destroy(Node* node) {

		if (node != NULL) {
			destroy(node->left);
			destroy(node->right);

			delete node;
			count--;
		}
	}

	// ������nodeΪ���Ķ�������������С��ֵ���ڵĽڵ�, �ݹ��㷨
	Node* minimum(Node* node) {
		if (node->left == NULL)
			return node;

		return minimum(node->left);
	}

	// ������nodeΪ���Ķ���������������ֵ���ڵĽڵ�, �ݹ��㷨
	Node* maximum(Node* node) {
		if (node->right == NULL)
			return node;

		return maximum(node->right);
	}

	// ɾ������nodeΪ���Ķ����������е���С�ڵ�, �ݹ��㷨
	// ����ɾ���ڵ���µĶ����������ĸ�
	Node* removeMin(Node* node) {

		if (node->left == NULL) {

			Node* rightNode = node->right;
			delete node;
			count--;
			return rightNode;
		}

		node->left = removeMin(node->left);
		return node;
	}

	// ɾ������nodeΪ���Ķ����������е����ڵ�, �ݹ��㷨
	// ����ɾ���ڵ���µĶ����������ĸ�
	Node* removeMax(Node* node) {

		if (node->right == NULL) {

			Node* leftNode = node->left;
			delete node;
			count--;
			return leftNode;
		}

		node->right = removeMax(node->right);
		return node;
	}

	// ɾ������nodeΪ���Ķ����������м�ֵΪkey�Ľڵ�, �ݹ��㷨
	// ����ɾ���ڵ���µĶ����������ĸ�
	Node* remove(Node* node, Key key) {

		if (node == NULL)
			return NULL;

		if (key < node->key) {
			node->left = remove(node->left, key);
			return node;
		}
		else if (key > node->key) {
			node->right = remove(node->right, key);
			return node;
		}
		else {   // key == node->key

			if (node->left == NULL) {
				Node* rightNode = node->right;
				delete node;
				count--;
				return rightNode;
			}

			if (node->right == NULL) {
				Node* leftNode = node->left;
				delete node;
				count--;
				return leftNode;
			}

			// node->left != NULL && node->right != NULL
			Node* successor = new Node(minimum(node->right));
			count++;

			successor->right = removeMin(node->right);
			successor->left = node->left;

			delete node;
			count--;

			return successor;
		}
	}

	// ����nodeΪ���Ķ�����������, Ѱ��key��floorֵ�����Ľڵ�, �ݹ��㷨
	Node* floor(Node* node, Key key) {

		if (node == NULL)
			return NULL;

		// ���node��keyֵ��ҪѰ�ҵ�keyֵ���
		// ��node�������key��floor�ڵ�
		if (node->key == key)
			return node;

		// ���node��keyֵ��ҪѰ�ҵ�keyֵ��
		// ��ҪѰ�ҵ�key��floor�ڵ�һ����node����������
		if (node->key > key)
			return floor(node->left, key);

		// ���node->key < key
		// ��node�п�����key��floor�ڵ�, Ҳ�п��ܲ���(���ڱ�node->key����С��key������ڵ�)
		// ��Ҫ������node��������Ѱ��һ��
		Node* tempNode = floor(node->right, key);
		if (tempNode != NULL)
			return tempNode;

		return node;
	}

	// ����nodeΪ���Ķ�����������, Ѱ��key��ceilֵ�����Ľڵ�, �ݹ��㷨
	Node* ceil(Node* node, Key key) {

		if (node == NULL)
			return NULL;

		// ���node��keyֵ��ҪѰ�ҵ�keyֵ���
		// ��node�������key��ceil�ڵ�
		if (node->key == key)
			return node;

		// ���node��keyֵ��ҪѰ�ҵ�keyֵС
		// ��ҪѰ�ҵ�key��ceil�ڵ�һ����node����������
		if (node->key < key)
			return ceil(node->right, key);

		// ���node->key > key
		// ��node�п�����key��ceil�ڵ�, Ҳ�п��ܲ���(���ڱ�node->keyС���Ǵ���key������ڵ�)
		// ��Ҫ������node��������Ѱ��һ��
		Node* tempNode = ceil(node->left, key);
		if (tempNode != NULL)
			return tempNode;

		return node;
	}

	// ����nodeΪ���Ķ�����������, Ѱ��key��������,��keyС�����ֵ���ڽڵ�, �ݹ��㷨
	// �㷨����ǰ�ѱ�֤key��������nodeΪ���Ķ�������
	Node* predecessorFromAncestor(Node* node, Key key) {

		if (node->key == key)
			return NULL;

		if (key < node->key)
			// �����ǰ�ڵ����key, ��ǰ�ڵ㲻�����Ǳ�keyС�����ֵ
			// �����������Ľ��ֱ�ӷ���
			return predecessorFromAncestor(node->left, key);
		else {
			assert(key > node->key);
			// �����ǰ�ڵ�С��key, ��ǰ�ڵ��п����Ǳ�keyС�����ֵ
			// ���Ҽ�������, ������洢��tempNode��
			Node* tempNode = predecessorFromAncestor(node->right, key);
			if (tempNode)
				return tempNode;
			else
				// ���tempNodeΪ��, ��ǰ�ڵ㼴Ϊ���
				return node;
		}
	}

	// ����nodeΪ���Ķ�����������, Ѱ��key��������,��key�����Сֵ���ڽڵ�, �ݹ��㷨
	// �㷨����ǰ�ѱ�֤key��������nodeΪ���Ķ�������
	Node* successorFromAncestor(Node* node, Key key) {

		if (node->key == key)
			return NULL;

		if (key > node->key)
			// �����ǰ�ڵ�С��key, ��ǰ�ڵ㲻�����Ǳ�key�����Сֵ
			// �����������Ľ��ֱ�ӷ���
			return successorFromAncestor(node->right, key);
		else {
			assert(key < node->key);
			// �����ǰ�ڵ����key, ��ǰ�ڵ��п����Ǳ�key�����Сֵ
			// �����������, ������洢��tempNode��
			Node* tempNode = successorFromAncestor(node->left, key);
			if (tempNode)
				return tempNode;
			else
				// ���tempNodeΪ��, ��ǰ�ڵ㼴Ϊ���
				return node;
		}
	}
	Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
		assert(p != NULL && q != NULL);
		if (root == NULL)
			return NULL;
		if (p->val < root->val && q->val < root->val)
			return lowestCommonAncestor(root->left, p, q);
		if (p->val > root->val && q->val > root->val)
			return lowestCommonAncestor(root->right, p, q);
		return root;
	}
};


void shuffle(int arr[], int n) {

	srand(time(NULL));
	for (int i = n - 1; i >= 0; i--) {
		int x = rand() % (i + 1);
		swap(arr[i], arr[x]);
	}
}

void SortArr(int arr[], int n)
{
	sort(arr + 1, arr + n + 1);
}