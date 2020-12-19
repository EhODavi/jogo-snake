#include "Screen.h"

// Construtor ✓
Screen::Screen(int height, int width) {
    this->width = width; // Inicializando width
    this->height = height; // Inicializando height

    // Alocando data e dataHeight
    data = new int*[width];
    dataHeight = new int[width];
    
    // Preenchendo dataHeight e alocando cada coluna do data
    for(int j = 0; j < width; j++) {
        dataHeight[j] = 0;
        data[j] = new int[0];
    }  
}

// Destrutor ✓
Screen::~Screen() {
    // Desalocando dataHeight e data
    for(int j = 0; j < width; j++) delete []data[j];   
    delete []dataHeight;
    delete []data;
}

// Construtor de cópia ✓
Screen::Screen(const Screen &other) {
    // Atribuindo 0 para width e height
    width = height = 0;  
    
    // Atribuindo NULL para dataHeight e data
    dataHeight = 0;
    data = 0;
    
    // Reaproveitando código com o operador de atribuição
    *this = other;
}

// Operador de atribuição ✓
Screen & Screen::operator=(const Screen &other) {
    if(this == &other) return *this; // Verificando auto-atribuição

    // Desalocando dataHeight e data
    for(int j = 0; j < width; j++) delete []data[j];   
    delete []dataHeight;
    delete []data;

    // Atribuindo o valor de width e height do other para o this
    width = other.width; 
    height = other.height;
        
    // Alocando dataHeight e data
    data = new int*[width];
    dataHeight = new int[width];
        
    // Preenchendo dataHeight e data
    for(int j = 0; j < width; j++) {
        dataHeight[j] = other.dataHeight[j];
        data[j] = new int[dataHeight[j]];

        for(int i = 0; i < dataHeight[j]; i++) {
            data[j][i] = other.data[j][i];
        }
    } 
	
    return *this; // Retornado o *this
}

// Retorna a largura da tela ✓
int Screen::getWidth() const {
    return width; // Retornando a largura da tela
}

// Retorna a altura da tela ✓
int Screen::getHeight() const {
    return height; // Retornando a altura da tela
}

// Retorna o valor de um elemento da tela ✓
int Screen::get(int r, int c) const {
    if(c < 0 || c >= width || r < 0 || r >= height) return WALL; // Se estivermos acessando alguma posição fora da tela, retornamos WALL
    if(r >= dataHeight[c]) return EMPTY; // Se estivermos acessando alguma posição dentro da tela, porém essa posição não está alocada, retornamos EMPTY

    return data[c][r]; // Agora temos garantia que é possível retornar o elemento da tela
}

// Atualiza o valor de um elemento da tela ✓
void Screen::set(int r, int c, int val) {
    if(r >= dataHeight[c]) { // Se estamos atualizando um valor da tela depois da última posição (PODE SER PRECISO REDIMENSIONAR)
        if(val == FOOD || val == SNAKE) { // Se val for FOOD ou SNAKE, precisaremos redimensionar a coluna (AUMENTAR O NÚMERO DE LINHAS DELA)
            // Alocando a nova coluna
            int* newColumn = new int[r + 1];
                
            // Preenchendo a nova coluna
            for(int i = 0; i < dataHeight[c]; i++) newColumn[i] = data[c][i];
            for(int i = dataHeight[c]; i < r; i++) newColumn[i] = EMPTY;
            newColumn[r] = val;

            // Desalocando a coluna antiga
            delete []data[c];
                
            // Atualizando os valores de dataHeight e data
            dataHeight[c] = r + 1;
            data[c] = newColumn;
        }
    } else if(r == dataHeight[c] - 1) { // Se estamos atualizando o valor na última posição (PODE SER PRECISO REDIMENSIONAR)
        if(val == SNAKE) { // Se val for SNAKE, iremos atualizar o elemento da linha r e coluna c apenas se ele for FOOD
            if(data[c][r] == FOOD) data[c][r] = val;
        } else if (val == EMPTY) { // Se val for EMPTY, precisaremos redimensionar a coluna (DIMINUIR O NÚMERO DE LINHAS DELA)
            // Variável que representa a nova quantidade de linhas da coluna
            int newRow = 0;

            // Percorrendo a coluna para saber qual é a posição do elemento mais importante
            for(int i = 0; i < dataHeight[c] - 1; i++) {
                if(data[c][i] == FOOD || data[c][i] == SNAKE) newRow = i + 1;
            }

            // Alocando a nova coluna
            int* newColumn = new int[newRow];
            
            // Preenchendo a nova coluna
            for(int i = 0; i < newRow; i++) newColumn[i] = data[c][i];      
            
            // Desalocando a coluna antiga
            delete []data[c];
            
            // Atualizando os valores de dataHeight e data
            dataHeight[c] = newRow;
            data[c] = newColumn;
        }
    } else { // Se estamos atualizando um valor antes da última posição (NÃO SERÁ PRECISO REDIMENSIONAR)
        if(val == FOOD) { // Se val for FOOD, iremos atualizar o elemento da linha r e coluna c apenas se ele for EMPTY
            if(data[c][r] == EMPTY) data[c][r] = val;
        } else if(val == SNAKE) { // Se val for SNAKE, iremos atualizar o elemento da linha r e coluna c apenas se ele for FOOD ou EMPTY
            if(data[c][r] == FOOD || data[c][r] == EMPTY) data[c][r] = val;
        } else { // Se val for EMPTY, iremos atualizar o elemento da linha r e coluna c apenas se ele for FOOD ou SNAKE
            if(data[c][r] == FOOD || data[c][r] == SNAKE) data[c][r] = val;
        }
    }
}