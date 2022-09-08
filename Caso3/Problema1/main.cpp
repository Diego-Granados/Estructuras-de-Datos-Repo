#include <iostream>
#include <string>
#include "../Stack/pila.cpp"
#include <sstream>

Stack<char> pila;

void split(string operacion, char separator, string * arreglo[]){
    
}

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
    string operation = "101+1";

    string postfix = "";
    pila.push('#');

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
                pila.pop();
            }
            pila.pop();
        } else if (!pila.empty){
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
            if (pila.getQuantity()!= 2 && operando != ""){
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
    cout << pilaOp.top() << endl;
}