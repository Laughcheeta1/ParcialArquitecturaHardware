#include "mbed.h"
#include <iostream>
#include <vector>

const int numRows = 4;
const int numCols = 4;

char keyMap[numRows][numCols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4), DigitalOut(D5)};
DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8), DigitalIn(D9)};

//BusIn Row(D2, D3, D4, D5);
//BusOut Col(D6, D7, D8, D9);

vector<int> getPressedNumber2();
int getPressedNumber();
void app1();
void app2();
void app3();
float getNumber(int number);

using namespace std;

int main() {
    while (true)
    {
        printf("Select the app you want to use right:\n(Enter '1' or '2' or '3'\n");
        int c = getPressedNumber();
        while (c < 1 && c > 3)
        {
            c = getPressedNumber();
            cout << "Enter a valid app to use\n";
        }

        cout << "The selected app is the " << c << endl;

        if (c == 1)
            app1();
        if (c == 2)
            app2();
        if (c == 3)
            app3();
    }
}

void app3()
{
    cout << "Format: #FFFFFF\n";

    PwmOut red(LED1);
    PwmOut green(LED2);
    PwmOut blue(LED3);

    red.period(0.01);
    green.period(0.01);
    blue.period(0.01);

    cout << "ingrese el numero de rojo\n";
    int number1 = getPressedNumber();
    cout << "ingrese el numero de verde\n";
    int number2 = getPressedNumber();
    cout << "ingrese el numero de azul\n";
    int number3 = getPressedNumber();

    red.write(getNumber(number1));
    green.write(getNumber(number2));
    blue.write(getNumber(number3));
}

float getNumber(int number)
{
    float result = 0;

    int firstNumber = number / 10;
    int secondNumber = number * 10;

    result += 16 * firstNumber;
    result += secondNumber;
    

    return result / 1000;
}


void app2()
{
    cout << "Ingrese una nota del 0 al 10, y le mostrare la letra de la nota correspondiente\n";
    int i = getPressedNumber();

    if (i <= 3 && i >= 0)
        printf("A\n");
    else if (i <= 4 && i > 3)
        printf("B\n");
    else if (i <= 5 && i > 4)
        printf("C\n");
    else if (i <= 7 && i > 5)
        printf("D\n");
    else if (i < 9 && i > 7)
        printf("E\n");
    else if (i <= 10 && i >= 9)
        printf("F\n");
    else
        printf("No ha entrado un numero valido\n");

    cout << "listo, app terminada\n";
}

void app1()
{
    cout << "La forma del polinomio es: a*(x^2) + b*x + c" << endl;
    cout << "ingrese por favor el valor de la 'a'\n";
    int a = getPressedNumber();

    cout << "ingrese por favor el valor de la 'b'\n";
    int b = getPressedNumber();

    cout << "ingrese por favor el valor de la 'c'\n";
    int c = getPressedNumber();

    bool imaginary = false;

    int interRaiz = b*b - 4*a*c;

    if (interRaiz < 0)
        imaginary = true;

    if (!imaginary)
    {
        cout << "El resultado es: " << (-b + sqrt(interRaiz)) / (2*a) << endl;
        cout << "O el otro resultado es: " << (-b - sqrt(interRaiz)) / (2*a) << endl;
    }
    else
    {
        cout << "El resultado es: (" << -b << " + " << sqrt(interRaiz) << "i) / " << 2*a <<  endl;
        cout << "El resultado es: (" << -b << " - " << sqrt(interRaiz) << "i) / " << 2*a <<  endl;
    }
}

int getPressedNumber()
{
    vector<int> res = getPressedNumber2();
    for (int i = 0; i < res.size(); i++)
    {   
        cout << res[i] << ", ";
    }
    cout << endl;
    int x = res.size();
    int result = 0;
    for (int i = 0; i < x; i++)
    {
        result += res[i] * pow(10, i);
    }

    return result;
}

vector<int> getPressedNumber2()
{
    printf("Recuerde que para terminar de escribir el numbero tiene que presionar la tecla '*'\n");
    vector <int> result;
    while (true){
        for (int i = 0; i < numRows; i++) {
            rowPins[i] = 0;
            
            for (int j = 0; j < numCols; j++) {
                if (!colPins[j]) {
                    if (keyMap[i][j] == '*')
                    {
                        rowPins[i] = 1;
                        ThisThread::sleep_for(500ms);
                        return result;
                    }

                    result.push_back(keyMap[i][j] - '0');
                    printf("pressed %c\n", keyMap[i][j]);

                    ThisThread::sleep_for(500ms);  // Evita lecturas múltiples mientras la tecla está presionada
                }
            }

            rowPins[i] = 1;
        }

        
    }
}