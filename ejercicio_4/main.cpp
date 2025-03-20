#include <iostream>
#include <memory>
#include <chrono>
using namespace std;

/*La primer funcion recibe ambos textos como strings y recibe un index que por default es 0 
Se chequea sin ambos tienen mismo tamano una vez que el index haya aumentado (mas facil de explicar
luego del segundo if) 
EL segundo if lo que hace es chequear que si para algun index, uno de los dos textos tiene ese tamano (y el otro 
no puede tener el mismo porque eso se chequea en el primer if) y es chequea si el caracter de cada texto en
en la posicion del indice es igual a la del otro texto respectivamente, si no es, es false. De esta forma devuelvo 
la funcion con los mismos textos, pero sumandole 1 al index, y ahi esta la recursion, hace el chequeo de los tamanos nuevamente
de si la letra en la misma posicion es la misma para ambos tectos y sigue
Elijo el tipo string para no tener que asignar y liberar memoria y me olvido de las fugas de memoria*/
bool string_equal(const string& text1, const string& text2, size_t index = 0) {
    if (index == text1.size() && index == text2.size()) return true;
    
    if (index == text1.size() || index == text2.size() || text1[index] != text2[index]) return false; 
    
    return string_equal(text1, text2, index + 1);
}

int main() {
    string texto1 = "Hoy voy a jugar al futbol con amigos por la tarde";
    string texto2 = "Hoy voy a jugar al futbol con amigos por la tarde";
    string texto3 = "Hola como va este texto es diferente a los anteriores";

    cout << "comparo texto 1 y 2 (true si son iguales false si no): " << string_equal(texto1, texto2)  << endl;
    cout << "comparo texto 2 y 3 (true si son iguales false si no): " << string_equal(texto1, texto3)  << endl;

    string str1 = "Este texto es para tomar el tiempo de ejecucion.";
    string str2 = "Este texto es para tomar el tiempo de ejecucion.";

    auto startTime = chrono::high_resolution_clock::now();
    bool resultado = string_equal(str1, str2);
    auto endTime = chrono::high_resolution_clock::now();

    auto elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
    cout << "Tiempo de ejecución: " << elapsedTime.count() << " nanosegundos" << endl;
    
    if (resultado) {
        cout << "Los strings son iguales" << endl;
    } else {
        cout << "Los strings son diferentes" << endl;
    }

    return 0;
}