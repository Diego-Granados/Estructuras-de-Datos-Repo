#include "Flight.h"
#include "generic/List.h"
#include <stdlib.h>
#include "generic/Node.h"
#include <ctime>
#include "queue.h"

#define CANT_PASAJEROS 142

// Esta función crea los vuelos y llena la lista de vuelos
void fillFlights(List<Flight> * pFlights, int pCantidad, int pStartHour, int pEndHour, string pAirlines[]) {
    for (int i = 1; i <= pCantidad ; i++){    

        int hora = rand() % (pEndHour-pStartHour) + pStartHour; // obtiene la hora cuando va a salir el avión
        int minu = rand() % 42; // Obtiene los minutos, tiene un rango de 1 a 42 para no tener que tomar en cuenta el caso de que sume más de 60.
        int atraso = rand() % 17; // Obtiene el atraso.
        int PassengerNum = rand() % CANT_PASAJEROS; // obtiene la cantidad de pasajeros abordo del avión
        int airlineIndex = rand() % 7; // obtiene una aerolínea al azar
    
        Flight * vuelo = new Flight(hora, minu,pAirlines[airlineIndex], i, PassengerNum, atraso); // crea el objeto del avión
        
        cout << "Vuelo: " << vuelo->getAirline() << ":"<<vuelo->getFlightNum() << endl;
        cout << " Sale el: " << vuelo->flightTimeString();
        cout << "El entero es: " << vuelo->getIntTimeValue() << endl;
        cout << " Cantidad de pasajeros: " << PassengerNum << endl << endl; 

        pFlights->add(vuelo,0); // lo añade a la lista
    }
} 


// Esta función crea las pistas de acuerdo con un número aleatorio.
void createQueues(int cantidad, List<Queue<Flight>> * colas){
    for (int i = 0; i < cantidad; i++){
        Queue<Flight> * cola = new Queue<Flight>();
        colas->add(cola,0);
    }
}

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


// Esta función imprime los contenidos de las colas.
void printQueuesList(int cantidad, List<Queue<Flight>> * pistas){
    for (int i = 0; i < cantidad; i++){
        cout << "Cola: " << i << endl;
        pistas->find(i)->getList()->PrintList();
    }
}

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

// Esta función despega los vuelos
void takeoffFlights(time_t currentTime, List<Queue<Flight>> * pistas, int cantidadVuelos, int cantidadPistas){
    while (cantidadVuelos != 0){ // mientras sigan habiendo vuelos
        for (int j = 0; j < cantidadPistas; j++){ // recorre todas las pistas.
            if (pistas->find(j)->isEmpty()){ // si la pista está vacía, se la salta
                continue;
            }
            if (pistas->find(j)->front()->getIntTimeValue() <= currentTime){ // si el tiempo de salida del primer avión es menor que el tiempo de salida, 
                Flight * vuelo = pistas->find(j)->dequeue(); // lo saca de la cola
                cantidadVuelos--; // decrementa la cantidad de vuelos
                char* currentTimeString = ctime(&currentTime); // obtiene un string de la fecha actual
                
                // Despliega mensajes de confirmación de la salida
                cout << "El vuelo " << vuelo->getAirline() << ":" << vuelo->getFlightNum() << endl;
                cout << "Salió a las: " << currentTimeString << "De la pista: " << j << endl;  
                cout << "Salía a las: " << vuelo->flightTimeString() << endl; 
                
            }
        }
        currentTime += 60; // le suma un minuto al tiempo actual.
    }
}


int main() {
    srand(time(NULL)); // Se inicializa el seed del random, para que siempre sean valores diferentes cada vez que se ejecuta
    List<Flight> vuelos; // crea la lista de vuelos
    time_t currentTime = time(0); // obtiene la hora actual
    tm * now = localtime(&currentTime); // Obtiene la hora actual en la estructura
    string airlines[7] = {"United","British","Copa","American", "Emirates", "Jet Blue", "Avianca"}; // es un arreglo con todas las aerolíneas disponibles.
    
    int cantVuels =  rand() % 100 + 1; // Obtiene un número del 1 al 100 de vuelos 
    int cantPistas = rand() % 4 + 2;

    int StartHour = rand() % (24 - now->tm_hour) + now->tm_hour; // Obtiene la hora mínima de cuando pueden empezar los vuelos. Esta es desde la hora actual a hasta las 24 horas.
    int maxhour = rand() % (24 - StartHour) + 1; // Obtiene un valor para sumarle a la hora donde terminan los vuelos
    int EndHour = StartHour + maxhour; // Obtiene la hora hasta donde van a llegar los vuelos.

    cout << "Cantidad de pistas: " << cantPistas << endl;
    cout << "Cantidad de vuelos: " << cantVuels << endl; 
    cout << "Start Hour: " << StartHour << " End Hour: " << EndHour << endl << endl;

    cout << "Vuelos: " << endl;

    fillFlights(&vuelos, cantVuels, StartHour, EndHour,airlines); // Llama a la función
    
    List<Queue<Flight>> pistas;

    createQueues(cantPistas, &pistas);  

    addFlights(&vuelos, &pistas,cantPistas);

    List<Queue<Flight>> pistas2;

    createQueues(cantPistas, &pistas2);  

    enqueueFlights(&vuelos, &pistas2,cantPistas);
    
// La función de printqueues se usa para revisar si todas las pistas tienen la cantidad correcta de aviones.
//    cout << endl; 
 //   printQueuesList(cantPistas, &pistas);

    cout << "Salidas 1: " << endl;
    takeoffFlights(currentTime, &pistas, cantVuels, cantPistas);

    cout << "Salidas 2: " << endl;
    takeoffFlights(currentTime, &pistas2, cantVuels, cantPistas);
    
}