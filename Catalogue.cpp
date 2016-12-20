/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
#include <vector>
#include <dirent.h>
#include <direct.h>
#include <stdlib.h>
//------------------------------------------------------ Include personnel
#include "Catalogue.h"


//------------------------------------------------------------- Constantes
const int LG = 20;
const int  TCstart = 1000;
const int maxMemeTrajet = 5;
const int fileTSStartingLine=6;
//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
void Catalogue::SauvegardeTotale() const
{
	string nomFichier;
    cout<<"veuillez donner le nom du fichier a utiliser :"<<endl;
	cin >> nomFichier;
	nomFichier += ".txt";
	time_t date = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	ofstream fichierSortie;
	fichierSortie.open(".\\battery\\"+nomFichier);
	
	//HeadLine
	fichierSortie << nomCatalogue << endl;
	fichierSortie << "Totale" << endl;
	fichierSortie << idTS-1 << endl;
	fichierSortie << idTC-TCstart-1 << endl;
	fichierSortie << ctime(&date) << endl;
	//Trajets Simples
	Parcours* currentParcours = listeTrajets;
	while (currentParcours->nextParcours != NULL)
	{
		currentParcours = currentParcours->nextParcours;
		if(currentParcours->trajetAssocie->id<=TCstart)
		{
			currentParcours->trajetAssocie->sauvegardeTrajet(fichierSortie);
		}
	}
	fichierSortie << endl;
	//Trajets composés
	currentParcours = listeTrajets;
	while (currentParcours->nextParcours != NULL)
	{
		currentParcours = currentParcours->nextParcours;
		if(currentParcours->trajetAssocie->id>TCstart)
		{
			currentParcours->trajetAssocie->sauvegardeTrajet(fichierSortie);
		}
	}
	
	fichierSortie.close();
}

void Catalogue::ChargementType(string nomFichier, int noOp) {

}

void Catalogue::ChargementCustomCity(string nomFichier){

}

void Catalogue::ChargementCustomID(string nomFichier) {

}

void Catalogue::ChargementTotal(string nomFichier)
{
	ifstream chargement;
	string lineText,lineText2;
    chargement.open(".\\battery\\"+nomFichier);
	if(chargement.good())
	{
		cout << "Le fichier a ete ouvert" << endl;
	}else
	{
		perror("Le fichier nexiste pas ou est en cours d'utilisation" );
	}
    // remplacement total du catalogue
    gotoOPLine(chargement,1);
    Parcours* currentParcours = listeTrajets;
    while(currentParcours->nextParcours != NULL)
    {
        currentParcours = currentParcours->nextParcours;
    }
    while(getline(chargement,lineText)) {
        if(atoi(lineText.substr(0,4).c_str())<=1000 && atoi(lineText.substr(0,4).c_str())>0) {
            stringToTrajetSimple(lineText);
        }
        if(atoi(lineText.substr(0,4).c_str())>1000){
            getline(chargement,lineText2);
            stringToTrajetCompose(lineText,lineText2);
        }
    }
}

string Catalogue::ListeFichiers() const
{
    //init des variables
    int fileID;
    int i=1;
	ifstream output;
    vector<string> fileNames;
    string outputName(".\\battery\\");
    string lineReader;
	DIR *dir;
	struct dirent *ent;
    //listage des fichiers du repertoire
	if ((dir = opendir (".\\battery")) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
            if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0) {
                cout<<"File "<<i++<<": ";
                cout<<ent->d_name;
                outputName.append(ent->d_name);
                fileNames.push_back(outputName);
                output.open(outputName);
                getline(output,lineReader);
                cout<<"|"<<lineReader;
                getline(output,lineReader);
                cout<<"|"<<lineReader<<endl;
                output.close();
                output.clear();
                outputName = ".\\battery\\";
            }
		}
		closedir (dir);
        //Phase de selection du catalogue a charger
        if(i!=1) {
            cout << "Veuillez indiquer le numero du catalogue a charger :" << endl;
            cin >> fileID;
            return fileNames[fileID - 1];
        }else{
            cout<< "Aucun Catalogue a charger. Retour au menu..."<<endl;
            cout<< "----------------------------------------------------"<<endl;
            return "0";
        }
	} else {
		//could not open dir
		perror ("Erreur lors de louverture du repertoire");
		return "0";
	}

}

