# Integrantes
1. Sebastian Ruiz Londoño
1. Santiago Yepes Mesa

# Descripcion Codigo
### Previo al Main
```
    #include "mbed.h"
    #include <iostream>
    #include <vector>
```
En las lineas previas al main se importan las librerias necesarias para que el codigo funcione correctamente. También incluimos la librería de <vector> para el funcionamiento del método getPressedNumber().

### Declaración de la matriz que se va a utilizar. 
```
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
```
En esta parte del código se declaran dos constantes "numRows" y "numCols" para declarar el numero de filas y de columnas que tiene el teclado numérico utilizado.
Después se crea una matriz la cual tiene como objetivo representar el diseño del teclado numérico 4x4, en donde cada elemento de la matriz es un botón del teclado utilizado.
Finalmente se crean arreglos de objetos DigitalOut y DigitalIn llamados rowPins y colPins, respectivamente, para controlar las filas y columnas del teclado numérico. 

### Declaración de funciones que se van a utilizar
```
vector<int> getPressedNumber2();
int getPressedNumber();
void app1();
void app2();
void app3();
float getNumber(int number);
```
Esta parte del código se declaran todas las funciones que se van a utilizar más adelante en el código.

### main()
```
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

```
La función main() es el punto de entrada del programa. El programa entra en un bucle infinito donde el usuario puede seleccionar una de las tres aplicaciones disponibles ingresando un número del 1 al 3. El número se lee utilizando la función getPressedNumber() que se explicará posteriormente.

### app3()

```
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
    
}
```
La función app3() incialmente declara los LED que se van a utilizar (red,green,blue) y también declara el periodo de prendido y apagado de las luces LED (0.01).

La función de este método es pedir al usuario los valores RGB en formato decimal, tomando primero los valores del color rojo, después los valores del color verde y por último los valores del color azul; esto con el objetivo de mostrar el color resultante en la bombilla LED.

### app2()

```
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

```
El método de app2() le pide un número al usuario entre el 1 y el 10, una vez ingresado el número el método le retorna al usuario una letra (desde la A hasta la F) según el numero que haya ingresado.

### app1()
```
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

    interRaiz = abs(interRaiz);
    
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
```
La función app1() permite al usuario ingresar coeficientes de un polinomio cuadrático y calcula sus raíces, teniendo en cuenta las raíces imaginarias.

### getPressedNumber()
```
int getPressedNumber()
{
    vector<int> res = getPressedNumber2();
    cout << endl;
    int x = res.size();
    int result = 0;
    for (int i = 0; i < x; i++)
    {
        result += res[i] * pow(10, i);
    }

    cout << "the number you entered was: " << result << endl;
    return result;
}
```
Este método tiene como función llamar al método getPressedNumber2() el cual le devuele un vector con dígitos para comvertir este vector a un número entero.

### getPressedNumber2()
```
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
```
El método getPressedNumber2() se encarga de leer los números ingresados por el usuario desde un teclado numérico 4x4 y convertirlos en una secuencia de dígitos(vector de dígitos) que posteriormente se convertirán en un número entero.

