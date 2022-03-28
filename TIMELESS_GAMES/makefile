#Pour Linux : rien
#Pour Windows : -lmingw32

#Pour Linux : make
#Pour Windows : mingw32-make

#LDFLAGS chez nous = -Llib
#LDFALGS lib fac = -L/info/etu/l2info/s200470/SDL2_LIB/lib
#Exécution : ./bin/accueil

# Paramètres de la compilation
CC = gcc
CXXFLAGS = -Wall -g
LDFLAGS = -I./include -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm

# Paramètres du makefile
APPNAME = ./bin/accueil #ici le nom de l'exécutable
EXT = .c
SRCDIR = ./src
OBJDIR = ./obj

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

RM = rm
DELOBJ = $(OBJ)

all: $(APPNAME)
	@echo Compilation reussie

# Compilation
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo Tout les fichiers objets ont bien ete generes

# Construit les fichiers .o avec les .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)
