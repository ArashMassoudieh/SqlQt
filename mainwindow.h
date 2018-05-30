#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QDockWidget* dock(int i);
    void status_write(QString s);

public slots:
    void openCSV();
    void OnSqlCommandsAction();
    void OnAddRow();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
