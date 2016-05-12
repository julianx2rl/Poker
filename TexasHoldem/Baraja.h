/**
* @file Baraja.h
* @version 1.0
* @date 07/05/2016
* @author GrupoProgra: Julian Arguedas Torres B50587 - Milton Delgado Fernandez B12188 - Kenneth Walker Fernandez B37663
* @title Clase Baraja
* @brief
*/

#pragma once

#include <list>
#include "Carta.h"

class Baraja
{
private:

	list<Carta*> listaCartas;

public:
	/**
	* @brief Constructor por defecto de Baraja
	*/
	Baraja();

	/**
	* @brief Saca una carta de la baraja
	* @return Puntero a una carta de la baraja
	*/
	Carta* getCarta();

	/**
	* @brief Le da a la Baraja un orden psudoaleatorio
	*/
	void barajarCartas();

	/**
	* @brief Imprime por Consola el estadi de la Baraja
	*/
	void imprimirMazo();

	/**
	* @brief Destruye la baraja y crea una nueva completa
	*/
	void reset();

	/**
	* @brief Destructor de Baraja
	*/
	~Baraja();
};
