//
// Created by Eddard on 2023-02-17.
//

#include "Node.h"

template<typename T>
bool Node<T>::operator<(const Node &other) const { return value < other.value; }
template<typename T>
bool Node<T>::operator==(const Node &other) const { return value == other.value; }
template<typename T>
bool Node<T>::operator>(const Node &other) const { return value > other.value; }

template<typename T>
Node<T>::Node(T value_, Node *parent_) : value(value_), parent(parent_) {}

template<typename T>
Node<T> *Node<T>::add_child(T value_, int direction) {
    child[direction] = make_unique<Node<T>>(value_, this);
    child[direction]->parent = this;
    return child[direction].get();
}

template<typename T>
void Node<T>::attach_child(Node *node, int direction) {
    child[direction].reset(node);
    child[direction]->parent = this;
}

template<typename T>
void Node<T>::attach_to(Node *parent_) { parent_->attach_child(this, *this > *parent_); }

template<typename T>
unique_ptr<Node<T>> *Node<T>::get_ptr() {
    if (parent == nullptr) return nullptr;
    return &parent->child[*this > *parent];
}

template<typename T>
void Node<T>::rotate(int direction, unique_ptr<Node<T>> *root) {
    assert(child[!direction] != nullptr);
    
    Node *node0 = parent;
    Node *node1 = this;
    Node *node2 = child[!direction].get();
    Node *node3 = child[!direction]->child[direction].get();
    
    unique_ptr<Node> *ptr1 = node0 ? node1->get_ptr() : root;
    unique_ptr<Node> *ptr2 = &child[!direction];
    unique_ptr<Node> *ptr3 = &child[!direction]->child[direction];
    
    ptr1->swap(*ptr2);
    ptr2->swap(*ptr3);
    
    node1->parent = node2;
    node2->parent = node0;
    if (node3) node3->parent = node1;
}

template<typename T>
Node<T>::~Node() {
    cout << "~" << value << " ";
}

template<typename T>
ostream &operator<<(ostream &COUT, Node<T> &u) {
    COUT << u.value;
    return COUT;
    
}
