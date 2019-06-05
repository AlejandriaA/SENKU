#include "Funciones.h"

char** generar_tablero(int filas_columnas, int centro, int borde_1, int borde_2, int tab) { //recibe dimensiones según el tipo de tablero
	char** tablero = nullptr; //crear 'tablero' 
	tablero = new char* [filas_columnas]; //tablero es un arreglo
	for (int i = 0; i < filas_columnas; i++) {
		tablero[i] = new char[filas_columnas]; //tablero es un arreglo de arreglos tipo char
	}
	for (int i = 0; i < filas_columnas; i++) { //recorrer matriz para dibujar tablero
		for (int j = 0; j < filas_columnas; j++) {
			if (i == centro && j == centro) {
				tablero[i][j] = '+'; //colocar espacio vacío en el centro
			}
			else {
				switch (tab) { //'tab' indica el tipo de tablero
				case 1: case 2: //para el tablero inglés y alemán
					if ((i < borde_1 || i > borde_2) && (j < borde_1 || j > borde_2)) {
						tablero[i][j] = ' '; //no forma parte del tablero
					}
					else {
						tablero[i][j] = 'O'; //colocar fichas
					}
					break;
				case 3: //para el tablero diamante
					if (i + j >= 13 || i + j <= 3 || i - j >= 5 || j - i >= 5) {
						tablero[i][j] = ' '; //no forma parte del tablero
					}
					else {
						tablero[i][j] = 'O'; //colocar fichas
					}
				}
			}
		}
	}
	return tablero; //retornar dirección del tablero
}

void imprimir_tablero(char** tablero, int filas_columnas) { //imprimir el tablero
	cout << " ";
	for (int i = 1; i <= filas_columnas; i++) { //imprimir números de las columnas
		cout << "    " << i;
	}
	cout << endl;
	for (int i = 0; i < filas_columnas; i++) { //recorrer tablero
		cout << i + 1; //imprimir números de las filas
		for (int j = 0; j < filas_columnas; j++) {
			cout << setw(5) << tablero[i][j]; //imprimir cada posición
		}
		cout << endl << endl;
	}
}

bool posiciones_invalidas(char** tablero, int fila1, int columna1, int fila2, int columna2, int filas_columnas) { //revisar si las posiciones ingresadas son inválidas
	if (fila1 > 0 && fila1 < filas_columnas && fila2 > 0 && fila2 < filas_columnas && columna1 > 0 && columna1 < filas_columnas && columna2 > 0 && columna2 < filas_columnas) { //si están dentro del rango del tablero
		if (tablero[fila1 - 1][columna1 - 1] == 'O') { //si hay una ficha en la posición de origen
			if (tablero[fila2 - 1][columna2 - 1] == '+') { //si la posición de destino está vacía
				if (columna1 == columna2) { //si la ficha se está moviendo verticalmente
					if (fabs(fila2 - fila1) == 2) { //si se está moviendo solo dos espacios
						if (fila2 > fila1) { //si se está moviendo hacia abajo
							if (tablero[fila1][columna1 - 1] == 'O') //si hay una ficha en el medio de ambas posiciones
								return false; //las posiciones no son inválidas
							else return true; // las posiciones son inválidas
						}
						else { //si se está moviendo hacia arriba
							if (tablero[fila1 - 2][columna1 - 1] == 'O') //si hay una ficha en el medio de ambas posiciones
								return false; //las posiciones no son inválidas
							else return true; //las posiciones son inválidas
						}
					}
					else return true; //las posiciones son inválidas
				}
				else if (fila1 == fila2) { //si la ficha se está moviendo horizontalmente
					if (fabs(columna2 - columna1) == 2) { //si se está moviendo solo dos espacios
						if (columna2 > columna1) { //si se está moviendo a la derecha
							if (tablero[fila1 - 1][columna1] == 'O') //si hay una ficha en el medio de ambas posiciones
								return false; //las posiciones no son inválidas
							else return true; //las posiciones son inválidas
						}
						else { //si se está moviendo a la izquierda
							if (tablero[fila1 - 1][columna1 - 2] == 'O') //si hay una ficha en el medio de ambas posiciones
								return false; //las posiciones no son inválidas
							else return true; //las posiciones son inválidas
						}
					}
					else return true; //las posiciones son inválidas
				}
				else return true; //las posiciones son inválidas
			}
			else return true; //las posiciones son inválidas
		}
		else return true; //las posiciones son inválidas
	}
	else return true; //las posiciones son inválidas
}

void mover_ficha(char** tablero, int filas_columnas) { //ingresar posiciones y mover la ficha

	int fila1, columna1, fila2, columna2;
	do {
		cout << "Ingrese la posicion de origen (fila, columna): ";
		cin >> fila1 >> columna1; //posición de origen
		cout << "Ingrese la posicion de destino (fila, columna): ";
		cin >> fila2 >> columna2; //posición de destino
		cout << endl;
	} while (posiciones_invalidas(tablero, fila1, columna1, fila2, columna2, filas_columnas)); //seguir pidiendo posiciones mientras que las que se ingresen sean inválidas

	tablero[fila1 - 1][columna1 - 1] = '+'; //eliminar ficha en la posición de origen
	tablero[fila2 - 1][columna2 - 1] = 'O'; //poner la ficha en la posición de destino
	if (columna1 == columna2) { //si la ficha se mueve verticalmente
		if (fila2 > fila1) //si se mueve hacia abajo
			tablero[fila2 - 2][columna1 - 1] = '+'; //eliminar la ficha del medio
		else //si se mueve hacia arriba
			tablero[fila1 - 2][columna1 - 1] = '+'; //eliminar la ficha del medio
	}
	if (fila1 == fila2) { //si la ficha se mueve horizontalmente
		if (columna2 > columna1) //si se mueve a la derecha
			tablero[fila1 - 1][columna2 - 2] = '+'; //eliminar la ficha del medio
		else //si se mueve a la izquierda
			tablero[fila1 - 1][columna1 - 2] = '+'; //eliminar la ficha del medio
	}

}

