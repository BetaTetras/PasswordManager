#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "DataExplorer.h"
#include "Tools.h"


// Création du type String 
typedef char* String;

/* =-=-=-=-=-= GETTEUR =-=-=-=-=-= */
// get du nombre de Colonne/Ligne
int getNbColonne(String DATA);
int getNbLigne(String DATA);

// get des VALEUR des différente colonne/Ligne
String getLigne(String DATA,int x);
String getColonne(String Ligne,int x);
String getLigneXcolonneY(String DATA,int X,int Y); // get d'une case spécifique 
String* getListeColonne(String DATA,int x); // get d'une LISTE d'élément d'une colonne

/* =-=-=-=-=-= MODIFICATEUR =-=-=-=-=-= */
// Modificateur D'AJOUT d'information
String addLigne(String DATA);
String addLigneV2(String DATA,int NbArg,...);
String addLigneAutoIndex(String DATA,int NbArg,...);  // Modificateur standard (Indexation automatique) 
String addLigneAutoIndexSpecificString(String DATA,String Input); // Modificateur utilise pour une fonction (non utilisable pas l'utilisateur de pref...)

// Modificateur de SUPPRESSION d'information
String removeLigne(String DATA); // Modificateur qui supprime la dernière ligne du DATA 
String removeOneIndex(String DATA,int Index);   // Modificateur qui supprime un index choisi

// Modificateur de MODIFICATION d'information
String modifieOneLigne(String DATA,int IndexLigne,String NewLine); // Modificateur qui modifie un index choisi

/* =-=-=-=-=-= DISPLAY =-=-=-=-=-= */
// Affiche une valeur choisi
void DisplaySpecifiqueListe(String DATA,String Element,int Colonne);
void DisplaySpecifiqueTable(String DATA,String Element,int Colonne);

// Affiche l'entièreté du fichier en format TABLEAU
void DisplayTable(String DATA);
void DisplayOrdonnedTable(String DATA,int Colonne);

// Affiche l'entièreté du fichier en format LISTE
void DisplayListe(String DATA); // Affiche le fichier en format liste
void DisplayOrdonnedListe(String DATA,int colonne);
/////////////////////////////////////////////////////////////////////////////////
                    /* =-=-=-=-=-= GETTEUR =-=-=-=-=-= */
/*
 * Retourne le nombre de colonne (Grâce au pipe)
 * Fonctionne comme ca carre par exemple si la premier ligne est fomée comme ceci :
 * |3|Facebook|john.doe@gmail.com|F@ceb00k_88|
 * 
 * Le code vas comptée 5 pipe, sachant qu'il y'a une pipe en trop alors il me suffit de comptée le 
 * nombre de pipe et de soustraire 1 pour avoire le nombre de colonne
*/
int getNbColonne(String DATA){
    int nbColonne = 0;
    for(int i=0;DATA[i] != '\n';i++){
        if(DATA[i] == '|'){
            nbColonne ++;
        }
    }
    return nbColonne-1;
}

/*
 * Retourne le nombre de Ligne (Grâce a la fin du DATA)
 * Lis l'entièretais du DATA jusqu'a qu'il rencontre une ligne NULL (Donc la fin du DATA)
*/
int getNbLigne(String DATA){
    int nbLigne = 0;
    for(int i=0;i<(int)strlen(DATA);i++){
        if(DATA[i] == '\n'){
            nbLigne++;
        }
    }
    return nbLigne;
}

/*
 * Retourne la ligne avec l'index voulue (Commence a 0)
 * Récupère, avec un index voulue, une string qui correspond a la ligne voulue
 * 
 * Exemple :
 * Si j'appelle la fonction : getLine(DATA,2);
 *  -> |2|Instagram|john.doe@gmail.com|In$tagramLove7|
*/
String getLigne(String DATA,int Index){
    if(Index > getNbLigne(DATA)){
        printf_RGB(255,0,0,"# Erreur ...\n# Index > NbLigne!\n");
        return NULL;
    }

    String Buffer = (String)calloc(strlen(DATA)+1,sizeof(char));
    strcpy(Buffer,DATA);

    int IndexStart = 0;
    int IndexEnd = 0;

    if(Index == 0){
        IndexStart = 0;
    }else{
        for(int i=0;i<Index-1;i++){
            IndexStart = _strchr(Buffer,'\n');
            Buffer[IndexStart] = '#';
        }
        IndexStart = _strchr(Buffer,'\n');
        Buffer[IndexStart] = '#';
    }
    IndexEnd = _strchr(Buffer,'\n');
    if(Index != 0){
        return strbcpy(DATA,IndexStart+1,IndexEnd); // +1 pour pas avoir le \n
    }else{
        return strbcpy(DATA,IndexStart,IndexEnd); // Pas le +1 par ce que ....Y'a pas de \n
    }
    
}

