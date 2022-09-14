#include "stack.h"
#include "queue.h"
#include "generic/List.h"
#include <vector>
#include <string>

using namespace std;
/*
template <class T>

class pregunta1 {
    private:
        List<Stack<T>> listapilas;
    public:
        pregunta1(){
            listapilas = new List();
        }
        processCell(Queue<T> pQueue){
            
            Stack<T> * pila = new Stack();
            while (!pQueue.isEmpty()){
                pila->push(pQueue.dequeue());
            }
            this->listapilas.add(pila);
            return listapilas;
        }
};
*/
enum Category { BASE = 0, CENTER = 1, TOP  = 2};

struct Ingrediente {
    Category type;
    string name;
};

Stack<Ingrediente>* createBurguer(vector<Ingrediente> pIngredientes) {
    Stack <Ingrediente> pila;
    for (int i = 0; i < 3; i++){
        Category tipo;
        switch (i){
            case 0:
                tipo = BASE;
                break;
            case 1:
                tipo = CENTER;
                break;
            case 2:
                tipo = TOP;
                break;
        }
        for (Ingrediente elemento : pIngredientes){
            cout << elemento.name << endl;
            cout << tipo << endl;
            if (elemento.type == tipo){
                
                pila.push(&elemento);
            }
        }
    }
    while (!pila.isEmpty()){
        cout << "Ingrediente: " << (pila.pop())->name << endl;
    }
   
}


int main(){
    Ingrediente panbase;
    panbase.type = BASE;
    panbase.name = "Pan base";
    Ingrediente carne;
    carne.type = CENTER;
    carne.name = "Carne";
    Ingrediente queso;
    queso.type = CENTER;
    queso.name = "Queso";
    Ingrediente pantop;
    pantop.type = TOP;
    pantop.name = "Pan TOP";
    vector<Ingrediente> Ingredientes = {carne, pantop, queso, panbase};
    createBurguer(Ingredientes);
    
}