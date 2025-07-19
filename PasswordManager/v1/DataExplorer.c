#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataExplorer.h"
#include "Tools.h"


// Création du type String 
typedef char* String;

/* =-=-=-=-=-= GETTEUR =-=-=-=-=-= */
// get du nombre de Colonne/Ligne
int getNbColonne(FILE *fichier);
int getNbLigne(FILE *fichier);

// get des VALEUR des différente colonne/Ligne
String getLigne(FILE *fichier,int x);
String getColonne(String Ligne,int x);
String getLigneXcolonneY(FILE *fichier,int X,int Y); // get d'une case spécifique 
String* getListeColonne(FILE *fichier,int x); // get d'une LISTE d'élément d'une colonne

/* =-=-=-=-=-= MODIFICATEUR =-=-=-=-=-= */
// Modificateur D'AJOUT d'information

void addLigne(FILE *fichier);
void addLigneAutoIndex(FILE *fichier);  // Modificateur standard (Indexation automatique) 
void addLigneAutoIndexSpecificString(FILE *fichier,String Input); // Modificateur utilise pour une fonction (non utilisable pas l'utilisateur de pref...)

// Modificateur de SUPPRESSION d'information
FILE* removeLigne(FILE *fichier); // Modificateur qui supprime la dernière ligne du fichier 
FILE* removeOneIndex(FILE *fichier,int x);   // Modificateur qui supprime un index choisi

FILE* modifieOneLigne(FILE *fichier,int x,String NewLine); // Modificateur qui modifie un index choisi

/* =-=-=-=-=-= REPONDEUR =-=-=-=-=-= */
int isAlreadyHere(FILE *fichier,int x,String Input); //Repond a la question si une certaine ligne est deja présente dans le fichier

/* =-=-=-=-=-= DISPLAY =-=-=-=-=-= */
void DisplaySpecifique(FILE *fichier,String Element);
void DisplayListe(FILE *fichier); // Affiche le fichier en format liste
void DisplayOrdonnedListe(FILE *fichier,int colonne);
void DisplayTable(FILE *fichier); // Affiche le fichier en format tableau 
void DisplayOrdonnedTable(FILE *fichier,int Colonne); // Affiche le fichier en fomrmat tableau avec possibilitée d'ordonnée par colonne 


/* =-=-=-=-=-= TOOLS =-=-=-=-=-= */
void goToEnd(FILE *fichier); // Deplace le cuseur du lecteur de fichier a la fin du fichier
void goTo(FILE *fichier,int x); // Deplace le curseur du lecteur de fichier a l'index x du fichier (x = ligne)


/////////////////////////////////////////////////////////////////////////////////
/*
 * Retourne le nombre de colonne (Grâce au pipe)
 * Fonctionne comme ca carre par exemple si la premier ligne est fomée comme ceci :
 * |3|Facebook|john.doe@gmail.com|F@ceb00k_88|
 * 
 * Le code vas comptée 5 pipe, sachant qu'il y'a une pipe en trop alors il me suffit de comptée le 
 * nombre de pipe et de soustraire 1 pour avoire le nombre de colonne
*/
int getNbColonne(FILE *fichier){
    rewind(fichier);    // Remets le cuseur au debut du fichier
    String Ligne = (String)calloc(500,sizeof(char));    // Ligne buffer
    fgets(Ligne,500,fichier);   // Récupère la premier ligne du fichier 
    int nbPipe = 0; // Variable compteur de pipe ("|")
    for(int i=0;i<strlen(Ligne);i++){   // de 0 aux nombre de caractère de la premier ligne du fichier faire ...
        if(Ligne[i] == '|'){    // Si le caractère numéro i est une pipe ("|") faire ...
            nbPipe ++;  // Incrémentation du nombre de pipi
        }
    }

    free(Ligne);    // Libére l'espace memoire de la ligne lue
    return nbPipe-1; // retourne le nombre de colonne
}