/*
 * Retourne la colonne avec l'index voulue (Commence a 0)
 * Récupère, avec un index voulue, une string qui correspond a la colonne voulue DEPUIS UNE STRING
 * 
 * Exemple :
 * Si j'appelle la fonction : getColonne(DATA,2);
 *  -> ERREUR : on dois entrée UNE STRING
 * 
 * Si j'appelle la fonction : getColonne(getLigne(DATA,2),2);
 *  -> john.doe@gmail.com
 * 
 * Notée bien qu'il n'y a pas de \n
*/
String getColonne(String Ligne,int Colonne){
    Colonne ++;  // Incrémentation de 1 de x
    int indexX; // Création d'une varaible indexX utilise pour l'utilisation de 
    int indexY; // ''
    String LigneTampon = (String)calloc(500,sizeof(char));  // Création d'une ligne tampon pour pas modifier la ligne actuelle du DATA
    strcpy(LigneTampon,Ligne);  // Copie de la ligne actuelle vers la nouvelle ligne

    int Index;  // Création d'une variable d'index tampons

    // Ma methode d'extraction de donnée avec des caractère de séparation
    for(int i=0;i<Colonne-1;i++){ 
        Index = strchr(LigneTampon,'|') - LigneTampon;
        LigneTampon[Index] = '#';
    }
    indexX = Index = strchr(LigneTampon,'|') - LigneTampon;
    strcpy(LigneTampon,Ligne);
    for(int i=0;i<Colonne;i++){
        Index = strchr(LigneTampon,'|') - LigneTampon;
        LigneTampon[Index] = '#';
    }
    indexY = Index = strchr(LigneTampon,'|') - LigneTampon;

    free(LigneTampon);
    return strbcpy(Ligne,indexX+1,indexY); // "+1" pour exclusion de la première pipe
}

/*
 * Retourne la case avec le numéro de la ligne et de la colonne (Commence a 0)
*/
String getLigneXcolonneY(String DATA,int Ligne,int Colonne){
    return getColonne(getLigne(DATA,Ligne),Colonne);
}

