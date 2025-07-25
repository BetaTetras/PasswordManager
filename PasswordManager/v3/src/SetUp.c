#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/Tools.h"

typedef char* String;

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$&'()*+,-./:;<=>?@[]^_`{ }~|"

int main(){
    FILE *fichier = fopen("DATA.txt","r");
    if(fichier != NULL){
        printf("\n# Erreur...\n# DATA.txt deja present, SetUp deja Initialise\n\n");
        fclose(fichier);
        pause();
        return 1;
    }

    String MDP1 = (String)calloc(100,sizeof(char));
    String MDP2 = (String)calloc(100,sizeof(char));

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= SetUp PasswordManager V.3 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    printf("Bienvenue dans le SetUp de PassWordManager v3!\n");
    printf("Pour garantir la securite de vos mots de passe, vos donnees seront chiffrees\n");
    printf("grace a un mot de passe maitre.\n\n");

    printf(" - ATTENTION : Ce mot de passe est indispensable pour acceder a vos donnees !\n");
    printf(" - En cas d'oubli, il sera impossible de les recuperer.\n\n");

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
            printf("\n# Erreur...\n# Les deux mot de passe ne sont pas identique...\n\n");
        }
    }

    FILE *fichierCreation = fopen("DATA.txt","w+");
    fprintf(fichierCreation,"|Index|Application|Identifiant|Mot de passe|\n");
    fclose(fichierCreation);

    printf("Votre mot de passe est : %s\n\n",MDP1);
    removeEnter(MDP1);
    EncryptingName("DATA.txt",MDP1);
    free(MDP1);
    free(MDP2);
    pause();
    return 0;
}
