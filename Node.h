#ifndef NODE_H
#define NODE_H

#include <iostream>

template<class T> struct Node{
    Node<T>(T value){
        next = nullptr;
        this->value = value;
    }
    Node<T>* next;
    T value;
};

#endif // NODE_H