/*
 * Retourne la liste des élément d'une colonne avec l'index voulue (Commence a 0)
*/
String* getListeColonne(String DATA,int Colonne){
    int nbLigne = getNbLigne(DATA);

    String* ListeColonne = (String*)calloc(nbLigne+1,sizeof(String));

    for(int i=0;i<nbLigne;i++){
        ListeColonne[i] = (String)calloc(500,sizeof(char));
        strcpy(ListeColonne[i],getLigneXcolonneY(DATA,i,Colonne));
    }

    ListeColonne[nbLigne] = NULL;

    return ListeColonne;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            /* =-=-=-=-=-= MODIFICATEUR =-=-=-=-=-= */

/*
 * Ajoute une ligne a la fin du DATA en demandant a chaque colonne leur valeur
*/
String addLigne(String DATA){
    int nbEntry = getNbColonne(DATA);    // Définire le nombre d'entrée de l'utilisateur avec le nombre de colonne a remplire 
    String NewLigne = (String)calloc(1000,sizeof(char)); // Buffer de la nouvelle ligne 
    String Buffer = (String)calloc(1000,sizeof(char));   // Buffer

    strcat(NewLigne,"|");   // Ajout du caractère '|' au debut de la nouvelle ligne

    for(int i=0;i<nbEntry;i++){ // Pour le nombre d'entrée ...
        printf("Entree la valeur de la colonne %d :\n   > ",i+1);   // Demande a l'utilisateur d'ajouter une valeur a la colonne i
        fgets(Buffer,1000,stdin);
        Buffer[strlen(Buffer)-1] = '\0';    // Suppresion du caractère d'entée "\n"
        strcat(NewLigne,Buffer);    // Concaténation de la valeur entrée avec la ligne deja existante 
        strcat(NewLigne,"|");
    }

    DATA = realloc(DATA, strlen(DATA) + strlen(NewLigne) + 1);

    strcat(DATA,NewLigne);
    return DATA;
}

/*
 * Ajoute une ligne a la fin du DATA en demandant a chaque colonne leur valeur
 *
 * Version supplémentaire avec ARGS ...
*/
String addLigneV2(String DATA,int NbArg,...){
    va_list ARGS;
    va_start(ARGS,NbArg);

    String NewArg;
    String Buffer = (String)calloc(1,sizeof(char));
    Buffer[0] = '|';

    for(int i=0;i<NbArg;i++){
        NewArg = va_arg(ARGS,String);

        Buffer = realloc(Buffer,strlen(Buffer) + strlen(NewArg) + 2);
        strcat(Buffer,NewArg);
        strcat(Buffer,"|");
    }
    strcat(Buffer,"\n");

    DATA = realloc(DATA,strlen(DATA) + strlen(Buffer));
    strcat(DATA,Buffer);

    va_end(ARGS);
    free(Buffer);
    return DATA;
}


/*
 * Ajoute une ligne à la fin du DATA avec une indexation automatique (doit suivre le format attendu).
 *
 * Exemple :
 * -> |4|LinkedIn|john.doe@gmail.com|L!nkedInJobs2025|
 *    "|4|[...]" est généré automatiquement par l'indexation.
 */
String addLigneAutoIndex(String DATA,int NbArg,...){
    va_list ARGS;
    va_start(ARGS,NbArg);

    String NewArg;
    String Buffer = (String)calloc(10,sizeof(char));
    Buffer[0] = '|';
    Buffer[1] = '\0';

    String indexSTR = intToString(getNbLigne(DATA));
    strcat(Buffer,indexSTR);
    strcat(Buffer,"|");

    for(int i=0;i<NbArg;i++){
        NewArg = va_arg(ARGS,String);

        Buffer = realloc(Buffer,strlen(Buffer) + strlen(NewArg) + 3);
        strcat(Buffer,NewArg);
        strcat(Buffer,"|");
    }
    strcat(Buffer,"\n");

    DATA = realloc(DATA,strlen(DATA) + strlen(Buffer) +1);
    strcat(DATA,Buffer);

    va_end(ARGS);
    free(Buffer);
    return DATA;
}

/*
 * Ajoute une ligne specifique a la fin du DATA avec une indexation automatique

 * Ajoute a la fin du DATA séléctionnée une string prés entrée sans demandée a
 * l'utilisateur d'entrée des valeurs en respectant une idexation adéquat
 * 
 * Exemple :
 * addLigneAutoIndexSpecificString(DATA,"Test1|Test2|Test3|");
 * 
 * -> |x|Test1|Test2|Test3|\n
 * 
 * CETTE FONCTION CORRESPOND PLUS A UNE SOUS FONCTION
 * 
*/
String addLigneAutoIndexSpecificString(String DATA, String Input){
    size_t sizeNewLine = nbDigit(getNbLigne(DATA)) + (strlen(Input)) + 5 + 1;

    DATA = realloc(DATA,(strlen(DATA)+1) + sizeNewLine);

    strcat(DATA,"|");
    strcat(DATA,intToString(getNbLigne(DATA)));
    strcat(DATA,"|");
    strcat(DATA,Input);
    strcat(DATA,"\n");

    return DATA;
}

String addLigneAutoIndexSpecificStringV2(String DATA,int NbArg,...){
    if(NbArg != 3){
        printf_RGB(255,0,0,"# Erreur...\n# Cette fonction require exactement 3 argument ici\n");
        return "Loser";
    }
    va_list ARGS;
    va_start(ARGS,NbArg);

    String* listeArgs = (String*)calloc(NbArg,sizeof(String));
    size_t sizeArgs = 0;

    String Arg;
    for(int i=0;i<NbArg;i++){
        Arg = va_arg(ARGS,String);
        listeArgs[i] = calloc(strlen(Arg)+1,sizeof(char));
        strcpy(listeArgs[i],Arg);
        sizeArgs += strlen(listeArgs[i]);
    }

    // sizeArgs = Taille des arguments; 5 = '|'; nbDigit = Index; 1 = '\n' ; 1 = '\0'
    String NewLine = (String)calloc(sizeArgs + 5 + nbDigit(getNbLigne(DATA)) + 1 + 1,sizeof(char));
    NewLine[0] = '\0';
    strcat(NewLine,"|");
    strcat(NewLine,intToString(getNbLigne(DATA)));
    strcat(NewLine,"|");

    for(int i=0;i<NbArg;i++){
        strcat(NewLine,listeArgs[i]);
        strcat(NewLine,"|");
    }
    strcat(NewLine,"\n");

    // strlen(DATA) = Taille de base;strlen(NewLine) = La taille de la nouvelle ligne
    // 1 = '\n'; 1 = '\0';
    DATA = realloc(DATA,strlen(DATA) + strlen(NewLine) + 1 + 1);

    strcat(DATA,NewLine);

    
    free(listeArgs);
    free(NewLine);
    return DATA;
}


/*
 * Suppression de la dernière ligne du DATA
 * 
 * Etant donnee son fonctionnement (fermeture du DATA pour suprimmer puis renomme un même DATA)
 * il faut IMPERTIVEMENT repointer le nom du pointeur qui pointer vers l'ancien DATA 
 * 
 * Exemple d'utilisation :
 * FILE *Temp = fopen("Temp.txt", "w+");
 * ...
 * DATA = removeLigne(DATA);
 * 
*/
String removeLigne(String DATA){
    int NbLigne = getNbLigne(DATA);

    int IndexEnd = 0;
    int i = 0;

    while(i< NbLigne -1){
        if(DATA[IndexEnd] == '\n'){
            i++;
        }
        IndexEnd ++ ;
    }

    return strbcpy(DATA,0,IndexEnd);
}

/*
 * Suppression d'une ligne dans le DATA depuis un index
 *
 * Etant donnee son fonctionnement (fermeture du DATA pour suprimmer puis renomme un même DATA)
 * il faut IMPERTIVEMENT repointer le nom du pointeur qui pointer vers l'ancien DATA 
 * 
 * Exemple d'utilisation :
 * FILE *Temp = fopen("Temp.txt", "w+");
 * ...
 * DATA = removeOneIndex(DATA,10);
 * 
*/
String removeOneIndex(String DATA,int IndexLigne){
    String cpyDATA = malloc(strlen(DATA) + 1);

    cpyDATA[0] = '\0';

    for(int i=0;i<IndexLigne;i++){
        strcat(cpyDATA,getLigne(DATA,i));
        strcat(cpyDATA,"\n");
    }

    String Buffer;
    int IndexStart;
    int IndexEnd;
    for(int i = IndexLigne+1;i<getNbLigne(DATA);i++){
        Buffer = getLigne(DATA,i);
        Buffer[0] = '#';
        IndexStart = _strchr(Buffer,'|');
        Buffer[IndexStart] = '#';
        IndexEnd = strlen(Buffer);
        
        cpyDATA = addLigneAutoIndexSpecificString(cpyDATA,strbcpy(Buffer,IndexStart+1,IndexEnd));
    }

    DATA = realloc(DATA,strlen(cpyDATA) +1);
    strcpy(DATA, cpyDATA);

    free(cpyDATA);
    return DATA;
}

/*
 * Modifie une ligne choisi en entrée par une string prés entrée
 * 
 * Exemple d'utilisation :
 * FILE *Temp = fopen("Temp.txt", "w+");
 * ...
 * DATA = modifieOneLigne(DATA,10,"johnny.d@netflix.com|N3tfl!x&Chil1|");
 * 
*/
String modifieOneLigne(String DATA,int IndexLigne,String NewLine){
size_t taille_cpy = strlen(NewLine) + 1; // +1 pour '\n'
    for(int i=0; i<getNbLigne(DATA); i++){
        if(i != IndexLigne){
            taille_cpy += strlen(getLigne(DATA,i)) + 1; // +1 pour '\n'
        }
    }
    String cpyDATA = malloc(taille_cpy + 1); // +1 pour '\0'
    cpyDATA[0] = '\0';


    for(int i=0;i<IndexLigne;i++){
        strcat(cpyDATA,getLigne(DATA,i));
        strcat(cpyDATA,"\n");
    }

    cpyDATA = addLigneAutoIndexSpecificString(cpyDATA,NewLine);

    for(int i = IndexLigne+1;i<getNbLigne(DATA);i++){
        strcat(cpyDATA,getLigne(DATA,i));
        strcat(cpyDATA,"\n");
    }

    // NewSize = Taille de DATA + la différence avec la ligne modifier
    DATA = realloc(DATA,strlen(cpyDATA) + 1);
    strcpy(DATA, cpyDATA);

    // free(cpyDATA);
    return DATA;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    /* =-=-=-=-=-= DISPLAY =-=-=-=-=-= */
        
/* =-=-=-=-=-= TABLEAU =-=-=-=-=-=*/

/*
 * Affiche une liste de puis un DATA passée en entrée qui dois respectée le formatage
 * Prend en entrée un DATA cible, un element cibler ainsi que la colonne ciblée
*/
void DisplaySpecifiqueTable(String DATA,String Element,int Colonne){
    String* ListeColonne = getListeColonne(DATA,Colonne); // Affecte les valeur

    String* ListeLigne = (String*)calloc(getNbElementListe(ListeColonne),sizeof(String));

    int NbColonne = getNbColonne(DATA);
    int* TabCarMax = (int*)calloc(NbColonne,sizeof(int));

    for(int i=0;i<getNbElementListe(ListeColonne);i++){
        if(strcmp(toUpperCase(Element),toUpperCase(ListeColonne[i])) == 0){
            addInListe(ListeLigne,getLigne(DATA,i));
        }
    }

    if(getNbElementListe(ListeLigne) == 0){
        printf_RGB(255,0,0,"\n# Erreur...\n# Aucune application nomme '%s' trouvee ...\n\n",Element);
        return;
    }

    // Récupère le nombre max de car de chaque colonne
    int Buffer;
    for(int i=0;i<NbColonne;i++){
        for(int j=0;j<getNbElementListe(ListeLigne);j++){
            Buffer = strlen(getColonne(ListeLigne[j],i));
            if(Buffer > TabCarMax[i]){
                TabCarMax[i] = Buffer;
            }
        }
    }

    //Cas ou la longeur max d'une ligne ne dépasse pas la longeur de la premier ligne
    for(int i=0;i<NbColonne;i++){
        if(TabCarMax[i] < (int)strlen(getLigneXcolonneY(DATA,0,i))){ // On caste les res en int au lieux de size_t
            TabCarMax[i] = (int)strlen(getLigneXcolonneY(DATA,0,i)); // ''
        }
    }

        // Affiche la premier ligne
    int NbEspace;
    for(int i=0;i<NbColonne;i++){
        printf("|  ");
        printf("%s ",getLigneXcolonneY(DATA,0,i));

        NbEspace = TabCarMax[i] - strlen(getLigneXcolonneY(DATA,0,i));
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

    for(int i=0;i<getNbElementListe(ListeLigne);i++){
        for(int j=0;j<NbColonne;j++){
            printf("|  ");
            printf("%s ",getColonne(ListeLigne[i],j));

            NbEspace = (TabCarMax[j] - strlen(getColonne(ListeLigne[i],j)));
            for(int k=0;k<NbEspace;k++){
                printf(" ");
            }
        }
        printf("|\n");
    }

    for(int i=0;i<NbCarTot;i++){
        printf("-");
    }
    printf("\n");
}

void DisplayTable(String DATA){
    int NbColonne = getNbColonne(DATA);
    int* TabCarMax = (int*)calloc(NbColonne,sizeof(int));

    // Récupère le nombre max de car de chaque colonne
    int Buffer;
    for(int i=0;i<NbColonne;i++){
        for(int j=0;j<getNbLigne(DATA);j++){
            Buffer = strlen(getLigneXcolonneY(DATA,j,i));
            if(Buffer>TabCarMax[i]){
                TabCarMax[i] = Buffer;
            }
        }
    }

    int NbCarTot = 0;
    for(int i=0;i<NbColonne;i++){
        NbCarTot += TabCarMax[i];
    }
    NbCarTot += (4*NbColonne) + 1;

    // // Cas ou la longeur max d'une ligne ne dépasse pas la longeur de la premier ligne
    // for(int i=0;i<NbColonne;i++){
    //     if(TabCarMax[i] < (int)strlen(getLigneXcolonneY(DATA,0,i))){ // On caste les res en int au lieux de size_t
    //         TabCarMax[i] = (int)strlen(getLigneXcolonneY(DATA,0,i)); // ''
    //     }
    // }

    for(int i=0;i<NbCarTot;i++){
        printf("-");
    }
    printf("\n");
    
    // Affiche la premier ligne
    int NbEspace;
    for(int i=0;i<NbColonne;i++){
        printf("|  ");
        printf("%s ",getLigneXcolonneY(DATA,0,i));

        NbEspace = TabCarMax[i] - strlen(getLigneXcolonneY(DATA,0,i));
        for(int j=0;j<NbEspace;j++){
            printf(" ");
        }
    }
    printf("|\n");

    for(int i=0;i<NbCarTot;i++){
        printf("-");
    }
    printf("\n");

    // Affiche tout les lignes
    for(int i=1;i<getNbLigne(DATA);i++){
        for(int j=0;j<NbColonne;j++){
            printf("|  ");
            printf("%s ",getLigneXcolonneY(DATA,i,j));

            NbEspace = (TabCarMax[j] - strlen(getLigneXcolonneY(DATA,i,j)));
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

void DisplayOrdonnedTable(String DATA,int Colonne){
    int NbColonne = getNbColonne(DATA);
    int* TabCarMax = (int*)calloc(NbColonne,sizeof(int));

    // Récupère le nombre max de car de chaque colonne
    int Buffer;
    for(int i=0;i<NbColonne;i++){
        for(int j=0;j<getNbLigne(DATA);j++){
            Buffer = strlen(getLigneXcolonneY(DATA,j,i));
            if(Buffer>TabCarMax[i]){
                TabCarMax[i] = Buffer;
            }
        }
    }

    // Cas ou la longeur max d'une ligne ne dépasse pas la longeur de la premier ligne
    for(int i=0;i<NbColonne;i++){
        if(TabCarMax[i] < (int)strlen(getLigneXcolonneY(DATA,0,i))){ // On caste les res en int au lieux de size_t
            TabCarMax[i] = (int)strlen(getLigneXcolonneY(DATA,0,i)); // ''
        } 
    }
    
    // Affiche la premier ligne
    int NbEspace;
    for(int i=0;i<NbColonne;i++){
        printf("|  ");
        printf("%s",getLigneXcolonneY(DATA,0,i));

        NbEspace = TabCarMax[i] - strlen(getLigneXcolonneY(DATA,0,i)) + 1;
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
    String* DejaAfficher = (String*)calloc(1000,sizeof(String));
    String StringBuffer = (String)calloc(1000,sizeof(char));

    int BoolCouleur = 0;
    int BoolFound = 0;
    for(int i=1;i<getNbLigne(DATA);i++){
        // Reinitialisateur de couleur
        if(BoolCouleur == 2){
            BoolCouleur = 0;
        }

        // Réinitialisation de BoolFound
        BoolFound = 0;
        StringBuffer = getLigneXcolonneY(DATA,i,Colonne);

        // Vérifie si la ligne qu'on vas traiter n'est pas déja traiter 
        for(int i=0;i<getNbElementListe(DejaAfficher);i++){
            if(strcmp(DejaAfficher[i],StringBuffer) == 0){
                BoolFound = 1;
                break;
            }
        }

        if(BoolFound == 1){
            continue;
        }
       
        // On ajoute l'élément qu'on est entrain de traiter dans la liste des deja traiter
        addInListe(DejaAfficher,StringBuffer);

        // Switch de couleur
        BoolCouleur++;
        if (BoolCouleur == 2){
            BoolCouleur = 0;
        }

        // Selon la couleur faire ...
        if(BoolCouleur == 0){
            for(int i=1;i<getNbLigne(DATA);i++){
                if(strcmp(StringBuffer,getLigneXcolonneY(DATA,i,Colonne)) == 0){
                    for(int j=0;j<NbColonne;j++){
                    printf("|  ");
                    // %s car on veut afficher une String donnée avec les %, sans sa il interprete mal les % et décale les résultats
                    printf_RGB(0,0,255,"%s",getLigneXcolonneY(DATA,i,j));
                    printf(" ");

                    NbEspace = (TabCarMax[j] - strlen(getLigneXcolonneY(DATA,i,j)));
                        for(int k=0;k<NbEspace;k++){
                            printf(" ");
                        }
                    }
                printf("|\n");
                }
            }
        }else if(BoolCouleur == 1){
            for(int i=1;i<getNbLigne(DATA);i++){
                if(strcmp(StringBuffer,getLigneXcolonneY(DATA,i,Colonne)) == 0){
                    for(int j=0;j<NbColonne;j++){
                    printf("|  ");
                    // ''
                    printf_RGB(255,255,0,"%s",getLigneXcolonneY(DATA,i,j));
                    printf(" ");

                    NbEspace = (TabCarMax[j] - strlen(getLigneXcolonneY(DATA,i,j)));
                        for(int k=0;k<NbEspace;k++){
                            printf(" ");
                        }
                    }
                printf("|\n");
                }
            }
        }        
    }

    // Affiche la barre de fin
    for(int i=0;i<NbCarTot;i++){
        printf("-");
    }
    printf("\n");
}

/* =-=-=-=-=-= LISTE =-=-=-=-=-=*/

/*
 * Affiche une liste de puis un DATA passée en entrée qui dois respectée le formatage
 * Prend en entrée un DATA cible, un element cibler ainsi que la colonne ciblée
*/
void DisplaySpecifiqueListe(String DATA,String Element,int Colonne){
    String* ListeColonne = getListeColonne(DATA,Colonne);

    for(int i=0;i < getNbElementListe(ListeColonne);i++){
        if(strcmp(ListeColonne[i],Element) == 0){
            printf("%s : %s\n",getLigneXcolonneY(DATA,0,Colonne),getLigneXcolonneY(DATA,i,Colonne)); // Affichage des info 
            for(int j=0;j<getNbColonne(DATA);j++){
                if(strcmp(getLigneXcolonneY(DATA,0,Colonne),getLigneXcolonneY(DATA,0,j)) != 0 && strcmp("Index",getLigneXcolonneY(DATA,0,j)) != 0){
                    printf("    %s : %s\n",getLigneXcolonneY(DATA,0,j),getLigneXcolonneY(DATA,i,j));
                }
            }
        }
    }
}

void DisplayListe(String DATA){
    for(int i=1;i<getNbLigne(DATA);i++){
        for(int j=1;j<getNbColonne(DATA);j++){
            printf("%s : %s\n",getLigneXcolonneY(DATA,0,j),getLigneXcolonneY(DATA,i,j));
        }
        printf("\n");
    } 
}
void DisplayOrdonnedListe(String DATA,int colonne){
    String* ListeDejaAfficher = (String*)calloc(500,sizeof(String));
    String Buffer = (String)calloc(500,sizeof(char));

    int BoolCouleur = 0;
    int BoolFound = 0;
    for(int i=1;i<getNbLigne(DATA);i++){
        strcpy(Buffer, getLigneXcolonneY(DATA, i, colonne));
        BoolFound = 0;

        for(int j=0;j<getNbElementListe(ListeDejaAfficher);j++){
            if(strcmp(Buffer,ListeDejaAfficher[j]) == 0){
                BoolFound = 1;
            }
        }

        if(BoolFound == 0){
            BoolCouleur++;
            if (BoolCouleur == 2){
                BoolCouleur = 0;
            }
            if(BoolCouleur == 0){
                printf_RGB(0,0,255,"%s",getLigneXcolonneY(DATA,0,colonne));
                printf(" : ");
                printf_RGB(0,0,255,"%s",Buffer);
                printf("\n");
                for(int j=1;j<getNbLigne(DATA);j++){
                    if(strcmp(Buffer,getLigneXcolonneY(DATA,j,colonne)) == 0){
                        for(int k=1;k<getNbColonne(DATA);k++){
                            if(strcmp(getLigneXcolonneY(DATA,0,colonne),getLigneXcolonneY(DATA,0,k)) != 0){
                                printf_RGB(0,0,255,"    %s : %s\n",getLigneXcolonneY(DATA,0,k),getLigneXcolonneY(DATA,j,k));
                            }
                        }
                        printf("\n");
                    }
                }
            }else if(BoolCouleur == 1){
                printf_RGB(255,255,0,"%s",getLigneXcolonneY(DATA,0,colonne));
                printf(" : ");
                printf_RGB(255,255,0,"%s",Buffer);
                printf("\n");
                for(int j=1;j<getNbLigne(DATA);j++){
                    if(strcmp(Buffer,getLigneXcolonneY(DATA,j,colonne)) == 0){
                        for(int k=1;k<getNbColonne(DATA);k++){
                            if(strcmp(getLigneXcolonneY(DATA,0,colonne),getLigneXcolonneY(DATA,0,k)) != 0){
                                printf_RGB(255,255,0,"    %s : %s\n",getLigneXcolonneY(DATA,0,k),getLigneXcolonneY(DATA,j,k));
                            }
                        }
                        printf("\n");
                    }
                }
            }
        }
        addInListe(ListeDejaAfficher,Buffer);
    }

}