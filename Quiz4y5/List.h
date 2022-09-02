#include "Node.h"
#include "eventos/event.h"

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

        void add(T *pData) {
            Node<T> *newNode = new Node<T>(pData);

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
        void insert(int pPosition, T *pData) {
            
            if (pPosition<getSize() && first!=NULL) {
                Node<T> *newNodo = new Node<T>(pData);

                T* result = find(pPosition);
                
                newNodo->setNext(searchPosition);
                if (searchPosition->getPrev()!=NULL) {
                    searchPosition->getPrev()->setNext(newNodo);
                    newNodo->setPrev(searchPosition->getPrev()); 
                    searchPosition->setPrev(newNodo);
                    
                } else {
                    this->first = newNodo;
                }
                
                quantity++;
            } else {
                add(pData);
            }
        }

        bool remove(int pPosition) {
            bool result = false;
            if (first!=NULL && pPosition<getSize()) {
                Node<T> *search = first;
                if (pPosition!=0) {
                    T* data = find(pPosition);

                    if (searchPosition!=last) {
                        searchPosition->getPrev()->setNext(searchPosition->getNext());
                        searchPosition->getNext()->setPrev(searchPosition->getPrev());
                        searchPosition->setNext(NULL);
                    }
                    else {
                        last = searchPosition->getPrev();
                        last->setNext(NULL);
                    }              
                    
                    searchPosition->setPrev(NULL);
                    delete searchPosition;
                } else {
                    first = first->getNext();
                    first->setPrev(NULL);
                  //  search->setNext(NULL);
                    delete search;
                }
                quantity--;
            }
            return result;
        } 
};

#endif