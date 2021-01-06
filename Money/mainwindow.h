#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qgetrateonline.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    qreal yuan=0;
    qreal bisuo=0;
    qreal times=0;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //自定义槽
    void on_getRate(qreal rate);
    void on_pushButtonTrans_clicked();

    void on_doubleSpinBoxBiSuo_editingFinished();

    void on_doubleSpinBoxYuan_editingFinished();

    void on_actRateOnline_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
