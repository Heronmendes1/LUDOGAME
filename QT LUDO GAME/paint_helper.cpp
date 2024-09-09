#include <paint_helper.h>

#include <PlayerColor.h>
#include <Pawn.h>
#include <GameWindow.h>
#include <ValueError.h>

#include <QDebug>

namespace painthelp {

    // Retorna a área retangular absoluta na tela da célula pelas suas coordenadas x e y
    QRect getCellRect(int x, int y) {
        return QRect(
            GameWindow::BOARD_BOUND + (x * GameWindow::CELL_SIZE),
            GameWindow::BOARD_BOUND + (y * GameWindow::CELL_SIZE),
            GameWindow::CELL_SIZE, GameWindow::CELL_SIZE);
    }

    // Equivalente a getCellRect(int, int), mas usa QPoint como parâmetro em vez disso
    QRect getCellRect(QPoint cell) {
        return getCellRect(cell.x(), cell.y());
    }

    // Retorna a região retangular que cobre a casa do jogador vermelho
    QRect getRedHomeRect() {
        return QRect (
            GameWindow::BOARD_BOUND,
            GameWindow::BOARD_BOUND,
            GameWindow::CELL_SIZE * 6,
            GameWindow::CELL_SIZE * 6
        );
    }

    // Retorna a região retangular que cobre a casa do jogador amarelo
    QRect getYellowHomeRect() {
        QRect cell = getCellRect(9, 0);
        return QRect (
            cell.x(), cell.y(),
            GameWindow::CELL_SIZE * 6,
            GameWindow::CELL_SIZE * 6
        );
    }

    // Retorna a região retangular que cobre a casa do jogador azul
    QRect getBlueHomeRect() {
        QRect cell = getCellRect(9, 9);
        return QRect (
            cell.x(), cell.y(),
            GameWindow::CELL_SIZE * 6,
            GameWindow::CELL_SIZE * 6
        );
    }

    // Retorna a região retangular que cobre a casa do jogador verde
    QRect getGreenHomeRect() {
        QRect cell = getCellRect(0, 9);
        return QRect (
            cell.x(), cell.y(),
            GameWindow::CELL_SIZE * 6,
            GameWindow::CELL_SIZE * 6
        );
    }

    // Retorna a região retangular como QRect cobrindo a caixa de destino
    QRect getDestRect() {
        QRect cell = getCellRect(6, 6);
        return QRect (
            cell.x(), cell.y(),
            GameWindow::CELL_SIZE * 3,
            GameWindow::CELL_SIZE * 3
        );
    }

    // Move o canto do retângulo para o centro de si mesmo
    QRect shiftToCenter(QRect it) {
        return QRect (
            it.x() + (GameWindow::CELL_SIZE / 2),
            it.y() + (GameWindow::CELL_SIZE / 2),
            GameWindow::CELL_SIZE,
            GameWindow::CELL_SIZE
        );
    }

    // Retorna o vetor de retângulos onde círculos brancos dentro das casas devem ser desenhados
    QVector<QRect> getHomeCircleRects() {
        return QVector<QRect> {
            shiftToCenter(getCellRect(1, 1)),
            shiftToCenter(getCellRect(1, 3)),
            shiftToCenter(getCellRect(3, 1)),
            shiftToCenter(getCellRect(3, 3)),

            shiftToCenter(getCellRect(10, 1)),
            shiftToCenter(getCellRect(12, 1)),
            shiftToCenter(getCellRect(10, 3)),
            shiftToCenter(getCellRect(12, 3)),

            shiftToCenter(getCellRect(10, 10)),
            shiftToCenter(getCellRect(12, 10)),
            shiftToCenter(getCellRect(10, 12)),
            shiftToCenter(getCellRect(12, 12)),

            shiftToCenter(getCellRect(1, 10)),
            shiftToCenter(getCellRect(1, 12)),
            shiftToCenter(getCellRect(3, 10)),
            shiftToCenter(getCellRect(3, 12)),
        };
    }

