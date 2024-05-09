#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();



private slots:
    void on_dkck_clicked();

    void on_gbck_clicked();

    void on_read_receive();

    void on_fsck_clicked();

    void on_qkck_clicked();

private:
    Ui::Widget *ui;
    QSerialPort *serialPort;
};
#endif // WIDGET_H
