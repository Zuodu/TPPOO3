/*************************************************************************
                           TrajetCompose  -  description
                             -------------------
    début                : Decembre 2016
    copyright            : (C) 2016 par Yohan GRACIA et Zifan YAO
*************************************************************************/

//---------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
//------------------------------------------------------ Include personnel
#include "TrajetCompose.h"
//------------------------------------------------------------- Constantes
const int TCstart = 1000;
//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void TrajetCompose::sauvegardeTrajet(ofstream &unFlux)
{
	Parcours * current = listeEscales;
	unFlux << id;
	unFlux << "|"<< depart << "|" << arrivee<< endl;
	while(current!=NULL)
	{
		current->trajetAssocie->sauvegardeTrajet(unFlux);
		current = current->nextParcours;
	}
	unFlux << endl;
}

void TrajetCompose::afficherTrajet() const
{
#ifdef MAP
	cout << "Appel a la methode <afficherTrajet>" << endl;
#endif
	Parcours * current = listeEscales;
	cout << "| TC"<<(id-TCstart)<<" = ";
	while(current!=NULL)
	{
		//cout << "TrajetCompose afficher while" << endl;
		current->trajetAssocie->afficherTrajet();
        cout << " | ";
		current = current->nextParcours;
	}
    cout<<endl;
}


//-------------------------------------------- Constructeurs - destructeur
TrajetCompose::TrajetCompose (int unId,char* unDepart, char* unArrivee, Parcours* uneListeEscales)
        :Trajet(unDepart, unArrivee)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
    listeEscales = uneListeEscales;
    id = unId;
} //----- Fin de TrajetCompose


TrajetCompose::~TrajetCompose ( )

{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
	Parcours* currentParcours = listeEscales;
	while(currentParcours->nextParcours != NULL)
	{
		listeEscales = listeEscales->nextParcours;
		delete currentParcours;
		currentParcours = listeEscales;
	}
	delete currentParcours;
} //----- Fin de ~TrajetCompose


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

