#include <QApplication>
#include <QMainWindow>
#include <QDialog>
#include <QObject>
#include <QFileDialog>
#include <QPushButton>
#include <QString>
#include <QPixmap>
#include <QDebug>

#include <GameWindow.h>
#include <ValueError.h>

#include <paint_helper.h>
#include <SaveGameEngine.h>

#include "ui_welcome.h"

void loadClicked(QMainWindow &welcomeWindow) {
    GameWindow *gameWin;

    QString filename = QFileDialog::getOpenFileName(
        &welcomeWindow,
        QString("Carregar Jogo"),
        QString(),
        QString("Salvamento de jogo Ludo Z+ (*.lzs)"));

    if(filename == "")
        return; // Cancelado

    welcomeWindow.close();

    // Apenas para liberar a memória
    QObject::connect(gameWin, &GameWindow::exit, gameWin, [gameWin](){
        gameWin->close();
        delete gameWin;
        qDebug() << "Janela excluída";
    });
}

void startClick(Ui::WelcomeWindow &ui, QMainWindow &welcomeWindow) {
    GameWindow *gameWin;

    unsigned int players {};

    if (ui.radioTwo->isChecked())
        players = 2;
    else if (ui.radioThree->isChecked())
        players = 3;
    else if (ui.radioFour->isChecked())
        players = 4;

    gameWin = new GameWindow(players);
    gameWin->show();
    welcomeWindow.close();

    // Apenas para liberar a memória
    QObject::connect(gameWin, &GameWindow::exit, gameWin, [gameWin](){
        gameWin->close();
        delete gameWin;
        qDebug() << "Janela excluída";
    });
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow welcomeWindow {};
    Ui::WelcomeWindow ui {};
    ui.setupUi(&welcomeWindow);

    ui.logo->setPixmap(QPixmap(QString(":/images/ludo_z.png")).scaledToHeight(ui.logo->height()));
    welcomeWindow.show();

    QObject::connect(ui.startButton, &QPushButton::clicked, &welcomeWindow, [&ui, &welcomeWindow](){
        startClick(ui, welcomeWindow);
    });

    // Teste
    QRect cr = painthelp::getCellRect(0,0);
    qDebug() << cr.x() << cr.y();
    QRect g = painthelp::getPawnGeometry(cr);
    qDebug() << g.x() << g.y();

    try {
        return app.exec();
    } catch (ValueError *e) {
        qDebug() << e->why();
    }
}
