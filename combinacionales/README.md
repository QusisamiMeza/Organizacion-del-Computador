#   ¿QUÉ OPERACIONES HACE EL CIRCUITO inversor_4 SOBRE B?

El circuito _**inversor_4**_ tiene 2 entradas: una de 4 bits (**B**) y otra de un bit (**INV**). Esta última es la entrada de selección que determinará cuál será la salida.

El circuito separa los 4 bits de la entrada **B**, para luego invertir cada uno de ellos con la puerta *NOT*. Posteriormente unifica los 4 bits y a este resultado se le suma 1 con el circuito *incrementador_4*. Recordemos que el motivo de estas operaciones se debe a la lógica que se necesita implementar para negar un número: se niegan todos sus bits y se le suma 1.

Tanto el número **B** como **-B** pasan a ser entradas/datos de un multiplexor, cuyo bit de selección es **INV**. Es decir, el *multiplexor* se encargará de pasar **B** ó **-B** como salida del circuito, dependiendo de si **INV** vale **0** ó **1**.

Por lo tanto, cuando el bit de selección **INV** es **0**, la salida del circuito es el mismo número **B**. En cambio, si **INV** es **1**, la salida será su inverso aditivo **(-B)**. 
