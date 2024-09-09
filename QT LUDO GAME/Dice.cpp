#include <Dice.h>

#include <QString>
#include <QDebug>

#include <GameWindow.h>
#include <ValueError.h>

const QColor Dice::COLOR_DICE_SECONDARY = QColor (57, 60, 63);

Dice::Dice(QWidget *parent, unsigned int init_val) :
    QWidget(parent), current_value(init_val) {}

Dice::~Dice() {}

unsigned int Dice::getValue() {
    return current_value;
}

void Dice::setValue(unsigned int v) {
    if(v < 1 || v > 6)
        ValueError::raise_new(QString("Dice::setValue : Valor inválido para a face do dado : ")
                                  .arg(v));

    current_value = v;
    this->repaint();
}

QColor Dice::getColor() {
    return backColor;
}

void Dice::setColor(QColor c) {
    this->backColor = c;
    this->repaint();
}

void Dice::setVisualSize(qreal size) {
    /* Deixando um espaço extra para que possamos girar o dado corretamente
     * Isso é importante porque um quadrado precisa de espaço extra para caber quando
     * é girado */
    qreal abs_size = 2 * (qSqrt((size*size)/2));
    this->setFixedSize(abs_size, abs_size);
    this->size = size;
}

qreal Dice::getVisualSize() {
    return size;
}

void Dice::rotate(int graus) {
    this->rotation = graus;
    repaint();
}

int Dice::getRotation() {
    return this->rotation;
}

void Dice::setEnabled(bool e) {
    this->enabled = e;
}

bool Dice::isEnabled() {
    return this->enabled;
}

void Dice::mousePressEvent(QMouseEvent*) {
    if(!this->isEnabled())
        return;

    emit clicked();
}

void Dice::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Aplica a rotação primeiro
    // Traduza corretamente para que o nosso "espaço extra" não atrapalhe o desenho
    // Veja: comentários em Dice::setDiceSize
    painter.translate(this->width() / 2, this->height() / 2);
    painter.rotate(rotation);

    /* Traduza para o canto direito, mantendo metade do "espaço extra" como
     * espaço de margem em todos os lados */
    painter.translate(this->width() / -2 + (this->width() - this->getVisualSize()) / 2,
                      this->height() / -2 + (this->height() - this->getVisualSize())/2);

    QPainterPath outline {};

    /* Espaço extra (metade da largura da borda) deixado para o contorno,
     * isso causa melhorias na renderização gráfica */
    outline.addRoundedRect(
        QRectF(
            QPointF(
                GameWindow::STROKE_WIDTH / 2.0,
                GameWindow::STROKE_WIDTH / 2.0),
            QPointF(
                this->getVisualSize() - (GameWindow::STROKE_WIDTH / 2.0),
                this->getVisualSize() - (GameWindow::STROKE_WIDTH / 2.0)
                )),
        10, 10
        );

    QPen pen(COLOR_DICE_SECONDARY, GameWindow::STROKE_WIDTH);

    painter.setPen(pen);
    painter.setBrush(backColor);
    painter.drawPath(outline);

    // Desenha os números no dado
    painter.setBrush(COLOR_DICE_SECONDARY);
    qreal dot_rad = this->getVisualSize() / 12.0; // Raio dos pontos
    QPointF center = QPointF {getVisualSize() / 2, getVisualSize() / 2};

    QPointF left = QPointF {center.x() - (dot_rad * 3), center.y()};
    QPointF right = QPointF {center.x() + (dot_rad * 3), center.y()};

    QPointF top = QPointF {center.x(), center.y() - (dot_rad * 3)};
    QPointF bottom = QPointF {center.x(), center.y() + (dot_rad * 3)};

    QPointF topleft = QPointF {left.x(), top.y()};
    QPointF topright = QPointF {right.x(), top.y()};

    QPointF bottomleft = QPointF {left.x(), bottom.y()};
    QPointF bottomright = QPointF {right.x(), bottom.y()};

    switch (current_value) {
    case 1:
        painter.drawEllipse(center, dot_rad, dot_rad);
        break;

    case 2:
        painter.drawEllipse(left, dot_rad, dot_rad);
        painter.drawEllipse(right, dot_rad, dot_rad);
        break;

    case 3:
        painter.drawEllipse(center, dot_rad, dot_rad);
        painter.drawEllipse(left, dot_rad, dot_rad);
        painter.drawEllipse(right, dot_rad, dot_rad);
        break;

    case 4:
        painter.drawEllipse(topleft, dot_rad, dot_rad);
        painter.drawEllipse(topright, dot_rad, dot_rad);
        painter.drawEllipse(bottomleft, dot_rad, dot_rad);
        painter.drawEllipse(bottomright, dot_rad, dot_rad);
        break;

    case 5:
        painter.drawEllipse(center, dot_rad, dot_rad);
        painter.drawEllipse(topleft, dot_rad, dot_rad);
        painter.drawEllipse(topright, dot_rad, dot_rad);
        painter.drawEllipse(bottomleft, dot_rad, dot_rad);
        painter.drawEllipse(bottomright, dot_rad, dot_rad);
        break;

    case 6:
        painter.drawEllipse(top, dot_rad, dot_rad);
        painter.drawEllipse(bottom, dot_rad, dot_rad);
        painter.drawEllipse(topleft, dot_rad, dot_rad);
        painter.drawEllipse(topright, dot_rad, dot_rad);
        painter.drawEllipse(bottomleft, dot_rad, dot_rad);
        painter.drawEllipse(bottomright, dot_rad, dot_rad);
        break;

    default:
        break;
    }
}
