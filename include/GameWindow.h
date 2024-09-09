#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QString>
#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QVector>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QTimer>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>

#include <GameScreen.h>

class Game;
class Board;
class Pawn;
class Dice;
enum class PlayerColor;

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    /* Define o estado do jogo.
     * ROLLING : o dado precisa ser lançado.
     * MOVING : o jogador precisa escolher um peão para mover.
     * ANIMATING : Uma animação está em execução. */
    enum GameState {ROLLING, MOVING, ANIMATING};

    // Cores para cada jogador, fundo e contorno
    static const QColor COLOR_RED;
    static const QColor COLOR_YELLOW;
    static const QColor COLOR_BLUE;
    static const QColor COLOR_GREEN;
    static const QColor BG_COLOR;
    static const QColor STROKE_COLOR;

    // Cor para o fundo do dado
    static const QColor COLOR_RED_LIGHT;
    static const QColor COLOR_YELLOW_LIGHT;
    static const QColor COLOR_BLUE_LIGHT;
    static const QColor COLOR_GREEN_LIGHT;

    // Espaço a deixar em todos os lados, além do tabuleiro
    static const int BOARD_BOUND = 5;

    // Largura e altura de cada célula
    static const int CELL_SIZE = 40;

    // Tamanho do ponto guia
    static const int GUIDER_DOT_SIZE = 4;

    // Tamanho visual do peão
    static const int PAWN_SIZE = 25;

    // Tamanho do dado
    static const int DICE_SIZE = 50;

    // Tamanho do contorno
    static const int STROKE_WIDTH = 2;

    // Tempo para animar um movimento de peão de um único passo
    static const int ANIMATION_DURATION = 120;

    // Tempo para a animação do lançamento do dado
    static const int DICE_ANIMATION_DURATION = 800;

    // Distância que o dado é sacudido
    static const int DICE_SHAKE_DISTANCE = 25;

    // Construtor e destruidor
    explicit GameWindow(unsigned int players_count);

    ~GameWindow();

    /* Retorna uma representação em string amigável do nome do usuário */
    QString getUserName(PlayerColor color);

    /* Atualiza adequadamente a interface de usuário de acordo com o valor de `state` e o jogador atual */
    void updateUi();

    /* Cria um diálogo para salvar o arquivo
     * Retorna: verdadeiro se o jogo foi salvo, falso caso contrário */
    bool saveGame();

signals:
    /* Chamado quando o jogo termina, após completar todos os eventos de fechamento.
     * A memória mantida por esta janela deve ser liberada aqui */
    void exit();

public slots:
    /* Chamado quando um peão colidiu e precisa voltar para casa
    * peão: o peão que deve ser enviado para casa */
    void pawnClashed(Pawn *pawn);

    /* Chamado quando um visual de peão é clicado e habilitado */
    void pawnChosen(Pawn *p);

    /* Chamado quando o visual do dado é clicado */
    void rollDiceClicked();

private slots:

    /* Chamado quando a animação do visual do peão é concluída
     * p: o Peão que foi animado */
    void pawnAnimationFinished(Pawn*);

    /* Chamado quando a animação do lançamento do dado é concluída */
    void diceAnimationFinished();

    /* Chamado quando o usuário solicita sair do jogo através da barra de menu */
    void exitRequested();

private:
    unsigned int players_count {}; // Número de jogadores
    Game *mGame {}; // jogo atual
    Board *mBoard {};
    GameState state {}; // Estado do jogo

    GameScreen *mScreen {}; // Widget central

    QWidget *footer {}; // Widget para interação do usuário
    QVBoxLayout *footerLayout {}; // Layout para o rodapé
    Dice *dice; // Controle do dado
    QLabel *hintLabel {}; // Texto de dica
    QSequentialAnimationGroup *animationGroup {}; // Animação do peão
    QParallelAnimationGroup *diceAnimationGroup {}; // Animação do lançamento do dado

    bool needs_to_save {false}; // O usuário tem alterações não salvas se isto for verdadeiro

    // Inicializa a janela. Função de conveniência. Chamado apenas nos construtores e uma vez
    void init();

    /* Faz o visual do peão se mover */
    void movePawnVisual(Pawn *p, int oldpos);

    // Move os visuais dos peões através de uma animação
    void animateVisualMovement(Pawn* p, int startRel);

    // Anima o dado antes de mostrar seu valor
    void animateDiceRoll();

protected:
    void closeEvent(QCloseEvent*);
};
#endif //GameWindow.h
