// Fornece funções auxiliares para o paintEvent do GameWindow
#ifndef paint_helper_h
#define paint_helper_h

#include <QVector>
#include <QString>
#include <QRect>
#include <QPoint>

class Pawn;
enum class PlayerColor;

/* Este namespace fornece funções auxiliares para desenhar o tabuleiro e os peões.
 * A maioria dos argumentos das funções refere-se a `posições relativas` dos elementos.
 * (por relativa, quero dizer não se referindo a pontos na tela, mas sim uma célula no tabuleiro
 * sendo um ponto e a posição dos peões sendo esses pontos)
 * Isso não deve ser confundido com pontos na tela, que são retornados
 * pela maioria dessas funções. Pense neste namespace como um meio de converter a geometria `relativa`
 * em geometria `de tela` */
namespace painthelp {

// Retorna a área retangular absoluta na tela da célula pelas suas coordenadas x e y
QRect getCellRect(int x, int y);

// Equivalente a getCellRect(int, int), mas usa QPoint como parâmetro em vez disso
QRect getCellRect(QPoint cell);

// Retorna a região retangular que cobre a casa do jogador vermelho
QRect getRedHomeRect();

// Retorna a região retangular que cobre a casa do jogador amarelo
QRect getYellowHomeRect();

// Retorna a região retangular que cobre a casa do jogador azul
QRect getBlueHomeRect();

// Retorna a região retangular que cobre a casa do jogador verde
QRect getGreenHomeRect();

// Retorna a região retangular como QRect cobrindo a caixa de destino
QRect getDestRect();

/* Move o canto do retângulo para o centro de si mesmo
     * NOTA: O parâmetro passado para esta função refere-se à geometria da tela */
QRect shiftToCenter(QRect it);

// Retorna o vetor de retângulos onde círculos brancos dentro das casas devem ser desenhados
QVector<QRect> getHomeCircleRects();

// Retorna a geometria dos peões quando estão em casa
QRect getPawnHomePosGeometry(PlayerColor color, int which);

// Retorna a geometria do peão quando está em casa
QRect getPawnDestGeometry(PlayerColor);
QRect getPawnDestGeometry(Pawn*);

// Retorna a geometria visual de um peão se colocado em 'cellRect'
QRect getPawnGeometry(QRect cellRect);

// Retorna a geometria visual de um peão se colocado na célula (célula dada como x e y)
QRect getPawnGeometry(int x, int y);

// Retorna a geometria visual de um peão se colocado na célula (célula dada como ponto no tabuleiro)
QRect getPawnGeometry(QPoint);

// Retorna a geometria do peão dado
QRect getPawnGeometry(Pawn *p);

// Retorna o ponto adjacente ao ponto dado, localizado abaixo dele
QPoint pointBelow(QPoint p);

// Retorna o ponto adjacente ao ponto dado, localizado à direita dele
QPoint pointRight(QPoint p);

// Retorna o ponto adjacente ao ponto dado, localizado acima dele
QPoint pointAbove(QPoint p);

// Retorna o ponto adjacente ao ponto dado, localizado à esquerda dele
QPoint pointLeft(QPoint p);

// Retorna o QRect na célula onde os pontos-guia devem ser desenhados
QRect getGuiderRegion(QRect cell);
}

#endif
