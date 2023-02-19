//
// Created by Eddard on 2023-02-17.
//

#include "BST.h"

template<typename T>
[[nodiscard]] Node<T> *BST<T>::find(const T x) const { return find(x, root.get()); }

template<typename T>
[[nodiscard]] Node<T> *BST<T>::lower_bound(T value) const { return lower_bound(value, root.get()); }

template<typename T>
[[nodiscard]] Node<T> *BST<T>::upper_bound(T value) const { return upper_bound(value, root.get()); }

template<typename T>
Node<T> *BST<T>::insert(T value) {
    if (root == nullptr) {
        root = make_unique<Node<T>>(value, nullptr);
        return root.get();
    }
    
    Node<T> *current = root.get(), *parent = root.get();
    
    while (current != nullptr) {
        if (value == current->value) return nullptr;
        parent = current;
        current = current->child[value > current->value].get();
    }
    
    return parent->add_child(value, value > parent->value);
}

template<typename T>
Node<T> *BST<T>::erase(T value) {
    Node<T> *u = find(value);
    if (u == nullptr)
        throw invalid_argument("Value doesn't exist.");
    return erase(u);
}

template<typename T>
void BST<T>::print(int mode) const {
    if (mode < 0 || mode > 2) throw invalid_argument("print mode must belong to {0, 1, 2}");
    
    vector<Node<T> *> ptrs;
    traverse(ptrs, root.get(), mode);
    
    for (auto ptr: ptrs) cout << *ptr << " ";
    cout << endl;
}

template<typename T>
void BST<T>::balance() {
    vector<Node<T> *> sorted;
    getPtrs(sorted, root.get());
    balance(sorted, nullptr, 0, (int) sorted.size());
}

template<typename T>
BST<T>::~BST() {
    cout << "~BST" << endl;
}

template<typename T>
[[nodiscard]] Node<T> *BST<T>::find(const T value, Node<T> *u) const {
    if (u == nullptr) return nullptr;
    if (*u == value) return u;
    return find(value, u->child[*u < value].get());
}

template<typename T>
[[nodiscard]] Node<T> *BST<T>::lower_bound(T value, Node<T> *u) const {
    if (u == nullptr) return nullptr;
    if (*u < value) return lower_bound(value, u->child[1].get());
    Node<T> *ptr = lower_bound(value, u->child[0].get());
    return ptr ? ptr : u;
}

template<typename T>
[[nodiscard]] Node<T> *BST<T>::upper_bound(T value, Node<T> *u) const {
    if (u == nullptr) return nullptr;
    if (*u <= value) return upper_bound(value, u->child[1].get());
    Node<T> *ptr = upper_bound(value, u->child[0].get());
    return ptr ? ptr : u;
}

template<typename T>
Node<T> *BST<T>::erase(Node<T> *u) {
    
    unique_ptr<Node<T>> *ptr;
    
    if (u->child[0] && u->child[1]) {
        Node<T> *v = u->child[1].get();
        while (v->child[0]) v = v->child[0].get();
        swap(u->value, v->value);
        
        if (u == v->parent)
            ptr = &u->child[1];
        else
            ptr = &v->parent->child[0];
        
        u = v;
    } else
        ptr = u->get_ptr();
    
    if (!ptr) ptr = &root;
    
    if (!u->child[0] && !u->child[1]) {
        Node<T> *parent = u->parent;
        ptr->reset();
        return parent;
    }
    
    for (int i = 0; i < 2; ++i) {
        if (!u->child[i]) {
            u->child[!i]->parent = u->parent;
            *ptr = std::move(u->child[!i]);
            return ptr->get();
        }
    }
    
    assert(0);
    return nullptr;
    
}

template<typename T>
void BST<T>::traverse(vector<Node<T> *> &v, Node<T> *u, int mode) const {
    if (u == nullptr) return;
    
    if (mode == 0) v.push_back(u);
    traverse(v, u->child[0].get(), mode);
    if (mode == 1) v.push_back(u);
    traverse(v, u->child[1].get(), mode);
    if (mode == 2) v.push_back(u);
}

template<typename T>
void BST<T>::getPtrs(vector<Node<T> *> &v, Node<T> *u) {
    if (u == nullptr) return;
    // Left
    getPtrs(v, u->child[0] != nullptr ? u->child[0].get() : nullptr);
    
    unique_ptr<Node<T>> *ptr = u->get_ptr();
    if (ptr == nullptr) ptr = &root;
    
    v.push_back(ptr->release());
    u->parent = nullptr;
    // Right
    getPtrs(v, u->child[1] ? u->child[1].get() : nullptr);
}

template<typename T>
void BST<T>::balance(vector<Node<T> *> &sorted, Node<T> *parent, int l, int r) {
    if (r - l == 0) return;
    int mid = (l + r) / 2;
    
    if (parent == nullptr) root.reset(sorted[mid]);
    else sorted[mid]->attach_to(parent);
    
    balance(sorted, sorted[mid], l, mid);
    balance(sorted, sorted[mid], mid + 1, r);
}

template<typename T>
unique_ptr<Node<T>> *BST<T>::get_root() {
    return &root;
}

