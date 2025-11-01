#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

template<class T>
class LinkedList{ public:
    LinkedList<T>(){
        head = nullptr;
    };
    Node<T>* head;

    void pushBack (T value);
    void insert(int index, T value);

    void erase(int pos);
    void clear();

    void print();

    Node<T>* at(int pos);
    int size();
};

template<class T>
    void LinkedList<T>::pushBack(T value){
    Node<T>* newNode = new Node<T>(value);
    if(head == nullptr){
        head = newNode;
        return;
    }

    Node<T>* it = head;
    while(it->next != nullptr){
        it = it->next;
    }
    it->next = newNode;
    return;
}

template<class T>
    void LinkedList<T>::insert(int index, T value){
    if(index > size() - 1 || size() == 0){
        return;
    }
    Node<T>* pushNode = at(index);
    pushNode->value = value;
}

template<class T>
void LinkedList<T>::print(){
    if(size() == 0){
        std::cout << "No elements in list" << std::endl;
        return;
    }
    for(int i = 0; i < (int) size(); i++){
        std::cout << i << ": " << at(i)->value << std::endl;
    }
}

template<class T>
int LinkedList<T>::size(){
    if(head == nullptr){
        return 0;
    }

    int index = 0;
    Node<T>* it = head;
    while(it != nullptr){
        it = it->next;
        index++;
    }
    return index;
}

template<class T>
    void  LinkedList<T>::clear(){
    int l = size() - 1;

    while(l != -1){
        delete at(l);
        l--;
    }

    head = nullptr;


}


template<class T>
    void LinkedList<T>::erase(int pos){
    if(size() == 0 || pos < 0 || pos >= size() ){
        return;
    }
    if(pos == 0){
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node<T>* before = at(pos - 1);
    Node<T>* toDelete = before->next;
    before->next = toDelete->next;
    delete toDelete;

}

template<class T>
    Node<T>* LinkedList<T>::at(int pos){
        if(pos == 0){
           return head;
        }

        int index = 1;
        Node<T>* tmp = head->next;
        while(tmp != nullptr){
            if(pos == index){
                return tmp;
            }
            tmp = tmp->next;
            index++;
        }
        return nullptr;
    }


#endif // LINKEDLIST_H
