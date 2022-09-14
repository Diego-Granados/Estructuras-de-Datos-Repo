#include "node.cpp"
#include <string>
#include <iostream>

using namespace std;

#ifndef STACK 

#define STACK 1

template <class T>
class Stack {
        

    public:
        Node<T> *first;
        int quantity;
        bool empty;

        Stack() {
            first = nullptr;
            quantity = 0;
            empty = true;
        }

        void push(T pData) {
            Node<T> *newNode = new Node<T>(&pData);

            if (quantity>0) {
                newNode->setNext(this->first);
                this->first = newNode;
            } else {
                this->first = newNode;
            }

            empty = false;
            quantity++;
        }

        T top() {
            return (this->first->getData());
        }

        T* topNode() { // para las pilas que tienen nodos como datos, se retorna un puntero al nodo en sí 
            return (this->first->getDataPtr());
        }

        int getQuantity() {
            return quantity;
        }

        void pop(){
            Node<T>* elem = first;
            first = first->getNext();
            quantity--;
            if (quantity == 0){
                empty = true;
            }
            delete elem;
        }

        T find(T pData){
            Node<T> * searchPtr = this->first;
            while (searchPtr != nullptr && searchPtr->getData()->name != pData){
                searchPtr = searchPtr->next;
            }
            if (searchPtr == nullptr){
                return -1;
                cout << "Se terminó la lista" << endl;
            }
            return *(searchPtr->data);
        }

        void PrintStack(){ // esta función imprime todos los contenidos de la pila.
            Node<T> * printPtr = this->first;
            while(printPtr != nullptr){
                cout << printPtr << endl;
                cout << printPtr->getData() << endl;
                printPtr = printPtr-> next;
            }
        }
};
#endif