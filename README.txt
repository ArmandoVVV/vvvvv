Documentación:

struct Game;          							//un struct que contiene la mayoria del material con la que se va a trabajar el juego.
typedef struct Game* gameRef;						//un apuntador a la struct Game para ahorrarnos el asterisco cada que se manda a llamar al struct.
struct FlipDirection;							//Un struct con todas las direcciones posibles en las que puede ser volteada una ficha.
typedef struct FlipDirection* directions;				//Un apuntador a la struct FlipDirection para ahorrarnos los asteriscos.

void RE_startGame(gameRef);						//Se elige el tamaño de nuestro tablero, se elige si se juega contra CPU, se establecen
						  			  todos los valores necesarios dentro de nuestra struct y se define la posicion de las
						  			  fichas iniciales del tablero

void RE_showBoard(gameRef);						//Se encarga de mostrar la interfaz gráfica de nuestro estado del juego al momento
void RE_showBoard_CMD(gameRef);						//Función comentada que servía para mostrar el tablero con stdin y stdout
int RE_winnerCheck(gameRef);						//Devuelve numero (+) si tokens negros ganan, numero(-) si blancos ganan y 0 si es empate
void RE_placeToken(gameRef);						//Posiciona el token en la coordenada seleccionada y aumenta 1 el total de tokens

int RE_validCheck(gameRef, directions, int row, int column);		//Checa si la posición es valida de acuerdo a las reglas del juego
int RE_getCoord(gameRef, directions);					//Convierte la posición donde damos click a la coordenada donde hicimos click, devuelve 1
									  si la coordenada esta dentro del rango y 0 si no esta en el rango
void RE_flip(gameRef, directions);					//Voltea las fichas que se tengan que voltear al poner la nueva ficha de acuerdo a las
									  reglas del juego
void RE_switchPlayer(gameRef);						//Cambia el turno al siguiente jugador
void RE_directionReset(directions);					//Reestablece la struct FlipDirection a todos sus valores en 0
void RE_availableMove(gameRef, directions);				//Checa si existe un movimiento posible en todo el tablero
void RE_getScore(gameRef);						//Asigna los valores del total de fichas negra y de fichas blancas

void delay(int number_of_seconds);					//Recibe un entero que son las désimas de segundo que el juego se va a quedar pausado
void RE_saveGame(gameRef);						//Salva el estado actual del juego incluyendo todas las fichas en el tablero, el tamaño del
									  tablero, el total de fichas y el turno actual
void RE_resumeGame(gameRef);						//Carga el archivo de guardado



Conclusiones:
Empezando desde el principio del proyecto, hubo complicaciones al querer instalar CLion ya que tuvimos dificultad al encontrar
donde se podia descargar con licencia y ya que lo tuvimos instalado también se nos complicó dentro del mismo Clion poder correr
el programa por problemas de del compilador ya que usabamos MinGW que no era compatible con importar el raylib.

Al empezar el proyecto estuvo facil la parte de declarar nuestro struct del juego, se nos complicó hasta que tuvimos
que hacer la función que detecta si la posición donde queremos poner la ficha es válida o no, ya que tuvimos que
pensar mucho en como la resolveríamos para ya despues codificarla, ya en código tambien estuvo difícil debuggearla porque
era una función muy grande, decidimos hacerla así de grande porque no se nos ocurrió hacer una función para cada movimiento.
Nuestro diseño al principio estaba hecho con una salida en la que las fichas se diferenciaban por "X" y "O" pero esto era
solamente para ir viendo como iba funcionando nuestro código ya que al final lo tendríamos que pasar a raylib para una
interfaz gráfica decente. Nuestro struct Game fue cambiando mucho a lo largo del desarrollo del proyecto porque a la vez que
hacíamos cosas nuevas le teníamos que agregar más cosas y por eso los elementos del juego cambiaban mucho, hubo funciones que
comentamos codigo parcial como en la de getCoord porque cambiamos el diseño de recibir las filas y columnas y la función anterior
a la de showBoard esta comentada como showBoard_CMD que representaba el tablero en una interfaz stdin y stdout.
La parte final de nuestro proyecto fue la implementación de la IA que realizaba movimientos y el guardado de juego, por eso es
lo mas incompleto del proyecto.

Los aprendizajes que obtuvimos de esta practica fueron a utilizar los structs, nuevos algoritmos como el de la validación de
la posición valida, a usar la libreria raylib para mejor diseño, a usar la herramiento de debuggeo que nos da Clion, aprendimos a
trabajar en equipo en desarrollo de código ya que nunca habíamos usado github, a importar bibliotecas externas usando CMake,
aprendimos a leer documentaciones de librerias externas y nos familiarizamos más con los tipos de datos abstractos.