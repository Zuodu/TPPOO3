/*************************************************************************
                           Catalogue.h  -  description
                             -------------------
    début                : 16/11/2016
    copyright            : (C) 2016 par Yohan GRACIA et Zifan YAO
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H
using namespace std;
//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <fstream>
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
	void SauvegardeTypeTrajet() const;
	void SauvegardeFonctionVille() const;
	void SauvegardeIntervalle() const;
	void MenuSauvegarde() const;
	void ChargementTotal(string st);
    void ChargementType(string st,int);
    void ChargementCustomCity(string st);
    void ChargementCustomID(string st);
	string ListeFichiers() const;
	void MenuChargement();
    void delete2D(char** table);
    void delete2D(int** table);
    void delete3D(int*** table);
    bool AfficherCatalogue () const;
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
    string getArriveeFromString(const string st);
    string getDepartFromString(const string st);
    bool fileExists (const string st) const;
    void stringToTrajetSimple(const string st);
    void stringToTrajetCompose(const string st,const string st2);
    void gotoOPLine(ifstream &input);
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

