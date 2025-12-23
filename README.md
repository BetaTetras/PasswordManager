# 🔑 | PasswordManager
![Badge Langage](https://img.shields.io/badge/Langage%20:-C-blue?style=plastic)
![Badge Licence](https://img.shields.io/badge/Licence%20:-MIT-darkblue?style=plastic)
![Badge Version](https://img.shields.io/badge/Version%20:-v6_STABLE-lim?style=plastic)
![Badge État](https://img.shields.io/badge/État%20%3A-En%20cours...-orange?style=plastic)

**PasswordManager** est une application développée en C par Grégoire GIBRAT permettant de gérer, administrer et manipuler sa propre base de données de mots de passe. 

Pour faire fonctionner **PasswordManager**, le code utilise deux bibliothèques :

- [🔍] *DataExplorer.c : Bibliothèque C qui permet la manipulation de fichiers de base de données type txt*
- [⚙️] *Tools.c : Bibliothèque C qui contient des outils utiles pour le développement de DataExplorer et de PasswordManager*

## 📋 | Fonctionnalités de PasswordManager

| **Fonctionnalités**                                            |
|----------------------------------------------------------------|
| [✏️]  *Modification*                                           |
| **Création** de compte dans la base de données.                |
| **Suppression** de compte dans la base de données.             |
| **Modification** de valeurs dans la base de données.           |
| [🔍] *Affichage*                                               |
| **Affichage** d'une valeur choisie - *(v2)*                    |
| **Affichage** en format tableau ordonné par un type de valeur  |
| **Affichage** en format de liste ordonnée par un type de valeur|
| **Affichage** UI avec deplacement par fléche - *(v5)*          |
| [🔩]  *Utilitaire*                                             |
| **Générateur** de mot de passe fort - *(v2)*                   |
| **Cryptage** des information - *(v3)*                          |
| **Sauvegarde** de la base de donnée - *(v5)*                   |
| **Chiffrage** coustant, même pendant l'utilisation - *(v6)*   |

## ⚙️ | Fonctionnement et déploiement 
### Requis :
- *Version 1 à 6* -  N'importe quel PC sous Win 11 (*gcc* et *mingw32-make* conseillée) 
- *Version 4 et version 6* - N'importe quel PC sous n'importe distribution Linux (*gcc* conseillée) 

### Lancement :
##### *Pour v1 et v2 :* - ![Badge OS](https://img.shields.io/badge/OS%20:-WINDOWS-GREEN?style=plastic)
-  Se lance normalement depuis l'exe. Attention cependant à vos antivirus qui peuvent empêcher le lancement de l'application, le code source est à votre disposition pour vérifier son contenu.
- Si vous avez *gcc* sur votre Windows, placez-vous dans le dossier de la version souhaitée depuis votre terminal et entrez cette commande pour recompiler le programme afin de s'assurer de son bon fonctionnement :
```bash
  cd C:\[...]\PasswordManager\vX\
  gcc .\DataExplorer.c .\DataExplorer.h .\Tools.c .\Tools.h .\PasswordManager.c -o PasswordManager
```
##### *Pour v3 :* -  ![Badge OS](https://img.shields.io/badge/OS%20:-WINDOWS-GREEN?style=plastic)
- D'abord lancer SetUp.exe qui se trouve ici : `C:\[...]\PasswordManager\v3\bin\SetUp.exe`
- Puis vous pouvez lancée PasswordManager.exe : `C:\[...]\PasswordManager\v3\bin\PWM.exe` 
- Si vous avez *gcc* ainsi que *mingw32-make* sur votre Windows, placez-vous dans le dossier de la version souhaitée depuis votre terminal et entrez cette commande pour recompiler le programme afin de s'assurer de son bon fonctionnement :
```bash
  cd C:\[...]\PasswordManager\vX\
  mingw32-make
```
##### *Pour v4 :* -  ![Badge OS](https://img.shields.io/badge/OS%20:-WINDOWS-GREEN?style=plastic) ![Badge OS](https://img.shields.io/badge/OS%20:-LINUX-blue?style=plastic)

#### Sous **Windows** :
- Le SetUp.exe a étais fusionnée avec PasswordManager.exe donc il suffit de lancer directement PasswordManager.exe qui est ici :`C:\[...]\PasswordManager\v4\windows\bin\PasswordManager.exe`
- Si vous avez *gcc* ainsi que *mingw32-make* sur votre Windows, placez-vous dans le dossier de la version souhaitée depuis votre terminal et entrez cette commande pour recompiler le programme afin de s'assurer de son bon fonctionnement :
```bash
  cd C:\[...]\PasswordManager\v4\Windows
  mingw32-make
```
- Si l'erreur qui vous indique que le chiffrement n'a pas étais effectuée lors de la dernière utilisation s'affichie il faut utiliser l'executable BackUp.exe qui est ici : `C:\[...]\PasswordManager\v4\Windows\bin\BackUp.exe`

#### Sous **Linux** :
- Il suffit de lancer PasswordManager qui est ici : `C:\[...]\PasswordManager\v4\Linux\bin\BackUp.exe`
- Si vous avez gcc et make sur votre linux, placez-vous dans le dossier de la version souhaitée depuis votre terminal et entrez cette commande pour recompiler le programme afin de s'assurer de son bon fonctionnement :
```bash
  cd C:\[...]\PasswordManager\v4\linux
  make
```
- Si l'erreur qui vous indique que le chiffrement n'a pas étais effectuée lors de la dernière utilisation s'affichie il faut utiliser l'executable BackUp.exe qui est ici : `C:\[...]\PasswordManager\v4\Linux\bin\BackUp.exe`

##### *Pour v5 :* -  ![Badge OS](https://img.shields.io/badge/OS%20:-WINDOWS-GREEN?style=plastic) ![Badge Version](https://img.shields.io/badge/Etat%20:-UNSTABLE-darkred?style=plastic)

#### Sous **Windows** :
- Si vous avez *gcc* ainsi que *mingw32-make* sur votre Windows, placez-vous dans le dossier de la version souhaitée depuis votre terminal et entrez cette commande pour recompiler le programme afin de s'assurer de son bon fonctionnement :
```bash
  cd C:\[...]\PasswordManager\v5\Windows
  mingw32-make
```
- Si l'erreur qui vous indique que le chiffrement n'a pas étais effectuée lors de la dernière utilisation s'affichie il faut utiliser l'executable BackUp.exe qui est ici : `C:\[...]\PasswordManager\v5\Windows\bin\BackUp.exe`

- La sauvegarde des bases de données se trouve dans le fichier et ils peuvent étre générée depuis l'application avec l'option concernée
Emplacement des sauvergarde : `C:\[...]\PasswordManager\v5\Windows\saves`
##### *Pour V6 :* -  ![Badge OS](https://img.shields.io/badge/OS%20:-WINDOWS-GREEN?style=plastic) ![Badge OS](https://img.shields.io/badge/OS%20:-LINUX-blue?style=plastic) ![Badge Version](https://img.shields.io/badge/Etat%20:-STABLE-LIM?style=plastic) 

#### Sous **Windows** :
- Si vous avez *gcc* ainsi que *mingw32-make* sur votre Windows, placez-vous dans le dossier de la version souhaitée depuis votre terminal et entrez cette commande pour recompiler le programme afin de s'assurer de son bon fonctionnement :
```bash
  cd C:\[...]\PasswordManager\v6\Windows
  mingw32-make
```
- Si l'erreur qui vous indique que le chiffrement n'a pas étais effectuée lors de la dernière utilisation s'affichie il faut utiliser l'executable BackUp.exe qui est ici : `C:\[...]\PasswordManager\v6\Windows\bin\BackUp.exe`

- La sauvegarde des bases de données se trouve dans le fichier et ils peuvent étre générée depuis l'application avec l'option concernée
Emplacement des sauvergarde : `C:\[...]\PasswordManager\v6\Windows\saves`

**À noter :**
-  Le fichier DATA.txt **suit un format STRICT**, le modifier à la main peut **provoquer des erreurs** *(comme par exemple avoir plusieurs "\n" à la fin du fichier)*  
- Pour des raisons structurelles, **il ne faut pas utiliser de caractères accentués (éèçàù) ni le caractère pipe ( | )** dans l'application

#### Sous **Linux** :
- Il suffit de lancer PasswordManager qui est ici : `C:\[...]\PasswordManager\v6\Linux\bin\PasswordManager`
- Si vous avez gcc et make sur votre linux, placez-vous dans le dossier de la version souhaitée depuis votre terminal et entrez cette commande pour recompiler le programme afin de s'assurer de son bon fonctionnement :
```bash
  cd C:\[...]\PasswordManager\v6\linux
  make
```
- Si l'erreur qui vous indique que le chiffrement n'a pas étais effectuée lors de la dernière utilisation s'affichie il faut utiliser l'executable BackUp.exe qui est ici : `C:\[...]\PasswordManager\v4\Linux\bin\BackUp.exe`

## 💡 | Remarques 
**PasswordManager** est une application créée pour apprendre et m'améliorer en C et dans l'algorithmie en général, dans le cadre de mes études en informatique... Donc c'est pas du sérieux les gars.

**ATTENTION** : Le chiffrement / déchifrrement est BUGGE !!! Je la fixerais avec la V6

## 📜 | Licence

Ce projet est sous licence **MIT** – Vous pouvez faire un peu ce que vous voulez tant que je suis crédité.
