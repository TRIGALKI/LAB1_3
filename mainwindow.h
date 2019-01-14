#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "queue.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();*/
    void showChanges();
    void btnRefresh();

    void on_createActionIngridentButton_clicked();

    void on_createIngridentButton_clicked();

    void on_LoadFromFileButton_clicked();

    void on_saveToFileButton_clicked();

    void on_deletNodeButton_clicked();

    void on_deletReceptButton_clicked();

private:
    Ui::MainWindow *ui;
    Queue Queue0;
    //Queue Queue1;
};

#endif // MAINWINDOW_H
