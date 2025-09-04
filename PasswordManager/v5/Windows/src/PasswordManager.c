/* ERREUR A FIX :
 * - Problème de connexion
 * - Implémentation des saves (A test)
 * - Maybe Implémentation de la back up ???
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/DataExplorer.h"
#include "../lib/Tools.h"

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$&'()*+,-./:;<=>?@[]^_`{ }~|"

int mainMenu(FILE *fichier,String MDP);
    void PasswordManager(FILE *fichier,String MDP);
        void ConsultationMDP(FILE *fichier);
            void AffichageTableau(FILE *fichier);
            void AffichageListe(FILE *fichier);
        void EditDataBase(FILE *fichier);
            void AjoutCompte(FILE *fichier);
            void SuppressionCompte(FILE *fichier);
            void ModificationCompte(FILE *fichier);
    void PlusInformation();

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

    FILE *testDATA = fopen("DATA.txt","r");

    String Buffer = (String)calloc(1000,sizeof(char));
    fgets(Buffer,1000,testDATA);

    if(strcmp(strbcpy(Buffer,1,6),"Index") == 0){
        printf_RED("\n# Erreur...\n# Le chiffrement n'a pas ete effectuer lors de l'ancienne fermeture de l'application...\n# Vous devez IMPERATIVEMENT fermer l'application DEPUIS l'application\n\n");
        pause();
        return 1;
    }

    String MDP = (String)calloc(100,sizeof(char));

    printf("\nMot de passe :\n    > ");
    fgets(MDP,100,stdin);
    removeEnter(MDP);

    UncryptingOneLigne(Buffer,MDP);

    if(strcmp(strbcpy(Buffer,1,6),"Index") != 0){
        printf("    /// DEBUG : %s\n",Buffer);
        printf_RED("\n# Error...\n# Mauvais mot de passe !\n\n");
        pause();
        return 1;
    }
    fclose(testDATA);
        
    UncryptingName("DATA.txt",MDP);

    FILE *DATA = fopen("DATA.txt","r+");

    mainMenu(DATA,MDP);
}

int mainMenu(FILE *fichier,String MDP){

    while(1)
    {
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.5 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n\n\n");



        switch (TerminalUi(5,3,"Password Manager","Plus d'information","Quitter..."))
        {
        case 1:
            PasswordManager(fichier,MDP);
        break;
            
        case 2:
            PlusInformation();
        break;

        case 3:
            EncryptingName("DATA.txt",MDP);
            return 0;
        break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void PasswordManager(FILE *fichier,String MDP){

    while(1){
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.5 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf_MAGENTA("[PasswordManager]\n\n");

        switch (TerminalUi(5,4,"Consultez les mots de passe","Ajouter/Supprimer/Modifier un compte","Cree une sauvegarde de la base de donnee","Retour ..."))
        {
        case 1:
            ConsultationMDP(fichier);
        break;
            
        case 2:
            EditDataBase(fichier);
        break;
            
        case 3: {
            String EncryptedData = EncryptingString(getFileFromName("DATA.txt"),MDP);
            String SavePath = AutoNaming("DataSaves", "../saves/", ".txt");

            FILE *NewFile = fopen(SavePath, "w");
            fprintf(NewFile, "%s", EncryptedData);
            fclose(NewFile);
            

            free(NewFile);

            system("cls");
            printf_GREEN("Une copie de votre base de donnee de mot de passe a etais faire dans le repetoire \"saves\"!\n\n\n");
            pause();

        }break;

        case 4:
            return;
        break;
        }
    }


}

void PlusInformation() {
    system("cls");

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager v3.0 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf_MAGENTA("[ Plus d'informations ]\n\n");

    printf("Createur     : Gregoire GIBRAT (BetaTetras)\n");
    printf("Version      : v5.0\n");
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
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConsultationMDP(FILE *fichier){
    String NomApplication = (String)calloc(1000,sizeof(char));

    while(1){
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.5 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf_MAGENTA("[PasswordManager] -> [Consultez les mots de passe] \n\n");

        switch (TerminalUi(5,4,"Affichage SELECTION","Affichage TABLEAU","Affichage LISTE","Retour ..."))
        {
        case 1:
            printf("\nEntre le nom de votre application :\n     > ");
            fgets(NomApplication,100,stdin);
            removeEnter(NomApplication);

            system("cls");

            DisplaySpecifiqueTable(fichier,NomApplication,1);

            printf("\n");
            pause();
        break;

        case 2:
            AffichageTableau(fichier);
        break;

        case 3:
            AffichageListe(fichier);
        break;
            
        case 4:
            return;
        break;
        }  
    }
}

void EditDataBase(FILE *fichier){

    while(1){
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.5 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf_MAGENTA("[PasswordManager] -> [Ajouter/Supprimer/Modifier...]\n\n");

        switch (TerminalUi(5,4,"Ajouter un compte","Supprimer un compte","Modifier un compte","Retour..."))
        {
        case 1:
            AjoutCompte(fichier);
        break;

        case 2:
            SuppressionCompte(fichier);
        break;
            
        case 3:
            ModificationCompte(fichier);
        break;

        case 4:
            return;
        break;
        }
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void AffichageTableau(FILE *fichier){

    while(1){
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.5 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf_MAGENTA("[PasswordManager] -> [Consultez les mots de passe] -> [Affichage TABLEAU]\n\n");

        switch (TerminalUi(5,4,"Affichage TABLEAU ordonnee par APPLICATION","Affichage TABLEAU ordonnee par IDENTIFIANT","Affichage TABLEAU ordonnee par MOT DE PASSE","Retour..."))
        {
        case 1:
            system("cls");

            DisplayOrdonnedTable(fichier,1);

            pause();
        break;

        case 2:
            system("cls");

            DisplayOrdonnedTable(fichier,2);

            pause();
        break;

        case 3:
            system("cls");

            DisplayOrdonnedTable(fichier,3);

            pause();
        break;

        case 4:
            return;  
        break;

        }  
    }
}

void AffichageListe(FILE *fichier){

    while(1){
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.5 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf_MAGENTA("[PasswordManager] -> [Consultez les mots de passe] -> [Affichage LISTE]\n\n");

        switch (TerminalUi(5,4,"Affichage LISTE ordonnee par APPLICATION","Affichage LISTE ordonnee par IDENTIFIANT","Affichage LISTE ordonnee par MOT DE PASSE","Retour..."))
        {
        case 1:
            system("cls");

            DisplayOrdonnedListe(fichier,1);
            
            pause();
        break;

        case 2:
            system("cls");

            DisplayOrdonnedListe(fichier,2);
            
            pause();
        break;

        case 3:
            system("cls");

            DisplayOrdonnedListe(fichier,3);
            
            pause();
            
        break;

        case 4:
          return;  
        break;

        }  
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void AjoutCompte(FILE *fichier){
    String NomApp = (String)calloc(1000,sizeof(char));
    String IdApp = (String)calloc(1000,sizeof(char));
    String MDP = (String)calloc(1000,sizeof(char));

    String FinaleLigne = (String)calloc(1000,sizeof(char));

    String* ListeApp = (String*)calloc(1000,sizeof(String));
        ListeApp = getListeColonne(fichier,1);
    String* ListeId = (String*)calloc(1000,sizeof(String));
        ListeId = getListeColonne(fichier,2);

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.5 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf_MAGENTA("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Ajout]\n\n");

    printf("Le nom de l'application concernee :\n   > ");
    fgets(NomApp,1000,stdin);
    removeEnter(NomApp);

    printf("\n");
    printf("Le nom de l'identifiant concernee :\n   > ");
    fgets(IdApp,1000,stdin);
    removeEnter(IdApp);

    for(int i=1;i<getNbElementListe(ListeApp);i++){
        if(strcmp(ListeApp[i],NomApp) == 0 && strcmp(ListeId[i],IdApp) == 0 ){
            printf("\n      # Erreur...\n      # Un compte avec cette identifiant existe deja dans cette application...\n\n\n");
            free(NomApp);
            free(IdApp);
            free(MDP);
            free(FinaleLigne);
            free(ListeApp);
            free(ListeId);
            pause();
            return;
        }
    }

    printf("\n");
    printf("Le mot de passe du compte concernee (\"Auto\" pour generer un mot de passe TRES fort):\n   > ");
    fgets(MDP,1000,stdin);
    removeEnter(MDP);
    if(strcmp(MDP,"Auto") == 0){  
        strcpy(MDP,generatPassword(1,1,1,50));
    }

    strcat(FinaleLigne,NomApp);
    strcat(FinaleLigne,"|");
    strcat(FinaleLigne,IdApp);
    strcat(FinaleLigne,"|");
    strcat(FinaleLigne,MDP);
    strcat(FinaleLigne,"|");
    
    addLigneAutoIndexSpecificString(fichier,FinaleLigne);

    printf_GREEN("\nCompte ajouter avec succes !\n");


    free(NomApp);
    free(IdApp);
    free(MDP);
    free(FinaleLigne);
    free(ListeApp);
    free(ListeId);
    pause();
    return;
}

void SuppressionCompte(FILE *fichier){
    String Input = (String)calloc(100,sizeof(char));

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.5 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf_MAGENTA("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Supprimer]\n\n");

    printf("Tableau de tout les compte reliee a la base de donnee :\n\n");
    DisplayTable(fichier);

    printf("\n");

    printf("Choisir un index a supprimer (0 pour retour) : \n     > ");
    fgets(Input,1000,stdin);
    if(strNbr(Input) == 0){
        return;
    }
    nbrBetween(Input,0,getNbLigne(fichier)-1);

    fichier = removeOneIndex(fichier,atoi(Input));

    system("cls");

    printf("Nouveau tableau:\n\n");

    DisplayTable(fichier);
    printf("\n\n");

    pause();
}

void ModificationCompte(FILE *fichier){
    String Input = (String)calloc(100,sizeof(char));
    String NewLigne = (String)calloc(1000,sizeof(char));

    String* ListeApp = (String*)calloc(1000,sizeof(String));
        ListeApp = getListeColonne(fichier,1);
    String* ListeId = (String*)calloc(1000,sizeof(String));
        ListeId = getListeColonne(fichier,2);

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.5 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf_MAGENTA("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Modifiee]\n\n");

    printf("Tableau de tout les compte reliee a la base de donnee :\n\n");
    DisplayTable(fichier);

    printf("\n");

    printf("Choisir un index a modifier : \n     > ");
    fgets(Input,1000,stdin);
    nbrBetween(Input,0,getNbLigne(fichier)-1);
    int choixLigne = strNbr(Input);

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.5 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf_MAGENTA("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Modifiee]\n\n");

    printf("Ligne selectionnee :\n");
    printf("    Application  : %s\n",getLigneXcolonneY(fichier,choixLigne,1));
    printf("    Identifiant  : %s\n",getLigneXcolonneY(fichier,choixLigne,2));
    printf("    Mot de passe : %s\n\n",getLigneXcolonneY(fichier,choixLigne,3));

    switch (TerminalUi(9,4,"Modifier l'application","Modifier l'identifiant","Modifier de mot de passe","Retour...")){
        case 1:
            printf("\nEntree la nouvelle application :\n  > ");
            fgets(Input,1000,stdin);
            removeEnter(Input);

            for(int i=0;i<getNbElementListe(ListeApp);i++){
                if(strcmp(Input,ListeApp[i]) == 0){
                    if(strcmp(getLigneXcolonneY(fichier,choixLigne,2),getLigneXcolonneY(fichier,i,2)) == 0){
                        free(Input);
                        free(NewLigne);
                        free(ListeApp);
                        free(ListeId);
                        printf_RED("\n# Erreur...\n# Un compte dans cette application existe deja avec cette identifiant...\n\n\n");
                        pause();
                        return;
                    }
                }
            }

            strcat(NewLigne,Input);
            strcat(NewLigne, "|");
            strcat(NewLigne,getLigneXcolonneY(fichier,choixLigne,2));
            strcat(NewLigne, "|");
            strcat(NewLigne,getLigneXcolonneY(fichier,choixLigne,3));
            strcat(NewLigne, "|");

            fichier = modifieOneLigne(fichier,choixLigne,NewLigne);

            printf_GREEN("\nChangement effectuee !\n\n");
            free(Input);
            free(NewLigne);
            free(ListeApp);
            free(ListeId);
            pause();  
        break;

        case 2:
            printf("\nEntree le nouvelle identifiant :\n  > ");
            fgets(Input,1000,stdin);
            removeEnter(Input);

            for(int i=0;i<getNbElementListe(ListeId);i++){
                if(strcmp(Input,ListeId[i]) == 0){
                    if(strcmp(getLigneXcolonneY(fichier,choixLigne,1),getLigneXcolonneY(fichier,i,1)) == 0){
                        free(Input);
                        free(NewLigne);
                        free(ListeApp);
                        free(ListeId);
                        printf_RED("\n# Erreur...\n# Un identifiant identique existe deja dans cette application...\n\n\n");
                        pause();
                        return;
                    }
                }
            }

            strcat(NewLigne,getLigneXcolonneY(fichier,choixLigne,1));
            strcat(NewLigne,"|");
            strcat(NewLigne,Input);
            strcat(NewLigne,"|");
            strcat(NewLigne,getLigneXcolonneY(fichier,choixLigne,3));
            strcat(NewLigne, "|");

            fichier = modifieOneLigne(fichier,choixLigne,NewLigne);

            printf_GREEN("Changement effectuee !\n\n");
            free(Input);
            free(NewLigne);
            free(ListeApp);
            free(ListeId);
            pause();  
        break;

        case 3:
            printf("\nEntree le nouveau mot de passe (\"Auto\" pour acceder au choix de generation):\n  > ");
            fgets(Input,1000,stdin);
            removeEnter(Input);
            if(strcmp(Input,"Auto") == 0){  
                strcpy(Input,generatPassword(1,1,1,50));
            }

            strcat(NewLigne,getLigneXcolonneY(fichier,choixLigne,1));
            strcat(NewLigne, "|");
            strcat(NewLigne,getLigneXcolonneY(fichier,choixLigne,2));
            strcat(NewLigne, "|");
            strcat(NewLigne,Input);
            strcat(NewLigne, "|");

            printf_GREEN("Changement effectuee !\n\n");
            modifieOneLigne(fichier,choixLigne,NewLigne);
            free(NewLigne);
            pause();
        break;

        case 4:
            return;
        break;
        
    }
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

    FILE *fichierCreation = fopen("DATA.txt","w+");

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
