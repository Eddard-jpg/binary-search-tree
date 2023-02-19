//
// Created by Eddard on 2023-02-18.
//

#ifndef DATASTRUCTURES_AVLNODE_H
#define DATASTRUCTURES_AVLNODE_H

#include "Node.h"

template<typename T>
class AVLNode : public Node<T> {
public:
    int height;
    
    explicit AVLNode(T value_, Node<T> *parent_ = nullptr);
    
    // Add child node, direction = 0 for left, 1 for right.
    Node<T> *add_child(T value_, int direction);
    
    int get_height();
    
    int balance_factor();
    
    void update_height();
    
    void rotate(int direction, unique_ptr<Node<T>> *root);
    
    void rebalance(unique_ptr<Node<T>> *root);
    
    ~AVLNode();
    
};


#endif //DATASTRUCTURES_AVLNODE_H
