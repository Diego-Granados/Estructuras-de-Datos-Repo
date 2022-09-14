#include "Node.h"

#ifndef LIST 

#define LIST 1

// 2. ajustar a que esta lista sea doblemente enlazada, cambia el add, find, insert y el remove
template <class T>
class List {
    private:
        Node<T> *first;
        Node<T> *last;
        int quantity;
        bool empty;
        Node<T> *searchPosition = NULL;

    public:
        List() {
            first = NULL;
            last = NULL;
            quantity = 0;
            empty = true;
        }

        void add(T *pData, int pPriority) {
            Node<T> *newNode = new Node<T>(pData, pPriority);

            if (quantity>0) {
                this->last->setNext(newNode);
                newNode->setPrev(this->last);
            } else {
                this->first = newNode;
            }
            this->last = newNode;

            empty = false;
            quantity++;
        }

        Node<T>* getFirst() {
            return this->first;
        }

        int getSize() {
            return quantity;
        }

        bool isEmpty() {
            return !quantity;
        }

        T* find(int pPosition) {
            T* result = NULL;
            searchPosition = this->first;

            if (pPosition<getSize()) {
                while(pPosition>0) {
                    searchPosition = searchPosition->getNext();
                    pPosition--;
                }
                result = searchPosition->getData();
            }

            return result;
        }

        // es que si el position es mayor a la cantidad, entonces inserto al final
        void insert(int pPosition, T *pData, int pPriority) {
            
            if (pPosition<getSize() && first!=NULL) {
                Node<T> *newNodo = new Node<T>(pData, pPriority);

                T* result = find(pPosition);
                
                newNodo->setNext(searchPosition);
                if (searchPosition->getPrev()!=NULL) {
                    searchPosition->getPrev()->setNext(newNodo);
                    newNodo->setPrev(searchPosition->getPrev()); 
                    searchPosition->setPrev(newNodo);
                    
                } else {
                    this->first->setPrev(newNodo);
                    this->first = newNodo;
                }
                
                quantity++;
            } else {
                add(pData,0);
            }
        }

        T* remove(int pPosition) {
            T* result = NULL;
            if (first!=NULL && pPosition<getSize()) {
                Node<T> *search = first;
                if (pPosition!=0) {
                    result = find(pPosition);

                    searchPosition->getPrev()->setNext(searchPosition->getNext());

                    if (searchPosition==last) {
                        last = searchPosition->getPrev();
                    }
                    searchPosition->setNext(NULL);
                } else {
                    first = first->getNext();
                    search->setNext(NULL);
                    result = search->getData();
                }
                quantity--;
                if (quantity == 0){
                    this->empty = true;
                }
            }
            return result;
        }
        
        void PrintList(){ // Esta función imprime la lista
            Node<T> * printPtr = this->first;
            cout << "Cantidad: " << quantity << endl;
            while(printPtr != nullptr){
                cout << "Nodo: "<< printPtr << endl;
                cout << "Número: " << printPtr->getData()->getFlightNum() << endl;
                cout << "Time: " <<  printPtr->getData()->getIntTimeValue() << endl << endl;
                printPtr = printPtr->getNext();
            }
        }
};

#endif