#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QString>

#include <admindialog.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_returnButton_clicked();

    void on_backButton_clicked();

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

    void on_loginButton_clicked();

    void closeAll();

    void showMain();

private:
    Ui::MainWindow *ui;
    int loginCycle;
    QStringList users;
    adminDialog *adminD;
    void setNumber(QString str);
    void getIP();
    int check_ppp_connection();

    char checkInternetMode();
    void setGsmPriority();
    void setEthernetPriority();

};

#endif // MAINWINDOW_H
