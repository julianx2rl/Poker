#include "stdafx.h"
#include "Jugador.h"


Jugador::Jugador()
{
	disponible = 300;
	list<Carta*> manita;
	done = false;
	char* nombre = "unknown";
}

Jugador::Jugador(char* name)
{
	disponible = 300;
	list<Carta*> manita;
	done = false;
	nombre = name;
}

void Jugador::recieve(Carta* man) {
	manita.push_front(man);
}

int Jugador::bet(int amount) {
	if (amount <= 0) {
		if (amount < disponible) {
			amount = disponible;
		}
		disponible = disponible - amount;
		return amount;
	}
	else {
		return 0;
	}
}

void Jugador::finish(){
	done = true;
}

void Jugador::reset() {
	done = false;
}

bool Jugador::check()
{
	return done;
}

Carta* Jugador::getCarta()
{
	list<Carta*>::iterator it1 = manita.begin();
	Carta * tmp = *it1;
	manita.pop_front();
	return tmp;
}

void Jugador::imprimir() {
	for (list<Carta *>::iterator it = manita.begin(); it != manita.end(); ++it) {
		cout << **it;
	}
}

int Jugador::getMoney()
{
	return disponible;
}

char* Jugador::getName()
{
	return nombre;
}

void Jugador::recieveMoney(int amount) {
	disponible = disponible + amount;
}

void Jugador::sort() {
	manita.sort();
}

list<Carta*> Jugador::returnHand() {
	return manita;
}

Jugador::~Jugador()
{
}
