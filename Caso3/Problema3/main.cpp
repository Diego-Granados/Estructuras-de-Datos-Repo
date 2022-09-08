#include <iostream>
#include <string>
#include "queue.cpp"

Queue<int> cola;

int main(){
    cout << "Enqueue: " << endl;
    for (int i = 0; i < 10; i++){
        cola.enqueue(i);
        cout << cola.getRear() << endl;
    }
    
    cola.PrintQueue();
    cout << "Dequeue: " << endl;
    while (!cola.empty){
        cout << "cola " << cola.getFront() << endl;
        cola.dequeue();
    }
}