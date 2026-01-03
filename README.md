# Organización del Computador

Repositorio correspondiente a los laboratorios prácticos de la materia Organización del Computador.

El proyecto aborda el estudio de la computadora desde una perspectiva de bajo nivel, incluyendo representación de datos, microarquitectura, diseño de circuitos, simulación de caché y programación cercana al hardware.

Todos los trabajos fueron desarrollados de forma grupal, promoviendo:

- División de tareas
- Discusión técnica
- Revisión de código
- Integración continua mediante Git

Los integrantes fueron:

- Lourdes Lier – [GitHub](https://github.com/lourdeslier)
- Melina Canal – [GitHub](https://github.com/melicanal)
- Qusisami Meza – [GitHub](https://github.com/QusisamiMeza) · [LinkedIn](https://www.linkedin.com/in/qusisami-luciana-meza-taco-229b2839a/)

---

## Laboratorios desarrollados y conceptos trabajados

### - Combinacionales
Diseño y análisis de circuitos combinacionales, aplicando lógica booleana y operaciones aritméticas a nivel de hardware.
Se implementaron circuitos como inversores y combinadores de bits, utilizando multiplexores y complemento a dos.

### - DataLab | Representación de Datos
Resolución de problemas de manipulación de datos a nivel de bits bajo fuertes restricciones del lenguaje C.
Se profundizó en la representación binaria de enteros y punto flotante (IEEE 754), optimizando soluciones sin estructuras de control ni operadores de alto nivel.

### - MicroLab | Taller de Microarquitectura
Análisis y extensión de una microarquitectura microprogramada, utilizando un procesador didáctico simulado.
Se programó en lenguaje ensamblador, se estudió el datapath y la unidad de control, y se agregaron nuevas instrucciones mediante microcódigo.

### - ASM Lab | Estructuras de Datos y Bajo Nivel
Implementación de estructuras de datos genéricas en C, haciendo uso intensivo de punteros y manejo manual de memoria.
Se trabajó con listas doblemente enlazadas y arreglos dinámicos, utilizando punteros a funciones para abstraer operaciones según el tipo de dato.

### - CacheLab | Simulador de Caché
Desarrollo de un simulador de caché parametrizable, enfocado en el análisis del rendimiento de memoria.
Se implementaron políticas de asociatividad y reemplazo LRU, recolectando métricas como hits, misses y tiempos de acceso a partir de trazas reales.