#include "mainwindow.h"
#include "ui_mainwindow.h"
#pragma execution_character_set("utf-8")
/*---------------------------------------------- 构造 ----------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置默认汇率
    ui->doubleSpinBoxTimes->setValue(12.6498);
    //设置提示信息
    QLabel *labInfo = new QLabel("Made by Meng");
    labInfo->setMinimumWidth(200);
    QFont font=labInfo->font();
    font.setPointSize(7);
    font.setBold(false);
    labInfo->setFont(font);
    ui->statusBar->addWidget(labInfo);
}

/*---------------------------------------------- 析构 ----------------------------------------------------------*/
MainWindow::~MainWindow()
{
    delete ui;
}

/*---------------------------------------------- 槽 获取在线汇率 ----------------------------------------------------------*/
void MainWindow::on_getRate(qreal rate)
{
    times = rate;
    ui->doubleSpinBoxTimes->setValue(times);
}

/*---------------------------------------------- 按键 转换汇率 ----------------------------------------------------------*/
void MainWindow::on_pushButtonTrans_clicked()
{
    bisuo = ui->doubleSpinBoxBiSuo->value();
    yuan= ui->doubleSpinBoxYuan->value();
    times= ui->doubleSpinBoxTimes->value();

    qreal values = yuan*times;
    ui->doubleSpinBoxBiSuo->setValue(values);
}

/*---------------------------------------------- 槽 编辑完比索数额 自动完成转换 ----------------------------------------------------------*/
void MainWindow::on_doubleSpinBoxBiSuo_editingFinished()
{
    bisuo = ui->doubleSpinBoxBiSuo->value();
    yuan= ui->doubleSpinBoxYuan->value();
    times= ui->doubleSpinBoxTimes->value();
    ui->doubleSpinBoxYuan->setValue(bisuo/times);



}

/*---------------------------------------------- 槽 编辑完人民币数额 自动完成转换 ----------------------------------------------------------*/
void MainWindow::on_doubleSpinBoxYuan_editingFinished()
{
    bisuo = ui->doubleSpinBoxBiSuo->value();
    yuan= ui->doubleSpinBoxYuan->value();
    times= ui->doubleSpinBoxTimes->value();

    qreal values = yuan*times;
    ui->doubleSpinBoxBiSuo->setValue(values);
}

/*---------------------------------------------- 动作 槽 获取在线汇率----------------------------------------------------------*/
void MainWindow::on_actRateOnline_triggered()
{
    /*--创建一个获取窗口--*/
    QGetRateOnline getRate;
    connect(&getRate,SIGNAL(getRate(qreal)),this,SLOT(on_getRate(qreal)));
    int ret = getRate.exec();
    if(QDialog::Accepted == ret)
    {
    }
}
