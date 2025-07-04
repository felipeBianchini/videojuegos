# Proyecto 2 de Creación de Videojuegos 2025-I

## Integrantes

Felipe Bianchini - C21178

Andre Salas - C27058

## Descripcion

El presente proyecto es un videojuego de plataformas, es decir, un juego que consiste en superar una serie de obstaculos para llegar a un punto final en el que se acaba el nivel. El juego se llama **Treasure Hunt**

## Juego

## Controles

A - Izquierda

D - Derecha

Espacio - Saltar / Subir en jumpables

W - Entrar a nivel / Subir escalera

I - Modo debug

P - Pausar

O - Reiniciar nivel

M - Volver al menu

Shift Izquierdo - Correr

### Menu Principal

El juego empieza en un menú principal en el que se puede mover libremente, el nivel es elegido presionando W en la puerta del mismo. Existen tres niveles, el primero está en la apertura del árbol, el segundo en la puerta de madera pequeña y el tercero en la puerta grande.

### Niveles

Al entrar a un nivel, se podrá mover libremente, el objetivo es superar enemigos y obstaculos hasta llegar al cofre que se encuentra en el final del nivel. Al llegar el nivel se terminará y se cargara el que le sigue.

### Enemigos

- **Pig:** Enemigo básico que se mueve en un area sin atacar directamente al jugador

- **Bird:** Enemigo que salta, es invencible al saltar

- **Turtle:** Enemigo invencible, si sus espinas están afuera la colision causa daño

## Compilación

Para compilar el juego se recomienda utilizar el makefile recomendado, es importante señalar que es necesario tener instaladas las bibliotecas SDL2, GLM y Sol para que la compilación funcione correctamente. Teniendo estas bibliotecas instaladas se puede compilar usando el comando

    make

Esto genera un ejecutable llamado game_engine.out, si desea correrlo puede hacerlo a mano o utilizar el siguiente comando:

    make run

En caso de querer ver la documentación doxygen se usa el comando:

    doxygen Doxyfile

Tras esto, se generará una carpeta llamada Doc, dentro de la cual se encontrará otra llamada html, donde se encuentra una versión html de la documentación.

## Diseño

El diseño del programa se encuentra en la carpeta diseño como una imagen png que contiene el diagrama UML del juego. Se incluye en este readme, pero debido a su tamaño se recomienda revisar la imagen completa para mejor legibilidad.

   ![Diagrama UML](/design/UML.png)


## Creditos

El código fue escrito principalmente en base a los videos del profesor Alberto Rojas, con comentarios Doxygen generados con ayuda de la IA Claude, con revisión posterior de nuestra parte.

Los sprites e imagenes fueron tomados de itch.io o de Google Images

Este proyecto fue creado por Felipe Bianchini (felipe.bianchini@ucr.ac.cr) y André Salas Chinchilla (correo andre.salaschinchilla@ucr.ac.cr) como parte del curso de desarrollo de videojuegos
