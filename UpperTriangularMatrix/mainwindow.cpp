#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->newMatrixButton, SIGNAL(cliced()), this, SLOT(on_newMatrixButton_clicked()));
    connect(ui->itemChangeButton, SIGNAL(cliced()), this, SLOT(on_itemChangeButton_clicked()));
    connect(ui->OkButton, SIGNAL(cliced()), this, SLOT(on_OkButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAMatrixLabel()
{
    ui->AMatrixlabel->clear();
    QString temp;
    int num;

    for(int i = 1; i <= AMatrixSize;i++) {
        for(int j = 1; j <= AMatrixSize;j++) {
            if(i <= j) {
                temp = ui->AMatrixlabel->text();
                num = (i - 1) * AMatrixSize + j - (i - 1) * i / 2 - 1;
                ui->AMatrixlabel->setText(temp + "\t" + QString::number(AMatrix[num]));
            } else {
                temp = ui->AMatrixlabel->text();
                ui->AMatrixlabel->setText(temp + "\t" + "0");
            }
        }
        temp = ui->AMatrixlabel->text();
        ui->AMatrixlabel->setText(temp + "\n");
    }
}

void MainWindow::setBMatrixLabel()
{
    ui->BMatrixLabel->clear();
    QString temp;
    int num;

    for(int i = 1; i <= BMatrixSize;i++) {
        for(int j = 1; j <= BMatrixSize;j++) {
            if(i <= j) {
                temp = ui->BMatrixLabel->text();
                num = (i - 1) * BMatrixSize + j - (i - 1) * i / 2 - 1;
                ui->BMatrixLabel->setText(temp + "\t" + QString::number(BMatrix[num]));
            } else {
                temp = ui->BMatrixLabel->text();
                ui->BMatrixLabel->setText(temp + "\t" + "0");
            }
        }
        temp = ui->BMatrixLabel->text();
        ui->BMatrixLabel->setText(temp + "\n");
    }
}

bool MainWindow::checkNumber(QString line)
{
    if(line[0] == '-') {
        if(line.size() > 5)
            return false;
        for(int i = 1; i < line.size(); i++) {
            if(line[i] < '0' || line[i] > '9')
                return false;
        }
    } else {
        if(line.size() > 4)
            return false;
        for(int i = 0; i < line.size(); i++) {
            if(line[i] < '0' || line[i] > '9')
                return false;
        }
    }

    return true;
}


void MainWindow::on_newMatrixButton_clicked()
{
    ui->sizeSpinBox_1->setVisible(true);
    ui->sizeSpinBox_2->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->AMatrixlabel->setText("0");
    ui->sizeSpinBox_1->setValue(1);
    ui->sizeSpinBox_1->setMaximum(5);

    numMenue = 1;
}

void MainWindow::on_itemChangeButton_clicked()
{
    ui->sizeSpinBox_1->setVisible(true);
    ui->sizeSpinBox_2->setVisible(true);
    ui->lineEdit->setVisible(true);
    setAMatrixLabel();
    ui->sizeSpinBox_1->setValue(1);
    ui->sizeSpinBox_1->setMaximum(AMatrixSize);
    ui->sizeSpinBox_2->setValue(1);
    ui->sizeSpinBox_2->setMaximum(AMatrixSize);
    ui->lineEdit->setText("0");
    numMenue = 2;
}

void MainWindow::on_OkButton_clicked()
{
    if(numMenue == 1) {
        AMatrix.clear();
        AMatrixSize = ui->sizeSpinBox_1->value();
        BMatrixSize = AMatrixSize;
        int sizeVector = (1 + AMatrixSize) * AMatrixSize / 2;

        for(int i = 0; i < sizeVector; i++) {
           AMatrix.push_back(7);
        }

        setAMatrixLabel();
    }
    if(numMenue == 2) {
        QString line = ui->lineEdit->text();
        if(checkNumber(line)) {
            int i = ui->sizeSpinBox_1->value();
            int j = ui->sizeSpinBox_2->value();
            int num = (i - 1) * AMatrixSize + j - (i - 1) * i / 2 - 1;

            AMatrix[num] = line.toInt();

            setAMatrixLabel();
        } else {
            ui->lineEdit->setText("Введите число(-10 000;10 000)");
        }

    }
}


