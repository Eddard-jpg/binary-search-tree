//
// Created by Eddard on 2023-02-18.
//

#include "AVLNode.h"

template<typename T>
AVLNode<T>::AVLNode(T value_, Node<T> *parent_):Node<T>(value_, parent_), height(0) {}


template<typename T>
Node<T> *AVLNode<T>::add_child(T value_, int direction) {
    Node<T>::child[direction] = make_unique<AVLNode>(value_);
    Node<T>::child[direction]->parent = this;
    return Node<T>::child[direction].get();
}

template<typename T>
void AVLNode<T>::attach_child(Node<T> *node, int direction) {
    Node<T>::attach_child(node, direction);
    update_height();
}

template<typename T>
void AVLNode<T>::attach_to(Node<T> *parent_) {
    Node<T>::attach_to(parent_);
    Node<T>::parent->update_height();
}

template<typename T>
int AVLNode<T>::get_height() { return height; }

template<typename T>
int AVLNode<T>::balance_factor() {
    int lh = Node<T>::child[0] ? Node<T>::child[0]->get_height() : -1;
    int rh = Node<T>::child[1] ? Node<T>::child[1]->get_height() : -1;
    return rh - lh;
}

template<typename T>
void AVLNode<T>::update_height() {
    height = 0;
    for (int i = 0; i < 2; ++i)
        if (Node<T>::child[i])
            height = max(height, Node<T>::child[i]->get_height() + 1);
    if (Node<T>::parent != nullptr)
        Node<T>::parent->update_height();
}

template<typename T>
void AVLNode<T>::rotate(int direction, unique_ptr<Node<T>> *root) {
    Node<T>::rotate(direction, root);
    update_height();
    Node<T>::parent->update_height();
}

template<typename T>
void AVLNode<T>::rebalance(unique_ptr<Node<T>> *root) {
    
    update_height();
    
    int bf = balance_factor();
    if (abs(bf) > 1) {
        assert(abs(bf) == 2);
        int direction = bf > 0;
        Node<T> *child = Node<T>::child[direction].get();
        
        int bf2 = child->balance_factor();
        if (bf2 * bf < 0)
            child->rotate(direction, root);
        this->rotate(!direction, root);
    }
    assert(abs(balance_factor()) <= 1);
    if (Node<T>::parent != nullptr) Node<T>::parent->rebalance(root);
    
}

template<typename T>
AVLNode<T>::~AVLNode() { cout << "~AVL " << Node<T>::value << " "; }
