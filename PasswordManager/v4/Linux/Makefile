# === Cible par défaut : tout compiler ===
all: bin/PasswordManager bin/BackUp

# === Options de compilation ===
# -Wall     => active tous les warnings importants
# -Wextra   => active encore plus de warnings utiles
# -Ilib     => permet d’inclure les fichiers .h dans le dossier "lib"
CFLAGS = -Wall -Wextra -Ilib

# === Créer le dossier bin si nécessaire ===
bin:
	mkdir -p bin

# === Compilation de PasswordManager ===
bin/PasswordManager: src/PasswordManager.c lib/DataExplorer.c lib/Tools.c | bin
	gcc $(CFLAGS) -o bin/PasswordManager src/PasswordManager.c lib/DataExplorer.c lib/Tools.c

# === Compilation de BackUp ===
bin/BackUp: src/BackUp.c lib/Tools.c | bin
	gcc $(CFLAGS) -o bin/BackUp src/BackUp.c lib/Tools.c

# === Nettoyage des exécutables et ressources ===
clean:
	rm -f bin/PasswordManager bin/BackUp
