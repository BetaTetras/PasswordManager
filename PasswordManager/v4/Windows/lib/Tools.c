#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Tools.h"

typedef char* String;

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$&'()*+,-./:;<=>?@[]^_`{ }~|"

// Fonction utile a la vérification et a l'uniformisation des entrée
void removeEnter(String Input);
void InputInspector(String Input);
void PasswordVerificator(String Alphabet,String Password);
void isANumber(String Input);
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

/////////////////////////////////////////////////////////////////////////

/*
 * Vérifie si une entrée de STRING qui est obligatoirement un nombre est entre deux valeur 
 * Utile pour les choix dans les menus.
*/
void nbrBetween(String Input,int x,int y){
    isANumber(Input);

    while(atoi(Input) < x || atoi(Input) > y){
        printf("\n      # Error...\n      # Tu dois choisir un nombre entre %d et %d\n",x,y);
        printf("      > ");
        fgets(Input,500,stdin);
        isANumber(Input);
    }
    
}

/*
 * Vérifie si une entrée de STRING est un nombre NATUREL avec atoi 
 * Atoi renvois 0 si la String n'est pas un nombre comme "123" si la string est "ABC" il renvois 0
*/
void isANumber(String Input){
    while(atoi(Input) == 0){
        printf("\n      # Error...\n      # Tu dois choisir un nombre NATUREL\n");
        printf("      > ");
        fgets(Input,500,stdin);
    }
}

/*
 * Supprime le '\n' supéficielle d'une entrée utilisateur...
 * En générale le fgets prend le ENTER de l'entrée utilisateur ducoup ca peut foutre le bordelle si on dois
 * afficher l'entrée utilisateur car on renverra le '\n' dans la sortie terminal ce qui ferra sautée des ligne
 * que l'on veut pas ou alors lors du traitement de string simplement
 * 
*/
void removeEnter(String Input){
    if(Input[strlen(Input)-1] == '\n'){
        Input[strlen(Input)-1] = '\0';
    }

}

/*
 * Ma version du atoi qui marche plutot bien je crois ... 
 *
*/
int strNbr(String Input){
    removeEnter(Input);
    int BoolNeg = 0;
    int i=0;
    if(Input[0] == '-'){
        BoolNeg = 1;
        i = 1;
    }
    for(i = 0 ;i< (int)strlen(Input);i++){ // On caste strlen en int au lieux de size_t
        if(Input[i] < '0' || Input[i] > '9'){
            return 0;
        }
    }
    int NbrFinale = 0;
    int IndexUnite = strlen(Input);

    if(BoolNeg == 0){
        IndexUnite = IndexUnite -1;
        for(int i=0;i< (int)strlen(Input);i++){ // On caste strlen en int au lieux de size_t
            NbrFinale = NbrFinale + (Input[i] - 48) * _pow(10,IndexUnite);
            IndexUnite --;
        }
        return NbrFinale;
    }else{
        IndexUnite = IndexUnite -2;
        for(int i=1;i< (int)strlen(Input);i++){ // On caste strlen en int au lieux de size_t
            NbrFinale = NbrFinale + (Input[i] - 48) * _pow(10,IndexUnite);
            IndexUnite --;
        }
        return -(NbrFinale);
    }
}

/*
 * Ma version du pow de la bibli math.h sauf que j'ai pas besoin d'appellée la bibli lol
*/
int _pow(int nbr,int pow){
    int nbrFinale = nbr;

    if(pow == 0){
        return 1;
    }else if(pow < 0){
        return 0;
    }
    for(int i=1;i<pow;i++){ 
        nbrFinale = nbrFinale * nbr;
    }
    return nbrFinale;
}

/*
 * Fonction qui copie une string d'un index x a un index y
 *
 * Exemple :
 * String s = "Hello123World!";
 * strbcpy(s,5,7): 
 *
 * -> "123"
*/
String strbcpy(String Input, int x,int y){
    String res = (String)calloc(500,sizeof(char));
    x++;    // Exclusion
    for(int i=0,j=x;j<y;i++,j++){
        res[i] = Input[j];
    }
    return res;
}

