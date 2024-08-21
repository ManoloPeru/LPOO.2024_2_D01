#include <iostream>

using namespace std;

int valorRomano(char c) {
    switch (c) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default: return -1; // Valor inválido
    }
}

bool validarRomano(char romano[], int n) {
    // Regla 4: La misma letra no puede repetirse más de tres veces seguidas
    for (int i = 0; i < n; ++i) {
        if (i > 2 && romano[i] == romano[i - 1] && romano[i - 1] == romano[i - 2] && romano[i - 2] == romano[i - 3]) {
            return false;
        }
        // Regla 5: L, V y D no pueden duplicarse
        if ((romano[i] == 'L' || romano[i] == 'V' || romano[i] == 'D') && i > 0 && romano[i] == romano[i - 1]) {
            return false;
        }
    }

    // Regla 6: Validar que si hay una cifra menor entre dos mayores, debe restar
    for (int i = 0; i < n - 1; ++i) {
        if (valorRomano(romano[i]) < valorRomano(romano[i + 1])) {
            if (romano[i] == 'I' && (romano[i + 1] == 'V' || romano[i + 1] == 'X')) continue;
            if (romano[i] == 'X' && (romano[i + 1] == 'L' || romano[i + 1] == 'C')) continue;
            if (romano[i] == 'C' && (romano[i + 1] == 'D' || romano[i + 1] == 'M')) continue;
            return false;
        }
    }

    return true;
}

int convertirRomanoADecimal(char romano[], int n) {
    int total = 0;

    for (int i = 0; i < n; ++i) {
        int valor = valorRomano(romano[i]);

        if (i < n - 1 && valor < valorRomano(romano[i + 1])) {
            total -= valor; // Si el valor actual es menor al siguiente, se resta
        }
        else {
            total += valor; // Si no, se suma
        }
    }

    return total;
}

string convertirDecimalARomano(int num) {
    string romano = "";

    // Arreglos separados para los valores decimales y sus correspondientes representaciones romanas
    int valores[] = { 100, 90, 50, 40, 10, 9, 5, 4, 1 };
    string simbolos[] = { "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

    // Recorremos los valores romanos de mayor a menor
    for (int i = 0; i < 9; ++i) {
        while (num >= valores[i]) {
            romano += simbolos[i];
            num -= valores[i];
        }
    }

    return romano;
}

int main() {
    char romano[100];  // Arreglo de caracteres para almacenar el número romano
    char c;
    int i = 0;
    int numero;

    //Problema 1: Los Números Romanos
    cout << "Ingrese un numero romano caracter por caracter.\nIngrese '0' [cero] para finalizar:\n";

    // Leer caracteres uno por uno
    while (cin >> c && c != '0') {
        romano[i++] = c;
    }

    // Validar el número romano
    if (!validarRomano(romano, i)) {
        cout << "El numero romano ingresado no es correcto.\n";
        return 1;
    }

    // Convertir a decimal y mostrar el resultado
    int decimal = convertirRomanoADecimal(romano, i);
    cout << "El numero decimal es: " << decimal << endl;

    //Problema 2: Los Números Romanos 2
    cout << "Ingrese un numero decimal entre 1 y 100: ";
    cin >> numero;

    // Validar que el número esté en el rango de 1 a 100
    if (numero < 1 || numero > 100) {
        cout << "El numero ingresado no es valido. Debe estar entre 1 y 100." << endl;
        return 1;
    }

    string numeroRomano = convertirDecimalARomano(numero);
    cout << "El numero romano correspondiente es: " << numeroRomano << endl;

    return 0;
}
