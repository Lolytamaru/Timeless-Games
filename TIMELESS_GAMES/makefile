# Librairies :
# Chez nous : -Llib
# A l'université : -L/info/etu/l2info/s200470/SDL2_LIB/lib
# Sur Windows : -lmingw32
#---------------------------------------------------------
# Compilation :
# Sur Linux : make
# Sur Windows : mingw32-make
#---------------------------------------------------------
# Exécution : ./bin/accueil
#---------------------------------------------------------

# Paramètres de la compilation
CC = gcc
CXXFLAGS = -Wall -g
LDFLAGS = -I./include -L/info/etu/l2info/s200470/SDL2_LIB/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm

# Exécutable
APPNAME = ./bin/accueil
# Fichiers .c
EXT = .c
# Dossier des fichiers .c
SRCDIR = ./src
# Dossier des fichiers .o
OBJDIR = ./obj
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
RM = rm
DELOBJ = $(OBJ)

all: $(APPNAME)
	@echo Compilation réussie \!

# Compilation
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo Tout les fichiers objets ont bien été générés.

# Construit les fichiers .o avec les .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

# Supprime les .o et l'exécutable
clean:
	$(RM) $(DELOBJ)
	$(RM) $(APPNAME)
	@echo Fichiers .o et accueil supprimés.
