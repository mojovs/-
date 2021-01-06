#include "qgetrateonline.h"

#include "ui_qgetrateonline.h"
#pragma execution_character_set("utf-8")
/*------------------------------------------ 构造 ----------------------------------------*/
QGetRateOnline::QGetRateOnline(QWidget *parent) : QDialog(parent), ui(new Ui::QGetRateOnline)
{
    ui->setupUi(this);
    /*--设置默认网址--*/
    ui->lineEditUrl->setText(QString("https://cn.exchange-rates.org/Rate/CNY/ARS").trimmed());
    /*--设置LCD样式--*/
    ui->lcdNumber->setStyleSheet("border: 1px solid green;color:green;background:silver");
}

/*------------------------------------------ 析构 ----------------------------------------*/
QGetRateOnline::~QGetRateOnline() { delete ui; }
/*------------------------------------------槽 开始从reply里面读取信息 ----------------------------------------*/
void QGetRateOnline::on_readyRead()
{
    QString strRate;
    /*-- 读取内容到数据里面 --*/
    QString data = reply->readAll();
    /*-- 显示文本框 --*/
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("---开始获取网络信息，请等待---");
    ui->plainTextEdit->appendPlainText("---开始读取---");
    ui->plainTextEdit->appendHtml(data);
    /*--开始处理文本，截取汇率--*/
    int len1 = data.indexOf(QString("人民币="));
    int len2 = data.indexOf(QString("阿根廷比索截"));
    if (-1 != len1 && -1 != len2) {
        strRate = data.mid(len1 + 4, len2 - len1 - 5);
        /*--设置lcd屏幕--*/
        ui->lcdNumber->display(strRate);
        /*--发送汇率--*/
        emit getRate(strRate.toDouble());
    }
}

/*------------------------------------------ 按键 获取在线汇率地址 ----------------------------------------*/
void QGetRateOnline::on_btnGetRate_clicked()
{
    /*--获取地址--*/
    QString strUrl = ui->lineEditUrl->text().trimmed();
    if (strUrl.isEmpty()) {
        QMessageBox::information(this, "错误", "输入为空");
        return;
    }
    QUrl urlSpec = QUrl::fromUserInput(strUrl);
    if (!urlSpec.isValid()) {
        QMessageBox::information(this, "错误", QString("无效URL:%1,错误信息 %2").arg(strUrl, urlSpec.errorString()));
        return;
    }

    /*--获取reply--*/
    reply = networkManager.get(QNetworkRequest(urlSpec));

    /*--函数绑定--*/
    connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}
/*------------------------------------------ 按键 缺省URL地址 ----------------------------------------*/
void QGetRateOnline::on_btnDefaultUrl_clicked() { ui->lineEditUrl->setText(QString("https://cn.exchange-rates.org/Rate/CNY/ARS").trimmed()); }
