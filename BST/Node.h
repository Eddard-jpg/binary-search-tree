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
    
    explicit Node(T value_, Node *parent_ = nullptr);
    
    virtual Node<T> *add_child(T value_, int direction);
    
    virtual void attach_child(Node *node, int direction);
    
    virtual void attach_to(Node *parent_);
    
    virtual unique_ptr<Node> *get_ptr();
    
    virtual void rotate(int direction, unique_ptr<Node<T>> *root);
    
    ~Node();
    
    virtual int get_height() { return 0; }
    
    virtual int balance_factor() { return 0; }
    
    virtual void update_height() {}
    
    virtual void rebalance(unique_ptr<Node<T>> *root) {}
    
};

#endif //DATASTRUCTURES_NODE_H
