#include "generic/List.h"

#ifndef QUEUE

#define QUEUE 1
 
template <class T>
class Queue {
    private:
        List<T>* queueList;
    
    public:
        Queue() {
            queueList = NULL;
            queueList = new List<T>();
        }

        // agregar al final
        void enqueue(T* pValue, int pPriority) {
            queueList->add(pValue, pPriority);
        }

        void priorityEnqueue(T * pData, int pPriority){      
            
            if (this->isEmpty()){ // si la pista está vacía, añade el vuelo simplemente
                this->enqueue(pData,pPriority);            
                return;
            }

            // revisa si el tiempo de salida del vuelo es mayor al primero de la pista.
            if (pPriority > this->queueList->getFirst()->getPriority()){ // Si es mayor, necesita añadirlo en el medio o al final
                Node<T> * searchPosition = this->queueList->getFirst(); // obtiene el primer nodo de la lista de la pista
                int j = 0; // esta variable se usa como índice en la lista
                while (searchPosition != nullptr){ // mientras el nodo no llegue al final
                    if (pPriority < searchPosition->getPriority()){ // si el tiempo de salida del vuelo es menor al del nodo actual,
                        this->queueList->insert(j, pData, pPriority); // se inserta en la lista
                        break; // se rompe el ciclo
                    } else { //si no, se sigue recorriendo la lista
                        j++;
                        searchPosition = searchPosition->getNext();
                    }  
                } 
                if (searchPosition == nullptr){ // si llegó al final,
                    this->enqueue(pData,pPriority); // añade el vuelo a la cola simplemente
                }
            } else if (pPriority == this->queueList->getFirst()->getPriority()){ // si el tiempo de salida es igual al vuelo del frente, 
                this->queueList->insert(1, pData,pPriority); // inserta el vuelo en la segunda posición
            } else if (pPriority < this->queueList->getFirst()->getPriority()){ // si el tiempo de salida es menor, lo añade al principio
                this->queueList->insert(0, pData, pPriority);
            }      
        }

        T* dequeue() {
            T* result = NULL;
            if (!queueList->isEmpty()) {
                result = queueList->remove(0);          
            }
            return result;            
        }

        T* front() {
            T* result = NULL;
            if (!queueList->isEmpty()) {
                result = queueList->find(0);
            }
            return result;
        }

        bool isEmpty() {
            return queueList->isEmpty();
        }

        // esta función obtiene el primero de la lista de aviones
        Node<T> * getListFirst(){
            return this->queueList->getFirst();
        }

        // esta función retorna la lista de vuelos como tal de cada pista.
        List<T> * getList(){
            return this->queueList;
        }
};

#endif


