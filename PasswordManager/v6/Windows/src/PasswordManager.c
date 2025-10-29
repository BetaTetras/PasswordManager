/*
 * WALL OF BUGS :
 *  
 *  ERREUR N°1:
 *      Coodown trop long si spam d'input qui ne sont pas des fléche
 *  ERREUR N°2:
 *      Pendant le cooldown si j'appuis sur beaucoup de fois les fleche
 *      ca fais n'imp et ca fais crash l'app
 *  ERREUR N°3:
 *      Modif de l'ID = crash
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/DataExplorer.h"
#include "../lib/Tools.h"

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$&'()*+,-./:;<=>?@[]^_`{ }~|"

int mainMenu(String Data,String MDP);
    String PasswordManager(String DATA,String MDP);
        String ConsultationMDP(String DATA);
            String AffichageTableau(String DATA);
            String AffichageListe(String DATA);
        String EditDataBase(String DATA);
            String AjoutCompte(String DATA);
            String SuppressionCompte(String DATA);
            String ModificationCompte(String DATA);
    String PlusInformation();

int SetUp();

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    FILE *testEXIST = fopen("DATA.txt","r");
    if(testEXIST == NULL){
        if(SetUp() == 1){
            return 1;
        }
    }
    system("cls");
    fclose(testEXIST);

    FILE *DataBrute = fopen("DATA.txt","r");
    String DATA = (String)calloc(100000,sizeof(char));
    // String DATA = getFileFromPointer(DataBrute);
    strcat(DATA,getFileFromPointer(DataBrute));
    fclose(DataBrute);
    String Buffer = getLigne(DATA,0);

   if(strcmp(strbcpy(Buffer,1,6),"Index") == 0){
        printf_RED("\n# Erreur...\n# Le chiffrement n'a pas ete effectuer lors de l'ancienne fermeture de l'application...\n# Vous devez IMPERATIVEMENT fermer l'application DEPUIS l'application\n\n");
        pause();
        return 1;
   } 

    String MDP = (String)calloc(100,sizeof(char));

    printf("\nMot de passe :\n    > ");
    fgets(MDP,100,stdin);
    removeEnter(MDP);

    UncryptingString(Buffer,MDP);

    if(strcmp(strbcpy(Buffer,1,6),"Index") != 0){
        printf("    /// DEBUG : %s\n",Buffer);
        printf_RED("\n# Error...\n# Mauvais mot de passe !\n\n");
        pause();
        return 1;
    }
        
    UncryptingString(DATA,MDP);

    mainMenu(DATA,MDP);

    return 0;
}

int mainMenu(String DATA,String MDP){
    while(1)
    {
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n\n\n");


        switch (TerminalUi(5,3,"Password Manager","Plus d'information","Quitter..."))
        {
        case 1:
            DATA = PasswordManager(DATA,MDP);
        break;
            
        case 2:
            DATA = PlusInformation(DATA);
        break;

        case 3:
            remove("DATA.txt");
            EncryptingString(DATA,MDP);
            FILE* FinalFile = fopen("DATA.txt","w");
            fprintf(FinalFile,"%s",DATA);
            fclose(FinalFile);
            return 0;
        break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

String PasswordManager(String DATA,String MDP){

    while(1){
        system("cls");

        

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf_MAGENTA("[PasswordManager]\n\n");

        switch (TerminalUi(5,4,"Consultez les mots de passe","Ajouter/Supprimer/Modifier un compte","Cree une sauvegarde de la base de donnee","Retour ..."))
        {
        case 1:
            DATA = ConsultationMDP(DATA);
        break;
            
        case 2:
            DATA = EditDataBase(DATA);
        break;
            
        case 3: {
            String cpyDATA = malloc(strlen(DATA)+1);
            strcpy(cpyDATA,DATA);

            String EncryptedData = EncryptingString(cpyDATA,MDP);
            String SavePath = AutoNaming("DataSaves", "../saves/", ".txt");

            FILE *NewFile = fopen(SavePath, "w");
            fprintf(NewFile, "%s", EncryptedData);
            fclose(NewFile);
            
            free(NewFile);
            free(cpyDATA);

            system("cls");
            printf_GREEN("Une copie de votre base de donnee de mot de passe a etais faire dans le repetoire \"saves\"!\n\n\n");
            pause();

        }
            return DATA;
        break;

        case 4:
            return DATA;
        break;
        }
    }

}

String PlusInformation(String DATA) {
    system("cls");

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager v6.0 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf_MAGENTA("[ Plus d'informations ]\n\n");

    printf("Createur     : Gregoire GIBRAT (BetaTetras)\n");
    printf("Version      : v6.0\n");
    printf("Code source  : https://github.com/BetaTetras/PasswordManager/tree/main/PasswordManager\n\n");

    printf("Presentation du projet :\n");
    printf("PasswordManager repond a un probleme que j'ai moi-même rencontre : le stockage et la gestion de mots de passe.\n");
    printf("Il n'est pas pratique de devoir fouiller dans une liste interminable de mots de passe stockes un peu partout...\n");
    printf("C'est la que PasswordManager intervient !\n\n");
    printf("Grâce a cette application, vous pouvez organiser vos mots de passe, les afficher sous forme de tableau ou de liste, ou encore faire une\n");
    printf("recherche ciblee pour retrouver rapidement l'information souhaitee.\n\n");
    printf("Plus besoin de galerer avec des notes eparpillees :\n");
    printf("PasswordManager centralise tout pour vous, simplement.\n\n");

    pause();

    return DATA;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

String ConsultationMDP(String DATA){
    String NomApplication = (String)calloc(1000,sizeof(char));

    while(1){
        system("cls");

        

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf_MAGENTA("[PasswordManager] -> [Consultez les mots de passe] \n\n");

        switch (TerminalUi(5,4,"Affichage SELECTION","Affichage TABLEAU","Affichage LISTE","Retour ..."))
        {
        case 1:
            printf("\nEntre le nom de votre application :\n     > ");
            fgets(NomApplication,100,stdin);
            printf("\n");
            if(strcmp(NomApplication,"") == 0){
                printf_RED("\n# Erreur\n# Il faut rentrer le nom d'une application !\n\n");
                pause();
                return DATA;
            }
            
            system("cls");

            removeEnter(NomApplication);
            DisplaySpecifiqueTable(DATA,NomApplication,1);

            printf("\n");
            pause();
        break;

        case 2:
            DATA = AffichageTableau(DATA);
        break;

        case 3:
            AffichageListe(DATA);
        break;
            
        case 4:
            return DATA;
        break;
        }  
    }
}

String EditDataBase(String DATA){

    while(1){
        system("cls");

        

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf_MAGENTA("[PasswordManager] -> [Ajouter/Supprimer/Modifier...]\n\n");

        switch (TerminalUi(5,4,"Ajouter un compte","Supprimer un compte","Modifier un compte","Retour..."))
        {
        case 1:
            DATA = AjoutCompte(DATA);
        break;

        case 2:
            DATA = SuppressionCompte(DATA);
        break;
            
        case 3:
            DATA = ModificationCompte(DATA);
        break;

        case 4:
            return DATA;
        break;
        }
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

String AffichageTableau(String DATA){

    while(1){
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf_MAGENTA("[PasswordManager] -> [Consultez les mots de passe] -> [Affichage TABLEAU]\n\n");

        switch (TerminalUi(5,4,"Affichage TABLEAU ordonnee par APPLICATION","Affichage TABLEAU ordonnee par IDENTIFIANT","Affichage TABLEAU ordonnee par MOT DE PASSE","Retour..."))
        {
        case 1:
            system("cls");

            DisplayOrdonnedTable(DATA,1);

            pause();
        break;

        case 2:
            system("cls");

            DisplayOrdonnedTable(DATA,2);

            pause();
        break;

        case 3:
            system("cls");

            DisplayOrdonnedTable(DATA,3);

            pause();
        break;

        case 4:
            return DATA;  
        break;

        }  
    }
}

String AffichageListe(String DATA){

    while(1){
        system("cls");

        

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf_MAGENTA("[PasswordManager] -> [Consultez les mots de passe] -> [Affichage LISTE]\n\n");

        switch (TerminalUi(5,4,"Affichage LISTE ordonnee par APPLICATION","Affichage LISTE ordonnee par IDENTIFIANT","Affichage LISTE ordonnee par MOT DE PASSE","Retour..."))
        {
        case 1:
            system("cls");

            DisplayOrdonnedListe(DATA,1);
            
            pause();
        break;

        case 2:
            system("cls");

            DisplayOrdonnedListe(DATA,2);
            
            pause();
        break;

        case 3:
            system("cls");

            DisplayOrdonnedListe(DATA,3);
            
            pause();
            
        break;

        case 4:
          return DATA;  
        break;

        }  
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

String AjoutCompte(String DATA){
    String NomApp = (String)calloc(1000,sizeof(char));
    String IdApp = (String)calloc(1000,sizeof(char));
    String MDP = (String)calloc(1000,sizeof(char));

    String* ListeApp = (String*)calloc(1000,sizeof(String));
        ListeApp = getListeColonne(DATA,1);
    String* ListeId = (String*)calloc(1000,sizeof(String));
        ListeId = getListeColonne(DATA,2);
        

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    

    printf_MAGENTA("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Ajout]\n\n");

    printf("Le nom de l'application concernee :\n   > ");
    fgets(NomApp,1000,stdin);
    removeEnter(NomApp);

    if(strcmp(NomApp,"") == 0){
        printf_RED("\n# Erreur ...\n# Il faut entrer le nom d'une application\n\n");
        free(IdApp);
        free(MDP);
        free(ListeApp);
        free(ListeId);
        pause();
        return DATA;
    }

    printf("\n");
    printf("Le nom de l'identifiant concernee :\n   > ");
    fgets(IdApp,1000,stdin);
    removeEnter(IdApp);

    if(strcmp(IdApp,"") == 0){
        printf_RED("\n# Erreur ...\n# Il faut entrer l'id d'une application\n\n");
        free(IdApp);
        free(MDP);
        free(ListeApp);
        free(ListeId);
        pause();
        return DATA;
    }

    for(int i=0;i<getNbElementListe(ListeApp);i++){
        if(strcmp(ListeApp[i],NomApp) == 0 && strcmp(ListeId[i],IdApp) == 0 ){
            printf("\n      # Erreur...\n      # Un compte avec cette identifiant existe deja dans cette application...\n\n\n");
            // free(NomApp);
            free(IdApp);
            free(MDP);
            free(ListeApp);
            free(ListeId);
            pause();
            return DATA;
        }
    }

    printf("\n");
    printf("Le mot de passe du compte concernee (\"Auto\" pour generer un mot de passe TRES fort):\n   > ");
    fgets(MDP,1000,stdin);
    removeEnter(MDP);
    if(strcmp(MDP,"Auto") == 0){  
        strcpy(MDP,generatPassword(1,1,1,50));
    }

    DATA = addLigneAutoIndexSpecificStringV2(DATA,3,NomApp,IdApp,MDP);

    printf_GREEN("\nCompte ajouter avec succes !\n");
    
    // free(NomApp);
    free(IdApp);
    free(MDP);
    free(ListeApp);
    free(ListeId);

    pause();
    return DATA;
}

String SuppressionCompte(String DATA){
    String Input = (String)calloc(100,sizeof(char));

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    

    printf_MAGENTA("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Supprimer]\n\n");

    printf("Tableau de tout les compte reliee a la base de donnee :\n\n");
    DisplayTable(DATA);

    printf("\n");

    printf("Choisir un index a supprimer (ENTER pour retour) : \n     > ");
    fgets(Input,1000,stdin);
    if(strcmp(Input,"") == 0){
        free(Input);
        return DATA;
    }
    nbrBetween(Input,0,getNbLigne(DATA)-1);

    DATA = removeOneIndex(DATA,atoi(Input));

    system("cls");

    printf("Nouveau tableau:\n\n");

    DisplayTable(DATA);
    printf("\n\n");

    pause();

    return DATA;
}

String ModificationCompte(String DATA){
    String Input = (String)calloc(100,sizeof(char));
    String NewLigne = (String)calloc(1000,sizeof(char));

    String* ListeApp = (String*)calloc(1000,sizeof(String));
        ListeApp = getListeColonne(DATA,1);
    String* ListeId = (String*)calloc(1000,sizeof(String));
        ListeId = getListeColonne(DATA,2);

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

      

    printf_MAGENTA("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Modifiee]\n\n");

    printf("Tableau de tout les compte reliee a la base de donnee :\n\n");
    DisplayTable(DATA);

    printf("\n");

    printf("Choisir un index a modifier (ENTER pour retour): \n     > ");
    fgets(Input,1000,stdin);
    removeEnter(Input);
    if(strcmp("",Input) == 0){
        free(Input);
        return DATA;
    }
    nbrBetween(Input,0,getNbLigne(DATA)-1);
    int choixLigne = strNbr(Input);

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf_MAGENTA("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Modifiee]\n\n");

    printf("Ligne selectionnee :\n");
    printf("    Application  : %s\n",getLigneXcolonneY(DATA,choixLigne,1));
    printf("    Identifiant  : %s\n",getLigneXcolonneY(DATA,choixLigne,2));
    printf("    Mot de passe : %s\n\n",getLigneXcolonneY(DATA,choixLigne,3));

    switch (TerminalUi(9,4,"Modifier l'application","Modifier l'identifiant","Modifier de mot de passe","Retour...")){
        case 1:
            printf("\nEntree la nouvelle application :\n  > ");
            fgets(Input,100,stdin);
            removeEnter(Input);

            for(int i = 0; i < getNbElementListe(ListeApp);i++){
                if(strcmp(Input,ListeApp[i]) == 0){
                    if(strcmp(getLigneXcolonneY(DATA,choixLigne,2),ListeId[i]) == 0){
                        free(Input);
                        free(NewLigne);
                        free(ListeApp);
                        free(ListeId);
                        printf_RED("\n# Erreur...\n# Un compte dans cette application existe deja avec cette identifiant...\n\n\n");
                        pause();
                        return DATA;
                    }
                }
            }

            strcat(NewLigne,Input);
            strcat(NewLigne,"|");
            strcat(NewLigne,getLigneXcolonneY(DATA,choixLigne,2));
            strcat(NewLigne,"|");
            strcat(NewLigne,getLigneXcolonneY(DATA,choixLigne,3));
            strcat(NewLigne,"|");

            DATA = modifieOneLigne(DATA,choixLigne,NewLigne);
            
            printf_GREEN("\nChangement effectuee !\n\n");
            pause();
        break;

        case 2:
            printf("\nEntree le nouvelle identifiant :\n  > ");
            fgets(Input,100,stdin);
            removeEnter(Input);

            for(int i = 0; i < getNbElementListe(ListeApp);i++){
                if(strcmp(getLigneXcolonneY(DATA,choixLigne,1),ListeApp[i]) == 0){
                    if(strcmp(Input,ListeId[i]) == 0){
                        free(Input);
                        free(NewLigne);
                        free(ListeApp);
                        free(ListeId);
                        printf_RED("\n# Erreur...\n# Un compte dans cette application existe deja avec cette identifiant...\n\n\n");
                        pause();
                        return DATA;
                    }
                }
            }

            strcat(NewLigne,getLigneXcolonneY(DATA,choixLigne,1));
            strcat(NewLigne,"|");
            strcat(NewLigne,Input);
            strcat(NewLigne,"|");
            strcat(NewLigne,getLigneXcolonneY(DATA,choixLigne,3));
            strcat(NewLigne,"|");

            DATA = modifieOneLigne(DATA,choixLigne,NewLigne);
            
            printf_GREEN("\nChangement effectuee !\n\n");
            pause();
        break;

        case 3:
            printf("\nEntree le nouveau mot de passe (\"Auto\" pour generer un mot de passe TRES fort):\n  > ");
            fgets(Input,100,stdin);
            removeEnter(Input);
            if(strcmp(Input,"Auto") == 0){  
                strcpy(Input,generatPassword(1,1,1,50));
            }

            strcat(NewLigne,getLigneXcolonneY(DATA,choixLigne,1));
            strcat(NewLigne,"|");
            strcat(NewLigne,getLigneXcolonneY(DATA,choixLigne,3));
            strcat(NewLigne,"|");
            strcat(NewLigne,Input);
            strcat(NewLigne,"|");

            DATA = modifieOneLigne(DATA,choixLigne,NewLigne);
            
            printf_GREEN("\nChangement effectuee !\n\n");
            pause();
        break;

        case 4:
            return DATA;
        break;
        
    }

    return DATA;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////

int SetUp(){
    FILE *fichier = fopen("DATA.txt","r");
    if(fichier != NULL){
        printf_RED("\n# Erreur...\n# DATA.txt deja present, SetUp deja Initialise\n\n");
        fclose(fichier);
        pause();
        return 1;
    }

    String MDP1 = (String)calloc(100,sizeof(char));
    String MDP2 = (String)calloc(100,sizeof(char));

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= SetUp PasswordManager V.4 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    printf("Bienvenue dans le SetUp de PassWordManager v3!\n");
    printf("Pour garantir la securite de vos mots de passe, vos donnees seront chiffrees\n");
    printf("grace a un mot de passe maitre.\n\n");

    printf_RED(" - ATTENTION : Ce mot de passe est indispensable pour acceder a vos donnees !\n");
    printf_RED(" - En cas d'oubli, il sera impossible de les recuperer.\n\n");

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
            printf_RED("\n# Erreur...\n# Les deux mot de passe ne sont pas identique...\n\n");
        }
    }

    FILE* fichierCreation = fopen("DATA.txt","w+");

    String Base = (String)calloc(50,sizeof(char));
    strcpy(Base,"|Index|Application|Identifiant|Mot de passe|\n");
    EncryptingString(Base,MDP1);
    fprintf(fichierCreation,Base);

    printf("Votre mot de passe est : %s\n\n",MDP1);
    removeEnter(MDP1);

    fclose(fichierCreation);
    free(MDP1);
    free(MDP2);
    return 0;
}
