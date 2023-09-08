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
En las lineas previas al main se importan las librerias necesarias para que el codigo funcione correctamente. También incluimos la librería de `vector` para el funcionamiento del método getPressedNumber().

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
En esta parte del código se declaran dos constantes `numRows` y `numCols` para declarar el numero de filas y de columnas que tiene el teclado numérico utilizado.
Después se crea una matriz la cual representa el diseño del teclado numérico 4x4, en donde cada elemento de la matriz es un botón del teclado utilizado.
Finalmente se crean arreglos de objetos `DigitalOut` y `DigitalIn` llamados `rowPins` y `colPins` respectivamente, para controlar las filas y columnas del teclado numérico. 

### Declaración de funciones que se van a utilizar
```
vector<int> getPressedNumber2();
int getPressedNumber();
void app1();
void app2();
void app3();

```
Esta parte del código se declaran todas las funciones que se van a utilizar más adelante en el código.

### main()
```
int main() {
    while (true)
    {
        cout << "Select the app you want to use right :\n(Enter '1' or '2' or '3'\n)";
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
```
La función `main()` es el punto de entrada del programa. El programa entra en un bucle infinito donde el usuario puede seleccionar una de las tres aplicaciones disponibles ingresando un número del 1 al 3, si el numero no esta fuera del rango, entonces el programa vuelve a pedirte que ingreses un numero.
Los números durante todo el programa siempre se leen mediante el uso del metodo `getPressedNumber()`.

### app3()
```
void app3()
{
    cout << "app 3 selected\n";

    PwmOut red(LED1);
    PwmOut green(LED2);
    PwmOut blue(LED3);

    red.period(0.01);
    green.period(0.01);
    blue.period(0.01);

    cout << "ingrese el numero de rojo (recuerde que tiene que introducir un numero entre 0 y 255):\n";
    float number1 = (float)getPressedNumber();
    while (number1 > 255 || number1 < 0)
    {
        cout << "ingreso un numero no valido, por favor vuevla a entrar el numero del rojo, desde 0 hasta 255\n";
        number1 = getPressedNumber();
    }

    cout << "ingrese el numero de verde (recuerde que tiene que introducir un numero entre 0 y 255):\n";
    float number2 = (float)getPressedNumber();
    while (number2 > 255 || number2 < 0)
    {
        cout << "ingreso un numero no valido, por favor vuevla a entrar el numero del verde, desde 0 hasta 255\n";
        number2 = getPressedNumber();
    }

    cout << "ingrese el numero de azul (recuerde que tiene que inroducir un numero entre 0 y 255):\n";
    float number3 = (float)getPressedNumber();
    while (number3 > 255 || number3 < 0)
    {
        cout << "ingreso un numero no valido, por favor vuevla a entrar el numero del azul, desde 0 hasta 255\n";
        number3 = getPressedNumber();
    }

    red.write(number1 / 255);
    green.write(number2 / 255);
    blue.write(number3 / 255);

    cout << "Listo! App 3 terminada\n";
}
```
La función `app3()` incialmente declara los LED que se van a utilizar (`red`, `green`, `blue`) y también declara el periodo de prendido y apagado de las luces LED (0.01).
Este método pide al usuario los valores RGB en formato decimal, tomando primero los valores del color rojo, después los valores del color verde y por último los valores del color azul (Todos los valores están entre 0 inclusivo y 255 inclusivo); por último el método convierte estos valores ingresados al porcentaje con respecto a 255, y luego los invierte (por medio de 1 - *porcentaje esperado*, esto debido a como funcionan las tarjetas que estamos usando), esto con el objetivo de mostrar el color resultante en la bombilla LED. El método siempre se asegura de que los valores ingresados por el usuario sean válidos, de lo contrario el método volverá a pedir los valores de los colores hasta que se ingrese un número válido.

### app2()

```
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
```
El método de `app2()` le pide un número al usuario entre el 1 y el 10 (el método siempre revisa si el numero ingresado está entre 1 y 10, de lo contrario el metodo pide nuevamente el número hasta que se ingrese un número válido). Una vez ingresado el número el método le muestra al usuario una letra mayúscula (desde la A hasta la F) según el numero que se haya ingresado.

### app1()
```
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
```
La función `app1()` permite al usuario ingresar coeficientes de un polinomio cuadrático y calcula sus raíces. Las respuestas que tengan números imaginarios se dejan indicadas.

