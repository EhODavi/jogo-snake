#ifndef SCREEN_H
#define SCREEN_H

class Screen {
    public:
        const static int FOOD = 0; // Constante que representa a comida ✓
        const static int SNAKE = 1; // Constante que representa a cobra ✓
        const static int EMPTY = 2; // Constante que representa o espaço vazio ✓
        const static int WALL = 3; // Constante que representa a parede ✓
        
        Screen(int height, int width); // Construtor ✓
        ~Screen(); // Destrutor ✓
        Screen(const Screen &other); // Construtor de cópia ✓
	    Screen & operator=(const Screen &other); // Operador de atribuição ✓
        int getWidth() const; // Retorna a largura da tela ✓
        int getHeight() const; // Retorna a altura da tela ✓
        int get(int r, int c) const; // Retorna o valor de um elemento da tela ✓
        void set(int r, int c, int val); // Atualiza o valor de um elemento da tela ✓
    private:
        int width; // Largura da tela ✓
        int height; // Altura da tela ✓
        int** data; // Matriz que representa a tela ✓
        int* dataHeight; // Quantidade de linhas de cada coluna da matriz ✓
};

#endif