#include <Game.h>

#include <QDebug>

#include <Board.h>
#include <Pawn.h>
#include <PlayerColor.h>
#include <ValueError.h>

Game::Game(unsigned int players) :
    players_count(players), mBoard(new Board{players}),
    currentSequence(new QVector<PlayerColor>{}), current(0),
    random(QRandomGenerator::securelySeeded()) {

    switch (players) {
    case 2:
        currentSequence->push_back(PlayerColor::RED);
        currentSequence->push_back(PlayerColor::BLUE); // Para que os peões fiquem em cantos opostos
        break;
    case 3:
        currentSequence->push_back(PlayerColor::RED);
        currentSequence->push_back(PlayerColor::YELLOW);
        currentSequence->push_back(PlayerColor::BLUE);
        break;
    case 4:
        currentSequence->push_back(PlayerColor::RED);
        currentSequence->push_back(PlayerColor::YELLOW);
        currentSequence->push_back(PlayerColor::BLUE);
        currentSequence->push_back(PlayerColor::GREEN);
        break;
    }
}

Game::~Game() {
    delete currentSequence;
    delete mBoard;
}

int Game::rollDice() {
    // TODO:: Gerar um número aleatório entre 1 e 6

    lastDiceValue = random.bounded(1, 7);
    return lastDiceValue;
}

PlayerColor Game::getCurrentPlayer() {
    return (*currentSequence)[current];
}

Board* Game::getGameBoard() {
    return mBoard;
}

QVector<Pawn*> Game::getPlayablePawns(int diceFace) {
    if (diceFace < 1 || diceFace > 6)
        ValueError::raise_new(QString("Valor de dado inválido: %1").arg(diceFace));

    QVector<Pawn*> result;
    QVector<Pawn*> pawns = mBoard->getAllPawns();

    for (auto p : pawns) {
        if (p->getColor() != getCurrentPlayer())
            continue;
        if (p->isAtHome() && diceFace != 6 && SIX_FOR_HOME)
            continue;
        if (p->hasReachedDestination())
            continue;
        if (p->getRelPosition() + diceFace > Pawn::DEST)
            continue;

        result.append(p);
    }

    return result;
}

unsigned int Game::predictRel(Pawn* pawn, unsigned int diceFace) {
    qInfo() << "Game::predictRel(Pawn*, int)";

    if (pawn->isAtHome() && diceFace != 6 && SIX_FOR_HOME)
        ValueError::raise_new(QString("Movimento inválido"));
    if (pawn->getRelPosition() + diceFace > Pawn::DEST)
        ValueError::raise_new(QString("Movimento inválido"));

    if (pawn->isAtHome()) // Apenas sair de casa por um passo
        return pawn->getRelPosition() + 1;
    else
        return pawn->getRelPosition() + diceFace;
}

bool Game::playMove(Pawn* pawn, int diceFace) {
    qInfo() << "Game::playMove(Pawn*, int)";

    // Define o número pelo qual vamos mover
    unsigned int futureRel {Game::predictRel(pawn, diceFace)};

    // O jogador terá outra vez?
    bool re_turn = diceFace == 6;

    // Peão que foi atingido por este ao se mover
    Pawn* toClash {nullptr};

    // Este peão não poderia ter colidido com ninguém, pois já chegou ao destino
    if (futureRel != Pawn::DEST) {

        // Se houver apenas um peão neste novo local, envie-o de volta para casa
        // Isso deve ser feito antes de mover o peão atual
        QVector<Pawn*> pawnsThere = mBoard->getPawnsAt(
            mBoard->getPawnCoordinates(
                pawn->getColor(),
                futureRel // Nossa futura posição
                )
            );

        if (pawnsThere.size() == 1 && pawnsThere[0]->getColor() != pawn->getColor()) {
            toClash = pawnsThere[0];
            re_turn = true;
        }

    } else {
        // Mas realmente ganhamos outra vez
        re_turn = true;
    }

    // Agora podemos mover o peão
    pawn->changePosition(futureRel);

    // E enviar o peão colidido de volta para casa
    if (toClash != nullptr)
        toClash->goBackHome();

    return re_turn;
}

void Game::changeCurrentPlayer() {
    if (current >= (unsigned int)(currentSequence->size()) - 1) {
        current = 0;
        return;
    }

    current++;
}

QVector<PlayerColor> Game::getCurrentPlayerSequence() {
    return *currentSequence;
}

unsigned int Game::getLastDiceValue() {
    return lastDiceValue;
}

bool Game::playerHasFinished(PlayerColor c) {
    for (auto p : mBoard->getAllPawnsByColor(c))
        if (!p->hasReachedDestination())
            return false;

    return true;
}

bool Game::isFinished() {
    unsigned int i = 0;
    for (auto c : *currentSequence)
        if (playerHasFinished(c))
            i++;

    return i >= players_count - 1;
}
