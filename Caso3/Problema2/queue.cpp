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
        Node<T> *front; // puntero al principio de la cola
        Node<T> *rear; // puntero al final de la cola.
        Stack<Node<T>> * pila1; // puntero a la pila 1
        Stack<Node<T>>  *pila2; // puntero a la pila 2
        int quantity;
        bool empty;

        Queue() {
            pila1 = new Stack<Node<T>>();
            pila2 = new Stack<Node<T>>();
            front = nullptr;
            rear = nullptr;
            quantity = 0;
            empty = true;
        }

        void enqueue(T pData) {
            Node<T> *newNode = new Node<T>(&pData); // Crea un nodo nuevo

            if (quantity==0) { // Si la cola está vacía,
                this->front = newNode; // el principio de la cola es el nodo.
            }
            newNode->next = this->rear; // El siguiente del nodo es el último actual
            if(this->rear != nullptr){
                this->rear->setPrev(newNode);
            }
            this->rear = newNode; // el nuevo nodo siempre va a ser el final de la cola
            
            
            pila1->push(*newNode); // se añade el nodo a la pila
            empty = false; // la lista ya no está vacía
            quantity++;
        }

        T getFront() {
            return (this->front->getData()); // retorna el principio de la cola
        }
        T getRear(){
            return (this->rear->getData()); // Retorna el final de la cola
        }

        int getQuantity() { // Retorna la cantidad de la cola
            return quantity;
        }

        void dequeue(){ // 
            if (pila1->empty && pila2->empty){ // si las dos pilas están vacías, no hay nada que popear
                cout << "ERROR: LAS DOS PILAS ESTÁN VACÍAS";
                this->empty = true; // se cambia el valor de empty de la cola
                return;
            }
            if (pila2->empty){ // si la pila 2 está empty, 
                while (!pila1->empty){ // mientras haya algo en la pila 1, 
                    pila2->push(pila1->top()); // se pushea el elemento a la pila 2
                    pila1->pop(); // se popea de la pila 1
                }
            }
            this->front = this->front->getPrev(); // se cambia el front de la cola
            pila2->pop();   // se popea el útimo element o de la pila 2, para sacarlo de la cola
            quantity--;
            if (!quantity){
                this->empty = true;
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

        void PrintQueue(){ // Esta función imprime todo lo que hay en la cola.
            Node<T> * printPtr = this->rear;
            while(printPtr != nullptr){
                cout << printPtr << endl;
                cout << printPtr->getData() << endl;
                printPtr = printPtr-> next;
            }
        }
};
#endif