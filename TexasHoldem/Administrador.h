
/**
* @file Administrador.h
* @version 1.0
* @date 07/05/2016
* @author GrupoProgra: Julian Arguedas Torres B50587 - Milton Delgado Fernandez B12188 - Kenneth Walker Fernandez B37663
* @title Clase Administrador
* @brief Controla la simulacion del poker
*/

#pragma once
#include "Jugador.h"
#include "Carta.h"
#include "Baraja.h"
#include "stdafx.h"


class Administrador
{
public:

	int lote;
	int apuestaMinima;
	list<Jugador*> juego;
	list<Carta*> mesa;
	Baraja mano;

	/**
	* @brief Constructor por defecto del Administrador
	*/
	Administrador();

	/**
	* @brief Inicia la simulacion del poker
	* @param jugadores Numero de jugadores
	*/
	void iniciarJuego(int jugadores);

	/**
	* @brief Da dos cartas a cada uno de los jugadores.
	*/
	void reparto();

	/**
	* @brief Inicia el juego.
	*/
	void jugar();

	/**
	* @brief Coloca una carta en la mesa.
	*/
	void poner();

	/**
	* @brief Le presenta las opciones disponibles al jugador.
	*/
	void preguntar();

	/**
	* @brief Imprime las cartas que han sido colocadas en la mesa.
	*/
	void imprimir();

	/**
	* @brief Calcula el valor de la jugada del conjunto de cartas.
	* @param listaCartas.
	* @return Valor de la jugada en las cartas del maso obtenido.
	*/
	int valorJugada(list<Carta*> listaCartas);

	/**
	* @brief Calcula cual jugador tiene la mejor jugada.
	* @return Retorna al ganador de la partida
	*/
	Jugador* calcular();

	/**
	* @brief Destructor de Administrador
	*/
	~Administrador();

};
