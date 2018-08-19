#include "admindialog.h"
#include "ui_admindialog.h"

#include <QDebug>

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QThread>
#include <QString>
#include <QDataStream>
#include <iostream>

#include <QProcess>
#include <QDir>

#include "dns_dialog.h"

using namespace std;

adminDialog::adminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminDialog)
{
    ui->setupUi(this);

    ethernetMode<<"DHCP"<<"Static"<<"Default_IP";
    internetMode<<"GSM"<<"Ethernet";

    ui->ethernet_Mode->addItems(ethernetMode);
    ui->ethernet_Mode->setCurrentIndex(0);

    ui->internet_Mode->addItems(internetMode);
    //ui->internet_Mode->setCurrentIndex(0);

    char c = checkInternetMode();

           if(c == 'E'){

               qDebug()<<"Ethernet Mode is Selected";
               ui->internet_Mode->setCurrentIndex(1);

           }else if(c == 'P'){
               qDebug()<<"GSM Mode is Selected";
               ui->internet_Mode->setCurrentIndex(0);

        }

    if(ui->internet_Mode->currentIndex() == 0){

        ui->ethernet_Mode->setEnabled(false);
        ui->ipTextEdit->setEnabled(false);
        ui->subnetTextEdit->setEnabled(false);
        ui->dnsTextEdit->setEnabled(false);
        ui->gatewayTextEdit->setEnabled(false);
    }
    focus =0;

    ui->dnsLockbutton->hide();
}

adminDialog::~adminDialog()
{
    delete ui;
}

void adminDialog::on_saveButton_clicked()
{
    // ethrenet Mode is selected
    if(ui->internet_Mode->currentIndex() == 1){

        // BuildRoot Path
        QString osPath ="/etc/network/interfaces";
        QString localPath = "/home/launchApps/Iconfig/IP_Config/interfaces";

    // Dhcp is enabled
    if(ui->ethernet_Mode->currentIndex() == 0){

        if (!QFile::exists(localPath))
        {
            QMessageBox msgBox;
            msgBox.setText("local Dhcp config file does not exit");
            msgBox.exec();

            return ;
        }

        if (QFile::exists(osPath))
        {
            QFile::remove(osPath);
        }else{
            QMessageBox msgBox;
            msgBox.setText("Os config file does not exit");
            msgBox.exec();

            return;
        }

         //Src __ Dest
        QFile::copy(localPath, osPath);

//        QString ipath ="/etc/network/interfaces";

//        QFile file(ipath);

//        if(!file.open(QIODevice::WriteOnly))
//        {
//            qDebug() << " Could not open the file for reading";
//            return ;
//        }

//        QTextStream out(&file);

//        out <<"auto eth0"<<endl
//            <<"iface eth0 inet dhcp";


    setEtherenetPriority();

//    QMessageBox msgBox;
//    msgBox.setText("Sytem will reboot in 30 sec");
//    msgBox.exec();

    system("reboot");

    }else if (ui->ethernet_Mode->currentIndex() == 1){ // static is enabled

        QString ipath ="/etc/network/interfaces";

        QFile file(ipath);

        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug() << " Could not open the file for reading";
            return ;
        }

        QTextStream out(&file);

        out <<"auto eth0"<<endl
            <<"iface eth0 inet static"<<endl
            <<"address "<<ui->ipTextEdit->toPlainText()<<endl
            <<"gateway "+ui->gatewayTextEdit->toPlainText()<<endl
            <<"netmask "<<ui->subnetTextEdit->toPlainText()<<endl
            <<"dns-nameservers "+ui->dnsTextEdit->toPlainText();

        file.flush();
        file.close();

        setEtherenetPriority();

//        QMessageBox msgBox;
//        msgBox.setText("Sytem will reboot in 30 sec");
//        msgBox.exec();

          system("reboot");



    }else { // Default Static IP

        QString ipath ="/etc/network/interfaces";

        QFile file(ipath);

        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug() << " Could not open the file for reading";
            return ;
        }

        QTextStream out(&file);

        out <<"auto eth0"<<endl
            <<"iface eth0 inet static"<<endl
            <<"address "<<"172.24.2.100"<<endl
            <<"gateway "<<"172.24.7.254"<<endl
            <<"netmask "<<"255.255.0.0"<<endl
            <<"dns-nameservers "<<"8.8.8.8 8.8.4.4";

        file.flush();
        file.close();

        setEtherenetPriority();

//        QMessageBox msgBox;
//        msgBox.setText("Sytem will reboot in 30 sec");
//        msgBox.exec();

          system("reboot");


    }


    }else{ // Gsm Mode is selected

        setGsmPriority();

//        QMessageBox msgBox;
//        msgBox.setText("Sytem will reboot in 30 sec");
//        msgBox.exec();

         system("reboot");


    }

}

void adminDialog::on_cancelButton_clicked()
{
    emit showMain();
    this->close();
}

void adminDialog::on_internet_Mode_currentIndexChanged(int index)
{
    ui->ethernet_Mode->setCurrentIndex(0);

    if(ui->internet_Mode->currentIndex() == 0){

        ui->ethernet_Mode->setEnabled(false);
        ui->ipTextEdit->setEnabled(false);
        ui->subnetTextEdit->setEnabled(false);

    }else {
        ui->ethernet_Mode->setEnabled(true);

    }
}

