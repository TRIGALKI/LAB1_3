#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "queue.h"
#include "qstring.h"
#include "ingrident.h"
#include "string.h"
#include <string>
#include "QFileDialog"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    btnRefresh();
}
void MainWindow::btnRefresh()
{
    if (Queue0.getLength()!=0)
    {
        ui->saveToFileButton->setEnabled(true);
        ui->deletReceptButton->setEnabled(true);
        ui->deletNodeButton->setEnabled(true);
        ui->tab_2->setEnabled(true);
    }
    else
    {
        ui->saveToFileButton->setEnabled(false);
        ui->deletReceptButton->setEnabled(false);
        ui->deletNodeButton->setEnabled(false);
        ui->tab_2->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showChanges()
{
    QString text;
    Queue::Iterator iterator;
    for(iterator=Queue0.begin(); iterator!=nullptr; iterator++)
    {
        if ((*iterator)->whichClass()==true)
        {
            const Ingrident *p = static_cast<const Ingrident*>(*iterator);
            text=text +"\nИНГРИДЕНТ >>----------|>" "\nName :" +
                    QString::fromStdString(p->getName()) + "\nValue :" +
                    QString::fromStdString(p->getValue()) + "\nNumber :" +
                    QString::number(p->getNumber());
        }
        else
        {
            const ActionIngrident *a =
                    static_cast<const ActionIngrident*>(*iterator);
            text=text +"\nДЕЙСТВИЕ @##||==========>"+"\nAction :" +
                    QString::fromStdString(a->getAction()) +
                    "\nDuration :" + QString::number(a->getDur());
        }
    }
    ui->textBrowser->setText(text);
}



void MainWindow::on_createActionIngridentButton_clicked()
{
    std::string action;
    float dur;
    double dur1;
    action=ui->lineEdit_3->text().toStdString();
    dur1=ui->doubleSpinBox->value();
    dur=float(dur1);
    ActionIngrident objName(action,dur);
    Queue0.addNode(objName);
    showChanges();
    btnRefresh();
}

void MainWindow::on_createIngridentButton_clicked()
{
    std::string name,value,action;
    int number;
    name = ui->lineEdit->text().toStdString();
    value = ui->lineEdit_2->text().toStdString();
    number = ui->spinBox->text().toInt();
    Ingrident objName(name,value,number);
    Queue0.addNode(objName);
    showChanges();
    btnRefresh();
}

void MainWindow::on_LoadFromFileButton_clicked()
{
    QString Qfilestr = QFileDialog::getOpenFileName();;
    string filestr = Qfilestr.toStdString();
    Queue0.readFromFile(filestr);
    showChanges();
    btnRefresh();
}

void MainWindow::on_saveToFileButton_clicked()
{
    QString Qfilestr = QFileDialog::getOpenFileName();;
    string filestr = Qfilestr.toStdString();
    Queue0.writeInFile(filestr);
}

void MainWindow::on_deletNodeButton_clicked()
{
    Queue0.deleteNode();
    showChanges();
    btnRefresh();
}

void MainWindow::on_deletReceptButton_clicked()
{
    Queue0.deleteQueue();
    QString text;
    text = "Пепел и пыль";
    ui->textBrowser->setText(text);
    btnRefresh();
}
