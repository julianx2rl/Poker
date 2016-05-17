#include "stdafx.h"
#include "Jugador.h"


Jugador::Jugador(char* name)
{
	disponible = 300;
	done = false;
	nombre = name;
}

Jugador::Jugador(char* name, int money)
{
	disponible = money;
	done = false;
	nombre = name;
}

void Jugador::recieve(Carta* man) {
	this->manita.push_front(man);
	this->manita.sort();
}

int Jugador::bet(int amount) {
	if (amount >= 0) {
		if (amount > this->disponible) {
			amount = this->disponible;
		}
		int tmp = this->disponible;
		this->disponible = tmp - amount;
		return amount;
	}
	else {
		return 0;
	}
}

void Jugador::finish() {
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
	list<Carta*>::iterator it1 = this->manita.begin();
	Carta * tmp = *it1;
	this->manita.pop_front();
	return tmp;
}

void Jugador::imprimir() {
	for (list<Carta *>::iterator it = this->manita.begin(); it != this->manita.end(); ++it) {
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

ostream & operator<<(ostream & out, Jugador & c) {
	return out << "[Nombre: " << c.nombre << "]";
}

Jugador::~Jugador()
{
}