void Catalogue::MenuChargement()
{
    string nomFichier;
    int noOp;
	cout<<"Menu Chargement :"<<endl;
	nomFichier = ListeFichiers();
    if(nomFichier=="0"){
        return;
    }else{
        nomFichier = nomFichier.substr(10);
        cout<<"Vous avez choisi le fichier : "<<nomFichier<<endl;
        cout << "Quelles trajets voulez-vous selectionner ?" << endl;
        cout << "1: Tous les trajets du fichier de sauvegarde." << endl;
        cout << "2: Que les trajets simples." << endl;
        cout << "3: Que les trajets composes." << endl;
        cout << "4: Par nom de ville." << endl;
        cout << "5: Selon une selection de trajets"<<endl;
        cin>> noOp;
        switch (noOp) {
            case 1:
                ChargementTotal(nomFichier);
                break;
            case 2:
                ChargementType(nomFichier,noOp);
                break;
            case 3:
                ChargementType(nomFichier,noOp);
                break;
            case 4:
                ChargementCustomCity(nomFichier);
                break;
            case 5:
                ChargementCustomID(nomFichier);
                break;
            default:
                cout << "Retour au menu principal..." << endl;
                return;
        }
    }
}

void Catalogue::delete2D(char **table)
{
#ifdef MAP
	cout << "Appel a la methode <delete2D char**>" << endl;
#endif
	int nbMax = idTC-TCstart+idTS;
	for(int i=0;i<nbMax;i++){
		delete[] table[i];
	}
	delete[] table;
}

void Catalogue::delete2D(int **table)
{
#ifdef MAP
	cout << "Appel a la methode <delete2D int**>" << endl;
#endif
	int nbMax = idTC-TCstart+idTS;
	for(int i=0;i<nbMax;i++){
		delete[] table[i];
	}
	delete[] table;
}

void Catalogue::delete3D(int ***table)
{
#ifdef MAP
	cout << "Appel a la methode <delete3D>" << endl;
#endif
	int nbMax = idTC-TCstart+idTS;
	for(int i=0;i<nbMax;i++) {
		for (int j = 0; j < nbMax; j++)
		{
			delete[] table[i][j];
		}
		delete[] table[i];
	}
	delete[] table;
}

void Catalogue::AfficherCatalogue () const
{
#ifdef MAP
	cout << "Appel a la methode <AfficherCatalogue>" << endl;
#endif
	cout <<"--------------------------------------------"<<endl;
	cout<<"Affichage du catalogue : "<< nomCatalogue << endl;
	cout <<"--------------------------------------------"<<endl;
	bool cataVide=true;
	Parcours* currentParcours = listeTrajets;
	while (currentParcours->nextParcours != NULL)
	{
		currentParcours = currentParcours->nextParcours;
		currentParcours->trajetAssocie->afficherTrajet();
		cataVide = false;
	}
	if(cataVide)
	{
		cout << "La catalogue est vide" << endl;
	}
	cout <<"--------------------------------------------"<<endl;
	cout <<"--------------FIN DU CATALOGUE--------------"<<endl;
}

