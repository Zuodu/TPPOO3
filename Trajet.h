/*************************************************************************
                           Trajet.h  -  description
                             -------------------
    début                : 16/11/2016
    copyright            : (C) 2016 par Yohan GRACIA et Zifan YAO
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------

#if ! defined ( TRAJET_H )
#define TRAJET_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
class Trajet
{
    friend class Catalogue;
//---------------------------------------------------------fonctions amies
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
	virtual void sauvegardeTrajet(std::ofstream &unFlux)=0;
	virtual void afficherTrajet() const =0;
	bool comparerTrajet(char* depart,char * arrivee) const;
    bool comparerArrivee(char* uneArrivee) const ;
    bool comparerDepart(char* unDepart) const ;

//-------------------------------------------- Constructeurs - destructeur
    Trajet (char* unDepart, char* unArrivee );

    virtual ~Trajet ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
	char* depart;
	char* arrivee;
	int id;
private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};
#endif //TRAJET_H

