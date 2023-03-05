//
// Created by Eddard on 2023-02-18.
//

#include "AVLNode.h"

template<typename T>
AVLNode<T>::AVLNode(T value_, Node<T> *parent_):Node<T>(value_, parent_), height(0) {}

template<typename T>
Node<T> *AVLNode<T>::add_child(T value_, int direction) {
    Node<T>::child[direction] = make_unique<AVLNode>(value_, this);
    return Node<T>::child[direction].get();
}

template<typename T>
int AVLNode<T>::get_height() const { return height; }

template<typename T>
int AVLNode<T>::balance_factor() {
    int lh = Node<T>::child[0] ? Node<T>::child[0]->get_height() : -1;
    int rh = Node<T>::child[1] ? Node<T>::child[1]->get_height() : -1;
    return rh - lh;
}

template<typename T>
void AVLNode<T>::update_height() {
    height = 0;
    for (auto &c: Node<T>::child)
        if (c)
            height = max(height, c->get_height() + 1);
}

template<typename T>
void AVLNode<T>::insert_rebalance(unique_ptr<Node<T>> *root) {
    
    update_height();
    
    int bf = balance_factor();
    if (abs(bf) > 1) {
        int direction = bf > 0;
        Node<T> *child = Node<T>::child[direction].get();
        
        int bf2 = child->balance_factor();
        if (bf2 * bf < 0) {
            child->rotate(direction, root);
            child->update_height();
        }
        Node<T>::rotate(!direction, root);
        update_height();
    }
    if (Node<T>::parent != nullptr) Node<T>::parent->insert_rebalance(root);
    
}

template<typename T>
void AVLNode<T>::erase_rebalance(unique_ptr<Node<T>> *root) { insert_rebalance(root); }
