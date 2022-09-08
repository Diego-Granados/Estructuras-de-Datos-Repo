#ifndef NODE 

#define NODE 1

using namespace std;

template <class T>

class Node {
        
    
    public:
        T data;
        Node *next;
        Node *prev;
        Node() {
            prev = nullptr;
            next = nullptr;
        }

        Node(T *pData) {
            this->data = *pData;
            next = nullptr;
            prev = nullptr;
        }

        T getData() {
             return data;
        }

        T* getDataPtr() {
             return &data;
        }

        Node* getNext() {
            return next;
        }

        Node* getPrev() {
            return prev;
        }

        void setNext(Node *pValue) {
            this->next = pValue;
        }
        void setPrev(Node *pValue){
            this->prev = pValue;
        }
};

#endif