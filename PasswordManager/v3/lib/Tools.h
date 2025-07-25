#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef char* String;

// Fonctions utilitaires
void removeEnter(String Input);
void InputInspector(String Input);
void PasswordVerificator(String Alphabet,String Password);

String strbcpy(String Input, int x, int y);
int strNbr(String Input);

void isANumber(String Input);
void nbrBetween(String Input, int x, int y);
int _pow(int nbr, int pow);

int getNbElementListe(String* Liste);
int getNbRepElementListe(String* Liste,String Element);
int getIsElementIsPresent(String* Liste,String Element);
void addInListe(String* Liste,String Element);

String generatPassword(int BoolMajMin,int BoolChiffre,int BoolSpe,int Longeur);
void pause();

String repeteur(String Ligne,String Key);
int getIndex(String Alphabet,char car);

FILE* Encrypting(FILE *fichier,String Key);
FILE* Uncrypting(FILE *fichier,String Key);
void EncryptingName(String NomFichier,String Key);
void UncryptingName(String NomFichier,String Key);
void EncryptingOneLigne(String Ligne,String Key);
void UncryptingOneLigne(String Ligne,String Key);


#endif
