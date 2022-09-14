#include <iostream>
#include <string>
#include "queue.cpp"


int main(){
    Queue<int> cola;

    cout << "Enqueue: " << endl;
    for (int i = 0; i < 10; i++){
        cola.enqueue(i);
        cout << cola.getRear() << endl;
    }
    
    cout << endl << "Contenidos de la cola desde el final hasta el principio: " << endl;
    cola.PrintQueue();
    cout << endl<< "Dequeue: " << endl;
    while (!cola.empty){
        cout << cola.getFront() << endl;
        cola.dequeue();
    }
}