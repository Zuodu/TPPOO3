using namespace std;
#include <iostream>
#include "Catalogue.h"
#include <cstring>

const int MAXL = 5;

void initCatalogue()
{
    char nomCatalogue [MAXL+1];
    strcpy(nomCatalogue,"Cata1");
    Catalogue *myCatalogue = new Catalogue(nomCatalogue);
    //myCatalogue ->SauvegardeTotale();
	//myCatalogue->MenuCatalogue();
	myCatalogue->MenuCatalogue();
	delete myCatalogue;
}

int main()
{
	initCatalogue();
    return 0;
}
