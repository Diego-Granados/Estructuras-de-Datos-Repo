// Diego Granados
// Estructuras de datos
// 8 de setiembre
// Quiz 6

#include <iostream>
#include <string>
#include <ctime>


using namespace std;

// Quiz #6
// 1. Utilizando esta clase agregue los atributos del vuelo: aerolinea, numero de vuelo, cantidad de pasajeros
// 2. Complete el constructor de la clase, de tal forma que se pueda modificar el flightTime para una hora y minutos específicos
// 3. Implementar alguna forma de convertir el time a un número entero de tal forma que entre menor la hora menor el número, eso en getIntTimeValue()
// 4. En el test.cpp, implementar la función fillFlights()
// fecha de entrega: jueves 8 de setiembre antes de las 10pm
// entrega al asistente al correo: kevinqj.2002@gmail.com
// subject: estructuras de datos - quiz #6
// adjuntan el archivo test.cpp y Flight.h

class Flight {

    private: 
        time_t flightTime; // Almacena el número entero de la hora de salida
        string aerolinea; // la compañía de aerolínea
        int numeroVuelo; // El número de vuelo
        int cantPasajeros; // La cantidad de pasajeros
        tm * leaveTime; // Esta estructura se usa para modificar la fecha de salida con base en los parámetros y para desplegarla en forma de texto

    public: 
        Flight(){}
        Flight(int pHour, int pMinutes, string pAirline, int pFlightNum, int pNumPassengers, int pDelay) {
            flightTime = time(0); // obtiene la fecha actual
            this->leaveTime = localtime(&flightTime); // cambia el valor del leaveTime a la fecha actual para que sea más fácil actualizarla

            this->aerolinea = pAirline; // cambia el valor
            this->numeroVuelo = pFlightNum;
            this->cantPasajeros = pNumPassengers;
            pMinutes += pDelay; // suma el atraso a los minutos 
            this->leaveTime->tm_hour = pHour; // cambia la hora
            this->leaveTime->tm_min = pMinutes; // Cambia los minutos
            this->leaveTime->tm_sec = 0; // Pone los minutos en 0 porque no interesan mucho

            flightTime = mktime(this->leaveTime); // Vuelve a convertir la fecha al entero
        }

        char* flightTimeString() {
            char* result = ctime(&(this->flightTime)); // Obtiene un texto con la fecha
            return result; // devuelve el resultado
        }

        int getIntTimeValue() {
            return flightTime; // Devuelev el entero
        }
        
        int getFlightNum(){
            return this->numeroVuelo; // retorna el número de vuelo.
        }            
        string getAirline(){
            return this->aerolinea; // retorna la aerolínea
        }
};
