#ifndef DATAEXPLORER_H
#define DATAEXPLORER_H

#include "Tools.h"

typedef char* String;

// =-=-=-=-=-= GETTEUR =-=-=-=-=-=
int getNbColonne(FILE *fichier);
int getNbLigne(FILE *fichier);

String getLigne(FILE *fichier, int Index);
String getColonne(String Ligne, int Colonne);
String getLigneXcolonneY(FILE *fichier, int Ligne, int Colonne);
String* getListeColonne(FILE *fichier, int Colonne);

// =-=-=-=-=-= MODIFICATEUR =-=-=-=-=-
void addLigne(FILE *fichier);
void addLigneAutoIndex(FILE *fichier);
void addLigneAutoIndexSpecificString(FILE *fichier, String Input);
FILE* removeLigne(FILE *fichier);
FILE* removeOneIndex(FILE *fichier, int x);
FILE* modifieOneLigne(FILE *fichier, int x, String NewLine);

// =-=-=-=-=-= DISPLAY =-=-=-=-=-=-=

void DisplaySpecifiqueListe(FILE *fichier, String Element,int Colonne);
void DisplaySpecifiqueTable(FILE *fichier,String Element,int Colonne);

void DisplayTable(FILE *fichier);
void DisplayOrdonnedTable(FILE *fichier, int Colonne);

void DisplayListe(FILE *fichier);
void DisplayOrdonnedListe(FILE *fichier,int colonne);

// =-=-=-=-=-= LIST UTILS =-=-=-=-=-=
int getNbElementListe(String* Liste);
int getNbRepElementListe(String* Liste, String Element);
void addInListe(String* Liste, String Element);

// =-=-=-=-=-= FILE POSITION =-=-=-=-=-=
void goToEnd(FILE *fichier);
void goTo(FILE *fichier, int x);

#endif // DATAEXPLORER_H
