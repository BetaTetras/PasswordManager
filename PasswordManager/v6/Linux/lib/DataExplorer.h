#ifndef DATAEXPLORER_H
#define DATAEXPLORER_H

#include "Tools.h"

typedef char* String;

// =-=-=-=-=-= GETTEUR =-=-=-=-=-=
int getNbColonne(String DATA);
int getNbLigne(String DATA);

String getLigne(String DATA, int Index);
String getColonne(String Ligne, int Colonne);
String getLigneXcolonneY(String DATA, int Ligne, int Colonne);
String* getListeColonne(String DATA, int Colonne);

// =-=-=-=-=-= MODIFICATEUR =-=-=-=-=-
String addLigne(String DATA);
String addLigneV2(String DATA,int NbArg,...);

String addLigneAutoIndex(String DATA,int NbArg,...);

String addLigneAutoIndexSpecificString(String DATA, String Input);
String addLigneAutoIndexSpecificStringV2(String DATA,int NbArg,...);

String removeLigne(String DATA);
String removeOneIndex(String DATA, int Index);

String modifieOneLigne(String DATA, int x, String NewLine);

// =-=-=-=-=-= DISPLAY =-=-=-=-=-=-=

void DisplaySpecifiqueListe(String DATA, String Element,int Colonne);
void DisplaySpecifiqueTable(String DATA,String Element,int Colonne);

void DisplayTable(String DATA);
void DisplayOrdonnedTable(String DATA, int Colonne);

void DisplayListe(String DATA);
void DisplayOrdonnedListe(String DATA,int colonne);

#endif // DATAEXPLORER_H
