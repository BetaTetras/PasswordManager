/* -=- BIBLIOTHEQUE -=- */
#include <stdio.h>   // Entrer / Sortie terminal 
#include <stdlib.h>  // Malloc,calloc ...
#include <string.h>  // Gestion de string
// #include <conio.h>   // Gestion des entrée en continue 
#include <time.h>    // Gestion de l'aleatoire
#include <unistd.h>  // Gestion du Sleep
// #include <windows.h> // Gestion terminal
#include <wchar.h>   // ACII étendu
// #include <io.h>      // _access 
#include <stdarg.h>
#include <termios.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Tools.h"


typedef char* String;

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$&'()*+,-./:;<=>?@[]^_`{ }~|"

// Fonction utile a la vérification et a l'uniformisation des entrée
void nbrBetween(String Input,int x,int y);
void isANumber(String Input);
void removeEnter(String Input);
void InputInspector(String Input);
void PasswordVerificator(String Alphabet,String Password);

// Fonction dérivée de string.h fais par moi pour diverse vérifiacation intermediaire
String strbcpy(String Input, int x,int y);
int _strchr(String Input,char Element);
String intToString(int NbINT);
int strNbr(String Input);
void fileCpy(FILE *fichier,String PathFolder,String Extention);
int _pow(int nbr,int pow);

// Fonction de traitement de "Liste" (C'est des tableau mais chuuut il faut pas le dire )
int getNbElementListe(String* Liste);
int getNbRepElementListe(String* Liste,String Element);
void addInListe(String* Liste,String Element);
int getIsElementIsPresent(String* Liste,String Element);
String toUpperCase(String Element);

//Fonction génératrice de mot de passe aleatoire avec paramétre de choix
String generatPassword(int BoolMajMin,int BoolChiffre,int BoolSpe,int Longeur);

// Fonction d'attente d'entrée (Très utile)
void _pause();

// Fonction pour les DataBackUp
void fileCpy(FILE *fichier,String PathFolder,String Extention);
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
void printf_RGB(int r, int g, int b, const char* format, ...);

// Formatage de string;
String StringFormatage(String Format,...);

// Manipulation du terminal
void HideCursor();
void gotoxy(int x, int y);

// Gestion UI
int TerminalUi(int Ystart,int n,...);

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
 * Fonction debug qui permet de vérifier une entée ou une string de facon totale même avec les caractére
 * non-visible habituelle comme '\0' ou '\n'
*/
void InputInspector(String Input){
    for(int i=0;i< (int)strlen(Input);i++){ // On caste strlen en int au lieux de size_t
        if(Input[i] == '\n'){
            printf_RGB(255,0,0,"&\n");
        }else if(Input[i] == '\0'){
            printf_RGB(0,0,255,"#");
        }else{
            printf("%c",Input[i]);
        }
    }
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    // x++;    // Exclusion
    for(int i=0,j=x;j<y;i++,j++){
        res[i] = Input[j];
    }
    return res;
}

