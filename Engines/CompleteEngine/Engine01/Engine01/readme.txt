Para crear entidades:
- Circle Collider Component: Es para definir la forma en la que se manejan las colisiones. 
	- radio: radio para colisionar, establecer como la mitad del ancho y del alto
	- ancho: ancho de la imagen, establecer de acuerdo con las dimensiones de la imagen 
	- alto: alto de la imagen, establecer de acuerdo con las dimensiones de la imagen 

- Rigid Body Component: Es para el movimiento de las entidades.
	- velocidad (vector): cantidad de pixeles que se mueve por segundo en x y en y, se define la dirección con el signo
	Nota: Si la entidad va a ser estática o se va a mover con teclas entonces dejar todo en 0

- Script Component: Para usar scripts con la entidad. Poner solo si el usuario va a controlar esa entidad. 
	- function: la función de scripting que se va a ejecutar para esa entidad

- Sprite Component: Es para la imagen de la entidad en pantalla. 
	- id: nombre de la entidad
	- ancho: ancho de la imagen, establecer de acuerdo con las dimensiones de la imagen 
	- alto: alto de la imagen, establecer de acuerdo con las dimensiones de la imagen 
	- srcRectX: 
	- srcRectY: 

- Transform Component: Para la posición, la rotación y la escala de la entidad.
	- position(vector): posicion en x y en y en donde va a aparecer la entidad
	- scale(vector): modificación de las dimensiones de la imagen en x y en y
	- rotation: angulo de rotación de la imagen, dejar en 0 si se quiere ver bien la imagen

- Animation Component: Para manejar la animación de las entidades.
	- numFrames: número de animaciones de la entidad, si se pone mas de las que tiene sale raro
	- frameSpeedRate: velocidad a la que cambian las animaciones
	- isLoop: si es un ciclo o no, es decir, si la animación se detiene o no


Los ids:
0: para algo, no usar
1: player
2: bullet
3: enemy1
4: enemy1 bullet
5: enemy2
6: enemy3
7: enemy4
10: extraLife
