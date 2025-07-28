#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/DataExplorer.h"
#include "../lib/Tools.h"

int mainMenu(FILE *fichier,String MDP);
    void PasswordManager(FILE *fichier);
        void ConsultationMDP(FILE *fichier);
            void AffichageTableau(FILE *fichier);
            void AffichageListe(FILE *fichier);
        void EditDataBase(FILE *fichier);
            void AjoutCompte(FILE *fichier);
            void SuppressionCompte(FILE *fichier);
            void ModificationCompte(FILE *fichier);
    void PlusInformation();

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    FILE *testExist = fopen("DATA.txt", "r+");
    if(testExist == NULL){
        printf("\n      # Error...\n      # DATA.txt n'existe pas, il faut d'abord lancer SetUp.exe pour la mise en place...\n\n");
        pause();
        return 1;
    }
    fclose(testExist);

    String MDP = (String)calloc(100, sizeof(char));

    printf("Mot de passe :\n    > ");
    fgets(MDP, 100, stdin);
    removeEnter(MDP);

    FILE *testRightPWD = fopen("DATA.txt", "r+");
    String Element = (String)calloc(100,sizeof(char));
    strcpy(Element,getLigne(testRightPWD,0));
    UncryptingOneLigne(Element,MDP);
    strcpy(Element,strbcpy(Element,0,6));

    if(Element == NULL || strcmp(Element, "Index") != 0){
        printf("\n      # Error...\n      # Mauvais mot de passe...\n\n");
        fclose(testRightPWD);
        free(MDP);
        pause();
        return 1;
    }
    fclose(testRightPWD);

    UncryptingName("DATA.txt",MDP);

    FILE *fichier = fopen("DATA.txt","r+");
    mainMenu(fichier,MDP);

    fclose(fichier);
    free(MDP);

    return 0;
}