/*
 * Fonction debug qui permet de vérifier une entée ou une string de facon totale même avec les caractére
 * non-visible habituelle comme '\0' ou '\n'
*/
void InputInspector(String Input){
    for(int i=0;i< (int)strlen(Input);i++){ // On caste strlen en int au lieux de size_t
        if(Input[i] == '\n'){
            printf("& ");
        }else if(Input[i] == '\0'){
            printf("# ");
        }else{
            printf("%c ",Input[i]);
        }
    }
}

/*
 * Retourne le nombre d'élément d'une liste de String
*/
int getNbElementListe(String* Liste){
    int i = 0;
    while(Liste[i] != NULL){
        i++;
    }
    return i;
}

/*
 * Retourne le nombre de répétition d'un élément particulier d'une liste de string
*/
int getNbRepElementListe(String* Liste,String Element){
    int NbRep =0;

    for(int i=0;i<getNbElementListe(Liste);i++){
        if(strcmp(Liste[i],Element) == 0){
            NbRep ++;
        }
    }

    return NbRep;
}

/*
 * Ajoute un élément a une liste String
*/
void addInListe(String* Liste,String Element){
    int NbElement = getNbElementListe(Liste);

    Liste[NbElement] = (String)calloc(500,sizeof(char));
    strcpy(Liste[NbElement],Element);
}

/*
 * Vérifie si un élément est présent dans une liste de String
*/
int getIsElementIsPresent(String* Liste,String Element){
    for(int i=0;i<getNbElementListe(Liste);i++){
        if(strcmp(Liste[i],Element) == 0){
            return 1;
        }
    }
    return 0;
}