void Catalogue::AddToCatalogue (Trajet *unTrajet)
{
#ifdef MAP
	cout << "Appel a la methode <AddToCatalogue>" << endl;
#endif
	Parcours* currentParcours = listeTrajets;
	while(currentParcours->nextParcours != NULL)
	{
		currentParcours = currentParcours->nextParcours;
	}
	Parcours *nouveauParcours = new Parcours(unTrajet);
	currentParcours->nextParcours = nouveauParcours;
}
void Catalogue::AddToCatalogueTSSaisie()
{
#ifdef MAP
	cout << "Appel a la methode <AddToCatalogueTSSaisie>" << endl;
#endif
	char unDepart[LG];
	char uneArrivee[LG];
	char unTransport[LG];
	cout << "Entree de TS"<<idTS<<" :"<<endl;
	cout << "Donnez la ville de depart" << endl;
	cin >> unDepart;
	cout << "Donnez la ville d'arrivee" << endl;
	cin >> uneArrivee;
	cout << "Donnez le moyen de transport" << endl;
	cin >> unTransport;
	char * depart = new char[LG]; //ajustement taille chaines de caractères
	char * arrivee = new char[LG];
	char * transport = new char[LG];

	//copie des attributs
	strcpy(depart, unDepart);
	strcpy(arrivee, uneArrivee);
	strcpy(transport, unTransport);

	TrajetSimple *unTrajet = new TrajetSimple(idTS,depart, arrivee, transport);
	AddToCatalogue(unTrajet);
	idTS++;
}

void Catalogue::AddToCatalogueTCSaisie()
{
#ifdef MAP
	cout << "Appel a la methode <AddToCatalogueTCSaisie>" << endl;
#endif
	char unDepartC[LG];
	char uneArriveeC[LG];
	char uneArrivee[LG];
	char unTransport[LG];
	cout << "entree de TC"<<idTC-TCstart<<" :"<<endl;
	cout << "Donnez la ville de depart du trajet compose" << endl;
	cin >> unDepartC;
	cout << "Donnez la ville d'arrivee du trajet compose" << endl;
	cin >> uneArriveeC;
	cout << "Donnez la ville d'arrivee du premier trajet simple" << endl;
	cin >> uneArrivee;
	cout << "Donnez le moyen de transport du premier trajet simple" << endl;
	cin >> unTransport;
	char * depart = new char[LG];
	char * departC = new char[LG];
	char * arrivee = new char[LG];
	char * arriveeC = new char[LG];
	char * transport = new char[LG];

	//copie des attributs
	strcpy(depart, unDepartC);
	strcpy(departC, unDepartC);
	strcpy(arrivee, uneArrivee);
	strcpy(arriveeC, uneArriveeC);
	strcpy(transport, unTransport);
	TrajetSimple *unTrajet = new TrajetSimple(idTC,depart, arrivee, transport);
	Parcours * premierParcours = new Parcours(unTrajet);
	TrajetCompose * unTrajetCompose = new TrajetCompose(idTC,departC, arriveeC, premierParcours);
	AddToCatalogue(unTrajetCompose);
	bool trajetFini = false;
	while (!trajetFini)
	{
		trajetFini=AddToCatalogueTCFin(arriveeC,premierParcours);
	}
	idTC++;
}

bool Catalogue::AddToCatalogueTCFin(char* arriveeC, Parcours* premierParcours)
{
#ifdef MAP
	cout << "Appel a la methode <AddToCatalogueTCFin>" << endl;
#endif
	char unDepart[LG];
	char uneArrivee[LG];
	char unTransport[LG];
	bool trajetFini = false;
	cout << "Donnez la ville de depart de votre trajet intermediaire" << endl;
	cin >> unDepart;
	cout << "Donnez la ville d'arrivee de votre trajet intermediaire" << endl;
	cin >> uneArrivee;
	cout << "Donnez le moyen de transport de votre trajet intermediaire" << endl;
	cin >> unTransport;
	char * depart = new char[LG];   //ajustement taille chaines de caractères
	char * arrivee = new char[LG];
	char * transport = new char[LG];
	strcpy(depart, unDepart);
	strcpy(arrivee, uneArrivee);
	strcpy(transport, unTransport);
	TrajetSimple *unTrajetSimple = new TrajetSimple(idTC,depart, arrivee, transport);
	Parcours * unParcours = new Parcours(unTrajetSimple);

	Parcours* currentParcours = premierParcours;
	while (currentParcours->nextParcours != NULL)
	{
		currentParcours = currentParcours->nextParcours;
	}
	currentParcours->nextParcours = unParcours;
	if (strcmp(arriveeC, arrivee)==0)
	{
		trajetFini = true;
	}
	//delete[] depart;
	//delete[] arrivee;
	//delete[] transport;
	return trajetFini;
}

