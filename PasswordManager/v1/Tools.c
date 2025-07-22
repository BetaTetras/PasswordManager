#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Tools.h"

typedef char* String;

void removeEnter(String Input);
void InputInspector(String Input);
void pause();

String strbcpy(String Input, int x,int y);
int strNbr(String Input);

void isANumber(String Input);
void nbrBetween(String Input,int x,int y);
int _pow(int nbr,int pow);

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
    for(i;i<strlen(Input);i++){
        if(Input[i] < '0' || Input[i] > '9'){
            return 0;
        }
    }
    int NbrFinale = 0;
    int IndexUnite = strlen(Input);

    if(BoolNeg == 0){
        IndexUnite = IndexUnite -1;
        for(int i=0;i<strlen(Input);i++){
            NbrFinale = NbrFinale + (Input[i] - 48) * _pow(10,IndexUnite);
            IndexUnite --;
        }
        return NbrFinale;
    }else{
        IndexUnite = IndexUnite -2;
        for(int i=1;i<strlen(Input);i++){
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
    for(int i=0;i<strlen(Input);i++){
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

void pause(){
    String Input = (String)calloc(10,sizeof(char));
    while(Input[0] != '\n'){
        printf("PUSH ENTER > ");
        fgets(Input,3,stdin);
        }
    free(Input);
}

// Pas de moi...
void setConsoleSize(int width, int height) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Définir la taille du buffer d'écran
    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(hOut, bufferSize);

    // Définir la taille de la fenêtre
    SMALL_RECT windowSize = {0, 0, width - 1, height - 1};
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);
}