#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Tools.h"

typedef char* String;

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$&'()*+,-./:;<=>?@[]^_`{ }~|"

void removeEnter(String Input);
void InputInspector(String Input);
void PasswordVerificator(String Alphabet,String Password);

String strbcpy(String Input, int x,int y);
int strNbr(String Input);

void isANumber(String Input);
void nbrBetween(String Input,int x,int y);
int _pow(int nbr,int pow);

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

/////////////////////////////////////////////////////////////////////////

void nbrBetween(String Input,int x,int y){
    isANumber(Input);

    while(atoi(Input) < x || atoi(Input) > y){
        printf("\n      # Error...\n      # Tu dois choisir un nombre entre %d et %d\n",x,y);
        printf("            > ");
        fgets(Input,500,stdin);
        isANumber(Input);
    }
    
}

void isANumber(String Input){
    while(atoi(Input) == 0){
        printf("\n      # Error...\n      # Tu dois choisir un nombre NATUREL\n");
        printf("            > ");
        fgets(Input,500,stdin);
    }
}

void removeEnter(String Input){
    if(Input[strlen(Input)-1] == '\n'){
        Input[strlen(Input)-1] = '\0';
    }

}

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

String strbcpy(String Input, int x,int y){
    String res = (String)calloc(500,sizeof(char));
    x++;    // Exclusion
    for(int i=0,j=x;j<y;i++,j++){
        res[i] = Input[j];
    }
    return res;
}

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

int getNbElementListe(String* Liste){
    int i = 0;
    while(Liste[i] != NULL){
        i++;
    }
    return i;
}

int getNbRepElementListe(String* Liste,String Element){
    int NbRep =0;

    for(int i=0;i<getNbElementListe(Liste);i++){
        if(strcmp(Liste[i],Element) == 0){
            NbRep ++;
        }
    }

    return NbRep;
}

void addInListe(String* Liste,String Element){
    int NbElement = getNbElementListe(Liste);

    Liste[NbElement] = (String)calloc(500,sizeof(char));
    strcpy(Liste[NbElement],Element);
}


int getIsElementIsPresent(String* Liste,String Element){
    for(int i=0;i<getNbElementListe(Liste);i++){
        if(strcmp(Liste[i],Element) == 0){
            return 1;
        }
    }
    return 0;
}

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

    fclose(fichier);
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

    fclose(fichier);
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