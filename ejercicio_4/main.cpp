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
la funcion con los mismos textos, pero sumandole 1 al index, y ahi esta la recursion, hace el chequeo de los tamanos 
nuevamente de si la letra en la misma posicion es la misma para ambos textos y sigue Elijo el tipo string para 
no tener que asignar y liberar memoria y me olvido de las fugas de memoria.
Para el punto 3 uso constexpr y en cambio a la anterior, le paso los textos como array de chars, de todas formas, 
funciona parecido, chequea si ambos textos llegaron al final con el /0, de no ser asi hago el chequeo de si el caracter
en el index actual es igual en ambos textos, de ser asi , aplico recursion aumentando el index. Los array de chars
al tener tamano fijo a diferencia de los strings, el compilador ya sabe que este tamano no puede cambiar. Con chronos evaluo el resultado que me da
la segunda funcion con constexpr pero esta misma se evaluo anteriormente en compilacion. Mejor explicado: 
Cuando una función está marcada con el constexpr que use , el compilador intenta evaluar su resultado 
en tiempos de compilación, para esto los argumentos tienen que ser constantes. La otra funcion usa string, que maneja 
de forma dinamica la memoria en cambio char* no tiene que gestionar memoria dinamica, puede buscar el caracter
/0 con acceso a memoria y listo.*/


bool string_equal(const string& text1, const string& text2, size_t index = 0) {
    if (index == text1.size() && index == text2.size()) return true;
    
    if (index == text1.size() || index == text2.size() || text1[index] != text2[index]) return false; 
    
    return string_equal(text1, text2, index + 1);
}

constexpr bool string_equal_constexpr(const char* text1, const char* text2, size_t index = 0) {
    if (text1[index] == '\0' && text2[index] == '\0') {
        return true;
    }
    if (text1[index] != text2[index]) {
        return false;
    }
    return string_equal_constexpr(text1, text2, index + 1);
}

int main() {
    string texto1 = "Hoy voy a jugar al futbol con amigos por la tarde";
    string texto2 = "Hoy voy a jugar al futbol con amigos por la tarde";
    string texto3 = "Hola como va este texto es diferente a los anteriores";

    cout << "comparo texto 1 y 2 con la funcion original (true si son iguales false si no): " << string_equal(texto1, texto2)  << endl;
    cout << "comparo texto 2 y 3 con la funcion original (true si son iguales false si no): " << string_equal(texto1, texto3)  << endl;

    string str1 = "Este texto es para tomar el tiempo de ejecucion.";
    string str2 = "Este texto es para tomar el tiempo de ejecucion.";

    auto startTime = chrono::high_resolution_clock::now();
    bool resultado = string_equal(str1, str2);
    auto endTime = chrono::high_resolution_clock::now();

    auto elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
    cout << "Tiempo de ejecución de la funcion normal : " << elapsedTime.count() << " nanosegundos" << endl;

   
    /*Ahora con la funcion de constexpr*/
    
    cout << "comparo textos con la funcion original (true si son iguales false si no): " << string_equal("Prueba de funcion con constexpr longitudes iguales", "Prueba de funcion con constexpr longitudes iguales")  << endl;
    cout << "comparo textos con la funcion original (true si son iguales false si no): " << string_equal("Prueba de funcion con constexpr longitudes distintas", "Prueba de funcion con constexpr longitudes iguales, deberia dar false")  << endl;

    constexpr bool resul2 = string_equal_constexpr("Este texto es para tomar el tiempo de ejecucion.",
        "Este texto es para tomar el tiempo de ejecucion.");
    auto startTime_constexpr = chrono::high_resolution_clock::now();
    bool resultado_constexpr = resul2;
    auto endTime_constexpr = chrono::high_resolution_clock::now();

    auto elapsedTime_constexpr = chrono::duration_cast<chrono::nanoseconds>(endTime_constexpr - startTime_constexpr);
    cout << "Tiempo de ejecución de la funcion con constexpr : " << elapsedTime_constexpr.count() << " nanosegundos" << endl;
    
    return 0;
}