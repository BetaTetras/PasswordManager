#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/Tools.h"

typedef char* String;

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$&'()*+,-./:;<=>?@[]^_`{ }~|"


int main(){
    FILE *testDATA = fopen("DATA.txt","r");
    if(testDATA == NULL){
        Color_printf_RED("\n# Erreur...\n# DATA.txt n'existe pas.\n\n");
        pause();
        return 1;
    }

    String Buffer = (String)calloc(500,sizeof(char));
    fgets(Buffer,500,testDATA);

    if(strcmp(strbcpy(Buffer,0,6),"Index") != 0){
        Color_printf_RED("\n# Erreur...\n# Le fichier est bien chiffrer... \n\n");
        pause();
        return 1;
    }
    fclose(testDATA);

    String MDP1 = (String)calloc(100,sizeof(char));
    String MDP2 = (String)calloc(100,sizeof(char));

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= BackUp PasswordManager V.4 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    printf("Bienvenue dans le BackUp de PassWordManager v4!\n");
    printf("En cas d'erreur de chiffrement ou alors la recuperation de base de donnee chiffree ce code serra utilisee\n\n");
    
    Color_printf_RED("Pour assuree une securite accrue nous allons vous demander d'entrer un nouveau mot de passe.\n\n");

    Color_printf_RED(" - ATTENTION : Ce mot de passe est indispensable pour acceder a vos donnees !\n");
    Color_printf_RED(" - En cas d'oubli, il sera impossible de les recuperer.\n\n");

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
            Color_printf_RED("\n# Erreur...\n# Les deux mot de passe ne sont pas identique...\n\n");
        }
    }
    printf("Votre mot de passe est : %s\n\n",MDP1);

    EncryptingName("DATA.txt",MDP1);

    Color_printf_GREEN("BASE DE DONNER FONCTIONNELLE !!!\n\n");
    pause();
}