bool quedan_movimientos(char** tablero, int filas_columnas, int borde) {
	string posibilidad_1 = "OO+"; //posibilidad que exista un movimiento
	string posibilidad_2 = "+OO"; //posibilidad que exista un movimiento
	for (int i = 0; i < filas_columnas; i++) { //recorrer tablero
		for (int j = 0; j < borde; j++) {
			string tres = ""; 
			tres = tres + tablero[i][j] + tablero[i][j + 1] + tablero[i][j + 2]; //agrupar 3 casilleros (horizontalmente) en 'tres'
			if (tres == posibilidad_1 || tres == posibilidad_2) //si la agrupacion de 3 coincide con las posibilidades 
				return true; //sí quedan movimientos
		}
	}
	for (int i = 0; i < borde; i++) {  //recorrer tablero
		for (int j = 0; j < filas_columnas; j++) {
			string tres = "";
			tres = tres + tablero[i][j] + tablero[i + 1][j] + tablero[i + 2][j]; //agrupar 3 casilleros (verticalmente) en 'tres'
			if (tres == posibilidad_1 || tres == posibilidad_2) //si la agrupacion de 3 coincide con las posibilidades 
				return true; //sí quedan movimientos
		}
	}
	return false; //si ninguna agrupacion coincidió con las posibilidades --> no quedan movimientos
}

void resultados(char** tablero, int filas_columnas) { 
	int fichas = 0; //contador
	for (int i = 0; i < filas_columnas; i++) { //recorrer tablero
		for (int j = 0; j < filas_columnas; j++) {
			if (tablero[i][j] == 'O') { 
				fichas += 1; //contar fichas que quedan en el tablero
			}
		}
	}
	if (fichas == 1) //si queda solo una ficha
		cout << endl << "GANASTE!!" << endl;
	else //si hay mas de una ficha
		cout << endl << "No quedan mas movimientos" << endl; 
}

void eliminar_tablero(char** tablero, int filas_columnas) { //recibe la dirección del tablero y lo elimina
	for (int i = 0; i < filas_columnas; i++) {
		delete[] tablero[i];
	}
	delete[] tablero;
	tablero = nullptr;
}

void tablero_ingles() {
	char** tablero = generar_tablero(7, 3, 2, 4, 1); //crear el tablero y guardar la dirección en 'tablero'
	imprimir_tablero(tablero, 7); //imprimir tablero
	do {
		mover_ficha(tablero, 8); //aceptar posiciones y mover fichas
		imprimir_tablero(tablero, 7); //imprimir tablero
	} while (quedan_movimientos(tablero, 7, 4)); //permitir seguir jugando mientras queden movimientos
	resultados(tablero, 7); //revisar si ganaste o perdiste cuando termina eljuego
	eliminar_tablero(tablero, 7); //elimina el tablero
}

void tablero_aleman() {
	char** tablero = generar_tablero(9, 4, 3, 5, 2); //crear el tablero y guardar la dirección en 'tablero'
	imprimir_tablero(tablero, 9); //imprimir tablero
	do {
		mover_ficha(tablero, 10); //aceptar posiciones y mover fichas
		imprimir_tablero(tablero, 9); //imprimir tablero
	} while (quedan_movimientos(tablero, 9, 6)); //permitir seguir jugando mientras queden movimientos
	resultados(tablero, 9); //revisar si ganaste o perdiste cuando termina eljuego
	eliminar_tablero(tablero, 9); //elimina el tablero
}

void tablero_diamante() {
	char** tablero = generar_tablero(9, 4, 3, 5, 3); //crear el tablero y guardar la dirección en 'tablero'
	imprimir_tablero(tablero, 9); //imprimir tablero
	do {
		mover_ficha(tablero, 10); //aceptar posiciones y mover fichas
		imprimir_tablero(tablero, 9); //imprimir tablero
	} while (quedan_movimientos(tablero, 9, 6)); //permitir seguir jugando mientras queden movimientos
	resultados(tablero, 9); //revisar si ganaste o perdiste cuando termina eljuego
	eliminar_tablero(tablero, 9); //elimina el tablero
}

void menu() {
	int opcion;
	do {
		cout << endl;
		cout << "----------------------------------------" << endl;
		cout << "            JUEGO SENKU            " << endl;
		cout << "----------------------------------------" << endl << endl;
		cout << "[1] Estilo ingles" << endl;
		cout << "[2] Estilo aleman" << endl;
		cout << "[3] Estilo diamante" << endl << endl;
		cout << "[0] Salir" << endl << endl;
		do {
			cout << "Seleccionar opcion : ";
			cin >> opcion;
		} while (opcion < 0 || opcion >3); //aceptar solo opciones 0, 1, 2, 3
		switch (opcion) { //opciones
		case 1:
			cout << endl << " || Estilo ingles ||" << endl << endl;
			tablero_ingles(); //usar el tablero ingles
			break;
		case 2:
			cout << endl << " || Estilo aleman ||" << endl << endl;
			tablero_aleman(); //usar el tablero aleman
			break;
		case 3:
			cout << endl << " || Estilo diamante ||" << endl << endl;
			tablero_diamante(); //usar el tablero diamante
			break;
		case 0:
			exit; //salir del programa
		}
	} while (opcion != 0); //seguir ejecutando el menu hasta que se escoja la opción 0
}