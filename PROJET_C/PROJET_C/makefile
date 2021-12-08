CPP=g++

# Les différents répertoires contenant respectivement les fichiers : Sources *.c, Headers *.h, Objets *.o, l'exécutable
SRCDIR=SRC
HEADDIR=INCLUDE
LIBDIR=OBJ
BINDIR=Bin

# L'exécutable
BIN=MonExecutable

# Où trouver les différents sources *.cpp qu'il faudra compiler pour créer les objets correspondants
SRCPP= $(wildcard $(SRCDIR)/*.cpp)
OBJCPP= $(SRCPP:$(SRCDIR)/%.cpp=$(LIBDIR)/%.o)

all: $(BIN)

#Création de l'exécutable
MonExecutable: $(OBJCPP)
# Création des différents *.o à partir des *.cpp
$(LIBDIR)/%.o: $(SRCDIR)/%.cpp $(HEADDIR)/%.h
	$(CPP) -o $@ -c $< $(CFLAGS)

# Nettoyage des objets => Tout sera recompiler !
clean:
	rm $(LIBDIR)/*.o

# Nettoyage complet => clean + effacement du l'exécutable
Clean: clean
	rm $(BINDIR)/*
