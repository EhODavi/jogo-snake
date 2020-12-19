#ifndef SNAKE_H 
#define SNAKE_H 

#include "Screen.h"

class Node { 
	public:
		Node(int l, int c): line(l), column(c), prev(0), next(0) {} // Construtor ✓
        
        Node* prev; // Ponteiro para o Nodo anterior ✓
		int line; // Linha do Nodo ✓
        int column; // Coluna do Nodo ✓
        Node* next; // Ponteiro para o proximo Nodo ✓
};

class Snake {
    public:
        Snake(int initialSize); // Construtor ✓
        ~Snake(); // Destrutor ✓
        Snake(const Snake &other); // Construtor de cópia ✓
	    Snake & operator=(const Snake &other); // Operador de atribuição ✓
        void draw(Screen &s, int state) const; // Desenha a cobra na tela ✓
        void move(int dr, int dc, bool eating); // Move a cobra ✓
        int getLength() const; // Retorna o tamanho da cobra ✓
    private:
        Node* first; // Ponteiro para o primeiro Nodo da cobra ✓
        Node* last; // Ponteiro para o último Nodo da cobra ✓

        // Funções auxiliares ✓
        void destroy(); // Função auxiliar para desalocar a memória ✓
        void create(); // Função auxiliar para alocar a memória ✓
        void push_back(int l, int c); // Função auxiliar para adicionar um Nodo depois da cabeça da cobra ✓
};

#endif