void adminDialog::setNumber(QString str){

    if(ui->ethernet_Mode->currentIndex() == 1){

        if(focus == 0){

            QString pstr = ui->ipTextEdit->toPlainText();

            pstr += str;

            ui->ipTextEdit->document()->setPlainText(pstr);

        }else if(focus == 1) {

            QString pstr = ui->subnetTextEdit->toPlainText();

            pstr += str;

            ui->subnetTextEdit->document()->setPlainText(pstr);

        }else if(focus == 2) {

            QString pstr = ui->gatewayTextEdit->toPlainText();

            pstr += str;

            ui->gatewayTextEdit->document()->setPlainText(pstr);

        }else if(focus == 3) {

            QString pstr = ui->dnsTextEdit->toPlainText();

            pstr += str;

            ui->dnsTextEdit->document()->setPlainText(pstr);

        }

    }


}

void adminDialog::on_oneButton_clicked()
{
    setNumber("1");
}

void adminDialog::on_twoButton_clicked()
{
    setNumber("2");
}

void adminDialog::on_threeButton_clicked()
{
    setNumber("3");
}

void adminDialog::on_fourButton_clicked()
{
    setNumber("4");
}

void adminDialog::on_fiveButton_clicked()
{
    setNumber("5");
}

void adminDialog::on_sixButton_clicked()
{
    setNumber("6");
}

void adminDialog::on_sevenButton_clicked()
{
    setNumber("7");
}

void adminDialog::on_eightButton_clicked()
{
    setNumber("8");
}

void adminDialog::on_nineButton_clicked()
{
    setNumber("9");
}

void adminDialog::on_zeroButton_clicked()
{
    setNumber("0");
}

void adminDialog::on_periodButton_clicked()
{
      setNumber(".");
}

void adminDialog::on_ethernet_Mode_currentIndexChanged(int index)
{
        if(ui->ethernet_Mode->currentIndex() == 1){


            ui->ipTextEdit->setEnabled(true);
            ui->subnetTextEdit->setEnabled(true);
            ui->gatewayTextEdit->setEnabled(true);
            ui->dnsTextEdit->setEnabled(true);
            focus = 0;

        }else{
            ui->ipTextEdit->setEnabled(false);
            ui->subnetTextEdit->setEnabled(false);
            ui->gatewayTextEdit->setEnabled(false);
            ui->dnsTextEdit->setEnabled(false);
        }
}

void adminDialog::on_backButton_clicked()
{
    if(focus == 0){

        if(ui->ipTextEdit->toPlainText().count() >0){

            QString str = ui->ipTextEdit->toPlainText();
            str.chop(1);
           ui->ipTextEdit->document()->setPlainText(str);

        }else{
            qDebug()<<"Not ok";
        }
    }else if (focus == 1){

        if(ui->subnetTextEdit->toPlainText().count() >0){

            QString str = ui->subnetTextEdit->toPlainText();
            str.chop(1);
           ui->subnetTextEdit->document()->setPlainText(str);

        }else{
            qDebug()<<"Not ok";
        }
    }else if (focus == 2){

        if(ui->gatewayTextEdit->toPlainText().count() >0){

            QString str = ui->gatewayTextEdit->toPlainText();
            str.chop(1);
           ui->gatewayTextEdit->document()->setPlainText(str);

        }else{
            qDebug()<<"Not ok";
        }
    }else if (focus == 3){

        if(ui->dnsTextEdit->toPlainText().count() >0){

            QString str = ui->dnsTextEdit->toPlainText();
            str.chop(1);
           ui->dnsTextEdit->document()->setPlainText(str);

        }else{
            qDebug()<<"Not ok";
        }
    }

}

void adminDialog::on_returnButton_clicked()
{
    if(focus == 0){

        focus  = 1;


       // ui->subnetTextEdit->setFocus();

    }else if (focus == 1){

        focus = 2;

        //ui->ipTextEdit->setFocus();
    }else if(focus == 2){

        focus = 3;
        //ui->gatewayTextEdit->setFocus();

    }else if(focus == 3){

        focus = 0;
       // ui->dnsTextEdit->setFocus();
    }
}

void adminDialog::on_closeButton_clicked()
{
    this->close();
    emit closeAll();
}

void adminDialog::setEtherenetPriority(){

    QString ipath ="/home/launchApps/Iconfig/IP_Config/internetMode.txt";

    QFile file(ipath);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << " Could not open the file for reading";
        return ;
    }

    QTextStream out(&file);
    out <<"E";
    file.flush();
    file.close();
    //system("reboot");

}

void adminDialog::setGsmPriority(){

    QString ipath ="/home/launchApps/Iconfig/IP_Config/internetMode.txt";

    QFile file(ipath);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << " Could not open the file for reading";
        return ;
    }

    QTextStream out(&file);
    out <<"P";
    file.flush();
    file.close();
    //system("reboot");
}

void adminDialog::on_dnsLockbutton_clicked()
{
    dnsdialog = new Dns_dialog(this);
    dnsdialog->show();
}


char adminDialog::checkInternetMode(){

    QString ipath ="/home/launchApps/Iconfig/IP_Config/internetMode.txt";

    QFile file(ipath);

    if (!file.open(QIODevice::ReadOnly)) {
        return -1;
    }


    char c;
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_6);

    in.readRawData(&c,1);

    return c;

}

//Not used
void adminDialog::showReboot(){

    QProcess::startDetached("/home/launchApps/Apps/RebootApp/rR1/Reboot -platform xcb");
}
