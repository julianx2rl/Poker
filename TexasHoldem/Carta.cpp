#include "stdafx.h"
#include "Carta.h"

using namespace std;

Carta::Carta(char numero, int valor, char palo) : numero(numero), valor(valor), palo(palo) {
}


Carta::~Carta() {
}

int Carta::getValor() const {
	return valor;
}

char Carta::getPalo() const {
	return palo;
}

int Carta::getNumero() const {
	return numero;
}

bool Carta::operator<(Carta & otra) {
	return this->valor < otra.valor;
}

ostream & operator<<(ostream & out, Carta & c) {
	return out << "[valor=" << c.valor << ", palo=" << c.palo << "]";
}