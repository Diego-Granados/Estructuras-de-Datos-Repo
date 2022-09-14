#include <iostream>

#ifndef NODE 

#define NODE 1

using namespace std;

// 1. pasar este nodo a doblemente enlazado
template <class T>
class Node {
    private:
        T *data;
        Node *next;
        Node *prev;
        int priority;
    
    public:
        Node() {
            data = NULL;
            next = NULL;
            priority = 0;
            prev = NULL;
        }

        Node(T *pData, int pPriority) {
            this->data = pData;
            next = NULL;
            prev = NULL;
            this->priority = pPriority;

        }


        void setPriority(int data){
            this->priority = data;
        }

        T* getData() {
            return data;
        }

        Node* getNext() {
            return next;
        }

        Node* getPrev(){
            return prev;
        }

        int getPriority(){
            return priority;
        }

        void setNext(Node *pValue) {
            this->next = pValue;
        }

        void setPrev(Node *pValue){
            this->prev = pValue;
        }
};

#endif