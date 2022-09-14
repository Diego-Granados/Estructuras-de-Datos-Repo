#include <iostream>
#include <string>
#include "../Stack/pila.cpp"
#include <sstream>



// Se necesita establecer un orden de precedencia para ver cuáles expresiones se evalúan primero.
int precedence(char character){
    if (character == '*' or character == '/' or character == '%'){ // En nuestro caso, las operaciones de mayor precedencia son *, /, %
        return 2;
    }
    if (character == '+' or character == '-'){ // los otros con menor precedencia son + y -
        return 1;
    }
    return 0;
}

int main(){

    Stack<char> pila; // en esta pila se van a almacenar los operadores

    string operation = "(((909+45)*2)-1500)-(72+96/8)"; // Esta es la operación que se va a convertir.

    string postfix = ""; // Aquí se va a almacenar la operación convertida

    pila.push('#'); // Se pone un carácter different para evitar que haya underflow.

    for (int indice = 0; indice < size(operation) ; indice++){
        if (operation[indice] >= '0' && operation[indice] <= '9'){ // Si el caracter es un número, se añade al operando
            postfix += operation[indice];
            if (operation[indice+1] < '0'){ // si el próximo caracter no es un número, se añade un espacio para separ operandos
                postfix += ' ';
            }
        } else if (operation[indice] == '('){ // si el caracter es unh (, se pushea
            pila.push('(');
        } else if (operation[indice] == ')'){ // Si el caracter es un ), se popea todo hasta sacar todo de la pila o llegar a un (
            while (pila.top() != '#' && pila.top() != '('){
                postfix += pila.top();   // se le suma el siguiente operando
                postfix += ' ';       // se añade un espacio para separarlo
                pila.pop(); // se popea de la pila.
            }
            pila.pop(); // se pop el último elemento o el (
        } else { // si la pila está vacía
            while (pila.top() != '#' && precedence(operation[indice]) <= precedence(pila.top())){ // mientras la pila no está vacía y la precedencia del caracter sea menor igual a la precedencia del caracter 
                postfix += pila.top(); // saco todo de la pila y se lo añado a la operación postfija
                postfix += ' '; // le pongo un espacio para separarlos
                pila.pop(); // saco de la pila
            }
            
            pila.push(operation[indice]); // pusheo el caracter
        }
    }

// finalmente, mientras la pila no esté vacía 
    while (pila.top() != '#'){
        postfix += pila.top(); // saco todo y lo añado a la operación
        pila.pop();
    }

    cout << postfix << endl;

    Stack<string> pilaOp; // en esta pila se van pusheando las operaciones y operandos
    string operando = ""; // En este string se van creando los operandos.
    for (char element : postfix) { // por cada aracter en la operación
        if (element >= '0' && element <= '9'){
            operando += element; // si es un número, lo añade al operando
        } else if (element == ' '){ // si es un espacio, 
            if (operando != ""){ // si el operando no está vacío, lo pushea
                pilaOp.push(operando);  
            }
            operando = ""; // restaura el operando a vacío para volver a conseguir el siguiente.
        } else { // si no, significa que tiene que hacer una operación
            stringstream operandos; // saca los operandos de la pila y los convierte a integers
            int op1;
            operandos << pilaOp.top();
            operandos >> op1;
            pilaOp.pop();
            int op2;
            stringstream operandos2;

            operandos2 << pilaOp.top();
            operandos2 >> op2;
            pilaOp.pop();
            if (element == '+'){      // realiza la operación correspondiente al operador.   
                pilaOp.push(to_string(op2 + op1)); // pushea el resultado a la pila para que sea el siguiente operador.
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