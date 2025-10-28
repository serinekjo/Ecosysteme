# Nom de l'exécutable
EXEC = simulation

# Fichiers sources
SRC = main.cpp univers.cpp organisme.cpp animal.cpp mouton.cpp loups.cpp herbe.cpp
OBJS = main.o univers.o organisme.o animal.o mouton.o loups.o herbe.o

# Fichiers objets
OBJ = $(SRC:.cpp=.o)

# Options de compilation
CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++17

# Règle par défaut
all: $(EXEC)

# Génération de l'exécutable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation des fichiers .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f *.o $(EXEC)

# Forcer la reconstruction complète
re: clean all
