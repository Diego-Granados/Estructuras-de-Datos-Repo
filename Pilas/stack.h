#include "../generic/List.h"

#ifndef STACK

#define STACK 1

template <class T>

class Stack {
private:
    List<T>* stackList;
public:
    Stack() {
        stackList = new List<T>();
    }

    // agregar al final
    void push(T* pValue) {
        stackList->addAtBegining(pValue);
    }

    T* pop() {
        T* result = NULL;
        if (!stackList->isEmpty()) {
            result = stackList->find(0);
            stackList->remove(0);
        }else{
            cout <<"Error: la pila esta vacia."<< endl;
        }
        return result;
    }

    T* top() {
        T* result = NULL;
        if (!stackList->isEmpty()) {
            result = stackList->find(0);
        }
        return result;
    }

    bool isEmpty() {
        return stackList->isEmpty();
    }

    int size() {
        return stackList->getSize();
    }
};

#endif