bool Catalogue::ligneVide(int index,int** matrixAdj,int nbMax)
{
#ifdef MAP
	cout << "Appel a la methode <ligneVide>" << endl;
#endif
	for(int i =0;i<nbMax;i++)
	{
		if(matrixAdj[index][i]==1)
		{
			return false;
		}
	}
	return true;
}

int*** Catalogue::RechercheGraphe(char *depart,char *arrivee,int **matrixAdj,int ***matrixIdAdj,char **matrixNodeAdj, int*** solutions,int nbMax)
{
#ifdef MAP
	cout << "Appel a la methode <RechercheGraphe>" << endl;
#endif
	int indexParcouru[nbMax];
	int departIndex = 0,arriveeIndex = 0;
	int currentDepartIndex =0;
	int lastDepartIndex = 0;
	int i,j,k,l;
	int indexParcouruIndex = 0;
	int currentSolutionIndex = 0,currentSolutionColumn = 0,lastT=0;
	bool over = false;
	//init des indexs : on les situe selon le depart et l'arrivee désirés
	for(i=0;i<nbMax;i++)
	{
		if(strcmp(matrixNodeAdj[i],depart)==0)
		{
			arriveeIndex = i;
		}
		if(strcmp(matrixNodeAdj[i],arrivee)==0)
		{
			departIndex = i;
			currentDepartIndex = i;
			lastDepartIndex = currentDepartIndex;
			for(l=0;l<nbMax;l++)
			{
				indexParcouru[l] = i;
			}
			indexParcouruIndex++;
		}
	}
	//recherche des trajets par profondeur
	while(!over)
	{
#ifdef MAP
		cout << "Tick while" << endl;
#endif
		for(j=0;matrixAdj[currentDepartIndex][j]!=1 && j<nbMax;j++){}//recherche du premier 1 de la ligne
		if(j==nbMax){j=nbMax-1;}

		if(j == arriveeIndex)
		{//si le 1 se trouve dans la colonne de l'arrivee
#ifdef MAP
			cout << "Tick solution trouvee!" << endl;
#endif
			solutions[currentSolutionIndex][currentSolutionColumn] = matrixIdAdj[currentDepartIndex][j];
			currentSolutionIndex++;// je change de ligne de solution (solution complète)
			lastT = currentSolutionColumn;
			currentSolutionColumn=0;//je remet le premier trajet à 0
			matrixAdj[currentDepartIndex][j] = 0;//je considère que le trajet a disparu
			//je reviens au début du while
		}else
		{
			if (!ligneVide(j, matrixAdj,nbMax))
			{//si la ligne suivante n'est pas vide,
#ifdef MAP
				cout << "Tick if de ligne pas vide" << endl;
#endif
				solutions[currentSolutionIndex][currentSolutionColumn] = matrixIdAdj[currentDepartIndex][j];
				currentSolutionColumn++;//j'enregistre le trajet à la suite,
				matrixAdj[currentDepartIndex][j] = 0;
				lastDepartIndex = currentDepartIndex;
				currentDepartIndex = j;// je change de ligne et j'enregistre la derniere ligne
				indexParcouru[indexParcouruIndex] = j;
				indexParcouruIndex++;// je dit que j'ai utilisé cette ligne
			} else
			{//SI LA LIGNE EST VIDE
#ifdef MAP
				cout << "Tick if de ligne vide" << endl;
#endif
				for(i=0;i<nbMax;i++)
				{
					for (k = 0; k < currentSolutionIndex; k++)
					{
						for (l = 0; l < nbMax; l++) {
							if (solutions[k][l] == matrixIdAdj[j][i])
							{
								if (k != (currentSolutionIndex - 1) && l != lastT)
								{
									for (i = l;i<nbMax;i++)
									{
										solutions[currentSolutionIndex][currentSolutionColumn] = solutions[k][i];
										currentSolutionColumn++;
									}
								}
							}
						}
					}
				}
				matrixAdj[currentDepartIndex][j] = 0;//si la ligne suivante est vide, je supprime ce trajet
				if(currentSolutionColumn>0)
				{
					solutions[currentSolutionIndex][currentSolutionColumn-1] = matrixIdAdj[0][0];
					currentSolutionColumn--;
				}else
				{
					solutions[currentSolutionIndex][currentSolutionColumn] = matrixIdAdj[0][0];
				}
			}
			//FIND DU DEUXIEME IF
		}//FIN DU PREMIER IF
		over = true;
		for(i=0;i<nbMax && over;i++){
			if(!ligneVide(indexParcouru[i],matrixAdj,nbMax)){
				if(currentDepartIndex!=j) {
					currentDepartIndex = lastDepartIndex;
				}
				over = false;
			}
		}
		// TODO : a confirmer que c'est necessaire
		if(j == nbMax-1 && currentDepartIndex == departIndex){over = true;}

	}
	return solutions;
}

