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
    int AMatrixSize, BMatrixSize, CMatrixSize;
    QVector<int> AMatrix, BMatrix, DifMatrix;
    void setAMatrixLabel();
    void setBMatrixLabel();
    bool checkNumber(QString line);


private slots:

    void on_newMatrixButton_clicked();

    void on_OkButton_clicked();

    void on_itemChangeButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
