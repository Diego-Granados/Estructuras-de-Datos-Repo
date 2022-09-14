#include "Flight.h"
#include "generic/List.h"
#include <stdlib.h>
#include <ctime>

#define CANT_PASAJEROS 142

// debe llenar una lista de pCantidad vuelos aleatorios cuya hora y minutos de partida esten entre pStartHour y pEndHour
// tomando en cuenta las restricciones de los minutos de salida segun el ejercicio 3 del caso #3
void fillFlights(List<Flight> * pFlights, int pCantidad, int pStartHour, int pEndHour, string pAirlines[]) {
    for (int i = 1; i <= pCantidad ; i++){    

        int hora = rand() % (pEndHour-pStartHour) + pStartHour; // obtiene la hora cuando va a salir el avión
        int minu = rand() % 42; // Obtiene los minutos, tiene un rango de 1 a 42 para no tener que tomar en cuenta el caso de que sume más de 60.
        int atraso = rand() % 17; // Obtiene el atraso.
        int PassengerNum = rand() % CANT_PASAJEROS; // obtiene la cantidad de pasajeros abordo del avión
        int airlineIndex = rand() % 7; // obtiene una aerolínea al azar
        cout << "Hora: "<< hora << " Minutos: " << minu << " Atraso: " << atraso << " Cantidad de pasajeros: " << PassengerNum << endl; 
    
        Flight vuelo(hora, minu,pAirlines[airlineIndex], i, PassengerNum, atraso); // crea el objeto del avión
        
        cout << "Vuelo: " << vuelo.getAirline() << ":"<<vuelo.getFlightNum() << " Sale el: " << vuelo.flightTimeString() << " y el entero es: " << vuelo.getIntTimeValue() << endl << endl;

        pFlights->add(&vuelo); // lo añade a la lista
    }
} 


int main() {
    srand(time(NULL)); // Se inicializa el seed del random, para que siempre sean valores diferentes cada vez que se ejecuta
    List<Flight> vuelos; // crea la lista de vuelos
    time_t currentTime = time(0); // obtiene la hora actual
    tm * now = localtime(&currentTime); // Obtiene la hora actual en la estructura
    string airlines[7] = {"United","British","Copa","American", "Emirates", "Jet Blue", "Avianca"}; // es un arreglo con todas las aerolíneas disponibles.
    
    int cantVuels = rand() % 100 + 1; // Obtiene un número del 1 al 100 de vuelos 
    
    int StartHour = rand() % (24 - now->tm_hour) + now->tm_hour; // Obtiene la hora mínima de cuando pueden empezar los vuelos. Esta es desde la hora actual a hasta las 24 horas.
    int maxhour = rand() % (24 - StartHour) + 1; // Obtiene un valor para sumarle a la hora donde terminan los vuelos
    int EndHour = StartHour + maxhour; // Obtiene la hora hasta donde van a llegar los vuelos.
    cout << "Cantidad de vuelos: " << cantVuels << endl; 
    cout << "Start Hour: " << StartHour << " End Hour: " << EndHour << endl;

    for (int j = 0; j < 5; j++){
        char* currentTimeString = ctime(&currentTime);
        cout << currentTimeString << endl;
        currentTime += 60;
    }
    

    
   // fillFlights(&vuelos, cantVuels, StartHour, EndHour,airlines); // Llama a la función
}