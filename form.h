#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <sqlops.h>
#include <qlist.h>
#include <qtextedit.h>
#include <qlabel.h>
#include <qlineedit.h>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void setup(QList<cField> *_Fields);
    QList<QTextEdit*> Text_Edit;
    QList<QLineEdit*> Line_Edit;
    QList<QLabel*> Label;

private:
    Ui::Form *ui;
    QList<cField> *Fields;
};

#endif // FORM_H
