#include <iostream>
using namespace std;
/*En el punto a se crea la matriz con un dos for anidados, empezando con valor 1 y sumando 1 en cada iteracion, la matriz es 
un arreglo de arreglos, se le pasa la dimension (es una matriz cuadrada)
Para imprimirla, es medio redundante, le paso la matriz y con dos for anidados la recorro imprimiendo,
esta bueno que en el main se le pida la dimension al usuario por teclado, entonces podes ir probando 
distintas dims y te las imprime. Muy importante mencionar que en el main reservo memoria con el new para cada arreglo, y
la libero con delete
En el b lo que hago para imprimir la matriz en un solo for, es calcular manualmente las posiciones
mi for empieza en k = n*n-1 lo que es la ultima posicion del arreglo (sabiendo que es matriz cuadrada)
y va disminuyendo hasta 0, ultima posicion. Con calculos se puede ver que haciendo la division entera de K 
por la dimension  se encuentra la fila, y la columna con el modulo, de esa forma tengo los indices de la matriz
en cada posicion. */

void Matriz_de_dim_N(int** matriz, int n) {
    int valor = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = valor++;
        }
    }
}

void imprimirM(int** matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void imprimirMatriz_unicobucle(int** matriz, int n) {
    for (int k = n * n - 1; k >= 0; k--) { 
        int i = k / n; 
        int j = k % n;
        cout << "M_" << n << "[" << i << "][" << j << "] = " << matriz[i][j] << endl;
    }
}

int main() {
    int n;
    cout << "Ingresar dimension de matriz:  ";
    cin >> n;

    /*Aca reservo memoria para la matriz (arreglo de arreglos)*/
    int** matriz = new int*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new int[n];
    } 

    Matriz_de_dim_N(matriz, n);

    cout << "\nImprimo la matriz:" << endl;
    imprimirM(matriz, n);

    cout << "\nImprimo la matriz en un for:" << endl;
    imprimirMatriz_unicobucle(matriz, n);

    /*Libero la memoria para cada arreglo dentro del arreglo, con delete*/
    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}