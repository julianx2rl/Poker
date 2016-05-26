// TexasHoldem.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Juego.h"


using namespace std;

int main() {
	Juego * juego = new Juego();

	juego->jugar();

	delete juego;
	return 0;
}