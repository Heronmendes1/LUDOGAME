#include <GameWindow.h>

#include <QDebug>

#include <Game.h>
#include <Board.h>
#include <Pawn.h>
#include <PlayerColor.h>
#include <Dice.h>
#include <paint_helper.h>
#include <ValueError.h>
#include <SaveGameEngine.h>

const QColor GameWindow::COLOR_RED = QColor (249,94,95);
const QColor GameWindow::COLOR_YELLOW = QColor (255,238,103);
const QColor GameWindow::COLOR_BLUE = QColor (3,175,212);
const QColor GameWindow::COLOR_GREEN = QColor (121,189,154);
const QColor GameWindow::BG_COLOR = QColor (251,248,248);
const QColor GameWindow::STROKE_COLOR = QColor (128,128,128);

const QColor GameWindow::COLOR_RED_LIGHT = QColor (255,134,134);
const QColor GameWindow::COLOR_YELLOW_LIGHT = QColor (255,252,151);
const QColor GameWindow::COLOR_BLUE_LIGHT = QColor (102,212,224);
const QColor GameWindow::COLOR_GREEN_LIGHT = QColor (153,235,148);

GameWindow::GameWindow(unsigned int players_count) :
    mGame {new Game(players_count)},
    mBoard {mGame->getGameBoard()},
    state {ROLLING},
    mScreen (new GameScreen(this)),
    footer {new QWidget(this)},
    footerLayout {new QVBoxLayout()},
    dice {new Dice(nullptr, 6)},
    hintLabel {new QLabel()} {

    init();
}

void GameWindow::init() {

    this->setCentralWidget(this->mScreen);
    this->setWindowTitle("Ludo Z+");

    // Configurar a barra de menus
    QMenuBar *menuBar = this->menuBar();
    QMenu *gameMenu = menuBar->addMenu("&Game");
    gameMenu->addSeparator();
    QAction *exitAction = gameMenu->addAction(QIcon::fromTheme("file-save"), "&Exit");
    connect(exitAction, &QAction::triggered, this, &GameWindow::exitRequested);

    dice->setVisualSize(DICE_SIZE);
    hintLabel->setFixedHeight(CELL_SIZE);

    footer->setFixedSize(CELL_SIZE * 5, dice->height()+hintLabel->height());
    footer->move((CELL_SIZE * 15),
                 BOARD_BOUND + (this->height() / 2)); // Para centralizar à direita

    hintLabel->setWordWrap(true);
    dice->setColor(COLOR_RED_LIGHT);
    hintLabel->setFixedWidth(footer->geometry().width());
    hintLabel->setAlignment(Qt::AlignCenter);

    footerLayout->addWidget(dice, 0, Qt::AlignCenter);
    footerLayout->addWidget(hintLabel, 0, Qt::AlignCenter);
    footer->setLayout(footerLayout);

    this->mScreen->setFixedSize(
        (BOARD_BOUND * 2) + (CELL_SIZE * 15) + footer->width(), // Espaço extra para o widget de interação,
        (BOARD_BOUND * 2) + (CELL_SIZE * 15)
        );

    QObject::connect(dice, SIGNAL(clicked()), this, SLOT(rollDiceClicked()));

    // Anexar todos os peões à janela do jogo
    for(auto pawn : mBoard->getAllPawns()) {
        pawn->attatchWindow(this);
        pawn->setEnabled(false); // Desabilitar todas as visualizações de peões (botões)
    }

    updateUi();
}

GameWindow::~GameWindow() {
    delete dice;
    delete hintLabel;
    delete footerLayout;
    delete footer;
    delete mGame;

    delete mScreen;
}

QString GameWindow::getUserName(PlayerColor color) {
    // TODO: Substituir este código temporário por algo mais sensato
    switch (color) {
    case PlayerColor::RED:
        return "Player 1";
    case PlayerColor::YELLOW:
        return "Player 2";
    case PlayerColor::BLUE:
        return "Player 3";
    case PlayerColor::GREEN:
        return "Player 4";

        // Isso nunca acontecerá
    default:
        ValueError::raise_new(QString("GameWindow::getUserName(PlayerColor) : Valor inválido de PlayerColor!"));
    }
#pragma GCC diagnostic ignored "-Wreturn-type"
}
#pragma GCC diagnostic warning "-Wreturn-type"

