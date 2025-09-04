# === Cible par défaut : tout compiler ===
all: bin/PasswordManager.exe bin/BackUp.exe

# === Options de compilation ===
# -Wall     => active tous les warnings importants
# -Wextra   => active encore plus de warnings utiles
# -Ilib     => permet d’inclure les fichiers .h dans le dossier "lib"
CFLAGS = -Wall -Wextra -Ilib

# === Créer le dossier bin si nécessaire ===
bin:
	cmd /C "if not exist bin mkdir bin"

# === Compilation de PasswordManager.exe avec icône ===
bin/PasswordManager.exe: src/PasswordManager.c lib/DataExplorer.c lib/Tools.c ico/PasswordManager.res | bin
	gcc $(CFLAGS) -o bin/PasswordManager.exe src/PasswordManager.c lib/DataExplorer.c lib/Tools.c ico/PasswordManager.res

# === Génération automatique du .res à partir du .rc ===
ico/PasswordManager.res: ico/PasswordManager.rc ico/PasswordManager.ico
	windres ico/PasswordManager.rc -O coff -o ico/PasswordManager.res

# === Compilation de BackUp.exe ===
bin/BackUp.exe: src/BackUp.c lib/Tools.c | bin
	gcc $(CFLAGS) -o bin/BackUp.exe src/BackUp.c lib/Tools.c

# === Nettoyage des exécutables et ressources ===
clean:
	del /Q bin\*.exe ico\*.res 2>nul || echo Rien à nettoyer.