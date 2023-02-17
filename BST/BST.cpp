//
// Created by Eddard on 2023-02-17.
//

#include "BST.h"

template<typename T>
bool BST<T>::find(const T x, Node<T> *u) const {
    if (u == nullptr) return false;
    if (u->value == x) return true;
    return find(x, u->child[u->value < x].get());
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
    
    getPtrs(v, u->child[0] != nullptr ? u->child[0].get() : nullptr);
    v.push_back(u->get_ptr(&root)->release());
    u->parent = nullptr;
    getPtrs(v, u->child[1] ? u->child[1].get() : nullptr);
}

template<typename T>
void BST<T>::balance(vector<Node<T> *> &sorted, Node<T> *parent, unique_ptr<Node<T>> &myPtr, int l, int r) {
    if (r - l == 0) return;
    int mid = (l + r) / 2;
    sorted[mid]->attach_to(parent, &root);
    
    balance(sorted, myPtr.get(), myPtr->child[0], l, mid);
    balance(sorted, myPtr.get(), myPtr->child[1], mid + 1, r);
}


template<typename T>
unique_ptr<Node<T>> *BST<T>::get_root() { return false; }

template<typename T>
void BST<T>::add(T value) {
    if (root == nullptr) {
        root = make_unique<Node<T>>(value, nullptr, root);
        return;
    }
    
    Node<T> *current = root.get(), *parent = root.get();
    
    while (current != nullptr) {
        if (value == current->value) return;
        parent = current;
        current = current->child[value > current->value].get();
    }
    
    parent->add_child(value, value > parent->value);
}

template<typename T>
[[nodiscard]] bool BST<T>::find(const T x) const { return find(x, root.get()); }

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
    balance(sorted, nullptr, root, 0, (int) sorted.size());
}

template<typename T>
BST<T>::~BST() {
    cout << "BST Destroyed" << endl;
}