void GameWindow::updateUi() {
    qInfo() << "GameWindow::updateUi()";

    // Definir a cor apropriada para o dado
    switch (mGame->getCurrentPlayer()) {
    case PlayerColor::RED:
        dice->setColor(COLOR_RED_LIGHT);
        break;
    case PlayerColor::YELLOW:
        dice->setColor(COLOR_YELLOW_LIGHT);
        break;
    case PlayerColor::BLUE:
        dice->setColor(COLOR_BLUE_LIGHT);
        break;
    case PlayerColor::GREEN:
        dice->setColor(COLOR_GREEN_LIGHT);
        break;
    }

    if (state == ROLLING) {
        hintLabel->setText(
            QString("%1: Role o dado!")
                .arg(getUserName(mGame->getCurrentPlayer()))
            );
        for (auto p : mBoard->getAllPawns())
            p->setEnabled(false);
        dice->setEnabled(true);

    } else if (state == MOVING) {
        hintLabel->setText(
            QString("%1: Escolha um peão para mover!")
                .arg(getUserName(mGame->getCurrentPlayer()))
            );
        dice->setEnabled(false);

    } else if (state == ANIMATING) {
        hintLabel->setText(QString(""));
        for (auto p : mBoard->getAllPawns())
            p->setEnabled(false);
        dice->setEnabled(false);

    } else
        ValueError::raise_new(QString("GameWindow::updateUi() : Valor inválido para GameWindow::state"));
}

void GameWindow::rollDiceClicked() {

    hintLabel->setText(QString(""));
    animateDiceRoll();
}
void GameWindow::animateDiceRoll() {
    state = ANIMATING;
    updateUi();

    if(diceAnimationGroup != 0)
        delete diceAnimationGroup;

    diceAnimationGroup = new QParallelAnimationGroup {};

    QPropertyAnimation *rollanimation = new QPropertyAnimation {dice, "rotation", diceAnimationGroup};
    rollanimation->setStartValue(0);
    rollanimation->setEndValue(360*8);
    rollanimation->setDuration(DICE_ANIMATION_DURATION);
    rollanimation->setEasingCurve(QEasingCurve::InOutQuad);

    QSequentialAnimationGroup *shake = new QSequentialAnimationGroup {diceAnimationGroup};

    for (int i = 0; i < 5; i++) {
        QPropertyAnimation *s = new QPropertyAnimation {dice, "pos", shake};
        s->setStartValue(QPoint(dice->x(), dice->y()));
        s->setKeyValueAt(0.25, QPoint(dice->x() - DICE_SHAKE_DISTANCE, dice->y()));
        s->setKeyValueAt(0.50, QPoint(dice->x(), dice->y()));
        s->setKeyValueAt(0.75, QPoint(dice->x() + DICE_SHAKE_DISTANCE, dice->y()));
        s->setEndValue(QPoint(dice->x(), dice->y()));
        s->setDuration(DICE_ANIMATION_DURATION / 5);
        s->setEasingCurve(QEasingCurve::InOutQuad);
        shake->addAnimation(s);
    }

    diceAnimationGroup->addAnimation(rollanimation);
    diceAnimationGroup->addAnimation(shake);
    diceAnimationGroup->start();

    connect(diceAnimationGroup, &QParallelAnimationGroup::finished,
            this,&GameWindow::diceAnimationFinished);
}

void GameWindow::diceAnimationFinished() {
    qDebug() << "GameWindow::diceAnimationFinished()";

    dice->setValue(mGame->rollDice());

    QVector<Pawn*> playables = mGame->getPlayablePawns(mGame->getLastDiceValue());

    if(playables.size() == 0) {
        mGame->changeCurrentPlayer(); // Não temos peões válidos para mover
        // Mas precisamos esperar um segundo!

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [timer, this](){
            this->updateUi();
            delete timer; // Não é necessário pará-lo, apenas exclua-o
        });

        timer->start(700);
        this->state = ROLLING;
        return; // Faz parecer que ainda estamos animando, mas é apenas uma pequena pausa entre os lançamentos de dados

    } else if(playables.size() == 1) { // Apenas um movimento disponível, preferível não perguntar
        pawnChosen(playables[0]); // Escolha automática

    } else {
        for (auto p : playables)
            p->setEnabled(true);

        state = MOVING;
    }

    updateUi();
}

