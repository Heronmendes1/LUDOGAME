#include <Board.h>

#include <QString>
#include <QDebug>

#include <Pawn.h>
#include <PlayerColor.h>
#include <Path.h>
#include <SaveGameEngine.h>
#include <ValueError.h>

Board::Board(unsigned int players) :
    players_count(players) {

/* Inicializa o vetor de jogadores */
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
    switch(players) {
    case 4:
        mPawns.append(new Pawn(PlayerColor::GREEN, 0));
        mPawns.append(new Pawn(PlayerColor::GREEN, 1));
        mPawns.append(new Pawn(PlayerColor::GREEN, 2));
        mPawns.append(new Pawn(PlayerColor::GREEN, 3));
    case 3:
        mPawns.append(new Pawn(PlayerColor::YELLOW, 4));
        mPawns.append(new Pawn(PlayerColor::YELLOW, 5));
        mPawns.append(new Pawn(PlayerColor::YELLOW, 6));
        mPawns.append(new Pawn(PlayerColor::YELLOW, 7));
    case 2:
        mPawns.append(new Pawn(PlayerColor::BLUE, 8));
        mPawns.append(new Pawn(PlayerColor::BLUE, 9));
        mPawns.append(new Pawn(PlayerColor::BLUE, 10));
        mPawns.append(new Pawn(PlayerColor::BLUE, 11));

        mPawns.append(new Pawn(PlayerColor::RED, 12));
        mPawns.append(new Pawn(PlayerColor::RED, 13));
        mPawns.append(new Pawn(PlayerColor::RED, 14));
        mPawns.append(new Pawn(PlayerColor::RED, 15));
        break;

    default:
        ValueError::raise_new(QString("Número inválido de jogadores. Valor esperado entre 2 e 4, mas obteve %1").arg(players));

#pragma GCC diagnostic warning "-Wimplicit-fallthrough"
    }
}

/* Destroi todos os recursos utilizados pela classe */
Board::~Board() {
    for (auto p : mPawns)
        delete p;
}

// Retorna o número de jogadores no jogo
unsigned int Board::getPlayersCount() {
    return players_count;
}

/* Retorna as coordenadas de um peão se sua cor e relpos forem iguais aos fornecidos
 * Isso não deve ser chamado quando o peão está em casa (relpos == -1) */
QPoint Board::getPawnCoordinates(PlayerColor color, unsigned int relpos) {
    qInfo() << "Board::getPawnCoordinates(PlayerColor, int) : relpos == " << relpos;

    if (relpos > Path::MAX_REL)
        ValueError::raise_new(QString("Board::getPawnCoordinates(PlayerColor, unsigned int) : Valor inválido para relpos == %1").arg(relpos));

    switch (color) {
    case PlayerColor::RED:
        return Path::getAbsoluteCordinates(relpos);
    case PlayerColor::YELLOW:
        return Path::rotatePointToRight(Path::getAbsoluteCordinates(relpos));
    case PlayerColor::BLUE:
        return Path::rotatePointToRight(Path::getAbsoluteCordinates(relpos), 2);
    case PlayerColor::GREEN:
        return Path::rotatePointToRight(Path::getAbsoluteCordinates(relpos), 3);

        // Isso nunca deve acontecer
    default:
        ValueError::raise_new(QString("Board::getPawnCoordinates(PlayerColor, int) : Cor de jogador inválida"));
    }
#pragma GCC diagnostic ignored "-Wreturn-type"
}
#pragma GCC diagnostic warning "-Wreturn-type"

/* Retorna as coordenadas do peão passado por ponteiro. O peão não precisa estar no tabuleiro
 * Isso não deve ser chamado quando o peão está em casa */
QPoint Board::getPawnCoordinates(Pawn* p) {
    return getPawnCoordinates(p->getColor(), p->getRelPosition());
}

// Retorna um vetor, que contém todos os peões no tabuleiro, incluindo os que ganharam ou estão em casa
QVector<Pawn*> Board::getAllPawns() {
    return mPawns;
}

// Retorna um vetor contendo todos os peões localizados no ponto dado no tabuleiro
QVector<Pawn*> Board::getPawnsAt(QPoint point) {
    qInfo() << "Board::getPawnsAt(QPoint)";

    QVector<Pawn*> result {};
    for (auto pawn : mPawns) {
        if(pawn->isAtHome()) // Ignora este
            continue;
        if(getPawnCoordinates(pawn).x() == point.x() && getPawnCoordinates(pawn).y() == point.y())
            result.append(pawn);
    }

    return result;
}

/* Retorna um ponteiro para o peão com o id passado. Os ids são únicos para todos os peões
 * no tabuleiro. O peão retornado deve estar no tabuleiro */
Pawn* Board::getPawnById(unsigned int id) {
    return mPawns[id];
}

/* Retorna um vetor de ponteiros para peões correspondentes à cor dada */
QVector<Pawn*> Board::getAllPawnsByColor(PlayerColor color) {
    if(color == PlayerColor::YELLOW && players_count == 2)
        ValueError::raise_new(QString("Board::getAllPawnsByColor : O jogo atual não tem a cor AMARELO"));
    if(color == PlayerColor::GREEN && players_count != 4)
        ValueError::raise_new(QString("Board::getAllPawnsByColor : O jogo atual não tem a cor VERDE"));

    QVector<Pawn*> result {};
    for (auto p : mPawns) {
        if(p->getColor() == color)
            result.append(p);
    }

    return result;
}

/* Retorna um ponteiro para o Peão identificado pela sua cor e índice (1~4)
 * Retorna nullptr se o peão não existir */
Pawn* Board::getPawn(PlayerColor color, unsigned int which) {
    if(color == PlayerColor::YELLOW && players_count == 2)
        return nullptr;
    if(color == PlayerColor::GREEN && players_count != 4)
        return nullptr;
    if(which > 4)
        return nullptr;

    int id {};
    switch (color) {
    case PlayerColor::GREEN:
        id = 0;
        break;
    case PlayerColor::YELLOW:
        id = 4;
        break;
    case PlayerColor::BLUE:
        id = 8;
        break;
    case PlayerColor::RED:
        id = 12;
        break;
    }

    return mPawns[id+which-1];
}
