#ifndef PAWN_H
#define PAWN_H

#include <QPoint>
#include <QRect>
#include <QWidget>
#include <QPaintEvent>
#include <QString>
#include <QPropertyAnimation>

class Board;
class GameWindow;
enum class PlayerColor;

class Pawn : public QWidget {
    Q_OBJECT
    Q_PROPERTY(qreal glow READ getGlow WRITE setGlow) // Proporção de brilho (variando de 0 a 1)
public:
    // Valor da posição inicial (home) para a posição relativa do peão
    static const int HOME = -1;
    // Valor da posição de destino (dest) para a posição relativa do peão
    static const int DEST = 56;

    // Duração de um ciclo de brilho (expandir e contrair)
    static const int GLOW_DURATION = 700;

    // Escala de brilho (na faixa de 0 a 1)
    static const qreal GLOW_SCALE;

    // Construtor: Não deve ser usado externamente (fora da biblioteca)
    // board - Ponteiro para o tabuleiro que irá conter o peão
    // color - cor do peão, id - id único para identificação
    Pawn(PlayerColor color, int id);

    // Destruidor virtual
    virtual ~Pawn();

    /* Anexa uma GameWindow ao peão, fazendo com que ele seja exibido na GameWindow
     * Isso também conecta os sinais do peão com os slots da GameWindow para callbacks
     * NOTA: Apenas uma janela pode (e normalmente, deve) ser anexada por vez! */
    void attatchWindow(GameWindow *w);

    /* Retorna a posição relativa do peão variando de -1 a 58 (HOME ATÉ DEST) */
    int getRelPosition();

    // Retorna a cor usada pelo peão
    PlayerColor getColor();

    // Retorna o id único do peão passado no momento da construção
    unsigned int getId();

    // Retorna o índice específico da cor para o peão (referido como 'which' em muitas funções)
    unsigned int getIndex();

    /* Calcula e retorna a posição atual do peão no tabuleiro
     * com base em sua posição relativa como um QPoint */
    QPoint getPositionOnBoard();

    // Retorna verdadeiro se o peão estiver em casa
    bool isAtHome();

    // Retorna verdadeiro se o peão tiver chegado ao destino
    bool hasReachedDestination();

    // Define a posição relativa do peão para a dada posição
    void changePosition(int rel);

    // Move o peão para frente pelos passos dados
    void moveForward(int steps);

    /* Retorna o peão à sua posição inicial, reiniciando seu percurso
     * clash : é devido a um choque? */
    void goBackHome(bool clash = true);

    /* Setter para a propriedade de brilho. (consulte a declaração da propriedade de brilho) */
    void setGlow(qreal glow);

    /* Getter para a propriedade de brilho */
    qreal getGlow();

    /* Define a usabilidade do peão. (ou seja, se ele pode ser clicado)
     * Se definido como verdadeiro, também inicia uma animação de brilho que é interrompida
     * quando a função é chamada com um valor falso */
    void setEnabled(bool enabled);

signals:
    /* Acionado quando o elemento visual do peão é clicado. Isso
     * deve acontecer quando o jogador escolhe seu peão para mover.
     * É dever da GameWindow receptora mover sua posição adequadamente
     * e chamar Game::playMove() depois disso */
    void visualClicked(Pawn* p);

    /* Acionado quando este peão é atingido por outro e precisa voltar para casa */
    void clashed(Pawn *p);

private:
    PlayerColor mColor {};
    unsigned int mId {};
    int mPos {}; // A posição relativa
    qreal mGlow {0}; // Proporção atual do brilho

    QPropertyAnimation *glowEffect {nullptr}; // Animação de brilho

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
};

#endif //Pawn.h
