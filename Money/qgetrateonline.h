#ifndef QGETRATEONLINE_H
#define QGETRATEONLINE_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QTextCodec>

namespace Ui {
class QGetRateOnline;
}

class QGetRateOnline : public QDialog
{
    Q_OBJECT

    QNetworkAccessManager networkManager;
    QNetworkReply *reply;
public:
    explicit QGetRateOnline(QWidget *parent = 0);
    ~QGetRateOnline();

private slots:
    /*--自定义槽--*/
    void on_readyRead();
    void on_btnGetRate_clicked();

    void on_btnDefaultUrl_clicked();
signals:
    void getRate(qreal rate);


private:
    Ui::QGetRateOnline *ui;
};

#endif // QGETRATEONLINE_H
