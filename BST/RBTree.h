//
// Created by Eddard on 2023-02-17.
//

#ifndef DATASTRUCTURES_RBTREE_H
#define DATASTRUCTURES_RBTREE_H

#include "RBNode.h"
#include "BST.h"

template<typename T>
class RBTree : public BST<T> {
public:
    
    Node<T> *insert(T value);
    
    void balance();

protected:
    
    Node<T> *erase(Node<T> *u);
    
};


#endif //DATASTRUCTURES_RBTREE_H
