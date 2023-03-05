//
// Created by Eddard on 2023-02-17.
//

#include "RBTree.h"

template<typename T>
Node<T> *RBTree<T>::insert(T value) {
    if (BST<T>::root == nullptr) {
        BST<T>::root = make_unique<RBNode<T>>(value, nullptr, black);
        ++BST<T>::size_;
        return BST<T>::root.get();
    } else {
        Node<T> *u = BST<T>::insert(value);
        if (u) u->insert_rebalance(BST<T>::get_root());
        return u;
    }
}

template<typename T>
Node<T> *RBTree<T>::erase(Node<T> *u) {
    
    if (u->get_color() == red || u->parent == nullptr) {
        return BST<T>::erase(u);
    }
    for (int i = 0; i < 2; ++i) {
        if (u->child[i]) {
            assert(u->child[i]->get_color()==red);
            u->child[i]->set_color(black);
            return BST<T>::erase(u);
        }
    }
    // u is a black non-root leaf.
    
    --BST<T>::size_;
    
    // new dummy node replacing u to start rebalancing from, deleted at the end.
    Node<T> *ptr(new RBNode<T>());
    ptr->parent = u->parent;
    ptr->set_color(black);
    u->get_ptr()->reset(ptr);
    
    ptr->erase_rebalance(BST<T>::get_root());
    
    ptr->get_ptr()->reset();
    return nullptr;
    
}

template<typename T>
void RBTree<T>::balance() { assert(0); }
