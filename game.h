#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define SNAKE_MAX_SIZE 5
#define OBS_MAX 100

//ASCII - Caracteres utilizados para montar os objetos do jogo.
#define CHAR_TAIL   176     //o
#define CHAR_SPACE  ' '
#define CHAR_BODY   '*'
#define CHAR_HEAD   'c'
#define CHAR_OBS    'x'


// Objetos do jogo, corpo, cauda, corpo e obstaculos
typedef enum SnakeObject
{
    HEAD = 1,
    BODY,
    TAIL,
    OBSTACLE
} SnakeObject;

// Um enum montado para definir o movimento CIMA, BAIXO, ESQUERDA e DIREITA da minhoca.
typedef enum Direction
{
    UP = 1,
    DOWN,
    LEFT,
    RIGHT,
    DIRECTION_NUMBER = 4
} Direction;


// A estrutura principal do programa, onde será utilizada guardar as posições dos obstaculos, as posições da minhoca e o tamanho X e Y do tabuleiro.
typedef struct SnakeGame
{
    int tabuleiro[10][10];
    int obstacles[OBS_MAX];
    int snake[SNAKE_MAX_SIZE];
    int gameSizeX;
    int gameSizeY;
} SnakeGame;

// Verifica o block atual selecionado e soma aos blocos visitados.
void incrementWalkCount(SnakeGame * snakeGame);

// Reseta todos blocos visitados - para o valor 0.
void resetWalkCount(SnakeGame * snakeGame);

// Obtém a quantidade todal de caminhadas que a minhoca fez no tabuleiro.
int getWalkSnakeCount(SnakeGame * snakeGame);

// Inicia a snake atribuindo a posição dela no Board.
// a posição selecionada será o ponto inicial da snake acompanhada do seu corpo no mesmo ponto da matriz.
void setSnakeToPosition(SnakeGame *snakeGame, const int boardX, const int boardY);

// Inicia os obstaculos atribuindo o valor '-1' para todas as posições do vetor obstaculos,
// onde a quantidade máxima de posições é de 100, mas nem sempre será usado as 100 posições
// então o valor '-1' será o identificador de que a posição do vetor obstaclo não contém um obstaculo.
void initItemObstacle(SnakeGame *snakeGame);

// Inicia o Snake atribuindo o valor '-1' para todas as posições do vetor snake,
// assim mantendo o snake fora do tabuleiro do game.
void initItemSnake(SnakeGame *snakeGame);

// Define o tamanho do tabuleiro da snake, a quantidade de posições do tabuleiro onde a snake pode se movimentar.
void setBoardSize(SnakeGame* snakeGame, const int boardX, const int boardY);

// Define o local de um obstaculo será gerado dentro do tabuleiro do jogo.
void setBoardObstacle(SnakeGame* snakeGame, const int boardX, const int boardY);

// Calcula os objetos "obstacles, snake" na matriz do SnakeGame e define o que será imprimido na tela.
void drawBoardGame(SnakeGame* snakeGame);

// Após os calculos do drawBoardGame, essa função recebe as posições para imprimir na tela (cabeça, corpo, cauda, obstaculos e espaços vazios).
void drawObject(const SnakeObject part);

// Movimenta a Snake para uma posição na tela definida como (Cima, Baixo, Esquerda e Direita).
int moveSnakeToPosition(SnakeGame* snakeGame, const Direction direction);

// Essa fução recebe um posicionamento X e Y de posicionamento no tabuleiro e retorna um valor real de posicionamento
// Ex: X = 5, Y = 5 e o tamanho do tabuleiro é 50 por 50, então o resultado será o posicionamento 255.
// Não existe uma Matriz board, o programa se baseia totalmente no calculo de posicionamento das parede, snake e obstaculos.
int getRealBoardPosition(SnakeGame * snakeGame, const int boardX, const int boardY);

// Retorna o caractere do obstaculo contido na posição selecionada.
// Função de suporte para o charItemOnSpace
int charObstaclePosition(SnakeGame * snakeGame, const int boardX, const int boardY);

// Retorna o caractere do corpo da snake referente a posição verificada.
// Função de suporte para o charItemOnSpace
int charPieceSnake(SnakeGame * snakeGame, const int boardX, const int boardY);

// após verificar qual parte do corpo da snake ou qual obstaculo está contida na posição selecionada
// a função retorna o caractere a ser imprimido na tela. Ex: (c = cabeça, x = obstaculo, * = corpo, o = cauda).
int charItemOnSpace(SnakeGame *snakeGame,const int boardX, const int boardY);

// Faz uma simples verificação na quantidade de obstaculos contidos no vetor "obstacles"
// e retorna a quantidade de obstaculos preenchido no vetor.
// Ex: Eu utilizei o setBoardObstacles 5 vezes, então o jogo terá 5 obstaculos no tabuleiro, porem o vetor é estático de tamanho 100
// então a função é simples e só retorna o valor '5' de obstaculo, simples, mas para evitar repetição de código.
int amountOfObstacles(SnakeGame* SnakeGame);

// Verifica se a Snake colidiu contra algum obstaculo.
int obstacleCollision(SnakeGame* snakeGame, const Direction snakeDirection);

// Verifica se a Snake colidiu contra alguma parte do corpo.
int bodyCollision(SnakeGame* snakeGame, const Direction snakeDirection);

// Verifica se a Snake colidiu contra alguma parede.
int wallCollision(SnakeGame* snakeGame, const Direction snakeDirection);

// Verifica se existe um obstaculo na posição X / Y selecionada
int checkObstacleOnPosition(SnakeGame *snakeGame,  const int positionX, const int positionY);

// Gera um valor random para se movimentar UP/DOWN/LEFT/RIGHT
int randomWalk();

//Retorna o tamanho X do tabuleiro
int getBoardSizeY(SnakeGame* snakeGame);

// Retorna o tamanho Y do tabuleiro
int getBoardSizeX(SnakeGame* snakeGame);

// Retorna a posição X onde a minhoca está
int getSnakePositionX(SnakeGame* snakeGame);

// Retorna a posição Y onde a minhoca está
int getSnakePositionY(SnakeGame* snakeGame);

// Simula N movimentos aleatórios da minhoca.
int simuleSnake(SnakeGame* snakeGame, const int randomMovAmounts);

#endif // GAME_H_INCLUDED
