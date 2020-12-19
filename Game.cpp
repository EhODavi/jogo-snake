#include "Game.h"

// Construtor ✓
Game::Game(int height, int width, int initialSize): snake(initialSize), screen(height,width) {
    // Desenhando a cobra na tela
    snake.draw(screen,Screen::SNAKE);
    
    // Inicializando a direção da cobra (INICIALMENTE, ELA ESTARÁ ANDANDO PARA A DIREITA)
    direction.line = 0;
    direction.column = 1;

    // Inicializando a cabeça da cobra (INICIALMENTE, A CABEÇA DA COBRA ESTARÁ NA LINHA 0 E COLUNA INITIALSIZE - 1)
    head.line = 0;
    head.column = initialSize - 1;

    // Inicializando as comidas do jogo (INICIALMENTE NÃO HÁ NENHUMA COMIDA NA TELA)
    food = new Food[10];
    numFood = 0;
}

// Destrutor ✓
Game::~Game() {
    delete []food; // Desalocando food
}

// Construtor de cópia ✓
Game::Game(const Game &other): snake(other.snake), screen(other.screen) {
    // Atribuindo o valor de direction, head e numFood do other para o this
    direction = other.direction;
    head = other.head;
    numFood = other.numFood;

    // Alocando food
    food = new Food[10];

    // Preenchendo food
    for(int i = 0; i < numFood; i++) food[i] = other.food[i];
}

// Operador de atribuição ✓
Game & Game::operator=(const Game &other) {
    if(this == &other) return *this; // Verificando auto-atribuição

    // Atribuindo o valor de snake, screen, direction, head e numFood do other para o this
    snake = other.snake;
    screen = other.screen;
    direction = other.direction;
    head = other.head;
    numFood = other.numFood;

    // Preenchendo food
    for(int i = 0; i < numFood; i++) food[i] = other.food[i];
	
    return *this; // Retornado o *this
}

// Retorna a tela do jogo ✓
const Screen & Game::getScreen() const {
    return screen; // Retornando a tela do jogo
}

// Avança com o jogo em uma iteração/unidade de tempo ✓
bool Game::step(int dr, int dc) {
    // Variável que representa a nova quantidade de comidas do jogo
    int newNumFood = 0;

    // Percorrendo food
    for(int i = 0; i < numFood; i++) {
        food[i].time--; // Diminuindo o tempo de cada comida
        
        // Se o tempo da comida for -1, quer dizer que ela deve ser retirada da tela
        if(food[i].time == -1) { 
            screen.set(food[i].line,food[i].column,Screen::EMPTY); // Retirando a comida da tela (TROCANDO FOOD POR EMPTY)
        } else { // Se o tempo da comida não for -1, quer dizer que ela deve continuar na tela
            food[newNumFood] = food[i]; // Mantendo a comida no food
            newNumFood++; // Incrementando a nova quantidade de comidas do jogo
        }
    }

    // Atualizando o valor de numFood
    numFood = newNumFood;

    // Atualizando a direção da cobra. Se for informado uma direção contrária ao movimento da cobra, ela continua na mesma direção
    if(direction.line != -dr || direction.column != -dc) {
        direction.line = dr;
        direction.column = dc;
    }
    
    // Atualizando a cabeça da cobra
    head.line = head.line + direction.line;
    head.column = head.column + direction.column;

    // Verificando se a cobra vai bater em uma parede ou se ela vai bater nela mesma
    if(screen.get(head.line,head.column) == Screen::SNAKE || screen.get(head.line,head.column) == Screen::WALL) return false; // Retornando false pois o movimento não foi realizado com sucesso

    // Apagando a cobra na tela
    snake.draw(screen,Screen::EMPTY);

    // Verificando se a cobra vai comer ou não. Se tiver uma comida, ela vai comer e crescer. 
    if(screen.get(head.line,head.column) == Screen::FOOD) {
        // Removendo a comida do jogo
        for(int i = 0; i < numFood; i++) {
            if(food[i].line == head.line && food[i].column == head.column) {
                for(int j = i; j < numFood - 1; j++) food[j] = food[j + 1];
                break;
            }
        }

        // Diminuindo a quantidade de comidas do jogo
        numFood--;

        snake.move(direction.line,direction.column,true); // Movendo a cobra
    } else { // Se não, ela vai apenas se mover
        snake.move(direction.line,direction.column,false); // Movendo a cobra
    }

    // Desenhando a cobra na tela
    snake.draw(screen,Screen::SNAKE);
    
    return true; // Retornando true pois o movimento foi realizado com sucesso
}

// Adiciona uma comida ao jogo ✓
void Game::addFood(int r, int c, int ttl) {
    // Iremos adicionar uma comida ao jogo se o pixel que formos atualizar for EMPTY e a quantidade de comidas for menor do que 10
    if(screen.get(r,c) == Screen::EMPTY && numFood < 10) {
        // Criando a nova comida
        Food newFood;

        // Inicializando a nova comida
        newFood.line = r;
        newFood.column = c;
        newFood.time = ttl;

        // Desenhando a nova comida na tela
        screen.set(r,c,Screen::FOOD);
        
        // Atualizando food e incrementando numFood
        food[numFood] = newFood;
        numFood++;
    }
}

// Retorna a quantidade de comidas do jogo ✓
int Game::getNumFood() const {
    return numFood; // Retornando a quantidade de comidas do jogo
}