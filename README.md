# Integrantes
1. Sebastian Ruiz Londoño
1. Santiago Yepes Mesa

# Descripcion Codigo
### Previo al Main
```
    #include "mbed.h"
    #include <iostream>
```
En las lineas previas al main se importan las librerias necesarias para que el codigo funcione correctamente.

### BusOut leds    
```
    BusOut leds(D2, D3, D4, D5, D6, D7, D8);
```
Esta línea inicializa un objeto BusOut llamado leds para controlar un conjunto de segmentos de LED. Los segmentos de LED están conectados a los pines D2 a D8 del microcontrolador.

### getnumber()
```
int getNumber();
```
Esta línea declara una función llamada getNumber() que devuelve un número entero. Posteriormente se explicara a detalle como funciona el método.

### main()
```
int main()
{
    int number;
    while (true)
    {
        if ((number = getNumber()) != -1)
        {
            leds.write(number);
        }
    }
}

```
La función main() es el punto de entrada del programa. Contiene un bucle infinito. Dentro del bucle, el programa llama a la función getNumber() para obtener un número del usuario. Si el número devuelto no es -1 (lo que indica una entrada válida), escribe los valores del segmento LED correspondiente en el objeto LED, mostrando efectivamente el número de entrada en la pantalla de 7 segmentos.

### getNumber()

```
int getNumber()
{
    cout << "enter the number you desire";
    char number;
    cin >> number;

    if (isdigit(number))
    {
        if (number == '0')
            return 126;
        else if (number == '1')
            return 48;
        else if (number == '2')
            return 109;
        else if (number == '3')
            return 121;
        else if (number == '4')
            return 51;
        else if (number == '5')
            return 91;
        else if (number == '6')
            return 95;
        else if (number == '7')
            return 112;
        else if (number == '8')
            return 127;
        else if (number == '9')
            return 115;
    }
        
    cout << "enter a valid number";
    return -1;
    
}
```
La función getNumber() es responsable de obtener un número del usuario y convertirlo en el valor apropiado para iluminar los segmentos correspondientes en la pantalla de 7 segmentos. Comienza solicitando al usuario que ingrese un número. Luego, lee un carácter de la entrada usando cin.

Si el carácter ingresado es un dígito (0-9), la función utiliza una serie de declaraciones if para asignar el carácter del dígito al valor correspondiente que debe escribirse en el objeto leds. Estos valores representan los valores binarios los cuales representan que segmentos deben activarse para mostrar el dígito específico. Luego, la función devuelve este valor.

Si el carácter ingresado no es un dígito, la función imprime un mensaje de error y devuelve -1 para indicar una entrada no válida.
