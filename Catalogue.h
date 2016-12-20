/*************************************************************************
                           Catalogue.h  -  description
                             -------------------
    début                : 16/11/2016
    copyright            : (C) 2016 par Yohan GRACIA et Zifan YAO
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Parcours.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
class Catalogue
{
    friend class Trajet;
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	void SauvegardeTotale() const;
	void MenuChargement();
	string ListeFichiers() const;
	void ChargementTotal(string);
    void ChargementType(string,int);
    void ChargementCustomCity(string);
    void ChargementCustomID(string);
    void delete2D(char** table);
    void delete2D(int** table);
    void delete3D(int*** table);
    void AfficherCatalogue () const;
    void AddToCatalogue(Trajet *unTrajet);
	void AddToCatalogueTSSaisie();
	void AddToCatalogueTCSaisie();
	bool AddToCatalogueTCFin(char* arriveeC, Parcours* premierParcours);
    bool ligneVide(int index,int** matrixAdj,int nbMax);
    int*** RechercheGraphe(char *depart,char *arrivee,int** matrixAdj,int*** matrixIdAdj,char** matrixNodeAdj, int*** solutions,int nbMax);
    void AfficherSolution(int *** solutions);
	void RechercheSimple();
    void RechercheAvancee();
    void MenuCatalogue ();

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Catalogue (char* unNom);

    virtual ~Catalogue ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void stringToTrajetSimple(const string st);
    void stringToTrajetCompose(const string st,const string st2);
    int gotoOPLine(ifstream &input,int codeOP);
    int ** MatriceAdjacenceInversee();
    char ** MatriceTrajetsInversee();
    int *** MatriceNomTrajetsInversee();
private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
    Parcours * listeTrajets;
    char * nomCatalogue;
    int idTC;
    int idTS;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};
#endif //CATALOGUE_H

