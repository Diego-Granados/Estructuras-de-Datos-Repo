### Estructura de datos: Caso 3
# Diego Granados Retana
# 13 de setiembre


## Problema 1:

Se necesita establecer un orden de precedencia para ver cuáles expresiones en la operación se evalúan primero. En nuestro caso, las operaciones de mayor precedencia son *, /, %, y las de menor precedencia son + y -. En la pila se van a almacenar los operadores y la operación en postfijo se va a almacenar en un string. Se inserta un caracter diferente a los que van a aparecer en la operación, para así evitar que haya un tipo de desbordamiento o problemas de que haya una pila vacía completamente. 

Primero, se recorre caracter por caracter. Si el caracter es un número, lo añade a la string del operando. Si es un (, lo mete en la pila. Si es un ), saca todo de la pila hasta vaciarla o llegar a un ( y lo añade a la string. Si es un operador, revisa la precedencia de este. Si es menor o igual a la precedencia del caracter adentro de la pila, suam todo lo que está adentro de la pila al string y lo saca. Luego, pushea el caracter a la pila. Finalmente, mietras la pila no esté vacía, luego de recorrer la operación original, saca todo lo que tiene en la pila y lo añade a la string.

Después, evalúa la operación. Crea otra pila donde se van a almacenar los operandos. Luego, recorre la operación postfija. Separa los operandos y los mete en la pila. Cuando encuentra un operador, saca los operandos de la pila y realiza la operación. Luego, pone el resultado en la pila para que sea un operando de la siguiente operación.

```

int precedence(char character){
    if (character == '*' or character == '/' or character == '%'){ 
        return 2;
    }
    if (character == '+' or character == '-'){ 
        return 1;
    }
    return 0;
}

int main(){

    Stack<char> pila;

    string operation = "(((909+45)*2)-1500)-(72+96/8)"; 

    string postfix = ""; 

    pila.push('#'); // Se pone un carácter different para evitar que haya underflow.

    for (int indice = 0; indice < size(operation) ; indice++){
        if (operation[indice] >= '0' && operation[indice] <= '9'){ 
            postfix += operation[indice];
            if (operation[indice+1] < '0'){ 
                postfix += ' ';
            }
        } else if (operation[indice] == '('){ 
            pila.push('(');
        } else if (operation[indice] == ')'){
            while (pila.top() != '#' && pila.top() != '('){
                postfix += pila.top();   
                postfix += ' ';      
                pila.pop(); // se popea de la pila.
            }
            pila.pop(); 
        } else { 
            while (pila.top() != '#' && precedence(operation[indice]) <= precedence(pila.top())){ 
                postfix += pila.top();
                postfix += ' ';
                pila.pop(); 
            }
            
            pila.push(operation[indice]);
        }
    }

    while (pila.top() != '#'){
        postfix += pila.top();
        pila.pop();
    }

    cout << postfix << endl;

    Stack<string> pilaOp;
    string operando = ""; 
    for (char element : postfix) {
        if (element >= '0' && element <= '9'){
            operando += element; 
        } else if (element == ' '){
            if (operando != ""){
                pilaOp.push(operando);  
            }
            operando = ""; 
        } else { 
            stringstream operandos; 
            int op1;
            operandos << pilaOp.top();
            operandos >> op1;
            pilaOp.pop();
            int op2;
            stringstream operandos2;

            operandos2 << pilaOp.top();
            operandos2 >> op2;
            pilaOp.pop();
            if (element == '+'){      
                pilaOp.push(to_string(op2 + op1)); 
            }
            if (element == '-'){
                pilaOp.push(to_string(op2 - op1));
            }
            if (element == '*'){                
                pilaOp.push(to_string(op2 * op1));
            }
            if (element == '/'){                
                pilaOp.push(to_string(op2 / op1));
            }
            if (element == '%'){                
                pilaOp.push(to_string(op1 % op2));
            }
        }
    }
    cout << pilaOp.top() << endl; // imprime el resultado
}
```

## Problema 2:

Para este problema, yo definí la siguiente cola. Tiene dos pilas. En la primera se van a almacenar los elementos que meto cuando les hago enqueue y en la segunda los elementos que se van a sacar cuando hago dequeue. Para el enqueue, verifico que la pila 1 esté vacía. Si lo está, lo mete a la pila. Modifico los punteros al frente de la pila y al final de la pila para luego usarlos en las funciones que despliegan los datos. En la función de dequeue, reviso si las dos pilas no están vacías. Si no, reviso si la pila 2 está vacía. Esto es porque si no estuviera vacía y le paso los elementos de la pila 1 a la 2, quedarían en un orden totalmente equivocado. Para sacar los elementos de la cola, tengo que técnicamente darle vuelta a la pila 1, lo cual se logra pasando todos los elementos a la pila 2. Luego, saca el último elemento de la pila 2 para así haber realizado un dequeue.

```
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
```

## Problema 3

Para este problema, diseñé dos posibles soluciones, aunque muy parecidas. La primera es utilizando un método en el archivo principal y la segunda es utilizando un cola de prioridad. Hay una cantidad aleatoria de pists y de vuelos. Los vuelos se van insertando uno a uno a cada pista, primero en la primera, después en la segunda, y así van sucesivamente.

Primero, añado los aviones con la función hecha en el quiz. Después, hago las colas. En la primera solución, obtengo la lista la cola, y de también saco los nodos y los vuelos que pertenecen a la lista de vuelos. Si el vuelo está vacío, lo mete de primero. Si el tiempo de salida del primer vuelo es superior, el nuevo vuelo es insertado primero. Si es igual, es insertado de segundo. Si es inferior, el nuevo vuelo es añadido más adelante. Se busca hasta se encuentre la posición correcta. Luego de insertarlo, se sigue con el siguiente vuelo.

```
// Esta función añade todos los vuelos a las pistas
void addFlights(List<Flight> * vuelos, List<Queue<Flight>> * pistas, int cantidadPistas){
    Node<Flight> * vueloNode = vuelos->getFirst(); // obtiene el nodo del primer vuelo
    for (int indice = 0; indice < vuelos->getSize(); indice++){ // recorre la lista de vuelos}
        
        Flight * vuelo = vueloNode->getData(); // Obtiene el vuelo en sí
        int pistaNum = indice % cantidadPistas; // obtiene le índice de la pista
        Queue<Flight> * pista = pistas->find(pistaNum);
        if (pista->isEmpty()){ // si la pista está vacía, añade el vuelo simplemente
            vueloNode = vueloNode->getNext();
            pista->enqueue(vuelo,0);            
            continue;
        }

        // revisa si el tiempo de salida del vuelo es mayor al primero de la pista.
        if (vuelo->getIntTimeValue() > pista->front()->getIntTimeValue()){ // Si es mayor, necesita añadirlo en el medio o al final
            Node<Flight> * searchPosition = pista->getListFirst(); // obtiene el primer nodo de la lista de la pista
            int j = 0; // esta variable se usa como índice en la lista
            while (searchPosition != nullptr){ // mientras el nodo no llegue al final
                if (vuelo->getIntTimeValue() < searchPosition->getData()->getIntTimeValue()){ // si el tiempo de salida del vuelo es menor al del nodo actual,
                    pista->getList()->insert(j, vuelo,0); // se inserta en la lista
                    break; // se rompe el ciclo
                } else { //si no, se sigue recorriendo la lista
                    j++;
                    searchPosition = searchPosition->getNext();
                }  
            } 
            if (searchPosition == nullptr){ // si llegó al final,
                pista->enqueue(vuelo,0); // añade el vuelo a la cola simplemente
            }
        } else if (vuelo->getIntTimeValue() == pista->front()->getIntTimeValue()){ // si el tiempo de salida es igual al vuelo del frente, 
            pista->getList()->insert(1, vuelo,0); // inserta el vuelo en la segunda posición
        } else if (vuelo->getIntTimeValue() < pista->front()->getIntTimeValue()){ // si el tiempo de salida es menor, lo añade al principio
            pista->getList()->insert(0, vuelo,0);
        }
        vueloNode = vueloNode->getNext();
    }
}
```

Esta función es la que se utiliza para recorrer la lista de vuelos y la de pistas.

```
void enqueueFlights(List<Flight> * vuelos, List<Queue<Flight>> * pistas, int cantidadPistas){
    Node<Flight> * vueloNode = vuelos->getFirst(); // obtiene el nodo del primer vuelo
    for (int indice = 0; indice < vuelos->getSize(); indice++){ // recorre la lista de vuelos}
        
        Flight * vuelo = vueloNode->getData(); // Obtiene el vuelo en sí
        int pistaNum = indice % cantidadPistas; // obtiene le índice de la pista
        Queue<Flight> * pista = pistas->find(pistaNum);
        pista->priorityEnqueue(vuelo, vuelo->getIntTimeValue());
        vueloNode = vueloNode->getNext();

        
    }
}
```

Esta es la función de la cola de prioridad que se implementó. Es en esencia igual a la función addFlights, nada más que está implementada directamente en el enqueue de la cola.
```
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
```

En los resultados se pueden observar cómo los aviones salen en el orden correcto y si hay dos que tienen la misma hora de salida, salen por diferentes pistas.

