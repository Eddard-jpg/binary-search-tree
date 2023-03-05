//
// Created by Eddard on 2023-02-18.
//

#include "AVLTree.h"

template<typename T>
Node<T> *AVLTree<T>::insert(T value) {
    if (BST<T>::root == nullptr) {
        BST<T>::root = make_unique<AVLNode<T>>(value);
        ++BST<T>::size_;
        return BST<T>::root.get();
    } else {
        Node<T> *u = BST<T>::insert(value);
        if (u) u->insert_rebalance(BST<T>::get_root());
        return u;
    }
}

template<typename T>
Node<T> *AVLTree<T>::erase(Node<T> *u) {
    u = BST<T>::erase(u);
    if (u) u->erase_rebalance(BST<T>::get_root());
    return u;
}

template<typename T>
void AVLTree<T>::balance() { assert(0); }
