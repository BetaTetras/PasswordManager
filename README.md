
# 🔑 | PasswordManager
![Badge Langage](https://img.shields.io/badge/Langage-C-blue?style=plastic)
![Badge Version](https://img.shields.io/badge/Version-v3-green?style=plastic)
![Badge Etat](https://img.shields.io/badge/Etat%20%3A-En%20cour...-orange?style=plastic)



**PasswordManager** est une application développer en C par Grégoire GIBRAT permettant de gérer, administrée et manipuler sa propre base de donnée de mot de passe. 

Pour faire fonctioner **PasswordManager**, le code utilise deux bibliothéque :

- [🔍] *DataExplorer.c : Bibliothéque C qui permet la manipulation de fichier de base de donnée type txt*
- [⚙️] *Tools.c : Bibliothéque C qui contien des outil utile pour le developpement de DataExplorer et de PasswordManager*

## 📋 | Fonctionnalités de PasswordManager

| **Fonctionnalités**                                            |
|----------------------------------------------------------------|
| [✏️]  *Modification*                                           |
| **Création** de compte dans la base de donnée.                 |
| **Supression** de compte dans la base de donnée.               |
| **Modification** de valeur dans la base de donné.              |
| [🔍] *Affichage*                                               |
| **Affichage** d'une valeur choisie                             |
| **Affichage** en format tableau ordonnée par un type de valeur |
| **Affichage** en format de liste ordonnée par un type de valeur|
| [🔩]  *Utilitaire*                                             |
| **Générateur** de mot de passe fort                            |

## ⚙️ | Fonctionnement et déploiement 
**Requis :**
- N'importe quelle pc sous Win 11 *(même une pomme de terre peut faire tournée mon programme)*

**Lancement :**
- *Pour v1 et v2 :* Se lance normalement depuis l'exe. Attention cependant a vos anti-virus qui peut empecher le lancement de l'application, le code source est a votre disposition pour vérifier son contenue.
- Si vous avez gcc sur votre Win 11, placer vous dans le fichier de la version souhaiter depuis votre terminal et entrée cette commande pour recompiler le programme pour s'assurer son bon fonctionnement
```bash
  cd C:\[...]\PasswordManager\vX\
  gcc .\DataExplorer.c .\DataExplorer.h .\Tools.c .\Tools.h .\PasswordManager.c -o PasswordManager
```
**A noter :**
- *Pour v1 et v2 :* Le fichier DATA.txt **suis un format STRICTE**, le modifier a la main peut le rendre **produire des erreur** *(comme par exemple avoir plusieur "\n" a la fin du fichier)*
- Pour des raison structurelle **il ne faut pas utilisée des caractére accentuée (éèçàù) ou alors le caractére pipe ( | )** dans l'application

