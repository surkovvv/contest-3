//Дано число N < 106 и последовательность целых чисел из[-231..231] длиной N.Требуется построить бинарное дерево, заданное наивным порядком вставки.
//	Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root;
//иначе в левое поддерево root.Выведите элементы в порядке pre - order(сверху вниз).
//	Рекурсия запрещена.

#include <iostream>
#include <vector>
#include <assert.h>
#include <queue>
#include <stack>

template <typename T>
struct treeNode {
	treeNode() : key(0), left(NULL), right(NULL) {};
	treeNode(const T& value) : key(value), left(NULL), right(NULL) {};
	T key;
	treeNode* left, *right;
};
template <typename T>
class binTree {
public:
	void insert(const T& key);
	binTree() : root(NULL) {};
	std::vector<T> printTree();
	void Clear(treeNode<T>* root);
	~binTree() { Clear(root); };
private:
	treeNode<T>* root;
	template <typename Pred>
	void foo(Pred p);
};
template <typename T>
void binTree<T>::insert(const T& key) {
	treeNode<T>* tmp = new treeNode<T>(key);
	if (root == NULL) {
		root = tmp;
		return;
	}
	treeNode<T>* node = root; // наш итератор по дереву
	assert(node != nullptr);
	while ((node->left != NULL && node->key >= key) ||
		(node->right != NULL && node->key < key)) {
		if (key < node->key) node = node->left;
		else node = node->right;
	}
	if (key < node->key) 
		node->left = tmp;
	else 
		node->right = tmp;
}
template <typename T>
template <typename Pred>
void binTree<T>::foo(Pred p) {
	std::stack<treeNode<T>*> st;
	treeNode<T>* everBeen = root;
	treeNode<T>* node = root; // "итератор"
	while (!st.empty() || node != NULL) {
		if (!st.empty()) {
			node = st.top();
			st.pop();
		}
		while (node != NULL) {
			p(node);
			if (node->right != NULL) st.push(node->right);
			node = node->left;
		}
	}
}
template <typename T>
std::vector<T> binTree<T>::printTree() {
	std::vector<T> ans;
	foo([&ans](treeNode <T>* node) { ans.push_back(node->key); });
	return ans;
}

template <typename T>
void binTree<T>::Clear(treeNode<T>* r) {
	if (r != NULL) {
		Clear(r->left);
		Clear(r->right);
		delete r;
	}
}
int main() {
	int n;
	std::cin >> n;
	binTree<int> tree;
	int value;

	for (int i = 0; i < n; i++) {
		std::cin >> value;
		tree.insert(value);
	}
	auto ans = tree.printTree();
	for (auto val : ans) {
		std::cout << val << " ";
	}
	return 0;
}