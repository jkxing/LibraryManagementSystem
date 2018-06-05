#ifndef HELPPAGES_H
#define HELPPAGES_H

#include <QDialog>

namespace Ui {
class HelpPages;
}

class HelpPages : public QDialog
{
    Q_OBJECT

public:
    explicit HelpPages(QWidget *parent = 0);
    ~HelpPages();

private:
    Ui::HelpPages *ui;
};

#endif // HELPPAGES_H
