//
// Created by Eddard on 2023-02-17.
//

#include "Node.h"

template<typename T>
bool Node<T>::operator<(const Node& other) const { return value < other.value; }
template<typename T>
bool Node<T>::operator==(const Node& other) const { return value == other.value; }
template<typename T>
bool Node<T>::operator>(const Node& other) const { return value > other.value; }

template<typename T>
Node<T>::Node(T value_) : value(value_) {}

template<typename T>
Node<T>::Node(T value_, Node* parent_, unique_ptr<Node>& myPtr_) : value(value_), parent(parent_) {}

template<typename T>
void Node<T>::add_child(T value_, int direction) {
child[direction] = make_unique<Node<T>>(value_, this, child[direction]);
}

template<typename T>
void Node<T>::attach_child(Node* node, int direction) {
child[direction].reset(node);
child[direction]->parent.reset(this);
}

template<typename T>
void Node<T>::attach_to(Node* parent_, unique_ptr<Node<T>>* root) {
    parent = parent_;
    if (parent == nullptr) root->reset(this);
    else parent->child[*this > *parent].reset(this);
}

template<typename T>
unique_ptr<Node<T>>* Node<T>::get_ptr(unique_ptr<Node>* root) {
    if (parent == nullptr) return root;
    return &parent->child[*this > *parent];
}

template<typename T>
Node<T>::~Node() {
    cout << value << " Destroyed" << endl;
}