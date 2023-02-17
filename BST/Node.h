//
// Created by Eddard on 2023-02-17.
//

#ifndef DATASTRUCTURES_NODE_H
#define DATASTRUCTURES_NODE_H

#include <bits/stdc++.h>

#include <memory>
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
    
    [[nodiscard]] unique_ptr<Node> *getPtr() const {
        return myPtr;
    }
    
    void swapParent() {
        if (parent == nullptr) return;
        
        int f = value < parent->value;
        
        Node *node0 = parent->parent;
        Node *node1 = parent;
        Node *node2 = this;
        Node *node3 = f ? rightChild.get() : leftChild.get();
        
        unique_ptr<Node> *ptr1 = parent->myPtr;
        unique_ptr<Node> *ptr2 = myPtr;
        unique_ptr<Node> *ptr3 = f ? &rightChild : &leftChild;
        
        ptr1->swap(*ptr2);
        ptr2->swap(*ptr3);
        
        node1->parent = node2;
        node2->parent = node0;
        if (node3) node3->parent = node1;
        
        node1->myPtr = ptr3;
        node2->myPtr = ptr1;
        if (node3) node3->myPtr = ptr2;
        
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
