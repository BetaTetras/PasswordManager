#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/Tools.h"

typedef char* String;

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$&'()*+,-./:;<=>?@[]^_`{ }~|"


int main(){
    FILE *testDATA = fopen("DATA.txt","r");
    if(testDATA == NULL){
        printf_RGB(255,0,0,"\n# Erreur...\n# DATA.txt n'existe pas.\n\n");
        _pause();
        return 1;
    }

    String Buffer = (String)calloc(500,sizeof(char));
    fgets(Buffer,500,testDATA);

    if(strcmp(strbcpy(Buffer,1,6),"Index") != 0){
        printf_RGB(255,0,0,"\n# Erreur...\n# Le fichier est bien chiffrer... \n\n");
        _pause();
        return 1;
    }
    fclose(testDATA);

    String MDP1 = (String)calloc(100,sizeof(char));
    String MDP2 = (String)calloc(100,sizeof(char));

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= BackUp PasswordManager V.4 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    printf("Bienvenue dans le BackUp de PassWordManager v4!\n");
    printf("En cas d'erreur de chiffrement ou alors la recuperation de base de donnee chiffree ce code serra utilisee\n\n");
    
    printf_RGB(255,0,0,"Pour assuree une securite accrue nous allons vous demander d'entrer un nouveau mot de passe.\n\n");

    printf_RGB(255,0,0," - ATTENTION : Ce mot de passe est indispensable pour acceder a vos donnees !\n");
    printf_RGB(255,0,0," - En cas d'oubli, il sera impossible de les recuperer.\n\n");

    while(1){
        printf("Votre mot de passe (Caractere accentuer pas accepter):\n      > ");
        fgets(MDP1,100,stdin);
        removeEnter(MDP1);
        PasswordVerificator(ALPHABET,MDP1);
        printf("\n");
        printf("Reentrer votre mot de passe :\n      > ");
        fgets(MDP2,100,stdin);
        removeEnter(MDP2);
        printf("\n");
        if(strcmp(MDP1,MDP2) == 0){
            break;
        }else{
            printf_RGB(255,0,0,"\n# Erreur...\n# Les deux mot de passe ne sont pas identique...\n\n");
        }
    }
    printf("Votre mot de passe est : %s\n\n",MDP1);

    EncryptingName("DATA.txt",MDP1);

    printf_RGB(0,255,0,"BASE DE DONNER FONCTIONNELLE !!!\n\n");

    _pause();
}