    QRect getPawnHomePosGeometry(PlayerColor color, int which) {
        if(which < 1 || which > 4)
            ValueError::raise_new(QString("Valor inválido para o qual : %1").arg(which));

        QVector<QRect> v = getHomeCircleRects();
        switch (color) {
            case PlayerColor::RED:
                return getPawnGeometry(v[which-1]);
            case PlayerColor::YELLOW:
                return getPawnGeometry(v[which+3]);
            case PlayerColor::BLUE:
                return getPawnGeometry(v[which+7]);
            case PlayerColor::GREEN:
                return getPawnGeometry(v[which+11]);

            // Isso nunca deve acontecer.
            default:
                ValueError::raise_new(QString("paint_helper.cpp:getPawnHomePos : \
                Erro crítico (nenhum valor de enum caiu em um switch)"));
        }
        #pragma GCC diagnostic ignored "-Wreturn-type"
    }
    #pragma GCC diagnostic warning "-Wreturn-type"

    QRect getPawnDestGeometry(PlayerColor color) {
        QPoint cell;
        switch (color) {
            case PlayerColor::RED:
            cell = {6, 7};
            break;
            case PlayerColor::YELLOW:
            cell = {7, 6};
            break;
            case PlayerColor::BLUE:
            cell = {8, 7};
            break;
            case PlayerColor::GREEN:
            cell = {7, 8};
            break;
        }
        return getCellRect(QPoint(cell));
    }

    QRect getPawnDestGeometry(Pawn *p) {
        return getPawnDestGeometry(p->getColor());
    }

    /* Retorna a geometria que um peão deve ter de acordo com a
     * célula em que está no momento. Atualmente, tem o mesmo efeito que chamar 'getCellRect'
     * mas PODE diferir no futuro devido a modificações. O tamanho do peão é
     * tratado internamente pela própria classe Pawn */
    QRect getPawnGeometry(QRect cellRect) {
        return {
            cellRect.x(),
            cellRect.y(),
            GameWindow::CELL_SIZE, GameWindow::CELL_SIZE
        };
    }

    QRect getPawnGeometry(int x, int y) {
        return getPawnGeometry(getCellRect(x, y));
    }

    QRect getPawnGeometry(QPoint pos) {
        return getPawnGeometry(pos.x(), pos.y());
    }

    QRect getPawnGeometry(Pawn *p) {
        return getPawnGeometry(p->getPositionOnBoard());
    }

    // Retorna o ponto adjacente ao ponto dado, localizado abaixo dele
    QPoint pointBelow(QPoint p) {
        return QPoint {p.x(), p.y()+1};
    }

    // Retorna o ponto adjacente ao ponto dado, localizado à direita dele
    QPoint pointRight(QPoint p) {
        return QPoint {p.x()+1, p.y()};
    }

    // Retorna o ponto adjacente ao ponto dado, localizado acima dele
    QPoint pointAbove(QPoint p) {
        return QPoint {p.x(), p.y()-1};
    }

    // Retorna o ponto adjacente ao ponto dado, localizado à esquerda dele
    QPoint pointLeft(QPoint p) {
        return QPoint {p.x()-1, p.y()};
    }

    // Retorna o QRect na célula onde os pontos-guia devem ser desenhados
    QRect getGuiderRegion(QRect cell) {

        QPoint center = cell.center();

        qDebug() << cell.x() << cell.y();
        qDebug() << center.x() << cell.y();

        QPoint tl = {
            center.x() - ((GameWindow::GUIDER_DOT_SIZE / 2) + (GameWindow::STROKE_WIDTH * 2)),
            center.y() - ((GameWindow::GUIDER_DOT_SIZE / 2) + (GameWindow::STROKE_WIDTH * 2))
        };
        QPoint br = {
            center.x() + ((GameWindow::GUIDER_DOT_SIZE / 2) + (GameWindow::STROKE_WIDTH * 2)),
            center.y() + ((GameWindow::GUIDER_DOT_SIZE / 2) + (GameWindow::STROKE_WIDTH * 2))
        };

        qDebug() << cell.x() << cell.y();
        qDebug() << center.x() << center.y();
        return QRect {tl, br};
    }

}
