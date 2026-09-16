CXX = g++ # le compilateur utilisé

CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude # les options passées
LDLIBS = -lcpr $(shell pkg-config --libs sdl3)
CPPFLAGS = $(shell pkg-config --cflags sdl3)

SRC = src/main.cpp src/Grille.cpp src/Jeu.cpp src/Window.cpp src/GameObject.cpp # la liste des fichiers .cpp à compiler ensemble

BIN = main #le nom du programme généré

all: $(BIN)

# commande de compilation
$(BIN): $(SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SRC) -o $(BIN) $(LDLIBS)

clean:
	rm -f $(BIN)

.PHONY: all clean