void Catalogue::AfficherSolution(int *** solutions)
{
#ifdef MAP
	cout << "Appel a la methode <AfficherSolution>" << endl;
#endif
//TODO : faire une methode propre de parcours en largeur !!!
	int nbMax = idTC - TCstart + idTS;
	bool changerArete = true;
	bool sautLigne = false;
	cout << "Affichage des solutions disponibles" << endl;
	cout<<"--------------------------------------------------------------------------"<<endl;
	for (int g = (nbMax-1); g >=0; g--)
	{
		if(solutions[g][0][0]!=0)
		{
			cout << "Suggestion de Voyage : " << endl;
		}
		for (int i = (nbMax-1); i >= 0; i--)
		{
			if(solutions[g][i][0]!=0 && changerArete)
			{
				sautLigne = true;
				changerArete = false;
				cout << "Prendre un de ces trajets : ";
			}
			for(int j=0;j<maxMemeTrajet;j++)
			{

				if(solutions[g][i][j] !=0)
				{
					if(solutions[g][i][j]<=TCstart)
					{
						cout << " " << "TS" << solutions[g][i][j];
					}else {
						cout << " " << "TC" << solutions[g][i][j] - TCstart;
					}
				}
			}//FIN MEME ARETE
			if(sautLigne)
			{
				if(i>0){cout<<"     puis,";}else{cout<<"        puis vous etes arrive.";}
				cout<<endl;
				changerArete = true;
			}
			sautLigne = false;
		}
		//FIN MEME SOLUTION
	}//FIN DES SOLUTIONS
	cout<<"--------------------------------------------------------------------------"<<endl;
}

void Catalogue::RechercheSimple()
{
#ifdef MAP
	cout << "Appel a la methode <RechercheSimple>" << endl;
#endif
	char unDepart[LG];
	char uneArrivee[LG];
	cout << "Donnez la ville de depart qui vous interesse:" << endl;
	cin >> unDepart;
	cout << "Donnez la ville d'arrivee qui vous interesse:" << endl;
	cin >> uneArrivee;
	char * departRecherche = new char[strlen(unDepart)];   //ajustement taille chaines de caractères
	char * arriveeRecherche = new char[strlen(uneArrivee)];
	strcpy(departRecherche, unDepart);
	strcpy(arriveeRecherche, uneArrivee);
	Parcours* currentParcours = listeTrajets;
	bool estEgal;
	bool auMoinsUn = false;
	while (currentParcours->nextParcours != NULL)
	{
		currentParcours = currentParcours->nextParcours;
		estEgal = currentParcours->trajetAssocie->comparerTrajet(departRecherche, arriveeRecherche);
		if (estEgal)
		{
			auMoinsUn = true;
			currentParcours->trajetAssocie->afficherTrajet();
		}
	}
	if (!auMoinsUn)
	{
		cout << "Aucun trajet du catalogue ne correspond a votre recherche" << endl;
	}
	delete[] departRecherche;
	delete[] arriveeRecherche;
}

