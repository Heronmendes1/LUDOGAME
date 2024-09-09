#ifndef DICE_H
#define DICE_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QPainterPath>
#include <QPointF>
#include <QRectF>
#include <QColor>
#include <QMouseEvent>
#include <QtGlobal>
#include <QtMath>

class GameWindow;

/* Esta classe representa o visual do dado na interface gráfica
 * NOTA: Este é apenas um widget para mostrar na janela e não tem nada a ver
 * com a lógica / aleatoriedade do dado */
class Dice : public QWidget {
    Q_OBJECT
    Q_PROPERTY(unsigned int value READ getValue WRITE setValue)
    Q_PROPERTY(QColor backColor READ getColor WRITE setColor)

    // Rotaciona o dado na tela (rotação medida em graus)
    Q_PROPERTY(qreal rotation READ getRotation WRITE rotate)

public:

    static const QColor COLOR_DICE_SECONDARY;

    /* O construtor
     * init_val: o valor inicial a ser mostrado no dado
     * stroke_width: largura gráfica do contorno */
    explicit Dice(QWidget *parent = nullptr, unsigned int init_val = 3);

    ~Dice();

    /* Getter e setter para a face do dado */
    unsigned int getValue();
    void setValue(unsigned int v);

    /* Getter e setter para a cor do dado */
    QColor getColor();
    void setColor(QColor c);

    /* Define o tamanho do dado
     * NOTA: Este não é o tamanho absoluto do widget, é calculado adicionando
     * um "espaço extra" a ele
     * leia os comentários na definição para mais detalhes */
    void setVisualSize(qreal size);
    qreal getVisualSize();

    // Rotaciona o dado pelos graus dados
    void rotate(int degrees);
    // Retorna a rotação atual
    int getRotation();

    /* Setter e getter para a usabilidade do dado
     * Se definido como verdadeiro, cliques são aceitos e ignorados se falso
     * NOTA: Não emitirá sinais de clique se definido como verdadeiro */
    void setEnabled(bool e);
    bool isEnabled();

signals:
    /* Emitido quando o dado é clicado */
    void clicked();

private:
    unsigned int current_value {};
    QColor backColor {};
    qreal size {};
    bool enabled {true};
    qreal rotation {0}; // Rotação em graus

    /* Aqui é onde você desenha */
    void paintEvent(QPaintEvent *e);

    void mousePressEvent(QMouseEvent *event);
};
#endif //DICE_H
