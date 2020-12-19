#include "Snake.h"

// Construtor ✓
Snake::Snake(int initialSize) {
	create(); // Chamando a função auxiliar create para reaproveitar código
	
	// Criando os Nodos da cobra
	for(int i = 0; i < initialSize; i++) push_back(0,i); // Chamando a função auxiliar push_back para reaproveitar código
}

// Destrutor ✓
Snake::~Snake() {
	destroy(); // Chamando a função auxiliar destroy para reaproveitar código
}

// Construtor de cópia ✓
Snake::Snake(const Snake &other) {
	create(); // Chamando a função auxiliar create para reaproveitar código	
	*this = other; // Reaproveitando código com o operador de atribuição
}

// Operador de atribuição ✓
Snake & Snake::operator=(const Snake &other) {
    if(this == &other) return *this; // Verificando auto-atribuição
	
	destroy(); // Chamando a função auxiliar destroy para reaproveitar código
	create(); // Chamando a função auxiliar create para reaproveitar código

	Node* curr = other.first; // Variável que percorre os Nodos da cobra other
		
	while(curr != 0) { // Percorrendo todos os Nodos da cobra other
		push_back(curr->line,curr->column); // Chamando a função auxiliar push_back para reaproveitar código
		curr = curr->next; // Indo para o proximo Nodo
	}

	return *this; // Retornado o *this
}

// Desenha a cobra na tela ✓
void Snake::draw(Screen &s, int state) const {
	Node* curr = first; // Variável que percorre os Nodos da cobra

	// Percorrendo todos os Nodos da cobra
	while(curr != 0) {
		s.set(curr->line,curr->column,state); // Marcando as posições da cobra com o identificador "state"
		curr = curr->next; // Indo para o proximo Nodo
	}
}

// Move a cobra ✓
void Snake::move(int dr, int dc, bool eating) {
	push_back(last->line + dr,last->column + dc); // Chamando a função auxiliar push_back para reaproveitar código
	
	// Se a cobra não estiver comendo, é preciso desalocar o primeiro Nodo
	if(!eating) { 
		Node* aux = first; // Variável auxiliar para guardar o first antigo
		first = first->next; // Atualizando o valor de first
		first->prev = 0; // Fazendo o prev do novo first ser NULL
		delete aux; // Desalocando o aux (first antigo)
	} 
}

// Retorna o tamanho da cobra ✓
int Snake::getLength() const {
	Node* curr = first; // Variável que percorre os Nodos da cobra
    int count = 0; // Variável que representa o tamanho da cobra
	
	// Percorrendo todos os Nodos da cobra
	while(curr != 0) { 
		count++; // Incrementando o tamanho da cobra
		curr = curr->next; // Indo para o proximo Nodo
	}

	return count; // Retornando o tamanho da cobra
}

// Função auxiliar para desalocar a memória ✓
void Snake::destroy() {
	Node* curr = first; // Variável que percorre os Nodos da cobra
    Node* aux; // Variável auxiliar 

	// Percorrendo todos os Nodos da cobra
	while(curr != 0) { 
		aux = curr->next; // Guardando o proximo Nodo em uma variável auxiliar
		delete curr; // Desalocando o Nodo
		curr = aux; // Indo para o proximo Nodo
	}
}

// Função auxiliar para alocar a memória ✓
void Snake::create() {
	first = last = 0; // Atribuindo NULL para first e last
}

// Função auxiliar para adicionar um Nodo depois da cabeça da cobra ✓
void Snake::push_back(int l, int c) {
	if(first == 0) { // Se ainda não foi criado nenhum Nodo da cobra
		first = last = new Node(l,c); // Criando o primeiro Nodo da cobra
	} else { // Se foi criado pelo menos um Nodo da cobra
		last->next = new Node(l,c); // Fazendo o next do last apontar para o novo Nodo
		last->next->prev = last; // Fazendo o prev do novo Nodo apontar para o last
		last = last->next; // Atualizando o valor do last para o novo Nodo criado
	}
}