#include <iostream>

void imprimirMatrizInversa(int** matriz, int n) {
    for (int k = n * n - 1; k >= 0; k--) { 
        int i = k / n;  // Fila
        int j = k % n;  // Columna
        std::cout << "M_" << n << "[" << i << "][" << j << "] = " << matriz[i][j] << std::endl;
    }
}

int main() {
    int n;
    std::cout << "Ingrese un valor para n: ";
    std::cin >> n;

    int** matriz = new int*[n];
    
    int valor = 1;
    for (int i = 0; i < n; i++) {
        matriz[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matriz[i][j] = valor++;
        }
    }

    // Llamamos a la función
    imprimirMatrizInversa(matriz, n);

    // Liberamos la memoria
    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}