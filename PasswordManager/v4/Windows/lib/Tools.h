#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef char* String;

// Fonction utile a la vérification et a l'uniformisation des entrée
void removeEnter(String Input);
void InputInspector(String Input);
void PasswordVerificator(String Alphabet,String Password);
void nbrBetween(String Input,int x,int y);

// Fonction dérivée de string.h fais par moi pour diverse vérifiacation intermediaire
String strbcpy(String Input, int x,int y);
int strNbr(String Input);
int _pow(int nbr,int pow);

// Fonction de traitement de "Liste" (C'est des tableau mais chuuut il faut pas le dire )
int getNbElementListe(String* Liste);
int getNbRepElementListe(String* Liste,String Element);
int getIsElementIsPresent(String* Liste,String Element);
void addInListe(String* Liste,String Element);
String toUpperCase(String Element);

//Fonction génératrice de mot de passe aleatoire avec paramétre de choix
String generatPassword(int BoolMajMin,int BoolChiffre,int BoolSpe,int Longeur);

// Fonction d'attente d'entrée (Très utile)
void pause();

//Fonction rattachée a l'encryption de fichier
String repeteur(String Ligne,String Key);
int getIndex(String Alphabet,char car);

// Fonction d'encryptage
FILE* Encrypting(FILE *fichier,String Key);
FILE* Uncrypting(FILE *fichier,String Key);
void EncryptingName(String NomFichier,String Key);
void UncryptingName(String NomFichier,String Key);
void EncryptingOneLigne(String Ligne,String Key);
void UncryptingOneLigne(String Ligne,String Key);

// Gestion des couleurs terminal
void Color_printf_RED(String Element);
void Color_printf_GREEN(String Element);
void Color_printf_BLUE(String Element);
void Color_printf_YELLOW(String Element);
void Color_printf_MAGENTA(String Element);
void Color_printf_BLACK(String Element);
void Color_printf_GRAY(String Element);
void Color_printf_TEST(String Element);

void FILEcpy(FILE *fichier,String NomNouveauFichier);

#endif
