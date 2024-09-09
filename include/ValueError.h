#ifndef VALUE_ERROR_H
#define VALUE_ERROR_H

#include <QException>
#include <QString>

/* Esta classe define a exceção que é lançada em todo o projeto quando um
 * valor usado ou passado para uma função é inválido */
class ValueError : public QException {
public:

    //Construtor padrão - razão vazia
    ValueError();

    void raise() const override;
    ValueError *clone() const override;

    /*Constrói um novo ValueError com a razão passada*/
    ValueError(QString why);

    /*Constrói e lança um novo ValueError*/
    static void raise_new(QString why);

    /*Retorna a razão da exceção*/
    QString why();
private:
    QString reason {};
};

#endif //VALUE_ERROR_H
