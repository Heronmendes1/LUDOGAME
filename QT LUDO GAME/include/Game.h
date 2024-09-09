#ifndef GAME_H
#define GAME_H

#include <QRandomGenerator>
#include <QVector>

class Pawn;
class Board;
class SaveGameEngine;
enum class PlayerColor;

class Game {

public:
    /* Esta é uma constante de configuração.
     * Valor verdadeiro significa que o peão precisa de um seis para sair de casa.
     * TODO: Isso deve estar sob controle do usuário */
    static constexpr bool SIX_FOR_HOME = true;

    /* players: número de jogadores no jogo */
    Game(unsigned int players);

    /* Cria uma nova instância e copia dados do estado salvo */
    Game(SaveGameEngine *save);

    /* Copia dados para o estado salvo */
    void serializeInto(SaveGameEngine *save);

    /* Deleta e libera TODOS os recursos utilizados */
    virtual ~Game();

    /* Retorna um int entre 1 e 6 que pode ser usado como dado */
    int rollDice();

    /* Retorna um ponteiro para a instância do GameBoard usada */
    Board* getGameBoard();

    /* Retorna um QVector de Peões que podem se mover pelo valor da face do dado passado */
    QVector<Pawn*> getPlayablePawns(int diceFace);

    /* Retorna a posição relativa prevista do peão se ele se mover pelo
     * valor do dado dado */
    unsigned int predictRel(Pawn* p, unsigned int diceFace);

    /* Move o peão pelo valor da face do dado, lida as consequências adicionais
     * (como, outro Peão sendo derrubado) e permite que o próximo jogador jogue se o dado não
     * mostrar um 6.

     * NOTA: Isso deve ser chamado após você ter atualizado a IU usando
     * o valor do dado (veja: Game::rollDice())

     * Retorna: verdadeiro se o jogador tiver outra chance de jogar o dado (por
     * obter um 6 no dado ou por acertar outro peão), falso caso contrário */
    bool playMove(Pawn* pawn, int diceFace);

    /* Retorna o handle de PlayerColor do jogador que deve jogar a vez atual */
    PlayerColor getCurrentPlayer();

    /* Passa a vez para o próximo jogador */
    void changeCurrentPlayer();

    /* Retorna o vetor indicando a sequência de turnos dos jogadores */
    QVector<PlayerColor> getCurrentPlayerSequence();

    /* Obtém o último valor rolado pelo dado */
    unsigned int getLastDiceValue();

    /* Retorna verdadeiro se o jogador dado terminou de jogar, ou seja, quando todos os seus peões
     * chegaram ao destino */
    bool playerHasFinished(PlayerColor p);

    /* Retorna verdadeiro quando o jogo terminou, ou seja, quando apenas um jogador resta para
     * colocar todos os peões em casa */
    bool isFinished();

private:
    unsigned int players_count {}; // Número de jogadores no jogo
    Board* mBoard {}; // Tabuleiro do jogo
    QVector<PlayerColor> *currentSequence {}; // Sequência de Turnos dos Jogadores
    unsigned int current {}; // Índice do jogador atual na sequência
    unsigned int lastDiceValue {}; // Armazena o valor do dado rolado na última vez
    QRandomGenerator random {}; // Para randomização do dado
};

#endif // GAME_H
