#include <functional>
#include <utility>
#include <cstdlib>

template<typename T> struct treap_node {
    typedef treap_node<T>* node;

    T key;
    int priority;
    int size;
    node left;
    node right;
    
    treap_node(const T& _key):
        key(_key),
        priority(rand() ^ (rand() << 15)),
        size(1),
        left(0),
        right(0)
    {}

    inline void update_size() { size = (left ? left->size : 0) + (right ? right->size : 0) + 1; }
    inline void set_left(node _left) { left = _left; update_size(); }
    inline void set_right(node _right) { right = _right; update_size(); }
};

template<typename T> struct treap {
    typedef treap_node<T>* node;
    typedef std::pair<node, node> node_pair;
    
    node root;
    
    treap():
        root(0)
    {}
    virtual ~treap() {}
    
    bool insert(const T& x);
    bool erase(const T& x);
    bool contains(const T& x) const;
    int size() const;
    bool empty() const;
    
    bool insert_slow(const T& x);
    bool erase_slow(const T& x);
    
    static node_pair treap_split(node v, const T& key, bool less_equal = true);
    static node treap_merge(node left, node right);
};



template<typename T> typename treap<T>::node_pair treap<T>::treap_split(node v, const T& key, bool less_equal) {
    if (!v) return node_pair(0, 0);
    //TODO: rewrite to templates
    bool cmp_result = less_equal ? (!(key < v->key)) : (v->key < key);
    if (cmp_result) {
        node_pair p = treap_split(v->right, key, less_equal);
        v->set_right(p.first);
        p.first = v;
        return p;
    } else {
        node_pair p = treap_split(v->left, key, less_equal);
        v->set_left(p.second);
        p.second = v;
        return p;
    }
}

template<typename T> typename treap<T>::node treap<T>::treap_merge(node left, node right) {
    if (!left) return right;
    if (!right) return left;
    if (left->priority > right->priority) {
        left->set_right(treap_merge(left->right, right));
        return left;
    } else {
        right->set_left(treap_merge(left, right->left));
        return right;
    }
}


template<typename T> bool treap<T>::insert(const T& x) {
    return insert_slow(x);
}

template<typename T> bool treap<T>::erase(const T& x) {
    return erase_slow(x);
}

template<typename T> bool treap<T>::contains(const T& x) const {
    node v = root;
    while (v) {
        if (v->key < x) {
            v = v->right;
        } else if (x < v->key) {
            v = v->left;
        } else {
            return true;
        }
    }
    return false;
}

template<typename T> bool treap<T>::insert_slow(const T& x) {
    if (!root) {
        root = new treap_node<T>(x);
        return true;
    }
    node_pair p = treap_split(root, x);
    node r = p.first;
    if (r) while (r->right)
        r = r->right;
    if (r && !(r->key < x) && !(x < r->key)) {
        root = treap_merge(p.first, p.second);
        return false;
    }
    node v = new treap_node<T>(x);
    root = treap_merge(p.first, treap_merge(v, p.second));
    return true;
}

template<typename T> bool treap<T>::erase_slow(const T& x) {
    if (!root) return false;
    node_pair p = treap_split(root, x);
    if (!p.first) {
        root = p.second;
        return false;
    }
    node_pair q = treap_split(p.first, x, false);
    root = treap_merge(q.first, p.second);
    return q.second;
}

template<typename T> inline int treap<T>::size() const {
    return root ? root->size : 0;
}

template<typename T> inline bool treap<T>::empty() const {
    return size() == 0;
}

