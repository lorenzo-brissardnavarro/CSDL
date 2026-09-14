CXX = g++ # le compilateur utilisé

CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -I/ucrt64/include # les options passées
LDLIBS = -lcpr

SRC = src/main.cpp src/Grille.cpp src/Jeu.cpp # la liste des fichiers .cpp à compiler ensemble

BIN = main #le nom du programme généré

all: $(BIN)

# commande de compilation
$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN) $(LDLIBS)

clean:
	rm -f $(BIN)

.PHONY: all clean