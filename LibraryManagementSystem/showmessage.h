#ifndef SHOWMESSAGE_H
#define SHOWMESSAGE_H

#include <QDialog>

namespace Ui {
class ShowMessage;
}

class ShowMessage : public QDialog
{
    Q_OBJECT

public:
    explicit ShowMessage(QWidget *parent = 0);
    ~ShowMessage();

private:
    Ui::ShowMessage *ui;
};

#endif // SHOWMESSAGE_H
