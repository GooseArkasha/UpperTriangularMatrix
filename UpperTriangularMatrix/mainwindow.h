#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int numMenue = 0;
    bool difFlag = false, equalFlag = false;
    QVector<int> AMatrixVector, BMatrixVector, DifMatrixVector; //Хранятся элементы матрицы, расположенные не ниже главной диаголнали
    int AMatrixSize = 0, BMatrixSize = 0, DifMatrixSize = 0;    //Данное должно обновляться только при создании новой матрицы


    //Функции обновления лейблов с матрицами
    void setAMatrixLabel();

    void setBMatrixLabel();

    void setDifMatrixLabel();

    //Функции проверки введенных данных
    bool checkNumber(QString line);         //Используется для проверки при введении 1 числа

    bool checkLine(QString line, int i);    //Используется для проверки при введении строки


private slots:

    void on_newMatrixButton_clicked();

    void on_OkButton_clicked();

    void on_itemChangeButton_clicked();

    void on_getValueButton_clicked();

    void on_lineEntryButton_clicked();

    void on_difMatrixButton_clicked();

    void on_equalMatrixButton_clicked();

    void on_lineEntryAButton_clicked();

    void on_itemChangeAButton_clicked();

    void on_lineEntryBButton_clicked();

    void on_itemChangeBButton_clicked();

    void on_difRezButton_clicked();

    void on_equalButton_clicked();

    void on_saveMatrixButton_clicked();

    void on_downloadMatrixButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