void GameWindow::pawnChosen(Pawn *p) {
    qInfo() << "GameWindow::pawnChosen()";

    qDebug() << "mGame->getLastDiceValue()" << mGame->getLastDiceValue();
    qDebug() << "Pawn::getRelPosition() == " << p->getRelPosition();
    p->raise(); // Para que seja visível por cima
    movePawnVisual(p, mGame->predictRel(p, mGame->getLastDiceValue()));
}

void GameWindow::movePawnVisual(Pawn *p, int newrel) {
    qInfo() << "GameWindow::movePawnVisual()";

    if(p->isAtHome()) {
        QRect geom = painthelp::getPawnGeometry(Board::getPawnCoordinates(
            p->getColor(), newrel
            ));
        p->setGeometry(geom);
        pawnAnimationFinished(p); // Sem animação, então sem espera
        state = ROLLING;

    } else {
        // Nosso feitiço mágico.. Ha..ha..
        state = ANIMATING;
        animateVisualMovement(p, newrel);
    }

    updateUi();
}

void GameWindow::animateVisualMovement(Pawn* p, int endRel) {
    qInfo() << "GameWindow::animateVisualMovement() endRel == " << endRel;

    if(animationGroup != 0)
        delete animationGroup;

    animationGroup = new QSequentialAnimationGroup();
    int startRel = p->getRelPosition();

    for (int i = startRel + 1; i <= endRel; i++) {
        QRect iniCell = painthelp::getPawnGeometry(mBoard->getPawnCoordinates(p->getColor(), i-1));
        QRect destCell;

        if(i == Pawn::DEST)
            // Está entrando na destinação, então...
            destCell = painthelp::getPawnDestGeometry(p);
        else
            destCell = painthelp::getPawnGeometry(mBoard->getPawnCoordinates(p->getColor(), i));

        QPropertyAnimation *animation = new QPropertyAnimation (p, "geometry");
        animation->setDuration(ANIMATION_DURATION);
        animation->setStartValue(iniCell);
        animation->setEndValue(destCell);
        animationGroup->addAnimation(animation);

        animationGroup->addPause(100); // Isso parece suave
    }

    connect(animationGroup, &QSequentialAnimationGroup::finished, this, [this, p](){this->pawnAnimationFinished(p);});
    animationGroup->start();
}

void GameWindow::pawnAnimationFinished(Pawn *p) {
    if (!mGame->playMove(p, mGame->getLastDiceValue()))
        mGame->changeCurrentPlayer();

    state = ROLLING;
    updateUi();
}

void GameWindow::pawnClashed(Pawn *p) {
    p->changePosition(Pawn::HOME);
    // Esta linha é usada no construtor de Pawn e possui detalhes no comentário lá
    p->setGeometry(painthelp::getPawnHomePosGeometry(p->getColor(), ((p->getId()+1) % 4) + 1));
}

void GameWindow::exitRequested() {
    this->close(); // Isso vai automaticamente para GameWindow::closeEvent()
}

void GameWindow::closeEvent(QCloseEvent* event) {
    if(!needs_to_save)
        return;

    QMessageBox dialog {};
    dialog.setIcon(QMessageBox::Question);
    dialog.setText("Confirmar saída");
    dialog.setInformativeText("Você gostaria de salvar o jogo antes de sair?");
    dialog.addButton(QMessageBox::Discard);
    dialog.addButton(QMessageBox::Cancel);

    int ret = dialog.exec();

    switch (ret) {
    case QMessageBox::Cancel:
        event->ignore(); // Não fazer nada
        break;
    case QMessageBox::Discard:
        event->accept();
        break;
    }
}
