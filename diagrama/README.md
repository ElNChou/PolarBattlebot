# Diagrama electromecánico

El arma es muy simple: Solo utiliza un pin digital para mover un motor hacia atrás, tensando así el resorte hasta que la rueda llega al final y se suelta, liberando un golpe sencillo y rápido, para luego volver a cargarse.

¿Pero cómo movemos el motor? No es suficiente con solo aplicarle el pin digital, por lo que compartirá un puenteH con la tercera omniwheel. La idea de esto es que aproveche la energía proporcionada por la batería, pues debe ser capaz de oponerse al resorte.

Para que esto se pueda hacer utilizando un solo pin, se cierra la parte del circuito donde normalmente iría el ENB, en el Pin1B se coloca el que queramos usar para activar el motor y Pin2B estará siempre cerrado, así que lo conectamos a a tierra sacrificando a la vez la flexibilidad de mover el motor en resera, pero para el arma no nos interesa. Gracias a eso, podemos controlar el motor aprovechando la pila de la batería sencillamente, utilizando un solo pin.
