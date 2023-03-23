## Explicación del codigo main.cpp ##

Iniciamos el código llamando a las librerias que contengan las funciones i variables necessaria para ejecutar el prodecimiento que queremos. A parte de *Arduino.h*, en esta práctica necessitaremos la libreria *Wire.h* que contendra las funciones necessarias para mantener una conexion con nuestros dispositivos I2C. 

```c
#include <Arduino.h>
#include <Wire.h>
```

En la setup iniciaremos con la conexion Wire i Serial. Miestras la conexion con el serial no este activa, procederemos con el *I2C Scanner*.

```c
void setup()
{
Wire.begin();

Serial.begin(115200);
while (!Serial);             
Serial.println("\nI2C Scanner");
}
```

Empezamos el vucle del procedimiento declarando una variables e iniciando el escaneo de los dispostivos I2C. 

- La variable bit *error* controlara si es que hay algun error en la transmision de la connexion
- La variable bit *address* almacenara el valor de la direccion de cada dispostivo para identificarlo. Cada dispositivo registrado tiene una dirección assignada.
- La variable int *nDevices* contara el numero de dipostivos I2C connectados al Esp32.

```c
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
```

Ejecutamos un *for* para empezar la transmission I2C hacia cada dirrecion de dispostivo I2C i comprobar si es que hay angun error en la transmission.


```c
  for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
```

Si la variable error da zero, enviamos un menssaje al sistema conforme se ha encontrado una dipositivo en esa direccion *address*, retornado como tal su valor en Hexadecimal. acumulamos un valos en la variable *nDevices*.

```c
  if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
```

En el caso de que la variable error de 4 (valor que retorna el estado final de la transmission), se envia un menssaje al sistema conforme ha habido algun error deconocido en la dirreccion *address*, generalmente porque el dispositivo I2C assignado a la dirrecion no se encuentra connectado al Esp32. 

```c
  else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
```

Por ultimo i no menos importante, enviamos un menssaje al sistema conforme no hemos encontrado ningun dispostivo connectado, si es que la variable *nDevices* no ha acumulado ningun valor. En el caso contrario, daremos el escaneado por completado. Despues, simplemente procederemos con un *delay* (5 segundo es óptimo) para ejecutar nuestro siguente escaneo.

```c
    if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);
}
```