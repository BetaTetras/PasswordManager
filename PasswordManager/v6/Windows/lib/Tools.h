#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Définit des mouvement et des touches
typedef enum{
    HAUT = 'z',
    BAS = 's',
    GAUCHE = 'q',
    DROITE = 'd',
} Direction;

typedef char* String;

// Fonction utile a la vérification et a l'uniformisation des entrée
void removeEnter(String Input);
void InputInspector(String Input);
void PasswordVerificator(String Alphabet,String Password);
void nbrBetween(String Input,int x,int y);

// Fonction dérivée de string.h fais par moi pour diverse vérifiacation intermediaire
String strbcpy(String Input, int x,int y);
int _strchr(String Input,char Element);
int strNbr(String Input);
int _pow(int nbr,int pow);
int nbDigit(int nb);

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

// Fonction pour les DataBackUp
void fileCpy(FILE *fichier,String PathFolder,String NomDuFichier);
String* GetListeFichier(String Path);
String AutoNaming(String BaseStr,String Path,String Extention);

//Fonction rattachée a l'encryption de fichier
String repeteur(String Ligne,String Key);
int getIndex(String Alphabet,char car);
String getFileFromName(String fileName);
String getFileFromPointer(FILE *fichier);

// Fonction d'encryptage
FILE* Encrypting(FILE *fichier,String Key);
FILE* Uncrypting(FILE *fichier,String Key);
void EncryptingName(String NomFichier,String Key);
void UncryptingName(String NomFichier,String Key);
void EncryptingOneLigne(String Ligne,String Key);
void UncryptingOneLigne(String Ligne,String Key);
String EncryptingString(String Ligne,String Key);
String UncryptingString(String Ligne,String Key);

// Gestion des couleurs terminal
void printf_RED(String Text,...);
void printf_GREEN(String Text,...);
void printf_BLUE(String Text,...);
void printf_YELLOW(String Text,...);
void printf_MAGENTA(String Text,...);
void printf_BLACK(String Text,...);
void printf_GRAY(String Text,...);

// Formatage de string;
String StringFormatage(String Format,...);
String intToString(int Nombre);

// Manipulation du terminal
void HideCursor();
void gotoxy(int x, int y);

// Gestion UI
int TerminalUi(int Ystart,int n,...);

#endif