/*
 * Génére un mot de passe avec les paramètre choisie
*/
String generatPassword(int BoolMajMin,int BoolChiffre,int BoolSpe,int Longeur){
    srand(time(NULL));

    String Alphabet = (String)calloc(91,sizeof(char));

    if(BoolMajMin > 0){
        strcat(Alphabet,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    }

    if(BoolChiffre>0){
        strcat(Alphabet,"0123456789");
    }

    if(BoolSpe >0){
        strcat(Alphabet,"!#$&'()*+,-./:;<=>?@[]^_{}~");
    }

    String MDP = (String)calloc(Longeur,sizeof(char));

    for(int i=0;i<Longeur;i++){
        int NbRandom =rand() % strlen(Alphabet);
        MDP[i] = Alphabet[NbRandom];
    }

    return MDP;
}

/*
 * Fonction qui attend une entrée pour passée a la suite 
*/
void pause(){
    String Input = (String)calloc(10,sizeof(char));
    while(Input[0] != '\n'){
        printf("PUSH ENTER > ");
        fgets(Input,3,stdin);
        }
    free(Input);
}

FILE* Encrypting(FILE *fichier,String Key){
    rewind(fichier);
    FILE *temp = fopen("EncryptingTemp.txt" , "w");

    String LigneRepeter = (String)calloc(500,sizeof(char));
    String Ligne = (String)calloc(500,sizeof(char));

    int IndexLigneRepeter;
    int IndexLigne;
    int IndexFinale;

    String Alphabet = (String)calloc(93,sizeof(char));
        strcpy(Alphabet,ALPHABET);

    while(fgets(Ligne,500,fichier) != NULL){
        strcpy(LigneRepeter,repeteur(Ligne,Key));
        for(int i=0;i< (int)strlen(Ligne);i++){ // On caste strlen en int au lieux de size_ts
            IndexLigne = getIndex(Alphabet,Ligne[i]);
            IndexLigneRepeter = getIndex(Alphabet,LigneRepeter[i]);

            IndexFinale = (IndexLigne + IndexLigneRepeter) %92;

            if(Ligne[i] != '\n'){
                Ligne[i] = Alphabet[IndexFinale];
            }
        }
        fprintf(temp,"%s",Ligne);
    }

    fclose(temp);

    remove("DATA.txt");
    rename("EncryptingTemp.txt", "DATA.txt");

    return fopen("DATA.txt","r+");
}

FILE* Uncrypting(FILE *fichier,String Key){
    rewind(fichier);
    FILE *temp = fopen("UncryptingTemp.txt" , "w");

    String LigneRepeter = (String)calloc(500,sizeof(char));
    String Ligne = (String)calloc(500,sizeof(char));

    int IndexLigneRepeter;
    int IndexLigne;
    int IndexFinale;

    String Alphabet = (String)calloc(93,sizeof(char));
        strcpy(Alphabet,ALPHABET);

    while(fgets(Ligne,500,fichier) != NULL){
        strcpy(LigneRepeter,repeteur(Ligne,Key));
        for(int i=0;i<(int)strlen(Ligne);i++){ // On caste strlen en int au lieux de size_t
            IndexLigne = getIndex(Alphabet,Ligne[i]);
            IndexLigneRepeter = getIndex(Alphabet,LigneRepeter[i]);

            IndexFinale =  IndexLigne - IndexLigneRepeter;
            if(IndexFinale <0){
                IndexFinale += 92;
            }     

            if(Ligne[i] != '\n'&& Ligne[i] != '\r'){
                Ligne[i] = Alphabet[IndexFinale];
            }
        }
        fprintf(temp,"%s",Ligne);
    }

    fclose(temp);

    remove("DATA.txt");
    rename("UncryptingTemp.txt", "DATA.txt");

    return fopen("DATA.txt","r+");
}

void EncryptingOneLigne(String Ligne,String Key){
    String LigneRepeter = (String)calloc(500,sizeof(char));
    strcpy(LigneRepeter,repeteur(Ligne,Key));

    int IndexLigneRepeter;
    int IndexLigne;
    int IndexFinale;

    for(int i=0;i< (int)strlen(Ligne);i++){ // On caste strlen en int au lieux de size_ts
        IndexLigne = getIndex(ALPHABET,Ligne[i]);
        IndexLigneRepeter = getIndex(ALPHABET,LigneRepeter[i]);

        IndexFinale = (IndexLigne + IndexLigneRepeter) %92;

        if(Ligne[i] != '\n'){
            Ligne[i] = ALPHABET[IndexFinale];
        }
    }

}

void UncryptingOneLigne(String Ligne,String Key){
    String LigneRepeter = (String)calloc(500,sizeof(char));
    strcpy(LigneRepeter,repeteur(Ligne,Key));

    int IndexLigneRepeter;
    int IndexLigne;
    int IndexFinale;

    for(int i=0;i<(int)strlen(Ligne);i++){ // On caste strlen en int au lieux de size_t
        IndexLigne = getIndex(ALPHABET,Ligne[i]);
        IndexLigneRepeter = getIndex(ALPHABET,LigneRepeter[i]);

        IndexFinale =  IndexLigne - IndexLigneRepeter;
        if(IndexFinale <0){
            IndexFinale += 92;
        }     

        if(Ligne[i] != '\n'&& Ligne[i] != '\r'){
            Ligne[i] = ALPHABET[IndexFinale];
        }
    }
}

void EncryptingName(String NomFichier,String Key){
    FILE *fichier = fopen(NomFichier,"r+");
    FILE *temp = fopen("EncryptingTemp.txt" , "w");

    String LigneRepeter = (String)calloc(500,sizeof(char));
    String Ligne = (String)calloc(500,sizeof(char));

    int IndexLigneRepeter;
    int IndexLigne;
    int IndexFinale;


    while(fgets(Ligne,500,fichier) != NULL){
        strcpy(LigneRepeter,repeteur(Ligne,Key));
        for(int i=0;i< (int)strlen(Ligne);i++){ // On caste strlen en int au lieux de size_ts
            IndexLigne = getIndex(ALPHABET,Ligne[i]);
            IndexLigneRepeter = getIndex(ALPHABET,LigneRepeter[i]);

            IndexFinale = (IndexLigne + IndexLigneRepeter) %92;

            if(Ligne[i] != '\n'){
                Ligne[i] = ALPHABET[IndexFinale];
            }
        }
        fprintf(temp,"%s",Ligne);
    }

    fclose(fichier);
    fclose(temp);

    remove(NomFichier);
    rename("EncryptingTemp.txt", NomFichier);
    remove("EncryptingTemp.txt");
}

void UncryptingName(String NomFichier,String Key){
    FILE *fichier = fopen(NomFichier,"r+");
    FILE *temp = fopen("UncryptingTemp.txt" , "w");

    String LigneRepeter = (String)calloc(500,sizeof(char));
    String Ligne = (String)calloc(500,sizeof(char));

    int IndexLigneRepeter;
    int IndexLigne;
    int IndexFinale;

    while(fgets(Ligne,500,fichier) != NULL){
        strcpy(LigneRepeter,repeteur(Ligne,Key));
        for(int i=0;i<(int)strlen(Ligne);i++){ // On caste strlen en int au lieux de size_t
            IndexLigne = getIndex(ALPHABET,Ligne[i]);
            IndexLigneRepeter = getIndex(ALPHABET,LigneRepeter[i]);

            IndexFinale =  IndexLigne - IndexLigneRepeter;
            if(IndexFinale <0){
                IndexFinale += 92;
            }     

            if(Ligne[i] != '\n'&& Ligne[i] != '\r'){
                Ligne[i] = ALPHABET[IndexFinale];
            }
        }
        fprintf(temp,"%s",Ligne);
    }

    fclose(fichier);
    fclose(temp);

    remove(NomFichier);
    rename("UncryptingTemp.txt", NomFichier);
    remove("UncryptingTemp.txt");
}

String repeteur(String Ligne,String Key){
    int LongeurKey = strlen(Key);
    String NewLigne = (String)calloc(strlen(Ligne) + 1,sizeof(char));

    for(int i=0,j=0;i< (int)strlen(Ligne);i++,j++){ // On caste strlen en int au lieux de size_t
        if(j == LongeurKey){
            j=0;
        }
        NewLigne[i] = Key[j];
    }

    return NewLigne;
}

int getIndex(String Alphabet,char car){
    for(int i=0;i< (int)strlen(Alphabet);i++){ // On caste strlen en int au lieux de size_t
        if(Alphabet[i] == car){
            return i;
        }
    }

    return -1;
}

void PasswordVerificator(String Alphabet,String Password){
    int BoolError;
    do{
        BoolError = 0;
        for(int i=0;i<(int)strlen(Password);i++){
            if(getIndex(Alphabet,Password[i]) < 0){
                printf("\n# Erreur...\n# Caractere invalide dans le mot de passe (%c) ...\n\n",Password[i]);
                printf("Entrer un autre mot de passe :\n      > ");
                fgets(Password,100,stdin);
                removeEnter(Password);
                BoolError = 1;
                break;
            }
        }
    }while(BoolError);
}


String toUpperCase(String Element){
    String Result = (String)calloc(strlen(Element),sizeof(char));
    for(int i=0;i<(int)strlen(Element);i++){
        if(Element[i] >= 'a' && Element[i] <= 'z'){
            Result[i] = Element[i] - 32;
        }else{
            Result[i] = Element[i];
        }
    }
    return Result;
}

void Color_printf_RED(String Element){printf("\033[1;31m%s\033[0m",Element);}
void Color_printf_GREEN(String Element){printf("\033[1;32m%s\033[0m",Element);}
void Color_printf_BLUE(String Element){printf("\033[1;34m%s\033[0m",Element);}
void Color_printf_YELLOW(String Element){printf("\033[0;33m%s\033[0m",Element);}
void Color_printf_MAGENTA(String Element){printf("\033[0;35m%s\033[0m",Element);}
void Color_printf_BLACK(String Element){printf("\033[0;30m%s\033[0m",Element);}
void Color_printf_GRAY(String Element){printf("\033[0;37m%s\033[0m",Element);}
void Color_printf_TEST(String Element){printf("\033[0;37m%s\033[0m",Element);}

void FILEcpy(FILE *fichier,String NomNouveauFichier){
    rewind(fichier);

    FILE *nvFichier = fopen(NomNouveauFichier,"w+");
    String buffer = (String)calloc(500,sizeof(char));

    while(fgets(buffer,500,fichier) != NULL){
        fprintf(nvFichier,buffer);
    }

    fclose(nvFichier);
}