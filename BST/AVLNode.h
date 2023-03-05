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
    
    AVLNode() = default;
    
    explicit AVLNode(T value_, Node<T> *parent_ = nullptr);
    
    Node<T> *add_child(T value_, int direction);
    
    int get_height() const;
    
    int balance_factor();
    
    void update_height();
    
    void insert_rebalance(unique_ptr<Node<T>> *root);
    
    void erase_rebalance(unique_ptr<Node<T>> *root);
    
};


#endif //DATASTRUCTURES_AVLNODE_H
