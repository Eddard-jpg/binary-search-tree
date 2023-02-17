//
// Created by Eddard on 2023-02-17.
//

#ifndef DATASTRUCTURES_NODE_H
#define DATASTRUCTURES_NODE_H

#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Node {
public:
    T value;
    Node *parent = nullptr;
    unique_ptr<Node> child[2];
    
    
    bool operator<(const Node &other) const;
    
    bool operator==(const Node &other) const;
    
    bool operator>(const Node &other) const;
    
    explicit Node(T value_);
    
    Node(T value_, Node *parent_, unique_ptr<Node> &myPtr_);
    
    // Add child node, direction = 0 for left, 1 for right.
    void add_child(T value_, int direction);
    
    // Attach an existing node as a child, direction = 0 for left, 1 for right.
    void attach_child(Node *node, int direction);
    
    void attach_to(Node *parent_, unique_ptr<Node<T>> *root);
    
    unique_ptr<Node> *get_ptr(unique_ptr<Node> *root);
    
    ~Node();
    
};

template<typename T>
ostream &operator<<(ostream &COUT, Node<T> &u) {
    COUT << u.value;
    return COUT;
    
}

#endif //DATASTRUCTURES_NODE_H
