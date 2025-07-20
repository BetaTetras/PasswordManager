#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* String;

// Fonctions utilitaires
void removeEnter(String Input);
void InputInspector(String Input);
String strbcpy(String Input, int x, int y);
int strNbr(String Input);
void isANumber(String Input);
void nbrBetween(String Input, int x, int y);
int _pow(int nbr, int pow);
int getNbElementListe(String* Liste);
int getNbRepElementListe(String* Liste,String Element);
void addInListe(String* Liste,String Element);
void setConsoleSize(int width, int height) ;
void pause();


#endif
