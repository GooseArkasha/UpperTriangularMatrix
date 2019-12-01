#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->difRezButton->setVisible(false);

    connect(ui->newMatrixButton, SIGNAL(cliced()), this, SLOT(on_newMatrixButton_clicked()));
    connect(ui->itemChangeButton, SIGNAL(cliced()), this, SLOT(on_itemChangeButton_clicked()));
    connect(ui->OkButton, SIGNAL(cliced()), this, SLOT(on_OkButton_clicked()));
    connect(ui->getValueButton, SIGNAL(cliced()), this, SLOT(on_getValueButton_clicked()));
    connect(ui->lineEntryButton, SIGNAL(cliced()), this, SLOT(on_lineEntryButton_clicked()));
    connect(ui->difMatrixButton, SIGNAL(cliced()), this, SLOT(on_difMatrixButton_clicked()));
    connect(ui->lineEntryAButton, SIGNAL(cliced()), this, SLOT(on_lineEntryAButton_clicked()));
    connect(ui->itemChangeAButton,  SIGNAL(cliced()), this, SLOT(on_itemChangeAButton_clicked()));
    connect(ui->lineEntryBButton, SIGNAL(cliced()), this, SLOT(on_lineEntryBButton_clicked()));
    connect(ui->itemChangeBButton,  SIGNAL(cliced()), this, SLOT(on_itemChangeBButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


//Функции обновления лейблов с матрицами
void MainWindow::setAMatrixLabel()
{
    ui->AMatrixlabel->clear();

    QString temp;
    int num;

    for(int i = 1; i <= AMatrixSize;i++)
    {
        for(int j = 1; j <= AMatrixSize;j++)
        {
            if(i <= j)
            {
                temp = ui->AMatrixlabel->text();
                num = (i - 1) * AMatrixSize + j - (i - 1) * i / 2 - 1;
                ui->AMatrixlabel->setText(temp + "\t" + QString::number(AMatrixVector[num]));
            }
            else
            {
                temp = ui->AMatrixlabel->text();
                ui->AMatrixlabel->setText(temp + "\t" + "0");
            }
        }
        temp = ui->AMatrixlabel->text();
        ui->AMatrixlabel->setText(temp + "\n\n");
    }
}

void MainWindow::setBMatrixLabel()
{
    ui->BMatrixLabel->clear();
    QString temp;
    int num;

    for(int i = 1; i <= BMatrixSize;i++)
    {
        for(int j = 1; j <= BMatrixSize;j++)
        {
            if(i <= j)
            {
                temp = ui->BMatrixLabel->text();
                num = (i - 1) * BMatrixSize + j - (i - 1) * i / 2 - 1;
                ui->BMatrixLabel->setText(temp + "\t" + QString::number(BMatrixVector[num]));
            }
            else
            {
                temp = ui->BMatrixLabel->text();
                ui->BMatrixLabel->setText(temp + "\t" + "0");
            }
        }
        temp = ui->BMatrixLabel->text();
        ui->BMatrixLabel->setText(temp + "\n\n");
    }
}

void MainWindow::setDifMatrixLabel()
{
    ui->label->clear();
    QString temp;
    int num;

    for(int i = 1; i <= AMatrixSize;i++)
    {
        for(int j = 1; j <= AMatrixSize;j++)
        {
            if(i <= j)
            {
                temp = ui->label->text();
                num = (i - 1) * AMatrixSize + j - (i - 1) * i / 2 - 1;
                ui->label->setText(temp + "\t" + QString::number(DifMatrixVector[num]));
            }
            else
            {
                temp = ui->label->text();
                ui->label->setText(temp + "\t" + "0");
            }
        }
        temp = ui->label->text();
        ui->label->setText(temp + "\n\n");
    }
}

//Функции для проверки введенных данных
bool MainWindow::checkNumber(QString line)
{
    if(line[0] == '-')
    {
        if(line.size() > 5)
            return false;
        for(int i = 1; i < line.size(); i++)
        {
            if(line[i] < '0' || line[i] > '9')
                return false;
        }
    }
    else
    {
        if(line.size() > 4)
            return false;
        for(int i = 0; i < line.size(); i++)
        {
            if(line[i] < '0' || line[i] > '9')
                return false;
        }
    }

    return true;
}

bool MainWindow::checkLine(QString line, int i)
{
    int n = 0, mp = 1, first = 0, last;
    for(int k = 0; k < line.size(); k++)
    {
        if((line[k] < '0' || line[k] > '9') && line[k] != ' ' && line[k] != '-')
            return false;
        if(line[k] == '-')
            mp = -1;
        if(line[k] == ' ')
        {
            n++;
            if(n > AMatrixSize - i + 1)
                return false;
            last = k - 1;
            if(mp == -1)
            {
                if(last - first +1 > 5)
                    return false;
            }
            else
            {
                if(last - first +1 > 4)
                    return false;
            }
            first = k + 1;
            mp = 1;
        }
    }
    n++;
    if(n > AMatrixSize - i + 1)
        return false;
    last = line.size() - 1;
    if(mp == -1)
    {
        if(last - first +1 > 5)
            return false;
    }
    else
    {
        if(last - first +1 > 4)
            return false;
    }
    return true;
}


//Слоты
void MainWindow::on_newMatrixButton_clicked()
{
    //Настройка меню
    ui->matrixChangeMenue->setEnabled(false);
    ui->lineEdit->setEnabled(false);

    ui->difRezButton->setVisible(false);
    ui->equalButton->setVisible(false);

    ui->difMatrixButton->setDown(true);
    ui->equalMatrixButton->setDown(true);
    ui->saveMatrixButton->setDown(true);
    ui->downloadMatrixButton->setDown(true);

    ui->sizeSpinBox_1->setEnabled(true);
    ui->sizeSpinBox_1->setValue(1);
    ui->sizeSpinBox_1->setMaximum(5);

    ui->sizeSpinBox_2->setEnabled(false);

    ui->AMatrixlabel->setText("0");
    ui->BMatrixLabel->setText("");

    numMenue = 1;
}

void MainWindow::on_itemChangeButton_clicked()
{
    ui->matrixChangeMenue->setEnabled(false);
    ui->lineEdit->setEnabled(true);

    ui->difRezButton->setVisible(false);
    ui->equalButton->setVisible(false);

    ui->difMatrixButton->setDown(true);
    ui->equalMatrixButton->setDown(true);
    ui->saveMatrixButton->setDown(true);
    ui->downloadMatrixButton->setDown(true);

    ui->sizeSpinBox_1->setEnabled(true);
    ui->sizeSpinBox_1->setValue(1);
    ui->sizeSpinBox_1->setMaximum(AMatrixSize);

    ui->sizeSpinBox_2->setEnabled(true);
    ui->sizeSpinBox_2->setValue(1);
    ui->sizeSpinBox_2->setMaximum(AMatrixSize);

    ui->lineEdit->setText("0");

    ui->BMatrixLabel->setText("");
    setAMatrixLabel();

    numMenue = 2;
}

void MainWindow::on_getValueButton_clicked()
{
    ui->matrixChangeMenue->setEnabled(false);
    ui->lineEdit->setEnabled(true);

    ui->difRezButton->setVisible(false);
    ui->equalButton->setVisible(false);

    ui->difMatrixButton->setDown(true);
    ui->equalMatrixButton->setDown(true);
    ui->saveMatrixButton->setDown(true);
    ui->downloadMatrixButton->setDown(true);

    ui->sizeSpinBox_1->setEnabled(true);
    ui->sizeSpinBox_1->setValue(1);
    ui->sizeSpinBox_1->setMaximum(AMatrixSize);

    ui->sizeSpinBox_2->setEnabled(true);
    ui->sizeSpinBox_2->setValue(1);
    ui->sizeSpinBox_2->setMaximum(AMatrixSize);

    ui->lineEdit->setText("");
    ui->BMatrixLabel->setText("");
    setAMatrixLabel();

    numMenue = 3;
}

void MainWindow::on_lineEntryButton_clicked()
{
    ui->matrixChangeMenue->setEnabled(false);
    ui->lineEdit->setEnabled(true);

    ui->difRezButton->setVisible(false);
    ui->equalButton->setVisible(false);

    ui->difMatrixButton->setDown(true);
    ui->equalMatrixButton->setDown(true);
    ui->saveMatrixButton->setDown(true);
    ui->downloadMatrixButton->setDown(true);

    ui->sizeSpinBox_1->setEnabled(true);
    ui->sizeSpinBox_1->setValue(1);
    ui->sizeSpinBox_1->setMaximum(AMatrixSize);

    ui->sizeSpinBox_2->setEnabled(false);

    ui->lineEdit->setText("");
    ui->BMatrixLabel->setText("");
    setAMatrixLabel();

    numMenue = 4;
}

void MainWindow::on_difMatrixButton_clicked()
{
    ui->sizeSpinBox_1->setEnabled(false);
    ui->sizeSpinBox_2->setEnabled(false);
    ui->lineEdit->setEnabled(false);

    ui->difRezButton->setVisible(true);
    ui->equalButton->setVisible(false);

    ui->matrixChangeMenue->setEnabled(true);
    ui->getValueButton->setDown(true);
    ui->itemChangeButton->setDown(true);
    ui->lineEntryButton->setDown(true);
    ui->newMatrixButton->setDown(true);

    difFlag = true;
    equalFlag = false;

    if(BMatrixVector.size() == 0 || BMatrixVector.size() != AMatrixVector.size())
    {
        BMatrixSize = AMatrixSize;
        int sizeVector = (1 + BMatrixSize) * BMatrixSize / 2;

        for(int i = 0; i < sizeVector; i++) {
           BMatrixVector.push_back(0);
        }
    }
    setAMatrixLabel();
    setBMatrixLabel();

    numMenue = 5;
}

void MainWindow::on_lineEntryAButton_clicked()
{
    if(difFlag == true)
        ui->difRezButton->setVisible(true);
    else
        ui->difRezButton->setVisible(false);

    if(equalFlag == true)
        ui->equalButton->setVisible(true);
    else
        ui->equalButton->setVisible(false);

    ui->sizeSpinBox_1->setEnabled(true);
    ui->sizeSpinBox_1->setValue(1);
    ui->sizeSpinBox_1->setMaximum(AMatrixSize);

    ui->sizeSpinBox_2->setEnabled(false);

    ui->lineEdit->setEnabled(true);

    ui->lineEdit->setText("");
    numMenue = 4;
}

void MainWindow::on_itemChangeAButton_clicked()
{
    if(difFlag == true)
        ui->difRezButton->setVisible(true);
    else
        ui->difRezButton->setVisible(false);

    if(equalFlag == true)
        ui->equalButton->setVisible(true);
    else
        ui->equalButton->setVisible(false);

    ui->sizeSpinBox_1->setEnabled(true);
    ui->sizeSpinBox_1->setValue(1);
    ui->sizeSpinBox_1->setMaximum(AMatrixSize);

    ui->sizeSpinBox_2->setEnabled(true);
    ui->sizeSpinBox_2->setValue(1);
    ui->sizeSpinBox_2->setMaximum(AMatrixSize);

    ui->lineEdit->setText("0");

    ui->lineEdit->setEnabled(true);
    numMenue = 2;
}

void MainWindow::on_lineEntryBButton_clicked()
{
    if(difFlag == true)
            ui->difRezButton->setVisible(true);
        else
            ui->difRezButton->setVisible(false);

    if(equalFlag == true)
        ui->equalButton->setVisible(true);
    else
        ui->equalButton->setVisible(false);

        ui->sizeSpinBox_1->setEnabled(true);
        ui->sizeSpinBox_1->setValue(1);
        ui->sizeSpinBox_1->setMaximum(BMatrixSize);

        ui->sizeSpinBox_2->setEnabled(false);

        ui->lineEdit->setEnabled(true);

        ui->lineEdit->setText("");
        numMenue = 6;
}

void MainWindow::on_itemChangeBButton_clicked()
{
    if(difFlag == true)
        ui->difRezButton->setVisible(true);
    else
        ui->difRezButton->setVisible(false);

    if(equalFlag == true)
        ui->equalButton->setVisible(true);
    else
        ui->equalButton->setVisible(false);

    ui->sizeSpinBox_1->setEnabled(true);
    ui->sizeSpinBox_1->setValue(1);
    ui->sizeSpinBox_1->setMaximum(BMatrixSize);

    ui->sizeSpinBox_2->setEnabled(true);
    ui->sizeSpinBox_2->setValue(1);
    ui->sizeSpinBox_2->setMaximum(BMatrixSize);

    ui->lineEdit->setText("0");

    ui->lineEdit->setEnabled(true);
    numMenue = 7;
}

void MainWindow::on_difRezButton_clicked()
{
    DifMatrixVector.clear();
    for(int i = 0; i < AMatrixVector.size(); i++)
        DifMatrixVector.push_back(AMatrixVector[i] - BMatrixVector[i]);
    setDifMatrixLabel();
}

void MainWindow::on_equalMatrixButton_clicked()
{
    ui->sizeSpinBox_1->setEnabled(false);
    ui->sizeSpinBox_2->setEnabled(false);
    ui->lineEdit->setEnabled(false);

    ui->difRezButton->setVisible(false);
    ui->equalButton->setVisible(true);

    ui->matrixChangeMenue->setEnabled(true);
    ui->getValueButton->setDown(true);
    ui->itemChangeButton->setDown(true);
    ui->lineEntryButton->setDown(true);
    ui->newMatrixButton->setDown(true);

    difFlag = false;
    equalFlag = true;

    if(BMatrixVector.size() == 0 || BMatrixVector.size() != AMatrixVector.size())
    {
        BMatrixSize = AMatrixSize;
        int sizeVector = (1 + BMatrixSize) * BMatrixSize / 2;

        for(int i = 0; i < sizeVector; i++) {
           BMatrixVector.push_back(0);
        }
    }
    setAMatrixLabel();
    setBMatrixLabel();

    numMenue = 5;
}

void MainWindow::on_equalButton_clicked()
{
    bool flag = false;
    int i = 0;
    while(i < AMatrixVector.size())
    {
        if(AMatrixVector[i] != BMatrixVector[i])
        {
            flag = true;
            break;
        }
        i++;
    }
    if(flag == true)
        ui->label->setText("Не равны");
    else
        ui->label->setText("Равны");
}


void MainWindow::on_OkButton_clicked()
{
    if(numMenue == 1)
    {
        AMatrixVector.clear();
        AMatrixSize = ui->sizeSpinBox_1->value();
        int sizeVector = (1 + AMatrixSize) * AMatrixSize / 2;

        for(int i = 0; i < sizeVector; i++) {
           AMatrixVector.push_back(0);
        }

        setAMatrixLabel();
    }
    if(numMenue == 2)
    {
        QString line = ui->lineEdit->text();
        if(checkNumber(line))
        {
            int i = ui->sizeSpinBox_1->value();
            int j = ui->sizeSpinBox_2->value();
            if(i <= j)
            {
                int num = (i - 1) * AMatrixSize + j - (i - 1) * i / 2 - 1;
                AMatrixVector[num] = line.toInt();
                setAMatrixLabel();
            }
            else
            {
                ui->lineEdit->setText("Выбраный элемент не доступен");
            }

        }
        else
        {
            ui->lineEdit->setText("Введите число(-10 000;10 000)");
        }
    }

    if(numMenue == 3)
    {
        int i = ui->sizeSpinBox_1->value();
        int j = ui->sizeSpinBox_2->value();
        if(i <= j)
        {
            int num = (i - 1) * AMatrixSize + j - (i - 1) * i / 2 - 1;
            QString temp = QString::number(AMatrixVector[num]);
            ui->lineEdit->setText(temp);
        }
        else
        {
            ui->lineEdit->setText("0");
        }

    }

    if(numMenue == 4)
    {
        int i = ui->sizeSpinBox_1->value();
        QString line = ui->lineEdit->text();
        if(checkLine(line, i))
        {
           int first = 0, last, j = i, num;
           QString temp;
           for(int k = 0; k < line.size(); k++)
           {
               if(line[k] == " ")
               {
                   last = k - 1;
                   temp = line.mid(first, last - first + 1);
                   num = (i - 1) * AMatrixSize + j - (i - 1) * i / 2 - 1;
                   AMatrixVector[num] = temp.toInt();
                   j++;
                   first = k + 1;
               }
           }

           last = line.size() - 1;
           temp = line.mid(first, last - first + 1);
           num = (i - 1) * AMatrixSize + j - (i - 1) * i / 2 - 1;
           AMatrixVector[num] = temp.toInt();
           setAMatrixLabel();
        }
        else
        {
            ui->lineEdit->setText("Ошибка");
        }
    }

    if(numMenue == 6)
    {
        int i = ui->sizeSpinBox_1->value();
        QString line = ui->lineEdit->text();
        if(checkLine(line, i))
        {
           int first = 0, last, j = i, num;
           QString temp;
           for(int k = 0; k < line.size(); k++)
           {
               if(line[k] == " ")
               {
                   last = k - 1;
                   temp = line.mid(first, last - first + 1);
                   num = (i - 1) * BMatrixSize + j - (i - 1) * i / 2 - 1;
                   BMatrixVector[num] = temp.toInt();
                   j++;
                   first = k + 1;
               }
           }

           last = line.size() - 1;
           temp = line.mid(first, last - first + 1);
           num = (i - 1) * BMatrixSize + j - (i - 1) * i / 2 - 1;
           BMatrixVector[num] = temp.toInt();
           setBMatrixLabel();
        }
        else
        {
            ui->lineEdit->setText("Ошибка");
        }
    }

    if(numMenue == 7)
    {
        QString line = ui->lineEdit->text();
        if(checkNumber(line))
        {
            int i = ui->sizeSpinBox_1->value();
            int j = ui->sizeSpinBox_2->value();
            if(i <= j)
            {
                int num = (i - 1) * BMatrixSize + j - (i - 1) * i / 2 - 1;
                BMatrixVector[num] = line.toInt();
                setBMatrixLabel();
            }
            else
            {
                ui->lineEdit->setText("Выбраный элемент не доступен");
            }

        }
        else
        {
            ui->lineEdit->setText("Введите число(-10 000;10 000)");
        }
    }
}






