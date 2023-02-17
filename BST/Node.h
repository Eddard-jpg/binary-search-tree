//
// Created by Eddard on 2023-02-17.
//

#ifndef DATASTRUCTURES_NODE_H
#define DATASTRUCTURES_NODE_H

#include <bits/stdc++.h>

using namespace std;

class Node {
public:
    int value;
    Node *parent = nullptr;
    unique_ptr<Node> child[2];
    unique_ptr<Node> *myPtr = nullptr;
    
    bool operator<(const Node &other) const { return value < other.value; }
    bool operator==(const Node &other) const { return value == other.value; }
    bool operator>(const Node &other) const { return value > other.value; }
    
    explicit Node(int value_) : value(value_) {}
    
    Node(int value_, Node *parent_, unique_ptr<Node> &myPtr_) : value(value_), parent(parent_), myPtr(&myPtr_) {}
    
    // Add child node, direction = 0 for left, 1 for right.
    void add_child(int value_, int direction) {
        child[direction] = make_unique<Node>(value_, this, child[direction]);
    }
    
    // Attach an existing node as a child, direction = 0 for left, 1 for right.
    void attach_child(Node *node, int direction) {
        child[direction].reset(node);
        child[direction]->parent = this;
        child[direction]->myPtr = &child[direction];
    }
    
    void attach_to(Node *parent_, unique_ptr<Node> &myPtr_) {
        if (myPtr->get() == this)
            myPtr_ = std::move(*myPtr);
        else
            myPtr_.reset(this);
        parent = parent_;
        myPtr = &myPtr_;
    }
    
    ~Node() {
        cout << value << " Destroyed" << endl;
    }
    
};

ostream &operator<<(ostream &COUT, Node &u) {
    COUT << u.value;
    return COUT;
    
}


#endif //DATASTRUCTURES_NODE_H
