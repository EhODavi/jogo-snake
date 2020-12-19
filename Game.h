#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Screen.h"

struct Food {
    int line; // Linha da comida ✓
    int column; // Coluna da comida ✓
    int time; // Tempo da comida ✓
};

struct Direction {
    int line; // Linha da direção da cobra ✓
    int column; // Coluna da direção da cobra ✓
};

struct Head {
    int line; // Linha da cabeça da cobra ✓
    int column; // Coluna da cabeça da cobra ✓
};

class Game {
    public:
        Game(int height, int width, int initialSize); // Construtor ✓
        ~Game(); // Destrutor ✓
        Game(const Game &other); // Construtor de cópia ✓
	    Game & operator=(const Game &other); // Operador de atribuição ✓
        const Screen & getScreen() const; // Retorna a tela do jogo ✓
        bool step(int dr, int dc); // Avança com o jogo em uma iteração/unidade de tempo ✓
        void addFood(int r, int c, int ttl); // Adiciona uma comida ao jogo ✓
        int getNumFood() const; // Retorna a quantidade de comidas do jogo ✓
    private:
        Snake snake; // Cobra do jogo ✓
        Screen screen; // Tela do jogo ✓
        Food* food; // Comidas do jogo ✓
        Direction direction; // Direção da cobra ✓
        Head head; // Cabeça da cobra ✓
        int numFood; // Quantidade de comidas do jogo ✓
};

#endif