int _strchr(String Input,char Element){
    for(int i=0;i<(int)strlen(Input);i++){
        if(Input[i] == Element){
            return i;
        }
    }
    printf_RGB(255,0,0,"L'element '%c' n'est pas dans \"%s\"",Element,Input);
    return -1;
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

String intToString(int NbINT){
    long BufferINT = NbINT;
    int NbCar = 1;

    // Si négatif, réserver une place pour '-'
    if(BufferINT < 0){
        NbCar++;
        BufferINT = -BufferINT; // on travaille sur la valeur positive
    }

    long Temp = BufferINT;
    while(Temp/10 != 0){
        Temp /= 10;
        NbCar++;
    }

    String NbSTR = (String)calloc(NbCar+1, sizeof(char));
    NbSTR[NbCar] = '\0';

    int i = NbCar - 1;
    do{
        NbSTR[i] = (BufferINT % 10) + '0';
        BufferINT /= 10;
        i--;
    } while(BufferINT > 0);

    // Mettre le signe '-' si nécessaire
    if(NbINT < 0){
        NbSTR[0] = '-';
    }

    return NbSTR;
}


// Retourne le nombre de chiffre d'un int
int sizeInt(int n) {
    if (n == 0) return 1;

    int count = 0;
    if (n < 0) {
        count++;    // pour le signe '-'
        n = -n;
    }

    while (n > 0) {
        n /= 10;    // enlève le dernier chiffre
        count++;
    }
    return count;
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

int nbDigit(int nb){
    if(nb == 0){
        return 1;
    }

    int count = 0;
    while(nb >0){
        nb/=10;
        count ++;
    }

    return count;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

String toUpperCase(String Element){
    String Result = (String)calloc(strlen(Element)+1,sizeof(char));
    for(int i=0;i<(int)strlen(Element);i++){
        if(Element[i] >= 'a' && Element[i] <= 'z'){
            Result[i] = Element[i] - 32;
        }else{
            Result[i] = Element[i];
        }
    }

    Result[strlen(Element)] = '\0';
    return Result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Fonction qui attend une entrée pour passée a la suite 
*/
void _pause(){
    String Input = (String)calloc(10,sizeof(char));
    while(Input[0] != '\n'){
        printf("PUSH ENTER > ");
        fgets(Input,3,stdin);
        }
    free(Input);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* A METTRE SOUS LINUX */
// Pour accedée au fichier "Hello" il faut utilisée "Hello/"
// String AutoNaming(String BaseStr,String Path,String Extention){
//     time_t t = time(NULL);
//     struct tm tm_info = *localtime(&t);

//     String* Liste = GetListeFichier(Path);

//     String Name = (String)calloc(50,sizeof(char));

//     strcat(Name,StringFormatage("%s{%d-%d-%d}",BaseStr,tm_info.tm_mday,tm_info.tm_mon+1,(tm_info.tm_year+1900)-2000));
//     int NbSame = 0;
//     for(int i=0;i< getNbElementListe(Liste);i++){
//         if(strcmp(Liste[i],Name) == 0 || strcmp(strbcpy(Liste[i],0,strlen(Name)),Name) == 0){
//             NbSame ++;
//         }
//     }

//     if(NbSame > 0){
//         Name = StringFormatage("%s%c%d",Name,'v',NbSame);
//     }
    
//     Name = StringFormatage("%s%s",Name,Extention);

//         String FullPath;
//     if (strcmp(Path, "./") == 0 || strcmp(Path, ".") == 0) {
//         // dossier courant → pas besoin de préfixe
//         FullPath = StringFormatage("%s", Name);
//     } else {
//         // concat Path + "/" + Name
//         FullPath = StringFormatage("%s/%s", Path, Name);
//     }

//     return FullPath;
// }

String AutoNaming(String BaseStr, String Path, String Extention) {
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);

    String* Liste = GetListeFichier(Path);
    if (!Liste) Liste = (String*)calloc(1, sizeof(String)); // sécurité

    // Création du nom de base avec date
    String Name = StringFormatage("%s{%d-%d-%d}", BaseStr, tm_info.tm_mday, tm_info.tm_mon + 1, (tm_info.tm_year + 1900) - 2000);

    // Vérifier les doublons
    int NbSame = 0;
    for (int i = 0; i < getNbElementListe(Liste); i++) {
        if (strcmp(Liste[i], Name) == 0) {
            NbSame++;
        }
    }

    String FinalName;
    if (NbSame > 0) {
        FinalName = StringFormatage("%s%c%d%s", Name, 'v', NbSame, Extention);
    } else {
        FinalName = StringFormatage("%s%s", Name, Extention);
    }

    // Préfixe chemin si nécessaire
    String FullPath;
    if (strcmp(Path, "./") == 0 || strcmp(Path, ".") == 0) {
        FullPath = StringFormatage("%s", FinalName);
    } else {
        FullPath = StringFormatage("%s/%s", Path, FinalName);
    }

    // Libération mémoire
    free(Name);
    free(FinalName);
    if (Liste) {
        for (int i = 0; Liste[i]; i++) free(Liste[i]);
        free(Liste);
    }

    return FullPath;
}

void fileCpy(FILE *fichier,String PathFolder,String NomDuFichier){
    String Data = getFileFromPointer(fichier);

    FILE *NewFile = fopen(StringFormatage("%s%s%s",PathFolder,"NewFile",NomDuFichier),"w");
    
    fprintf(NewFile,Data);

    fclose(NewFile);
}

void createFolderIfNotExist(const char* path){
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0755);
    }
}

/* A METTRE SOUS LINUX */

// // Pour accedée au fichier "Hello" il faut utilisée "Hello/"
// String* GetListeFichier(String PathConst){
//     WIN32_FIND_DATA WinData;

//     String searchPath = (String)calloc(260,sizeof(char));
//     snprintf(searchPath,260,"%s*",PathConst);
//     // HANDLE hFind = FindFirstFile("Save/*", &ffd);
//     HANDLE hFind = FindFirstFile(searchPath, &WinData);

//     String* ListeFile = (String*)calloc(100,sizeof(String));
//     int NbFile = 0;

//     do{
//         if(strcmp(WinData.cFileName,".") != 0 && strcmp(WinData.cFileName,".." )!= 0){
//             ListeFile[NbFile] = (String)calloc(strlen(WinData.cFileName) + 1,sizeof(char));
//             strcpy(ListeFile[NbFile],WinData.cFileName);

//             NbFile ++;
//         }
//     }while(FindNextFile(hFind,&WinData) != 0);

//     ListeFile = realloc(ListeFile, sizeof(String) * (NbFile + 1));
//     ListeFile[NbFile] = NULL;

//     FindClose(hFind);
//     return ListeFile;
// }

String* GetListeFichier(char* Path) {
    DIR* dir = opendir(Path);
    if (!dir) {
        perror("Erreur ouverture dossier");
        return NULL;
    }

    struct dirent* entry;
    int capacity = 100;
    int NbFile = 0;
    String* ListeFile = (String*)calloc(capacity, sizeof(String));

    while ((entry = readdir(dir)) != NULL) {
        // On ignore "." et ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (NbFile >= capacity) {
            capacity *= 2;
            ListeFile = (String*)realloc(ListeFile, capacity * sizeof(String));
        }

        ListeFile[NbFile] = (String)calloc(strlen(entry->d_name) + 1, sizeof(char));
        strcpy(ListeFile[NbFile], entry->d_name);
        NbFile++;
    }

    closedir(dir);

    // Terminer la liste par NULL
    ListeFile = (String*)realloc(ListeFile, (NbFile + 1) * sizeof(String));
    ListeFile[NbFile] = NULL;

    return ListeFile;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

String getFileFromName(String fileName){
    long int Size;
    FILE *fichier = fopen(fileName, "r");

    fseek(fichier,0,SEEK_END);
    Size = ftell(fichier);
    rewind(fichier);

    String Data = (String)calloc(Size + 1,sizeof(char));
    fread(Data,1,Size,fichier);
    Data[Size] = '\0';

    fclose(fichier);
    return Data;
}

String getFileFromPointer(FILE *fichier){
    long int Size;

    fseek(fichier,0,SEEK_END);
    Size = ftell(fichier);
    rewind(fichier);

    String Data = (String)calloc(Size + 1,sizeof(char));
    fread(Data,1,Size,fichier);
    Data[Size] = '\0';

    return Data;
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
    FILE *TestExiste = fopen(NomFichier,"r");
    if(!TestExiste){
        printf_RGB(255,0,0,"# ERROR\n# '%s' inexistant ...\n\n",NomFichier);
        return;
    }
    fclose(TestExiste);

    FILE *fichierLecture = fopen(NomFichier,"r+");
    String DataBruteEncrypter = EncryptingString(getFileFromPointer(fichierLecture),Key);
    fclose(fichierLecture);

    FILE *fichierEcriture = fopen(NomFichier,"w+");
    fprintf(fichierEcriture,"%s",DataBruteEncrypter);
    fclose(fichierEcriture);
}

void UncryptingName(String NomFichier,String Key){
    FILE *TestExiste = fopen(NomFichier,"r");
    if(!TestExiste){
        printf_RGB(255,0,0,"# ERROR\n# '%s' inexistant ...\n\n",NomFichier);
        return;
    }
    fclose(TestExiste);

    FILE *fichierLecture = fopen(NomFichier,"r+");
    String DataBruteUncrypter = UncryptingString(getFileFromPointer(fichierLecture),Key);
    fclose(fichierLecture);

    FILE *fichierEcriture = fopen(NomFichier,"w+");
    fprintf(fichierEcriture,"%s",DataBruteUncrypter);
    fclose(fichierEcriture);
}

String UncryptingString(String Ligne,String Key){
    String LigneRepeter = (String)calloc(500,sizeof(char));

    int IndexLigneRepeter;
    int IndexLigne;
    int IndexFinale;

    strcpy(LigneRepeter,repeteur(Ligne,Key));
    for(int i=0;i<(int)strlen(Ligne);i++){ // On caste strlen en int au lieux de size_t
        IndexLigne = getIndex(ALPHABET,Ligne[i]);
        IndexLigneRepeter = getIndex(ALPHABET,LigneRepeter[i]);

        IndexFinale =  IndexLigne - IndexLigneRepeter;
        if(IndexFinale < 0){
            IndexFinale += 92;
        }     

        if(Ligne[i] != '\n'&& Ligne[i] != '\r'){
            Ligne[i] = ALPHABET[IndexFinale];
        }
    }

    return Ligne;
}

String EncryptingString(String Ligne,String Key){
    String LigneRepeter = (String)calloc(500,sizeof(char));

    int IndexLigneRepeter;
    int IndexLigne;
    int IndexFinale;

    strcpy(LigneRepeter,repeteur(Ligne,Key));
    for(int i=0;i< (int)strlen(Ligne);i++){ // On caste strlen en int au lieux de size_ts
        IndexLigne = getIndex(ALPHABET,Ligne[i]);
        IndexLigneRepeter = getIndex(ALPHABET,LigneRepeter[i]);

        IndexFinale = (IndexLigne + IndexLigneRepeter) %92;

        if(Ligne[i] != '\n'){
            Ligne[i] = ALPHABET[IndexFinale];
        }
    }

    return Ligne;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printf_RGB(int r, int g, int b, const char* format, ...) {
    va_list args;
    va_start(args, format);

    printf("\033[38;2;%d;%d;%dm", r, g, b);

    vprintf(format, args);

    printf("\033[0m");

    va_end(args);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String StringFormatage(String format,...){
	va_list FirstArgs;
	va_list SecondArgs;

	va_start(FirstArgs, format);
	va_copy(SecondArgs,FirstArgs);

	int sizeFinalString = 0;

	// Calcule de la taille du format sans les param
	for(int i=0;i<(int)strlen(format);i++){
		if(format[i] == '%' && (format[i+1] == 's' || format[i+1] == 'd' || format[i+1] == 'c')){
			i++;
			continue;
		}else{
			sizeFinalString ++;
		}
	}

	// Calcule de la taille de chaque argument
	for(int i=0;i<(int)strlen(format);i++){
		if(format[i] == '%'){
			if(format[i+1] == 'd'){
				int _int = va_arg(FirstArgs,int);
				sizeFinalString += sizeInt(_int);
				i++;
			}else if(format[i+1] == 's'){
				String _String = va_arg(FirstArgs,String);
				sizeFinalString += (int)strlen(_String);
				i++;
			}else if(format[i+1] == 'c'){
				// Inutile mais permet de passée a l'args suivant
				char _char = (char) va_arg(FirstArgs,int);
				sizeFinalString ++;
				i++;
			}
		}
	}

	String Final = (String)calloc(sizeFinalString+1,sizeof(char));

	int index = 0;

for(int i=0;i<(int)strlen(format);i++){
    if(format[i] == '%'){
        if(format[i+1] == 'd'){
            int _int = va_arg(SecondArgs,int);
            String temp = intToString(_int);
            strcat(Final,temp);
            index += strlen(temp);  // avancer de la longueur réelle
            free(temp);
            i++; // passer le caractère du format
        } else if(format[i+1] == 's'){
            String _String = va_arg(SecondArgs,String);
            strcat(Final,_String);
            index += strlen(_String);  // avancer de la longueur réelle
            i++;
        } else if(format[i+1] == 'c'){
            char _char = (char) va_arg(SecondArgs,int);
            Final[index] = _char;
            index++;
            Final[index] = '\0';
            i++;
        } else {
            // si format inconnu, on le copie tel quel
            Final[index] = format[i];
            index++;
            Final[index] = '\0';
        }
    } else {
        Final[index] = format[i];
        index++;
        Final[index] = '\0';
    }
}

	va_end(FirstArgs);
	va_end(SecondArgs);

	return Final;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HideCursor() {
    printf("\e[?25l");
    fflush(stdout); // force l’affichage immédiat
}

/* Affiche le curseur */
void ShowCursor() {
    printf("\033[?25h");
    fflush(stdout);
}

/* Déplace le curseur à la position (x, y) dans le terminal */
void gotoxy(int x, int y) {
    // x = colonne, y = ligne
    // ANSI escape code : \033[y;xH ou \e[y;xH
    printf("\033[%d;%dH", y, x);
    fflush(stdout); // force l'affichage immédiat
}

/* Efface l'écran */
void clearScreen() {
    printf("\033[2J\033[H");
}

/* Lit une touche sans attendre Enter */
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // mode non-canonique, pas d'écho
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

/* Vérifie si une touche a été pressée */
int kbhit() {
    struct termios oldt, newt;
    int oldf;
    int ch;
    int hit = 0;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();
    if (ch != EOF) {
        ungetc(ch, stdin);
        hit = 1;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    return hit;
}

int getArrowKey() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int ch = getchar();
    if (ch == 27) { // ESC
        int next1 = getchar();
        if (next1 == 91) { // '['
            int next2 = getchar();
            ch = next2; // A,B,C,D
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

/* FONCTION UI POUR AVOIR LE MENU A BOUTON */
/* TerminalUi version Linux */
int TerminalUi(int Ystart, int n, ...) {
    HideCursor();

    va_list Args;
    va_start(Args, n);
    String* TabString = (String*)calloc(n, sizeof(String));
    for (int i = 0; i < n; i++) {
        TabString[i] = va_arg(Args, String);
    }
    va_end(Args);

    int choix = 0;

    // Affichage initial
    for (int i = 0; i < n; i++) {
        gotoxy(0, Ystart + i);
        if (i == choix) {
            printf_RGB(255, 0, 0, "> [%d] - %s", i + 1, TabString[i]);
        } else {
            printf("  [%d] - %s", i + 1, TabString[i]);
        }
        printf("                                              ");
    }

    int key;
    while (1) {
        key = getArrowKey(); // lis correctement la touche

        // Efface ancienne sélection
        gotoxy(0, Ystart + choix);
        printf("  [%d] - %s                                              ", choix + 1, TabString[choix]);

        if (key == 'A' && choix > 0) {
            choix--;
        } else if (key == 'B' && choix < n - 1) {
            choix++;
        } else if (key == 10) { // Enter
            clearScreen();
            ShowCursor();
            free(TabString);
            return choix + 1;
        }

        // Redessine nouvelle sélection
        gotoxy(0, Ystart + choix);
        printf_RGB(255, 0, 0, "> [%d] - %s                                              ", choix + 1, TabString[choix]);
        usleep(30 * 1000);
    }

    ShowCursor();
    free(TabString);
    return -1;
}