void Catalogue::RechercheAvancee()
{
#ifdef MAP
	cout << "Appel a la methode <RechercheAvancee>" << endl;
#endif
	char *rechercheDepart = new char[LG];
	char *rechercheArrivee = new char[LG];
	int currentRow = 0;
	int currentDoublon = 0;
	int departIndex = 0;
	int arriveeIndex = 0;
	bool existeInMatRow = false;
	int nbMax = idTC-TCstart+idTS;
	int*** solutions = MatriceNomTrajetsInversee();
	int ** matrixInv = MatriceAdjacenceInversee();
	char** matrixTrjInv = MatriceTrajetsInversee();
	int *** matrixIdInv = MatriceNomTrajetsInversee();
	Parcours* currentParcours = listeTrajets;
	while (currentParcours->nextParcours != NULL){
		//chaque trajet est traite et mis dans les differentes matrices
		//on saute le premier qui est un init
		currentParcours = currentParcours->nextParcours;
		//traitement de l'arrivee
		for(int i=0;i<nbMax;i++)
		{
			if(currentParcours->trajetAssocie->comparerArrivee(matrixTrjInv[i]))
			{
				existeInMatRow = true;
			}
		}
		if(!existeInMatRow)
		{
			//matrixTrjInv[currentRow] = currentParcours->trajetAssocie->arrivee;
			strcpy(matrixTrjInv[currentRow],currentParcours->trajetAssocie->arrivee);
			currentRow++;
			existeInMatRow = false;
		}

		//traitement du depart
		for(int j=0;j<nbMax;j++) {
			if (currentParcours->trajetAssocie->comparerDepart(matrixTrjInv[j]))
			{
				existeInMatRow = true;
				departIndex = j;
			}
		}

		if(!existeInMatRow){
			//matrixTrjInv[currentRow] = currentParcours->trajetAssocie->depart;
			strcpy(matrixTrjInv[currentRow],currentParcours->trajetAssocie->depart);
			existeInMatRow = false;
			matrixInv[currentRow-1][currentRow] = 1;
			matrixIdInv[currentRow-1][currentRow][currentDoublon] = currentParcours->trajetAssocie->id;
			currentRow++;
		}
		if(existeInMatRow)
		{  // si sa ligne existe deja
			for(int k=0;k<nbMax;k++)
			{
				if (currentParcours->trajetAssocie->comparerArrivee(matrixTrjInv[k]))
				{
					arriveeIndex = k; // on cherche l'index de l'arrivee
				}
			}
			matrixInv[arriveeIndex][departIndex] = 1; // on indique le trajet exsite
			while(matrixIdInv[arriveeIndex][departIndex][currentDoublon]!=0)
			{
				currentDoublon++;
			} //on cherche la derniere case vide des id deja parcourus qui correspondent au meme trajet en gros
			matrixIdInv[arriveeIndex][departIndex][currentDoublon] = currentParcours->trajetAssocie->id;
			// on insere l'id du trajet actuel
		}
		// on reinitialise les doublons
		currentDoublon = 0;
		existeInMatRow = false;
		// on va au prochain trajet
	}//FIN DU WHILE

	//input de la recherche
	cout<<"Choisissez la ville de depart"<<endl;
	cin >>rechercheDepart;
	cout<<"Choisissez la ville d'arrivee"<<endl;
	cin >>rechercheArrivee;

	//calcul des solutions et affichage

	solutions = RechercheGraphe(rechercheDepart,rechercheArrivee,matrixInv,matrixIdInv,matrixTrjInv,solutions,nbMax);
	AfficherSolution(solutions);

	//delete
	//TODO : valgrind trouve une erreur, améliorer l'algo pour delete proprement.
	delete[] rechercheArrivee;
	delete[] rechercheDepart;
	delete2D(matrixTrjInv);
	delete2D(matrixInv);
	delete3D(solutions);
	delete3D(matrixIdInv);
	delete matrixTrjInv;
	delete matrixIdInv;

}

