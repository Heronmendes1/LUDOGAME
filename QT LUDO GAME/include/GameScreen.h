#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <QObject>
#include <QPaintEvent>
#include <QWidget>

#include <paint_helper.h>

class GameWindow;

/* Esta classe serve como o widget central do GameWindow */
class GameScreen : public QWidget {
    Q_OBJECT;

public:
    // Constrói um novo objeto recebendo um GameWindow como pai
    explicit GameScreen(GameWindow *parent);

    virtual ~GameScreen();

private:
    // Apenas funções auxiliares
    void drawHomes(QPainter &painter);
    void drawGuidePaths(QPainter &painter);

protected:
    virtual void paintEvent(QPaintEvent*);
};

#endif