/*
 * Retourne le nombre de Ligne (Grâce a la fin du fichier)
 * Lis l'entièretais du fichier jusqu'a qu'il rencontre une ligne NULL (Donc la fin du fichier)
*/
int getNbLigne(FILE *fichier){
    rewind(fichier);    // Remets le cuseur au debut du fichier
    String Ligne = (String)calloc(500,sizeof(char)); // Ligne buffer

    int nbLigne = 0;    // Variable compteur de ligne

    while(fgets(Ligne,500,fichier) != NULL) // Tant que la ligne lue depuis le fichier n'est pas NULL faire ...
    {
        nbLigne ++; // Incrémentation du nombre de ligne
    }

    free(Ligne);    // Libére l'espace memoire de la ligne lue
    return nbLigne; // Retourne le nombre de Ligne
}

/*
 * Retourne la ligne avec l'index voulue (Commence a 0)
 * Récupère, avec un index voulue, une string qui correspond a la ligne voulue
 * 
 * Exemple :
 * Si j'appelle la fonction : getLine(fichier,2);
 *  -> |2|Instagram|john.doe@gmail.com|In$tagramLove7|
*/
String getLigne(FILE *fichier,int Index){
    rewind(fichier);    // Remets le cuseur au debut du fichier
    String Ligne = (String)calloc(500,sizeof(char));    // Ligne buffer

    for(int i=0;i<Index;i++){  // Tant que i est inférieure a l'Index
        fgets(Ligne,500,fichier);   // Lire une ligne "dans le vide"
    }

    return fgets(Ligne,500,fichier); // retourne la ligne voulue
}

/*
 * Retourne la colonne avec l'index voulue (Commence a 0)
 * Récupère, avec un index voulue, une string qui correspond a la colonne voulue DEPUIS UNE STRING
 * 
 * Exemple :
 * Si j'appelle la fonction : getColonne(fichier,2);
 *  -> ERREUR : on dois entrée UNE STRING
 * 
 * Si j'appelle la fonction : getColonne(getLigne(fichier,2),2);
 *  -> john.doe@gmail.com
 * 
 * Notée bien qu'il n'y a pas de \n
*/
String getColonne(String Ligne,int x){
    x ++;  // Incrémentation de 1 de x
    int indexX; // Création d'une varaible indexX utilise pour l'utilisation de strbcpy
    int indexY; // ''
    String LigneTampon = (String)calloc(500,sizeof(char));  // Création d'une ligne tampon pour pas modifier la ligne actuelle du fichier
    strcpy(LigneTampon,Ligne);  // Copie de la ligne actuelle vers la nouvelle ligne

    int Index;  // Création d'une variable d'index tampons

    // Ma methode d'extraction de donnée avec des caractère de séparation
    for(int i=0;i<x-1;i++){ 
        Index = strchr(LigneTampon,'|') - LigneTampon;
        LigneTampon[Index] = '#';
    }
    indexX = Index = strchr(LigneTampon,'|') - LigneTampon;
    strcpy(LigneTampon,Ligne);
    for(int i=0;i<x;i++){
        Index = strchr(LigneTampon,'|') - LigneTampon;
        LigneTampon[Index] = '#';
    }
    indexY = Index = strchr(LigneTampon,'|') - LigneTampon;

    free(LigneTampon);
    return strbcpy(Ligne,indexX,indexY);
}

/*
 * Retourne la case avec le numéro de la ligne et de la colonne (Commence a 0)
*/
String getLigneXcolonneY(FILE *fichier,int Ligne,int Colonne){
    return getColonne(getLigne(fichier,Ligne),Colonne);
}

