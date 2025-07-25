# === Cible par défaut : tout compiler ===

all: bin/PWM.exe bin/SetUp.exe

# === Options de compilation ===
# -Wall     => active tous les warnings importants
# -Wextra   => active encore plus de warnings utiles
# -Ilib     => permet d’inclure les fichiers .h dans le dossier "lib"
CFLAGS = -Wall -Wextra -Ilib


# === Créer le dossier bin si nécessaire ===
bin:
	if not exist bin mkdir bin

# === Compilation de PWM.exe ===
bin/PWM.exe: src/PasswordManager.c lib/DataExplorer.c lib/Tools.c | bin
	gcc $(CFLAGS) -o bin/PWM.exe src/PasswordManager.c lib/DataExplorer.c lib/Tools.c

# === Compilation de SetUp.exe ===
bin/SetUp.exe: src/SetUp.c lib/DataExplorer.c lib/Tools.c | bin
	gcc $(CFLAGS) -o bin/SetUp.exe src/SetUp.c lib/DataExplorer.c lib/Tools.c

# === Nettoyage des exécutables ===
clean:
	del /Q bin\*.exe 2>nul || echo Rien à nettoyer.
