/*************************************************************************
                           Parcours  -  description
                             -------------------
    début                : Decembre 2016
    copyright            : (C) 2016 par Yohan GRACIA et Zifan YAO
*************************************************************************/

//---------- Réalisation de la classe <Parcours> (fichier Parcours.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
//------------------------------------------------------ Include personnel
#include "Parcours.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type Parcours::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Parcours::Parcours (Trajet *unTrajet)
// Algorithme :
//
{
	nextParcours = NULL;
	trajetAssocie = unTrajet;
#ifdef MAP
    cout << "Appel au constructeur de <Parcours>" << endl;
#endif
} //----- Fin de Parcours


Parcours::~Parcours ( )
// Algorithme :
//
{
	delete trajetAssocie;
#ifdef MAP
    cout << "Appel au destructeur de <Parcours>" << endl;
#endif
} //----- Fin de ~Parcours


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