/*
 * Retourne la liste des élément d'une colonne avec l'index voulue (Commence a 0)
*/
String* getListeColonne(FILE *fichier,int Colonne){
    rewind(fichier);
    int nbLigne = getNbLigne(fichier);

    String* ListeColonne = (String*)calloc(500,sizeof(String*));

    for(int i=0;i<nbLigne;i++){
        ListeColonne[i] = (String)calloc(500,sizeof(char));
        strcpy(ListeColonne[i],getLigneXcolonneY(fichier,i,Colonne));
    }

    return ListeColonne;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Ajoute une ligne a la fin du fichier en demandant a chaque colonne leur valeur
*/
void addLigne(FILE *fichier){
    rewind(fichier);    // Remets le cuseur au debut du fichier
    int nbEntry = getNbColonne(fichier);    // Définire le nombre d'entrée de l'utilisateur avec le nombre de colonne a remplire 
    String NewLigne = (String)calloc(500,sizeof(char)); // Buffer de la nouvelle ligne 
    String Buffer = (String)calloc(500,sizeof(char));   // Buffer

    strcat(NewLigne,"|");   // Ajout du caractère '|' au debut de la nouvelle ligne

    for(int i=0;i<nbEntry;i++){ // Pour le nombre d'entrée ...
        printf("Entree la valeur de la colonne %d :\n   > ",i+1);   // Demande a l'utilisateur d'ajouter une valeur a la colonne i
        fgets(Buffer,500,stdin);
        Buffer[strlen(Buffer)-1] = '\0';    // Suppresion du caractère d'entée "\n"
        strcat(NewLigne,Buffer);    // Concaténation de la valeur entrée avec la ligne deja existante 
        strcat(NewLigne,"|");
    }

    goToEnd(fichier);   // Aller la fin du fichier DATA
    fprintf(fichier,"%s",NewLigne); // Ajoutée la ligne crée dans le fichier
    fprintf(fichier,"\n"); // Ajout du saut de ligne pour la prochaine entrée
    free(Buffer);
    free(NewLigne);
}

/*
 * Ajoute une ligne à la fin du fichier avec une indexation automatique (doit suivre le format attendu).
 *
 * Exemple :
 * -> |4|LinkedIn|john.doe@gmail.com|L!nkedInJobs2025|
 *    "|4|[...]" est généré automatiquement par l'indexation.
 */
void addLigneAutoIndex(FILE *fichier){
    rewind(fichier);    

    String Ligne = (String)calloc(500,sizeof(char));
    String Buffer = (String)calloc(500,sizeof(char));
    String NewLigne = (String)calloc(500,sizeof(char));

    int nbEntry = getNbColonne(fichier);

    goToEnd(fichier);
    fprintf(fichier,"|%d|",getNbLigne(fichier)); // Indéxation automatique entre deux pipe

    for(int i=0;i<nbEntry-1;i++){ // Ajouter tout les valeur sauf pour l'index qui se mes automatiquement
        printf("Entree la valeur de la %d colonne :\n   > ",i+1);
        fgets(Buffer,500,stdin); // Entrée de la valeur
        removeEnter(Buffer); // suppression du caractére "\n"
        strcat(NewLigne,Buffer); // Ajout de l'entrée dans la future nouvelle ligne
        strcat(NewLigne,"|"); // Ajout d'une pipe
    }

    fprintf(fichier,NewLigne); // Ajout de la ligne a la fin du fichier
    fprintf(fichier,"\n"); // Ajout d'un caractére d'entrée pour la sécuritée 
    free(Ligne);
    free(Buffer);
    free(NewLigne);
}

/*
 * Ajoute une ligne specifique a la fin du fichier avec une indexation automatique

 * Ajoute a la fin du fichier séléctionnée une string prés entrée sans demandée a
 * l'utilisateur d'entrée des valeurs en respectant une idexation adéquat
 * 
 * Exemple :
 * addLigneAutoIndexSpecificString(fichier,"Test1|Test2|Test3|");
 * 
 * -> |x|Test1|Test2|Test3|\n
 * 
 * CETTE FONCTION CORRESPOND PLUS A UNE SOUS FONCTION
 * 
*/
void addLigneAutoIndexSpecificString(FILE *fichier, String Input){
    goToEnd(fichier);
    int ligne = getNbLigne(fichier);

    fprintf(fichier, "|%d|%s\n", ligne, Input);
    fflush(fichier); // Obligatoire idk pourquoi 
}


/*
 * Suppression de la dernière ligne du fichier
 * 
 * Etant donnée que pour supprimée des valeur dans un fichier il faut recrée un
 * fichier il faut donc recrée un pointeur vers le fichier, en effet due a
 * l'utilisation de fclose, le pointeur entrée en paramétre est supprimmer et 
 * il faut donc en recrée un nouveau
 * 
 * Exemple d'utilisation :
 * FILE *Temp = fopen("Temp.txt", "w+");
 * ...
 * fichier = removeLigne(fichier);
 * 
 * 
*/
FILE* removeLigne(FILE *fichier){
    FILE *Temp = fopen("Temp.txt", "w+");
    int nbLigne = getNbLigne(fichier);
    String Ligne = (String)calloc(500,sizeof(char));
    rewind(fichier);

    if(getNbLigne(fichier) <= 2){
        printf("\n      # Error...\n      # There is no ligne left little one\n\n");
        pause();
        return fopen("DATA.txt", "r+");;
    }

    rewind(fichier);
    for(int i=0;i<nbLigne-1;i++){
        fgets(Ligne,500,fichier);
        fprintf(Temp,"%s",Ligne);
    }
    fclose(Temp);
    fclose(fichier);
    remove("Data.txt");
    rename("Temp.txt","Data.txt");

    return fopen("DATA.txt", "r+");
}

/*
 * Suppression d'une ligne dans le fichier depuis un index
*/
FILE* removeOneIndex(FILE *fichier,int IndexLigne){
    FILE *Temp = fopen("Temp.txt", "w+");
    int nbLigne = getNbLigne(fichier);
    String Ligne = (String)calloc(500,sizeof(char));
    String BufferLigne = (String)calloc(500,sizeof(char));
    String NewLigne = (String)calloc(500,sizeof(char));

    rewind(fichier);
    for(int i=0;i<IndexLigne;i++){
        fgets(Ligne,500,fichier);
        fprintf(Temp,"%s",Ligne);
    }
    fgets(Ligne,500,fichier);
    
    int Index;
    for(int i=0;i<nbLigne-IndexLigne-1;i++){
        fgets(Ligne,500,fichier);
        strcpy(BufferLigne,Ligne);
        Index = strchr(BufferLigne,'|') - BufferLigne;
        BufferLigne[Index] = '#';

        addLigneAutoIndexSpecificString(Temp,strbcpy(BufferLigne,Index+3,strlen(BufferLigne)));
    }

    fichier = removeLigne(fichier);

    free(Ligne);
    free(BufferLigne);
    fclose(fichier);
    fclose(Temp);
    remove("DATA.txt");
    rename("Temp.txt","DATA.txt");

    return fopen("DATA.txt", "r+");
}

FILE* modifieOneLigne(FILE *fichier,int IndexLigne,String NewLine){
    FILE *Temp = fopen("Temp.txt", "w+");
    int nbLigne = getNbLigne(fichier);
    String Ligne = (String)calloc(500,sizeof(char));
    String BufferLigne = (String)calloc(500,sizeof(char));

    rewind(fichier);
    for(int i=0;i<IndexLigne;i++){
        fgets(Ligne,500,fichier);
        fprintf(Temp,"%s",Ligne);
    }
    fgets(Ligne,500,fichier);

    addLigneAutoIndexSpecificString(Temp,NewLine);

    int Index;
    for(int i=0;i<nbLigne-IndexLigne-1;i++){
        fgets(Ligne,500,fichier);
        removeEnter(Ligne);

        strcpy(BufferLigne,Ligne);
        Index = strchr(BufferLigne,'|') - BufferLigne;
        BufferLigne[Index] = '#';

        addLigneAutoIndexSpecificString(Temp,strbcpy(BufferLigne,Index+3,strlen(BufferLigne)));
    }

    free(Ligne);
    free(BufferLigne);
    fclose(fichier);
    fclose(Temp);
    remove("DATA.txt");
    rename("Temp.txt","DATA.txt");

    return fopen("DATA.txt", "r+");
}

int isAlreadyHere(FILE *fichier,int x,String Input){
    String* Liste = (String*)calloc(500,sizeof(char));

    if(Input[strlen(Input)-1] == '\n'){
        Input[strlen(Input)-1] = '\0';
    }
    Liste = getListeColonne(fichier,x);
    for(int i=0;i<getNbLigne(fichier);i++){
        if(strcmp(Input,Liste[i]) == 0 ){
            return 1;
        }
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////

void DisplaySpecifique(FILE *fichier,String Element){
    String Input = (String)calloc(100,sizeof(char));

    String* ListeApplication = (String*)calloc(500,sizeof(char));
    ListeApplication = getListeColonne(fichier,1);

    int BoolTrouvee = 0;

    printf("\nEntrer le nom de l'application :\n    > ");
    fgets(Input,500,stdin);
    removeEnter(Input);

    for(int i=0;i<getNbLigne(fichier);i++){
        if(strcmp(Input,ListeApplication[i]) == 0){
            BoolTrouvee = 1;
        }
    }

    if(BoolTrouvee == 1){
        printf("\nCompte pour l'application %s :\n",Input);
        for(int i=0;i<getNbLigne(fichier);i++){
            if(strcmp(Input,ListeApplication[i]) == 0){
                printf("    Identifiant : %s\n",getLigneXcolonneY(fichier,i,2));
                printf("    Mot de passe : %s\n\n",getLigneXcolonneY(fichier,i,3));
            }
        }
    }else{
        printf("Pas d'application '%s' trouvee ...\n",Input);
    }   
}

void DisplayTable(FILE *fichier){
    int NbColonne = getNbColonne(fichier);
    int* TabCarMax = (int*)calloc(NbColonne,sizeof(int));

    // Récupère le nombre max de car de chaque colonne
    int Buffer;
    for(int i=0;i<NbColonne;i++){
        for(int j=0;j<getNbLigne(fichier);j++){
            Buffer = strlen(getLigneXcolonneY(fichier,j,i));
            if(Buffer>TabCarMax[i]){
                TabCarMax[i] = Buffer;
            }
        }
    }

    // Cas ou la longeur max d'une ligne ne dépasse pas la longeur de la premier ligne
    for(int i=0;i<NbColonne;i++){
        if(TabCarMax[i] < strlen(getLigneXcolonneY(fichier,0,i))){
            TabCarMax[i] = strlen(getLigneXcolonneY(fichier,0,i));
        }
    }
    
    // Affiche la premier ligne
    int NbEspace;
    for(int i=0;i<NbColonne;i++){
        printf("|  ");
        printf("%s ",getLigneXcolonneY(fichier,0,i));

        NbEspace = TabCarMax[i] - strlen(getLigneXcolonneY(fichier,0,i));
        for(int j=0;j<NbEspace;j++){
            printf(" ");
        }
    }
    printf("|\n");

    // Calculer le nombre de caractère totale du tableau
    int NbCarTot = 0;
    for(int i=0;i<NbColonne;i++){
        NbCarTot += TabCarMax[i];
    }
    NbCarTot += (4*NbColonne) + 1;

    for(int i=0;i<NbCarTot;i++){
        printf("-");
    }
    printf("\n");

    // Affiche tout les lignes
    for(int i=1;i<getNbLigne(fichier);i++){
        for(int j=0;j<NbColonne;j++){
            printf("|  ");
            printf("%s ",getLigneXcolonneY(fichier,i,j));

            NbEspace = (TabCarMax[j] - strlen(getLigneXcolonneY(fichier,i,j)));
            for(int k=0;k<NbEspace;k++){
                printf(" ");
            }
        }
        printf("|\n");
    }
    
    // Affiche la barre de fin
    for(int i=0;i<NbCarTot;i++){
        printf("-");
    }
    printf("\n");
}

void DisplayOrdonnedTable(FILE *fichier,int Colonne){
    int NbColonne = getNbColonne(fichier);
    int* TabCarMax = (int*)calloc(NbColonne,sizeof(int));

    // Récupère le nombre max de car de chaque colonne
    int Buffer;
    for(int i=0;i<NbColonne;i++){
        for(int j=0;j<getNbLigne(fichier);j++){
            Buffer = strlen(getLigneXcolonneY(fichier,j,i));
            if(Buffer>TabCarMax[i]){
                TabCarMax[i] = Buffer;
            }
        }
    }

    // Cas ou la longeur max d'une ligne ne dépasse pas la longeur de la premier ligne
    for(int i=0;i<NbColonne;i++){
        if(TabCarMax[i] < strlen(getLigneXcolonneY(fichier,0,i))){
            TabCarMax[i] = strlen(getLigneXcolonneY(fichier,0,i));
        }
    }
    
    // Affiche la premier ligne
    int NbEspace;
    for(int i=0;i<NbColonne;i++){
        printf("|  ");
        printf("%s ",getLigneXcolonneY(fichier,0,i));

        NbEspace = TabCarMax[i] - strlen(getLigneXcolonneY(fichier,0,i));
        for(int j=0;j<NbEspace;j++){
            printf(" ");
        }
    }
    printf("|\n");

    // Calculer le nombre de caractère totale du tableau
    int NbCarTot = 0;
    for(int i=0;i<NbColonne;i++){
        NbCarTot += TabCarMax[i];
    }
    NbCarTot += (4*NbColonne) + 1;

    for(int i=0;i<NbCarTot;i++){
        printf("-");
    }
    printf("\n");

    // Affiche tout les lignes
    String* DejaAfficher = (String*)calloc(500,sizeof(String));
    String StringBuffer = (String)calloc(500,sizeof(char));

    int BoolFound = 0;
    for(int i=1;i<getNbLigne(fichier);i++){
        BoolFound = 0;
        StringBuffer = getLigneXcolonneY(fichier,i,Colonne);

        for(int i=0;i<getNbElementListe(DejaAfficher);i++){
            if(strcmp(DejaAfficher[i],StringBuffer) == 0){
                BoolFound = 1;
                break;
            }
        }

        if(BoolFound == 1){
            continue;
        }
       
        addInListe(DejaAfficher,StringBuffer);
        
        for(int i=1;i<getNbLigne(fichier);i++){
            if(strcmp(StringBuffer,getLigneXcolonneY(fichier,i,Colonne)) == 0){
                for(int j=0;j<NbColonne;j++){
                printf("|  ");
                printf("%s ",getLigneXcolonneY(fichier,i,j));

                NbEspace = (TabCarMax[j] - strlen(getLigneXcolonneY(fichier,i,j)));
                    for(int k=0;k<NbEspace;k++){
                        printf(" ");
                    }
                }
            printf("|\n");
            }
        }
        
    }

    // Affiche la barre de fin
    for(int i=0;i<NbCarTot;i++){
        printf("-");
    }
    printf("\n");

}

void DisplayListe(FILE *fichier){

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    for(int i=1;i<getNbLigne(fichier);i++){

        printf("Application : %s\n",getLigneXcolonneY(fichier,i,1));
        printf("Identifiant : %s\n",getLigneXcolonneY(fichier,i,2));
        printf("Mot de passe : %s\n",getLigneXcolonneY(fichier,i,3));
        printf("\n");
    }
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void DisplayOrdonnedListe(FILE *fichier,int colonne){
    String* ListeDejaAfficher = (String*)calloc(500,sizeof(String));
    String Buffer = (String)calloc(500,sizeof(char));

    int BoolFound = 0;
    for(int i=1;i<getNbLigne(fichier);i++){
        strcpy(Buffer, getLigneXcolonneY(fichier, i, colonne));
        BoolFound = 0;

        for(int j=0;j<getNbElementListe(ListeDejaAfficher);j++){
            if(strcmp(Buffer,ListeDejaAfficher[j]) == 0){
                BoolFound = 1;
            }
        }

        if(BoolFound == 0){
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
            printf("%s : %s\n",getLigneXcolonneY(fichier,0,colonne),Buffer);
            for(int j=1;j<getNbLigne(fichier);j++){
                if(strcmp(Buffer,getLigneXcolonneY(fichier,j,colonne)) == 0){
                    for(int k=1;k<getNbColonne(fichier);k++){
                        if(strcmp(getLigneXcolonneY(fichier,0,colonne),getLigneXcolonneY(fichier,0,k)) != 0){
                            printf("    %s : %s\n",getLigneXcolonneY(fichier,0,k),getLigneXcolonneY(fichier,j,k));
                        }
                    }
                    printf("\n");
                }
            }
        }
        addInListe(ListeDejaAfficher,Buffer);
    }

}

/////////////////////////////////////////////////////////////////////////////////

void goToEnd(FILE *fichier){
    // rewind(fichier);
    // String Buffer = (String)calloc(500,sizeof(char));
    // while(fgets(Buffer,500,fichier) != NULL){
    // }

    // free(Buffer);
    fseek(fichier, 0, SEEK_END);
}

void goTo(FILE *fichier,int x){
    rewind(fichier);
    String Buffer = (String)calloc(500,sizeof(char));
    if(x>getNbLigne(fichier)){
        printf("\n      # Error...\n      # You can't go too far little one\n\n");
        return;
    }
    rewind(fichier);
    for(int i=0;i<x;i++){
        fgets(Buffer,500,fichier);
    }
}
/////////////////////////////////////////////////////////////////////////////////