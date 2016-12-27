/*************************************************************************
                           Trajet.cpp  -  description
                             -------------------
    début                : 16/11/2016
    copyright            : (C) 2016 par Yohan GRACIA et Zifan YAO
*************************************************************************/
//---------- Réalisation de la classe <Trajet> (fichier Trajet.cpp) ------------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
//------------------------------------------------------ Include personnel
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe
//----------------------------------------------------------- Types privés
//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool Trajet::comparerTrajet(char* unDepart, char * uneArrivee) const
{
#ifdef MAP
	cout << "Appel a la methode <comparerTrajet>" << endl;
#endif
    bool correspond = false;
    if (strcmp(unDepart, depart) == 0 && strcmp(uneArrivee, arrivee) == 0)
    {
        correspond = true;
    }
    return correspond;
}

bool Trajet::comparerArrivee(char *uneArrivee) const
{
#ifdef MAP
	cout << "Appel a la methode <comparerArrivee>" << endl;
#endif
    return strcmp(uneArrivee, arrivee) == 0;
}

bool Trajet::comparerDepart(char *unDepart) const
{
#ifdef MAP
	cout << "Appel a la methode <comparerDepart>" << endl;
#endif
    return strcmp(unDepart, depart) == 0;
}

//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur
Trajet::Trajet (char* unDepart, char* unArrivee)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Trajet>" << endl;
#endif
	depart = unDepart;
	arrivee = unArrivee;
} //----- Fin de Trajet


Trajet::~Trajet ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Trajet>" << endl;
#endif
	delete []depart;
	delete []arrivee;
}
//----- Fin de ~Trajet


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

