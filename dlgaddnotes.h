#ifndef DLGADDNOTES_H
#define DLGADDNOTES_H

#include <QDialog>

namespace Ui {
class DlgAddNotes;
}

class DlgAddNotes : public QDialog
{
    Q_OBJECT

public:
    explicit DlgAddNotes(QWidget *parent = 0);
    ~DlgAddNotes();

private:
    Ui::DlgAddNotes *ui;

private slots:
    void onOkClicked();
};

#endif // DLGADDNOTES_H
