#ifndef DATAEXPLORER_H
#define DATAEXPLORER_H

#include "Tools.h"

typedef char* String;

// =-=-=-=-=-= GETTEUR =-=-=-=-=-=
int getNbColonne(FILE *fichier);
int getNbLigne(FILE *fichier);

String getLigne(FILE *fichier, int x);
String getColonne(String Ligne, int x);
String getLigneXcolonneY(FILE *fichier, int X, int Y);
String* getListeColonne(FILE *fichier, int x);

// =-=-=-=-=-= MODIFICATEUR =-=-=-=-=-
void addLigne(FILE *fichier);
void addLigneAutoIndex(FILE *fichier);
void addLigneAutoIndexSpecificString(FILE *fichier, String Input);
FILE* removeLigne(FILE *fichier);
FILE* removeOneIndex(FILE *fichier, int x);
FILE* modifieOneLigne(FILE *fichier, int x, String NewLine);

// =-=-=-=-=-= REPONDEUR =-=-=-=-=-=
int isAlreadyHere(FILE *fichier, int x, String Input);

// =-=-=-=-=-= DISPLAY =-=-=-=-=-=-=
void DisplaySpecifique(FILE *fichier, String Element);
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
