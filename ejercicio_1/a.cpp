#include <iostream>

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
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int n;
    std::cout << "Ingrese un valor para n: ";
    std::cin >> n;

    if (n <= 1) {
        std::cout << "n debe ser mayor a 1." << std::endl;
        return 1;
    }
    /*creo la matriz y reservo memoria, para cada array dentro del array*/
    int** matriz = new int*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new int[n];
    }
    Matriz_de_dim_N(matriz, n);
    imprimirM(matriz, n);

    /*como reserve memoria, aca libero con el delete*/
    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}


