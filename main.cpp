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


vector<int> getPressedNumber2();
int getPressedNumber();
void app1();
void app2();
void app3();

using namespace std;

int main() {
    while (true)
    {
        cout << "Select the app you want to use right:\n(Enter '1' or '2' or '3'\n";
        int c = getPressedNumber();
        while (c < 1 || c > 3)
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
    cout << "app 3 selected\n";

    PwmOut red(LED1);
    PwmOut green(LED2);
    PwmOut blue(LED3);

    red.period(0.01);
    green.period(0.01);
    blue.period(0.01);

    cout << "ingrese el numero de rojo (recuerde que tiene que inroducir entre 0 y 100, para que se refleje el porcentaje [0, 1]):\n";
    float number1 = (float)getPressedNumber();
    while (number1 > 100 || number1 < 0)
    {
        cout << "ingreso un numero no valido, por favor vuevla a entrar el numero del rojo, desde 0 hasta 100\n";
        number1 = getPressedNumber();
    }

    cout << "ingrese el numero de verde (recuerde que tiene que inroducir entre 0 y 100, para que se refleje el porcentaje [0, 1]):\n";
    float number2 = (float)getPressedNumber();
    while (number2 > 100 || number2 < 0)
    {
        cout << "ingreso un numero no valido, por favor vuevla a entrar el numero del rojo, desde 0 hasta 100\n";
        number2 = getPressedNumber();
    }

    cout << "ingrese el numero de azul (recuerde que tiene que inroducir entre 0 y 100, para que se refleje el porcentaje [0, 1]):\n";
    float number3 = (float)getPressedNumber();
    while (number3 > 100 || number3 < 0)
    {
        cout << "ingreso un numero no valido, por favor vuevla a entrar el numero del rojo, desde 0 hasta 100\n";
        number3 = getPressedNumber();
    }

    red.write(number1 / 100);
    green.write(number2 / 100);
    blue.write(number3 / 100);

    cout << "Listo! App 3 terminada\n";
}


void app2()
{
    cout << "app 2 selected\n";

    cout << "Ingrese una nota del 0 al 10, y le mostrare la letra de la nota correspondiente\n";
    int i = getPressedNumber();
    while (i > 10 || i < 0)
    {
        cout << "ingreso un numero no valido, por favor vuevla a entrar un numero entre el 1 y el 10\n";
        i = getPressedNumber();
    }

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

    cout << "Listo! App 2 terminada\n";
}

void app1()
{
    cout << "app 1 selected\n";

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

    interRaiz = abs(interRaiz);
    
    if (imaginary)
    {
        cout << "El resultado es: (" << -b << " + " << sqrt(interRaiz) << "i) / " << 2*a <<  endl;
        cout << "El resultado es: (" << -b << " - " << sqrt(interRaiz) << "i) / " << 2*a <<  endl;
    }
    else
    {
        cout << "El resultado es: " << (-b + sqrt(interRaiz)) / (2*a) << endl;
        cout << "O el otro resultado es: " << (-b - sqrt(interRaiz)) / (2*a) << endl;
    }

    cout << "Listo! App 1 terminada\n";
}

int getPressedNumber()
{
    vector<int> res = getPressedNumber2();
    int x = res.size();
    bool flag = false;

    if (res[0] == -1)
    {
        flag = true;
        res.erase(res.begin());
        x--;
    }

    int result = 0;
    for (int i = 0; i < x; i++)
    {
        result += res[i] * pow(10, x - i - 1);
    }

    if (flag)
        result *= -1;

    cout << "the number you entered was: " << result << endl;
    return result;
}

vector<int> getPressedNumber2()
{
    printf("Recuerde que para terminar de escribir el numero tiene que presionar la tecla '*'\nSi desea usar un numero negativo, presione '#' para introducir un '-'\n(cualquier '-' despues de la primera posicion sera ignorado)");
    vector <int> result;
    bool flag = true;
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
                    else if (keyMap[i][j] == '#')
                    {
                        if (flag && result.size() == 0)
                        {
                            result.push_back(-1);
                            cout << "pressed '-'\n";
                            flag = false;
                        }
                        else
                        {
                            cout << "'-' ignored\n";
                        }
                    }
                    else
                    {
                        result.push_back(keyMap[i][j] - '0');
                        printf("pressed %c\n", keyMap[i][j]);
                    }
                    

                    ThisThread::sleep_for(500ms);  // Evita lecturas múltiples mientras la tecla está presionada
                }
            }

            rowPins[i] = 1;
        }
    }
}