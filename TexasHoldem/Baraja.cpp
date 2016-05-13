#include "stdafx.h"
#include "Carta.h"
#include "Baraja.h"

using namespace std;

bool compararCartas(const Carta* a, const Carta* b);

Baraja::Baraja() {
	char numeros[] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'D', 'J', 'Q', 'K' };
	int valor[] = { 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	char palos[] = { 'D', 'C', 'T', 'E' };
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 4; j++) {
			this->listaCartas.push_front(new Carta(numeros[i], valor[i], palos[j]));
		}
	}
}

void Baraja::barajarCartas() {
	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		list<Carta*>::iterator it1 = listaCartas.begin();
		list<Carta*>::iterator it2 = listaCartas.begin();

		int r = rand() % 80;
		int s = listaCartas.size();

		int limite1 = rand() % listaCartas.size();
		int limite2 = rand() % listaCartas.size();

		for (int i = 0; i < limite1; i++) {
			++it1;
		}

		for (int i = 0; i < limite2; i++) {
			++it2;
		}

		Carta * tmp = *it1;
		*it1 = *it2;
		*it2 = tmp;
	}
}

void Baraja::imprimirMazo() {
	cout << "Cartas:" << endl;
	for (list<Carta*>::iterator it = listaCartas.begin(); it != listaCartas.end(); ++it) {
		cout << *it << endl;
	}
}

Carta* Baraja::getCarta() {
	list<Carta*>::iterator it1 = listaCartas.begin();
	Carta * tmp = *it1;
	listaCartas.pop_front();
	return tmp;
}

void Baraja::reset() {
	listaCartas.clear();
	char numeros[] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'D', 'J', 'Q', 'K' };
	int valor[] = { 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	char palos[] = { 'D', 'C', 'T', 'E' };
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 4; j++) {
			listaCartas.push_front(new Carta(numeros[i], valor[i], palos[j]));
		}
	}
}

bool compararCartas(const Carta* a, const Carta* b) {
	return a->getValor() == b->getValor() && a->getPalo() < b->getPalo() || a->getValor() < b->getValor();
}

Baraja::~Baraja() {
}