void Catalogue::MenuCatalogue ()
{
#ifdef MAP
	cout << "Appel a la methode <MenuCatalogue>" << endl;
#endif
	bool sortie =false;
	int choix =0;
    if( _mkdir( ".\\battery" ) == 0 ) {
        cout<<"dossier battery cree."<<endl;
    }else{
        cout<<"battery dir deja existant ou nest pas accessible."<<endl;
    }
        while(!sortie)
	{
		cout<<"Choisissez une operation:"<<endl;
		cout<<"1: Afficher le catalogue"<<endl;
		cout<<"2: Ajouter un trajet simple"<<endl;
		cout<<"3: Ajouter un trajet compose"<<endl;
		cout<<"4: Faire une recherche simple de parcours"<<endl;
		cout<<"5: Faire une recherche avancee de parcours" << endl;
		cout<<"6: Sauvegarder le catalogue"<<endl;
		cout<<"7: Charger un catalogue"<<endl;
		cout<<"8: Quitter le catalogue"<<endl;
		cin >> choix;
		switch (choix)
		{
			case 1:
				AfficherCatalogue();
				break;
			case 2:
				AddToCatalogueTSSaisie();
				break;
			case 3:
				AddToCatalogueTCSaisie();
				break;
			case 4:
				RechercheSimple();
				break;
			case 5:
				RechercheAvancee();
				break;
			case 6:
				SauvegardeTotale();
				break;
			case 7:
				MenuChargement();
				break;
			case 8:
				sortie = true;
				break;
			default:
				cout<<"Cette option n'est pas dans le catalogue"<<endl;
		}
	}
}
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Catalogue::Catalogue (char * unNom)
{
#ifdef MAP
	cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
	char* unDepart = new char[sizeof(unNom)/sizeof(char)];
	char* unArrivee = new char[sizeof(unNom)/sizeof(char)];
	char* unTransport = new char[sizeof(unNom)/sizeof(char)];
	strcpy(unDepart,unNom);
	strcpy(unArrivee,unNom);
	strcpy(unTransport,unNom);
	TrajetSimple* trajetInit = new  TrajetSimple(0,unDepart,unArrivee,unTransport);
	listeTrajets = new Parcours(trajetInit);
	nomCatalogue = unNom;
	idTC = TCstart+1;
	idTS = 1;

} //----- Fin de Catalogue


Catalogue::~Catalogue ( )

{
	Parcours* currentParcours = listeTrajets;
	while(currentParcours->nextParcours != NULL)
	{
		listeTrajets = listeTrajets->nextParcours;
		delete currentParcours;
		currentParcours = listeTrajets;
	}
	delete currentParcours;
#ifdef MAP
	cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
}
//----- Fin de ~Catalogue

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
int** Catalogue::MatriceAdjacenceInversee()
{
	int nbMax = idTC-1000+idTS;
	int** matrixAdj = new int*[nbMax];
	for(int i = 0;i<nbMax;i++){
		matrixAdj[i] = new int[nbMax];
	}
	for(int i = 0;i<nbMax;i++){
		for(int j=0;j<nbMax;j++){
			matrixAdj[i][j] = 0;
		}
	}

	return matrixAdj;
}

char **Catalogue::MatriceTrajetsInversee()
{
	int nbMax = idTC-1000+idTS;
	char ** matriceTrj = new char*[nbMax];
	for(int i = 0;i<nbMax;i++){
		matriceTrj[i] = new char[LG];
	}
	return matriceTrj;
}

int ***Catalogue::MatriceNomTrajetsInversee()
{
	int nbMax = idTC-1000+idTS;
	int*** matrixAdj = new int**[nbMax];
	for(int a = 0;a<nbMax;a++){
		matrixAdj[a] = new int*[nbMax];
		for(int b =0;b<nbMax;b++){
			matrixAdj[a][b] = new int[maxMemeTrajet];
		}
	}
	for(int i = 0;i<nbMax;i++){
		for(int j=0;j<nbMax;j++) {
			for (int k = 0; k < maxMemeTrajet; k++)
			{
				matrixAdj[i][j][k] = 0;
			}
		}
	}

	return matrixAdj;
}

