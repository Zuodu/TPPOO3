/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"
//------------------------------------------------------------- Constantes
const int TCStart = 1000;
//----------------------------------------------------------- Types privés
//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques
void TrajetSimple::sauvegardeTrajet(ofstream &unFlux)
{
	if(id <TCStart)
	{
		unFlux << id << "|" << depart << "|" << arrivee << "|" << transport<< endl;
	}else
	{
		unFlux <<"|"<< depart << "|" << arrivee << "|" << transport;
	}
}

void TrajetSimple::afficherTrajet() const
{
#ifdef MAP
	cout << "Appel a la methode <afficherTrajet>" << endl;
#endif
        if(id < TCStart)
		{
            cout << "| TS" << id << " = " << "de  " << depart << " a " << arrivee << " en " << transport << endl;
        }else{
            cout <<"de  " << depart << " a " << arrivee << " en " << transport;
        }
}

//-------------------------------------------- Constructeurs - destructeur
TrajetSimple::TrajetSimple (int unId,char* unDepart, char* unArrivee, char* unTransport)
:Trajet(unDepart, unArrivee)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
	transport = unTransport;
    id = unId;
} //----- Fin de TrajetSimple


TrajetSimple::~TrajetSimple ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
		delete []transport;
}
//----- Fin de ~TrajetSimple
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

