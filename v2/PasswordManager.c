#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataExplorer.h"
#include "Tools.h"

void PasswordManager(FILE *fichier);
    void ConsultationMDP(FILE *fichier);
        void AffichageTableau(FILE *fichier);
        void AffichageListe(FILE *fichier);
    void EditDataBase(FILE *fichier);
        void AjoutCompte(FILE *fichier);
        void SuppressionCompte(FILE *fichier);
        void ModificationCompte(FILE *fichier);

void PlusInformation(FILE *fichier);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Page principale :
 * 
 * Password Manager -> Ligne 62
 * Plus d'information -> Ligne 99
*/

int main(){
    FILE *fichier = fopen("DATA.txt" , "r+");
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
            PlusInformation(fichier);
        break;

        case 3:
            return 0;
        break;
        }
    }
    
    printf("\n -=-=- END -=-=-\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Page de l'application :
 * 
 * ConsultationMDP -> Ligne 114
 * EditDataBase -> Ligne 163
*/

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

void PlusInformation(FILE *fichier){
    system("cls");

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= PasswordManager V.1 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    printf("[Plus d'information]\n\n");

    printf("Createur : Gregoire GIBRAT (BetaTetras)\n");
    printf("Version  : V2.0\n");
    printf("Source code : ...\n\n");

    printf("Presentation du projet :\n");
    printf("PasswordManager repond a un probleme que j'ai moi meme\n");
    printf("rencontree : le stockage et la recherche de mot de passe !\n");
    printf("En effet c'est peu pratique de devoir chercher dans la\n");
    printf("liste interminable de mot de passe qu'on mes en place ...\n");
    printf("Et c'est a ce moment la que PasswordManager prends le relais !\n");
    printf("Grace a lui vous pouvez ordonnee vos mots de passe et \n");
    printf("recuperer vos mots de passe en un instant grace a l'affichage\n");
    printf("en mode tableau ou en mode liste ou tout simplement en \n");
    printf("fesans une recherche simple !\n\n\n");

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

/*
 * Page d'affichage  :
 * 
 * AffichageTableau -> Ligne 208
 * AffichageListe -> Ligne 267
*/

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
    int BoolError = 0;

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

