# === Cible par défaut : tout compiler ===
all: bin/PasswordManager bin/BackUp

# === Options de compilation ===
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

# === Nettoyage des exécutables ===
clean:
	rm -f bin/PasswordManager bin/BackUp
