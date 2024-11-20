# Códigos Arduino
El código de este robot tiene dos archivos, el archivo 'puenteH' contiene una clase que nos permite mover un motor solo llamando a 'motor.move(valor)', el cual puede interpretar la dirección del movimiento a partir del signo del número que recibe. Polar.ino es el código principal que permite la conexión a la aplicación y requiere tener "puente.h" en la carpeta del proyecto..

Asegúrate que los pines coincidan con los del programa:

Si te posicionas en la misma dirección en la que mira el iglú, "Right" es el motor conectado a la derecha, "Left" a la izquierda, y "Tail" el que está por detrás (opuesto a la puerta). Los tres pines en cada uno de estos motores van en el orden de "OUT1,OUT2,ENA".
