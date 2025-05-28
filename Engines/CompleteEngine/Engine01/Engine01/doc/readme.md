# Galactic Siege

## Descripción del juego

El juego es de tipo space invaders, es decir, consiste de una nave que se controla con comandos emitidos por el usuario
con el objetivo de eliminar a los enemigos y de esquivar sus proyectiles. En esta implementación se optó por automatizar 
el disparo de la nave del jugador, entonces no se requiere de ninguna tecla para disparar.
A continuación se enlistan las principales características del juego:

### Enemigos implementados

Se implementaron cuatro enemigos con diferentes mecánicas de ataque y movimiento. Los primeros tres son enemigos comunes,
mientras que el último es una especie de boss final. Estos son los enemigos implementados, así como sus nombres, sus habilidades
y la cantidad de puntos que dan por eliminarlos:

| Ruta | Nombre | Habilidades | Puntos por muerte |
|--------------|--------------|
| [Ver](../assets/images/enemy9.png) | Oculus | Se mueve horizontalmente disparando proyectiles hacia abajo | 100 |
| [Ver](../assets/images/enemy8.png) | Harasser | Persigue la nave y explota al alcanzarla | 50 |
| [Ver](../assets/images/enemy3.png) | Spiker | Se mueve aleatoriamente por la pantalla y arroja proyectiles en todas las direcciones | 250 |
| [Ver](../assets/images/boss2.png) | Overmaw | Se queda estático en la pantalla disparando oleadas con diferentes mecánicas de proyectiles. Al terminar con los proyectiles, invoca dos oleadas de los tres enemigos anteriores. Luego repite el ciclo. | 500 |

### Power Ups implementados

Se implementaron dos power ups con el objetivo de facilitar la supervivencia del jugador.
Estos son los power ups implementados, así como su habilidad:

| Ruta | Nombre | habilidad |
|--------------|--------------|
| [Ver](../assets/images/life_PU.png) | Vida extra | Otorga una vida adicional |
| [Ver](../assets/images/nuke_PU.png) | Bomba atómica | Cae una bomba atómica que elimina a todos los enemigos, menos a Overmaw |

### Niveles implementados

Se implementaron tres niveles, cada uno con diferente condición de victoria, enemigos disponibles y power ups disponibles.
Cada nivel es más complicado que el anterior. Estos son los niveles que se implementaron, así como sus características:

| Nivel | Enemigos presentes | Condición de victoria | Power Ups disponibles|
|--------------|--------------|
| 1 | Oculus, Harasser | Sobrevivir 60 segundos | Vida extra |
| 2 | Oculus, Harasser, Spiker | Sobrevivir 90 segundos | Vida extra, Bomba atómica |
| 3 | Oculus, Harasser, Spiker, Overmaw | Asesinar a Overmaw | Vida extra, Bomba atómica |

## Manual de uso

El usuario solo puede controlar el movimiento de la nave espacial. No se requiere de ninguna tecla para disparar puesto que esto está
automatizado. A continuación se enlistan las teclas que están habilitadas para el usuario, así como su función:

| Tecla |Función |
|--------------|--------------|
| W | Mueve la nave hacia arriba |
| S | Mueve la nave hacia abajo |
| A | Mueve la nave hacia la izquierda |
| D | Mueve la nave hacia derecha |

Adicionalmente, está habilitado el click izquierdo del mouse para seleccionar opciones en los menús.

## Instrucciones de ejecución

El juego está diseñado en el lenguaje de programación C++ con soporte para scripts de Lua.

### Requisitos del sistema

Para compilar el juego se requiere de un entorno compatible con C++ versión 17 o superior, además de las siguientes librerías:

| Librería |
|--------------|
| SDL2 |
| SDL_image_ |
| SDL_ttf_ |
| SDL_mixer |
| Sol2 |
| GLM |

### Estructura del proyecto

El proyecto consta de dos carpetas principales: **assets** y **src**. Dentro de **assets** hay varias subcarpetas, las cuales contienen
los sprites, los efectos de sonido, los backgrounds, la música, los fonts y los scripts de lua. Dentro de la carpeta **src** está todo el
código fuente separado en subcarpetas para mayor orden.

## Diagrama UML