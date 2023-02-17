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
    unique_ptr<Node> leftChild = nullptr, rightChild = nullptr;
    unique_ptr<Node> *myPtr = nullptr;
    
    bool operator<(const Node &other) const { return value < other.value; }
    bool operator==(const Node &other) const { return value == other.value; }
    bool operator>(const Node &other) const { return value > other.value; }
    
    explicit Node(int value_) : value(value_) {
        //cout << value << " Created" << endl;
    }
    
    void addLeft(int value_) {
        leftChild = make_unique<Node>(value_);
        leftChild->parent = this;
        leftChild->myPtr = &leftChild;
    }
    
    void addRight(int value_) {
        rightChild = make_unique<Node>(value_);
        rightChild->parent = this;
        rightChild->myPtr = &rightChild;
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
