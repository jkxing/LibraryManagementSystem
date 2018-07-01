#ifndef PREVIEWBOOKDIALOG_H
#define PREVIEWBOOKDIALOG_H

#include <QDialog>
#include <stdafx.h>

namespace Ui {
class PreviewBookDialog;
}

class PreviewBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewBookDialog(QWidget *parent,bsoncxx::document::value v);
    ~PreviewBookDialog();

private:
    Ui::PreviewBookDialog *ui;
};

#endif // PREVIEWBOOKDIALOG_H
