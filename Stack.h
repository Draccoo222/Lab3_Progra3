#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 200

#include <iostream>
using std::cout;

template <typename T>
class Stack {
private:
    int size = 0;
    T data[STACK_SIZE];

public:
    Stack<T>(){};



    void push(T newValue); // inserta en el tope
    T pop(); // eliminar y retornar

    bool empty();
};

template <typename T>
void Stack<T>::push(T newValue) {
    data[size] = newValue;
    size ++;
    return;
}

template <typename T>
T Stack<T>::pop() {
    if(size == 0) return -1;
    T toReturn =  data[size - 1];
    size = size - 1;
    return toReturn;
}


template <typename T>
bool Stack<T>::empty() {
    return size == 0;
}

#endif // STACK_H
