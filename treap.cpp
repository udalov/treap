#include <utility>

template<typename T> struct treap_node {
	T key;
	int priority;
	treap_node<T>* left;
	treap_node<T>* right;
	
	treap_node(const T& _key, int _priority):
		key(_key),
		priority(_priority),
		left(0),
		right(0)
	{}
};

template<typename T> struct treap {
	typedef treap_node<T>* node;
	typedef std::pair<node, node> node_pair;
	
	node root;
	
	treap(): root(0) {}
	virtual ~treap() {}
	
	void insert(const T& x);
	bool remove(const T& x);
	bool contains(const T& x) const;
	
	node_pair treap_split(node v, const T& key);
	node treap_merge(node left, node right);
};


template<typename T> typename treap<T>::node_pair treap<T>::treap_split(node v, const T& key) {
	if (!v) return node_pair(0, 0);
	// left tree should contain all keys <= key
	if (v->key <= key) {
		node_pair p = treap_split(v->right, key);
		v->right = p.first;
		p.first = v;
		return p;
	} else {
		node_pair p = treap_split(v->left, key);
		v->left = p.second;
		p.second = v;
		return p;
	}
}

template<typename T> typename treap<T>::node treap<T>::treap_merge(node left, node right) {
	if (!left) return right;
	if (!right) return left;
	if (left->priority > right->priority) {
		left->right = treap_merge(left->right, right);
		return left;
	} else {
		right->left = treap_merge(right->left, left);
		return right;
	}
}



template<typename T> void treap<T>::insert(const T& x) {
}

template<typename T> bool treap<T>::remove(const T& x) {
	return false;
}

template<typename T> bool treap<T>::contains(const T& x) const {
	return false;
}



int main() {
	return 0;
}