El pide al usuario el valor de `a`, `b` y `c`, los cuales son las partes que componen un polinomio cuadrático (a*(x^2) + b*x + c).
Después declara una variable booleana `imaginary`, la cual guarda si la respuesta va a ser compleja (contener un imaginario) o no, e inicialmente se establece como falsa.

Se calcula el determinante de (la parte interior de la raíz, `interRaiz`) de la formula de la solucion de una ecuación cuadrática y se verifica si este (`interRaiz`) es negativo. Si lo es, se establece `imaginary` en true, lo que indica que las raíces serán números complejos. Si `imaginary` es true, se imprime la solución en formato de número complejo. Si `imaginary` es false, se imprime la solución calculada. Para las soluciones se muestran ambas, cuando la formula es b + raiz y cuando es b - raiz.

### getPressedNumber()
```
int getPressedNumber()
{
    vector<int> res = getPressedNumber2();
    int x = res.size();
    bool negative = false;

    if (res[0] == -1)
    {
        negative = true;
        res.erase(res.begin());
        x--;
    }

    int result = 0;
    for (int i = 0; i < x; i++)
    {
        result += res[i] * pow(10, x - i - 1); // 7456 = 7000 + 400 + 50 + 6
    }

    if (negative)
        result *= -1;

    cout << "El numero que has entrado es: " << result << endl;
    return result;
}
```
Este método tiene como función llamar al método `getPressedNumber2()` el cual le devuele un vector con dígitos para convertir este vector a un número entero. 

Inicialmente inicializa una variable booleana `negative` en false. Esta variable se utilizará para determinar si el número es negativo. Después en el primer `if` verifica si el primer elemento del vector `res` es igual a -1, si es así, esto indica que el usuario indicó un número negativom, con ello se establece `negative` en true para indicar que el número es negativo después elimina el primer elemento del vector `res` ya que este representa el signo negativo y por último reduce x en 1 para reflejar la eliminación del signo negativo.

El for itera a través de los elementos del vector `res` para construir el número entero final basandose en este principio `4753 = 4000 + 700 + 50 + 3`, de esta manera vamos a multiplicar cada elemento del vector por su correspondiente potencia de 10, para que ese numero sume solamente a la posicion que le corresponde, es decir, si tenemos el vector [8, 7, 6], sabemos que el 8 pertenece a las centenas, el 7 a las decenas y el 6 a las unidades, con ello hariamos una suma de estos digitos, pero multiplicado por la potencia de 10 que lo hace estar en la posicion indicada, asi la suma quedaria `8 * (10^2) + 7 * (10 ^ 1) + 6 * (10 ^ 0)`, este es el principio que estamos haciendo dentro del for, lo unico es que es  `10 ^ (x - i - 1)` ese exponente viene del hecho que como la i va desde 0 hasta (x - 1), y necesitamos es multiplicar el por potencias de 10, pero decrecientes, entonces esto lo podemos solucionar por medio de `(x - i - 1)`.

El ultimo if chequea que si el numero debe de ser negativo, entonces vamos a multiplicar el resultado de la suma por -1 para convertir el numero en negativo.
Ya de ahi solo se retorna el numero.

### getPressedNumber2()
```
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
```
El método `getPressedNumber2()` se encarga de leer los números ingresados por el usuario desde un teclado numérico 4x4 y convertirlos en un vector dígitos, que posteriormente se convertirán en un número entero por medio de la funcion `getPressedNumber()`. 
El número puede ser positivo o negativo, esto se denota por medio de presionar la tecla `#` al inicio de meter el numero, y el ingreso se detiene cuando el usuario presiona la tecla `*`. 
El metodo dentro de esos for lo que hace es identificar cual fue la tecla del teclado (valga la redundancia) la cual fue presionada, una vez se identifico esta tecla, lo que hacemos es chekear a cual de estos casos pertenece la tecla presionada:
- Se presiono `*`: En este caso sensillamente significa que ya se termino de digitar el numero y se desea continuar, por ende salimos del metodo retornando el numero creado hasta ahora.
- Se presiono `#`: Esto se usa para indicar que el numero es negativo, o si estuviera escrito en un papel, escribirle `-` al inicio al numero. Solo se registra este negativo cuando es lo primero que se ingresa al numero, de lo contrario ese negativo se asumira como que se presiono accidentalmente por ende ignorandolo.
- Se presiono un numero: Cuando se presiona un numero normal, es decir, cualquier otra tecla (Ya que el teclado fisico solo tiene los numeros, el `*` y el `#`) a las previas mensionadas, convertimos el caracter que nos devuelve la matriz `keyMap` en un numero entero, y lo añadimos al vector para su eventual conversion.