int Catalogue::gotoOPLine(ifstream &input,int codeOP) {
    int line = 0;
    string lineText;
    switch (codeOP){
        case 1:
            input.seekg(input.beg);
            while(line !=fileTSStartingLine && getline(input,lineText)){
                line++;
            }
            return 0;
            break;
        case 2:
            input.seekg(input.beg);

    }
}

void Catalogue::stringToTrajetSimple(const string st)
{
    int i=0;
    string depart,arrivee,transport;
    while(st[i]!='|'){
        i++;
    }
    i++;
    while(st[i]!='|'){
        depart.push_back(st[i++]);
    }
    i++;
    while(st[i]!='|'){
        arrivee.push_back(st[i++]);
    }
    i++;
    while(i<st.size()){
        transport.push_back(st[i++]);
    }
    char* pdepart = new char[LG];
    char* parrivee = new char[LG];
    char* ptransport = new char[LG];
    strcpy(pdepart,depart.c_str());
    strcpy(parrivee,arrivee.c_str());
    strcpy(ptransport,transport.c_str());
    TrajetSimple * nouveauTrajet = new TrajetSimple(idTS,pdepart,parrivee,ptransport);
    AddToCatalogue(nouveauTrajet);
    idTS++;
}

void Catalogue::stringToTrajetCompose(const string st, const string st2)
{
    int i = 0;
    string departC, arriveeC, depart, arrivee, transport;
    char *pdepartC = new char[LG];
    char *parriveeC = new char[LG];
    while (st[i] != '|') {
        i++;
    }
    i++;
    while (st[i] != '|') {
        departC.push_back(st[i++]);
    }
    i++;
    while (i < st.size()) {
        arriveeC.push_back(st[i++]);
    }
    i = 1;
    strcpy(pdepartC, departC.c_str());
    strcpy(parriveeC, arriveeC.c_str());
    while (st2[i] != '|') {
        depart.push_back(st2[i++]);
    }
    i++;
    while (st2[i] != '|') {
        arrivee.push_back(st2[i++]);
    }
    i++;
    while (st2[i] != '|') {
        transport.push_back(st2[i++]);
    }
    i++;
    char *pdepart = new char[LG];
    char *parrivee = new char[LG];
    char *ptransport = new char[LG];
    strcpy(pdepart, depart.c_str());
    strcpy(parrivee, arrivee.c_str());
    strcpy(ptransport, transport.c_str());
    TrajetSimple* nouveauTrajetSimple = new TrajetSimple(idTC,pdepart,parrivee,ptransport);
    Parcours* nouveauParcours = new Parcours(nouveauTrajetSimple);
    TrajetCompose *nouveauTrajetCompose = new TrajetCompose(idTC, pdepartC, parriveeC, nouveauParcours);
    //FIN DE INIT
    depart.clear();
    arrivee.clear();
    transport.clear();
    while (i < st2.size()) {
        while (st2[i] != '|') {
            depart.push_back(st2[i++]);
        }
        i++;
        while (st2[i] != '|') {
            arrivee.push_back(st2[i++]);
        }
        i++;
        while (st2[i] != '|' && i<st2.size()) {
            transport.push_back(st2[i++]);
        }
        i++;
        char *pdepart2 = new char[LG];
        char *parrivee2 = new char[LG];
        char *ptransport2 = new char[LG];
        strcpy(pdepart2, depart.c_str());
        strcpy(parrivee2, arrivee.c_str());
        strcpy(ptransport2, transport.c_str());
        TrajetSimple *nouveauTrajet = new TrajetSimple(idTC, pdepart2, parrivee2, ptransport2);
        Parcours * currentParcours = new Parcours(nouveauTrajet);
        nouveauParcours->nextParcours = currentParcours;
        nouveauParcours = currentParcours;
        depart.clear();
        arrivee.clear();
        transport.clear();
    }
    AddToCatalogue(nouveauTrajetCompose);
}



//------------------------------------------------------- Méthodes privées
