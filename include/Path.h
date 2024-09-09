#ifndef PATH_H
#define PATH_H

#include <Qstring>

#include <QPoint>
#include <QVector>

/* Esta classe fornece uma maneira de saber exatamente onde no tabuleiro um peão deve ser
 * colocado. Ela converte a posição relativa de um peão em coordenadas na grade do tabuleiro.
 * NOTA: Esta classe não calcula nada, mas tem todas as coordenadas
 * pré-armazenadas como um membro estático que é usado para retornar as coordenadas. */
class Path {
public:
    static const unsigned int MAX_REL; // O valor máximo da posição relativa que um peão pode ter

    /* Retorna as coordenadas do peão na grade do tabuleiro usando sua posição relativa */
    static QPoint getAbsoluteCordinates(unsigned int rel);
    static QPoint rotatePointToRight(QPoint p);
    static QPoint rotatePointToRight(QPoint p, int times);
private:
    static QVector<QPoint> path; // Estrutura de dados para armazenar as coordenadas
    static const int TOP = 14; // Número total de células em uma linha (ou coluna)
};

#endif //Path.h
