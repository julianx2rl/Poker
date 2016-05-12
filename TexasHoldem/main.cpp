// TexasHoldem.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Baraja.h"
#include "Administrador.h"
#include <iostream>

using namespace std;

int main() {
	Administrador * juego = new Administrador();

	juego->iniciarJuego(2);
	juego->reparto();
	juego->jugar();

	delete juego;
	return 0;
}