int mainMenu(FILE *fichier,String MDP){
    String Input = (String)calloc(100,sizeof(char));

    while(1)
    {
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.1 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n\n\n");



        printf("1 - Password Manager\n");
        printf("2 - Plus d'information\n");
        printf("3 - Quitter...\n\n");
        printf("Fait un choix :\n   > ");
        fgets(Input,500,stdin);
        nbrBetween(Input,1,3);

        switch (strNbr(Input))
        {
        case 1:
            PasswordManager(fichier);
        break;
            
        case 2:
            PlusInformation();
        break;

        case 3:
            fclose(fichier);
            EncryptingName("DATA.txt",MDP);
            return 0;
        break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void PasswordManager(FILE *fichier){
    String Input = (String)calloc(100,sizeof(char));

    while(1){
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.1 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf("[PasswordManager]\n\n");

        printf("1 - Consultez les mots de passe\n");
        printf("2 - Ajouter/Supprimer/Modifier un compte\n");
        printf("3 - Retour ... \n\n");
        printf("Fait un choix :\n   > ");
        fgets(Input,10,stdin);
        nbrBetween(Input,1,3);

        switch (strNbr(Input))
        {
        case 1:
            ConsultationMDP(fichier);
        break;
            
        case 2:
            EditDataBase(fichier);
        break;
            
        case 3:
            free(Input);
            return;
        break;
        }
    }


}

void PlusInformation() {
    system("cls");

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager v3.0 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf("[ Plus d'informations ]\n\n");

    printf("Createur     : Gregoire GIBRAT (BetaTetras)\n");
    printf("Version      : v3.0\n");
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
    String Input = (String)calloc(100,sizeof(char));

    while(1){
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.1 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf("[PasswordManager] -> [Consultez les mots de passe] \n\n");

        printf("1 - Affichage SELECTION\n");
        printf("2 - Affichage TABLEAU\n");
        printf("3 - Affichage LISTE\n");
        printf("4 - Retour ...\n\n");
        printf("Fait un choix :\n   > ");
        fgets(Input,10,stdin);
        nbrBetween(Input,1,4);

        switch (strNbr(Input))
        {
        case 1:
            String NomApplication = (String)calloc(500,sizeof(char));
            removeEnter(Input);
            printf("\nEntre le nom de votre application :\n     > ");
            fgets(NomApplication,100,stdin);
            removeEnter(NomApplication);

            system("cls");

            DisplaySpecifiqueTable(fichier,NomApplication,1);

            printf("\n");
            while(Input[0] != '\n'){
                printf("PUSH ENTER > ");
                fgets(Input,3,stdin);
            }
        break;

        case 2:
            AffichageTableau(fichier);
        break;

        case 3:
            AffichageListe(fichier);
        break;
            
        case 4:
            free(Input);
            return;
        break;
        }  
    }
}

void EditDataBase(FILE *fichier){
    String Input = (String)calloc(100,sizeof(char));

    while(1){
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.1 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf("[PasswordManager] -> [Ajouter/Supprimer/Modifier...]\n\n");

        printf("1 - Ajouter un compte\n");
        printf("2 - Supprimer un compte \n");
        printf("3 - Modifier un compte\n");
        printf("4 - Retour... \n\n");
        printf("Fait un choix :\n   > ");
        fgets(Input,10,stdin);
        nbrBetween(Input,1,4);

        switch (strNbr(Input))
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
            free(Input);
            return;
        break;
        }
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void AffichageTableau(FILE *fichier){
    String Input = (String)calloc(100,sizeof(char));

    while(1){
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.1 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf("[PasswordManager] -> [Consultez les mots de passe] -> [Affichage TABLEAU]\n\n");

        printf("1 - Affichage TABLEAU ordonnee par APPLICATION\n");
        printf("2 - Affichage TABLEAU ordonnee par IDENTIFIANT\n");
        printf("3 - Affichage TABLEAU ordonnee par MOT DE PASSE\n");
        printf("4 - Retour...\n\n");
        printf("Fait un choix :\n   > ");
        fgets(Input,10,stdin);
        nbrBetween(Input,1,4);


        switch (strNbr(Input))
        {
        case 1:
            system("cls");

            DisplayOrdonnedTable(fichier,1);

            while(Input[0] != '\n'){
                printf("PUSH ENTER > ");
                fgets(Input,3,stdin);
            }
        break;

        case 2:
            system("cls");

            DisplayOrdonnedTable(fichier,2);

            while(Input[0] != '\n'){
                printf("PUSH ENTER > ");
                fgets(Input,3,stdin);
            }
        break;

        case 3:
            system("cls");

            DisplayOrdonnedTable(fichier,3);

            while(Input[0] != '\n'){
                printf("PUSH ENTER > ");
                fgets(Input,3,stdin);
            }
        break;

        case 4:
            free(Input);
            return;  
        break;

        }  
    }
}

void AffichageListe(FILE *fichier){
    String Input = (String)calloc(100,sizeof(char));

    while(1){
        system("cls");

        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.1 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

        printf("[PasswordManager] -> [Consultez les mots de passe] -> [Affichage LISTE]\n\n");

        printf("1 - Affichage LISTE ordonnee par APPLICATION\n");
        printf("2 - Affichage LISTE ordonnee par IDENTIFIANT\n");
        printf("3 - Affichage LISTE ordonnee par MOT DE PASSE\n");
        printf("4 - Retour...\n\n");
        printf("Fait un choix :\n   > ");
        fgets(Input,10,stdin);
        nbrBetween(Input,1,4);

        switch (strNbr(Input))
        {
        case 1:
            system("cls");

            DisplayOrdonnedListe(fichier,1);
            
            while(Input[0] != '\n'){
                printf("PUSH ENTER > ");
                fgets(Input,3,stdin);
            }
        break;

        case 2:
            system("cls");

            DisplayOrdonnedListe(fichier,2);
            
            while(Input[0] != '\n'){
                printf("PUSH ENTER > ");
                fgets(Input,3,stdin);
            }
        break;

        case 3:
            system("cls");

            DisplayOrdonnedListe(fichier,3);
            
            while(Input[0] != '\n'){
                printf("PUSH ENTER > ");
                fgets(Input,3,stdin);
            }
            
        break;

        case 4:
            free(Input);
          return;  
        break;

        }  
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void AjoutCompte(FILE *fichier){
    String Input = (String)calloc(100,sizeof(char));
    String FinaleLigne = (String)calloc(500,sizeof(char));
    int BoolFound = 0;

    String* ListeApp = (String*)calloc(500,sizeof(String));
        ListeApp = getListeColonne(fichier,1);
    String* ListeId = (String*)calloc(500,sizeof(String));
        ListeId = getListeColonne(fichier,2);

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.1 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Ajout]\n\n");

    printf("Le nom de l'application concernee :\n   > ");
    fgets(Input,500,stdin);
    removeEnter(Input);
    for(int i=0;i<getNbElementListe(ListeApp);i++){
        if(strcmp(ListeApp[i],Input) == 0){
            BoolFound = 1;
        }
    }
    strcat(FinaleLigne,Input);
    strcat(FinaleLigne,"|");

    printf("\n");
    printf("Le nom de l'identifiant concernee :\n   > ");
    fgets(Input,500,stdin);
    removeEnter(Input);
    for(int i=0;i<getNbElementListe(ListeId);i++){
        if(BoolFound == 1 && strcmp(ListeId[i],Input) == 0){
            printf("\n      # Erreur...\n      # Un compte avec cette identifiant existe deja dans cette application...\n\n\n");
            free(Input);
            free(FinaleLigne);
            free(ListeApp);
            free(ListeId);
            pause();
            return;
        }
    }
    strcat(FinaleLigne,Input);
    strcat(FinaleLigne,"|");

    printf("\n");
    printf("Le mot de passe du compte concernee (\"Auto\" pour generer un mot de passe TRES fort):\n   > ");
    fgets(Input,500,stdin);
    removeEnter(Input);
    if(strcmp(Input,"Auto") == 0){  
        strcpy(Input,generatPassword(1,1,1,50));
    }
    strcat(FinaleLigne,Input);
    strcat(FinaleLigne,"|");
    addLigneAutoIndexSpecificString(fichier,FinaleLigne);

    printf("\n\nCompte ajouter avec succes !\n");
    free(Input);
    free(FinaleLigne);
    free(ListeApp);
    free(ListeId);
    pause();
    return;
}

void SuppressionCompte(FILE *fichier){
    String Input = (String)calloc(100,sizeof(char));

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.1 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Supprimer]\n\n");

    printf("Tableau de tout les compte reliee a la base de donnee :\n\n");
    DisplayTable(fichier);

    printf("\n");

    printf("Choisir un index a supprimer (0 pour retour) : \n     > ");
    fgets(Input,500,stdin);
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
    String NewLigne = (String)calloc(500,sizeof(char));

    String* ListeApp = (String*)calloc(500,sizeof(String));
        ListeApp = getListeColonne(fichier,1);
    String* ListeId = (String*)calloc(500,sizeof(String));
        ListeId = getListeColonne(fichier,2);

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.1 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Modifiee]\n\n");

    printf("Tableau de tout les compte reliee a la base de donnee :\n\n");
    DisplayTable(fichier);

    printf("\n");

    printf("Choisir un index a modifier : \n     > ");
    fgets(Input,500,stdin);
    nbrBetween(Input,0,getNbLigne(fichier)-1);
    int choixLigne = strNbr(Input);

    system("cls");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.1 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf("[PasswordManager] -> [Ajouter/Supprimer/Modifier...] -> [Modifiee]\n\n");

    printf("Ligne selectionnee :\n");
    printf("    Application  : %s\n",getLigneXcolonneY(fichier,choixLigne,1));
    printf("    Identifiant  : %s\n",getLigneXcolonneY(fichier,choixLigne,2));
    printf("    Mot de passe : %s\n\n",getLigneXcolonneY(fichier,choixLigne,3));

    printf("1 - Modifier l'application\n");
    printf("2 - Modifier l'identifiant\n");
    printf("3 - Modifier de mot de passe\n");
    printf("4 - Retour...\n\n");
    printf("Fait un choix :\n   > ");
    fgets(Input,10,stdin);
    nbrBetween(Input,1,4);

    switch (strNbr(Input)){
        case 1:
            printf("\nEntree la nouvelle application :\n  > ");
            fgets(Input,500,stdin);
            removeEnter(Input);

            for(int i=0;i<getNbElementListe(ListeApp);i++){
                if(strcmp(Input,ListeApp[i]) == 0){
                    if(strcmp(getLigneXcolonneY(fichier,choixLigne,2),getLigneXcolonneY(fichier,i,2)) == 0){
                        free(Input);
                        free(NewLigne);
                        free(ListeApp);
                        free(ListeId);
                        printf("\n      # Erreur...\n      # Un compte dans cette application existe deja avec cette identifiant...\n\n\n");
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

            printf("\nChangement effectuee !\n\n");
            free(Input);
            free(NewLigne);
            free(ListeApp);
            free(ListeId);
            pause();  
        break;

        case 2:
            printf("\nEntree le nouvelle identifiant :\n  > ");
            fgets(Input,500,stdin);
            removeEnter(Input);

            for(int i=0;i<getNbElementListe(ListeId);i++){
                if(strcmp(Input,ListeId[i]) == 0){
                    if(strcmp(getLigneXcolonneY(fichier,choixLigne,1),getLigneXcolonneY(fichier,i,1)) == 0){
                        free(Input);
                        free(NewLigne);
                        free(ListeApp);
                        free(ListeId);
                        printf("\n      # Erreur...\n      # Un identifiant identique existe deja dans cette application...\n\n\n");
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

            printf("Changement effectuee !\n\n");
            free(Input);
            free(NewLigne);
            free(ListeApp);
            free(ListeId);
            pause();  
        break;

        case 3:
            printf("\nEntree le nouveau mot de passe (\"Auto\" pour acceder au choix de generation):\n  > ");
            fgets(Input,500,stdin);
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

            modifieOneLigne(fichier,choixLigne,NewLigne);
            free(NewLigne);
        break;

        case 4:
            return;
        break;
        
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////

