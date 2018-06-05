#ifndef EXITT_H
#define EXITT_H

#include <QDialog>

namespace Ui {
class exitt;
}

class exitt : public QDialog
{
    Q_OBJECT

public:
    explicit exitt(QWidget *parent = 0);
    ~exitt();

private:
    Ui::exitt *ui;
};

#endif // EXITT_H
