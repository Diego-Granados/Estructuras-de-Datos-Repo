#include "../Stack/pila.cpp"



#include "../Stack/node.cpp"
#include <string>
#include <iostream>

using namespace std;

#ifndef QUEUE 

#define QUEUE 1

template <class T>
class Queue {
        

    public:
        Node<T> *front;
        Node<T> *rear;
        Stack<Node<T>> pila1;
        Stack<Node<T>> pila2;
        int quantity;
        bool empty;

        Queue() {
            front = nullptr;
            rear = nullptr;
            quantity = 0;
            empty = true;
        }

        void enqueue(T pData) {
            Node<T> *newNode = new Node<T>(&pData);

            if (quantity==0) {
                this->front = newNode;
            }
            newNode->next = this->rear;
            this->rear = newNode;
            
            pila1.push(*newNode);
            empty = false;
            quantity++;
        }

        T getFront() {
            return (this->front->getData());
        }
        T getRear(){
            return (this->rear->getData());
        }

        int getQuantity() {
            return quantity;
        }

        void dequeue(){
            if (pila1.empty && pila2.empty){
                cout << "ERROR: LAS DOS PILAS ESTÁN VACÍAS";
                this->empty = true;
                return;
            }
            if (pila2.empty){
                while (!pila1.empty){
                    if (pila1.getQuantity() == 2){
                        cout << (pila1.topNode())->data << endl;
                        this->front = (pila1.topNode());
                    }
                    pila2.push(pila1.top());
                    pila1.pop();
                }
            }
            
            pila2.pop();   
            while (!pila2.empty){
                pila1.push(pila2.top());
                pila2.pop();
            } 
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

        void PrintQueue(){
            Node<T> * printPtr = this->rear;
            while(printPtr != nullptr){
                cout << printPtr << endl;
                cout << printPtr->getData() << endl;
                printPtr = printPtr-> next;
            }
        }
};
#endif