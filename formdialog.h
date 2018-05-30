#ifndef FORMDIALOG_H
#define FORMDIALOG_H

#include <QDialog>
#include <form.h>

namespace Ui {
class FormDialog;
}

class FormDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormDialog(QWidget *parent = 0, Form *_form=0);
    ~FormDialog();
    void setform(Form* _form);
private:
    Ui::FormDialog *ui;
    Form *form;
};

#endif // FORMDIALOG_H
