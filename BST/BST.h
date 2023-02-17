//
// Created by Eddard on 2023-02-17.
//

#ifndef DATASTRUCTURES_BST_H
#define DATASTRUCTURES_BST_H

#include <bits/stdc++.h>

#include <memory>
#include "Node.h"

using namespace std;

class BST {

protected:
    
    unique_ptr<Node> root = nullptr;
    
    bool find(int x, Node *u) {
        if (u == nullptr) return false;
        if (u->value == x) return true;
        if (u->value < x) return find(x, u->rightChild.get());
        return find(x, u->leftChild.get());
    }
    
    void traverse(vector<Node *> &v, Node *u, int mode) const {
        if (u == nullptr) return;
        
        if (mode == 0) v.push_back(u);
        
        traverse(v, u->leftChild.get(), mode);
        
        if (mode == 1) v.push_back(u);
        
        traverse(v, u->rightChild.get(), mode);
        
        if (mode == 2) v.push_back(u);
    }
    
    void getPtrs(vector<unique_ptr<Node>> &v, Node *u) {
        if (u == nullptr) return;
        
        getPtrs(v, u->leftChild.get());
        
        v.push_back(std::move(*u->myPtr));
        
        getPtrs(v, u->rightChild.get());
    }
    
    void balance(vector<unique_ptr<Node>> &sorted, unique_ptr<Node> &myPtr, Node *parent, int l, int r) {
        if (r - l == 0) return;
        
        int mid = (l + r) / 2;
        myPtr = std::move(sorted[mid]);
        myPtr->parent = parent;
        myPtr->myPtr = &myPtr;
        
        balance(sorted, myPtr->leftChild, myPtr.get(), l, mid);
        balance(sorted, myPtr->rightChild, myPtr.get(), mid + 1, r);
    }

public:
    
    void add(int value) {
        if (root == nullptr) {
            root = make_unique<Node>(value);
            root->myPtr = &root;
            return;
        }
        
        Node *current = root.get(), *parent = root.get();
        
        while (current != nullptr) {
            if (value == current->value) return;
            parent = current;
            if (value > current->value) current = current->rightChild.get();
            else current = current->leftChild.get();
        }
        
        if (value > parent->value) parent->addRight(value);
        else parent->addLeft(value);
        
    }
    
    bool find(int x) { return find(x, root.get()); }
    
    // Print all values of the BST, mode = 0 for pre-order traversal, 1 for in-order (default), or 2 for post-order.
    void print(int mode = 1) {
        
        if (mode < 0 || mode > 2) throw invalid_argument("print mode must belong to {0, 1, 2}");
        
        vector<Node *> ptrs;
        traverse(ptrs, root.get(), mode);
        
        for (auto ptr: ptrs) cout << *ptr << " ";
        cout << endl;
        
    }
    
    // Balance the BST manually.
    void balance() {
        vector<unique_ptr<Node>> sorted;
        getPtrs(sorted, root.get());
        balance(sorted, root, nullptr, 0, (int) sorted.size());
    }
    
    ~BST() {
        cout << "BST Destroyed" << endl;
    }
    
};


#endif //DATASTRUCTURES_BST_H
