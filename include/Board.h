#ifndef BOARD_H
#define BOARD_H

#include <string>

#include <QVector>
#include <QPoint>

class Pawn;
class SaveGameEngine;
enum class PlayerColor;

class Board {
public:

    // Construtor. Os jogadores - número de jogadores no jogo
    Board(unsigned int players);

    // Cria uma nova instância e copia os dados do estado salvo
    Board(SaveGameEngine *save);

    // Copia os dados para o estado salvo
    void serializeInto(SaveGameEngine *save);

    // Destruidor virtual
    virtual ~Board();

    // Retorna o número de jogadores no jogo
    unsigned int getPlayersCount();

    // Retorna as coordenadas de um peão se sua cor e relpos forem iguais ao fornecido
    static QPoint getPawnCoordinates(PlayerColor color, unsigned int relpos);

    // Retorna as coordenadas do peão passado por ponteiro. O peão não precisa estar no tabuleiro
    static QPoint getPawnCoordinates(Pawn* p);

    // Retorna um vetor que contém todos os Peões no tabuleiro, incluindo os que foram ganhos ou estão em casa
    QVector<Pawn*> getAllPawns();

    // Retorna um vetor contendo todos os Peões localizados no ponto dado no tabuleiro
    QVector<Pawn*> getPawnsAt(QPoint point);

    // Retorna um ponteiro para o peão com o id passado. Os ids são únicos para todos os peões
    // no tabuleiro. O peão retornado deve estar no tabuleiro
    Pawn* getPawnById(unsigned int id);

    // Retorna um vetor de ponteiros de peões correspondentes à cor dada
    QVector<Pawn*> getAllPawnsByColor(PlayerColor color);

    // Retorna um ponteiro para o Peão identificado pela sua cor e índice (1~4)
    // Retorna nullptr se o peão não existir
    Pawn* getPawn(PlayerColor color, unsigned int which);

private:
    unsigned int players_count {}; // Contador de jogadores
    QVector<Pawn*> mPawns {}; // Vetor contendo os ponteiros dos peões
};

#endif // BOARD_H
