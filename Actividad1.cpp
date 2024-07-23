

#include <iostream>
#include <string>
#include <regex>

using namespace std;

//Convierte un numero decimal a hexadecimal
string decimalAHexadecimal(string decNum) {
    int decimalNumber = stoi(decNum);
    string hexNumber;

    while (decimalNumber > 0) {
        int remainder = decimalNumber % 16;
        char hexDigit;

        if (remainder < 10)
            hexDigit = remainder + '0';
        else
            hexDigit = remainder - 10 + 'A';

        hexNumber = hexDigit + hexNumber;
        decimalNumber /= 16;
    }

    return hexNumber;
}


//Convierte un numero binario a decimal
int binarioADecimal(string binario) {
    int final = 0;
    int exp = 1;
    for (int i = binario.size() - 1; i >= 0; i--) {
        if (binario[i] == '1') {
            final += exp;
        }
        exp *= 2;
    }
    return final;
}

//Convierte un numero decimal a binario
string decimalABinario(string dec) {
    int decimal = stoi(dec);
    string aux = "";
    if (decimal == 0)
        return "0";

    while (decimal > 0) {
        aux = to_string(decimal % 2) + aux;
        decimal /= 2;
    }
    return aux;
}

//Convierte un numero hexadecimal a decimal
int hexadecimalADecimal(string hexadecimal) {
    int decimal = 0;
    int power = 0;

    for (int i = hexadecimal.size() - 1; i >= 0; --i) {
        char digit = hexadecimal[i];
        int value = 0;

        if (isdigit(digit)) {
            value = digit - '0';
        }
        else {
            value = toupper(digit) - 'A' + 10;
        }

        decimal += value * pow(16, power);
        ++power;
    }

    return decimal;
}

//Devuelve true si es un hex, false si no
bool isHex(string cadena) {

    return regex_match(cadena, regex("[0-9a-fA-F]+"));
}

//Devuelve true si es un binario, false si no
bool isBin(string cadena) {
    return regex_match(cadena, regex("[0-1]+"));
}

//Devuelve true si es un decimal, false si no
bool isDec(string cadena) {
    return regex_match(cadena, regex("[0-9]+"));

}

//Devuelve true si es una cadena de 2 bytes, false si no
bool is2Bytes(string cadena, int type) {
    //Decimal
    if (type == 0) {
        return stoi(cadena) <= 65535;
    }
    //Binary
    if (type == 1) {
        return cadena.size() <= 16;
    }
    //Hex
    return cadena.size() <= 4;
}

//Menu principal del convertidor
void detector() {
    string cadena;
    int aux;
    bool valid = false;
    do {
        valid = false;
        cout << "Escribe la cadena (2 bytes) o '-1' para salir" << endl;
        cin >> cadena;
        if (cadena == "-1")break;

        if (isHex(cadena)) {
            valid = true;
            if (is2Bytes(cadena, 2)) {
                cout << cadena << " encaja como hexadecimal" << endl;
                aux = hexadecimalADecimal(cadena);
                cout << "En decimal: " << to_string(aux) << endl;
                cout << "En binario: " << decimalABinario(to_string(aux)) << endl;
            }
            else cout << "Mayor de 2 bytes como hexadecimal" << endl;
            cout << "---------------------------------------------------------------------------" << endl;
        }

        if (isBin(cadena)) {
            valid = true;
            if (is2Bytes(cadena, 1)) {
                cout << cadena << " encaja como binario" << endl;
                aux = binarioADecimal(cadena);
                cout << "En decimal: " << to_string(aux) << endl;
                cout << "En hexadecimal: " << decimalAHexadecimal(to_string(aux)) << endl;
            }
            else cout << "Mayor de 2 bytes como binario" << endl;
            cout << "---------------------------------------------------------------------------" << endl;

        }

        if (isDec(cadena)) {
            valid = true;
            if (is2Bytes(cadena, 0)) {
                cout << cadena << " encaja como decimal" << endl;
                cout << "En hexadecimal: " << decimalAHexadecimal(cadena) << endl;
                cout << "En binario: " << decimalABinario(cadena) << endl;
            }
            else cout << "Mayor de 2 bytes como decimal" << endl;
            cout << "---------------------------------------------------------------------------" << endl;

        }

        if (!valid) {
            cout << "La cadena no coincide con ningun tipo" << endl;
            cout << "---------------------------------------------------------------------------" << endl;
        }

        cout << endl << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

    } while (true);
}

//Suma 2 cadenas hexadecimales y devuelve su resultado
string HexasAdd(string cadena1, string cadena2) {
    while (cadena1.length() < cadena2.length())
        cadena1 = "0" + cadena1;
    while (cadena2.length() < cadena1.length())
        cadena2 = "0" + cadena2;
    string result = "";
    int carry = 0;
    int number1, number2, sum;
    for (int i = cadena1.length() - 1; i >= 0; i--) {
        if (cadena1[i] < '9' + 1) number1 = cadena1[i] - '0';
        else number1 = toupper(cadena1[i]) - 'A' + 10;

        if (cadena2[i] < '9' + 1) number2 = cadena2[i] - '0';
        else number2 = toupper(cadena2[i]) - 'A' + 10;

        sum = number1 + number2 + carry;
        carry = 0;
        while (sum > 16) {
            carry++;
            sum = sum - 16;
        }
        result = decimalAHexadecimal(to_string(sum)) + "" + result;
    }
    if (carry > 0)  result = char(carry + '0') + result;
    return result;
}

//Menu de la suma hexadecimal
void hexaSum() {
    string cadena1, cadena2;
    int salir;
    do {
        cout << "Escribe el hexadecimal 1 (2 bytes):" << endl;
        cin >> cadena1;
        cout << "Escribe el hexadecimal 2 (2 bytes):" << endl;
        cin >> cadena2;
        if (is2Bytes(cadena1, 2) && is2Bytes(cadena2, 2)) {
            cadena1 = HexasAdd(cadena1, cadena2);
            cout << cadena1 << endl;
        }
        else cout << "Solo valores de 2 bytes" << endl;
        cout << "Desea salir? [Y/n]" << endl;
        cin >> cadena1;
        cout << "---------------------------------------------------------------------------" << endl;
        if (cadena1 != "n")break;
    } while (true);
}

//Menu principal del programa
void menu() {
    int eleccion;
    do {

        cout << "Que deseas hacer" << endl;
        cout << "1. Convertir cadenas" << endl;
        cout << "2. Sumar hexadecimales" << endl;
        cin >> eleccion;
        switch (eleccion) {
        case 1:
            detector();
            break;
        case 2:
            hexaSum();
            break;
        default:
            if (eleccion == -1)break;
            cout << "Escribe una opcion valida" << endl;
        }
        cout << "---------------------------------------------------------------------------" << endl;
    } while (eleccion != -1);
}

//Metodo Main
int main()
{
    menu();
}










