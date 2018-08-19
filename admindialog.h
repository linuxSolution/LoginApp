#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QString>
#include "dns_dialog.h"

namespace Ui {
class adminDialog;
}

class adminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adminDialog(QWidget *parent = 0);
    ~adminDialog();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void on_internet_Mode_currentIndexChanged(int index);

    void on_oneButton_clicked();

    void on_twoButton_clicked();

    void on_threeButton_clicked();

    void on_fourButton_clicked();

    void on_fiveButton_clicked();

    void on_sixButton_clicked();

    void on_sevenButton_clicked();

    void on_eightButton_clicked();

    void on_nineButton_clicked();

    void on_zeroButton_clicked();

    void on_ethernet_Mode_currentIndexChanged(int index);

    void on_periodButton_clicked();

    void on_backButton_clicked();

    void on_returnButton_clicked();

    void on_closeButton_clicked();

    void on_dnsLockbutton_clicked();

private:
    Ui::adminDialog *ui;
    Dns_dialog *dnsdialog;
    QStringList ethernetMode;
    QStringList internetMode;
    void setNumber(QString str);
    int focus;

    char checkInternetMode();
    void setEtherenetPriority();
    void setGsmPriority();

    void showReboot();

signals:
    void closeAll();
    void showMain();
};

#endif // ADMINDIALOG_H
