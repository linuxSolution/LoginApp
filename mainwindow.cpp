#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QProcess>
#include <QDir>

#include <QDebug>

#include <QFile>
#include <QTextStream>
#include <QThread>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <QThread>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    loginCycle = 0;
    users<<"admin"<<"service"<<"user";
    //users.append("hello");
    ui->setupUi(this);
    ui->adminButton->setChecked(true);
    ui->loginStatus->setVisible(false);
    ui->userNamecomboBox->addItems(users);
    ui->userNamecomboBox->setCurrentIndex(0);

    ui->userNamecomboBox->hide();

    ui->statusBar->showMessage("Ethernet IP");
    ui->statusBar->addPermanentWidget(ui->ipLabel);
    getIP();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_returnButton_clicked()
{

    if(loginCycle == 0){

        ui->passwordLineEdit->setFocus();
        ui->passwordLineEdit->setText("");
        ui->passwordLineEdit->setEchoMode(QLineEdit::EchoMode(2));

        loginCycle = 1;

    }else{

        ui->passwordLineEdit->setText("");
        ui->userNamecomboBox->setFocus();

        //loginCycle = 0;
    }

}

void MainWindow::on_backButton_clicked()
{
    if(ui->passwordLineEdit->text().count() >0){

        QString str = ui->passwordLineEdit->text();
        str.chop(1);
        ui->passwordLineEdit->setText(str);

    }else{
        qDebug()<<"Not ok";
    }

}

void MainWindow::setNumber(QString str){

    QString pstr = ui->passwordLineEdit->text();

    pstr += str;

    ui->passwordLineEdit->setText(pstr);
}

void MainWindow::on_oneButton_clicked()
{
    setNumber("1");
}

void MainWindow::on_twoButton_clicked()
{
    setNumber("2");
}

void MainWindow::on_threeButton_clicked()
{
    setNumber("3");
}

void MainWindow::on_fourButton_clicked()
{
    setNumber("4");
}

void MainWindow::on_fiveButton_clicked()
{
    setNumber("5");
}

void MainWindow::on_sixButton_clicked()
{
    setNumber("6");
}

void MainWindow::on_sevenButton_clicked()
{
    setNumber("7");
}

void MainWindow::on_eightButton_clicked()
{
    setNumber("8");
}

void MainWindow::on_nineButton_clicked()
{
    setNumber("9");
}

void MainWindow::on_zeroButton_clicked()
{
    setNumber("0");
}

void MainWindow::on_loginButton_clicked()
{
    QString admin = "511";
    QString service = "711";
    QString user = "911";

    QString path1 ="/home/launchApps/";
    QString path2 =" -platform xcb";

    QString qtplugin =" -platform xcb";

    if(ui->adminButton->isChecked()){

    //if(ui->userNamecomboBox->currentIndex() == 0){ // for comboBox

        QString adminPath = path1+""+path2;

        qDebug("admin");

        int x = QString::compare(admin, ui->passwordLineEdit->text(), Qt::CaseInsensitive);  // if strings are equal x should return 0

        if(x== 0){
            ui->loginStatus->setVisible(false);
            qDebug("admin login sucess");

            adminD = new adminDialog();

            connect(adminD,SIGNAL(closeAll()),this, SLOT(closeAll()));

            connect(adminD,SIGNAL(showMain()),this, SLOT(showMain()));

            this->hide();
            adminD->show();


        }else{
            ui->loginStatus->setVisible(true);
            qDebug("admin login failed");
        }

    }
    else if(ui->serviceButton->isChecked()){

    //else if(ui->userNamecomboBox->currentIndex() == 1){ // for comboBox

        qDebug("service");

        QString path ="/home/launchApps/Apaths/TestAppPath/tfp.txt";
        QFile file(path);

        if(!file.open(QIODevice::ReadOnly| QIODevice::Text))
        {
            qDebug() << "Could not open " << path;
            return;
        }

        QTextStream in(&file);

        QString stringer = in.readLine();

        file.close();

        qDebug() << "name_of_file_is  = "<<stringer;

        QString servicePath = path1+stringer+path2;

        int x = QString::compare(service, ui->passwordLineEdit->text(), Qt::CaseInsensitive);  // if strings are equal x should return 0

        if(x== 0){
            qDebug("service login sucess");

            this->hide();
            QProcess::execute(servicePath);
            ui->loginStatus->setVisible(false);
            this->show();

        }else{
            ui->loginStatus->setVisible(true);
            qDebug("service login failed");
        }

    }else if(ui->userButton->isChecked()){

        qDebug("user");

        QString path ="/home/launchApps/Apaths/ChargerAppPath/chargerFilePath.txt";
        QFile file(path);

        if(!file.open(QIODevice::ReadOnly| QIODevice::Text))
        {
            qDebug() << "Could not open " << path;
            return;
        }

        QTextStream in(&file);

        QString strig = in.readLine();

        file.close();

        qDebug() << "name_of_file_is  = "<<strig;

        QString userPath = path1+strig;

        int x = QString::compare(user, ui->passwordLineEdit->text(), Qt::CaseInsensitive);  // if strings are equal x should return 0

        if(x== 0){

           ui->loginStatus->setVisible(false);
            qDebug("user login sucess");


            this->hide();
            QProcess::startDetached(userPath);
            ui->loginStatus->setVisible(false);
            this->show();

        }else{

            ui->loginStatus->setVisible(true);
            qDebug("user login failed");
        }

    }

}

void MainWindow::closeAll(){

    this->close();
}

void MainWindow::getIP(){
    int n;
    struct ifreq ifr;
    char array[] = "eth0";

    n = socket(AF_INET, SOCK_DGRAM, 0);
    //Type of address to retrieve - IPv4 IP address
    ifr.ifr_addr.sa_family = AF_INET;
    //Copy the interface name in the ifreq structure
    strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
    ioctl(n, SIOCGIFADDR, &ifr);
    //close(n);
    //display result
    char ip_addr[100];
    strcpy(ip_addr,inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr));

    ui->ipLabel->setText(ip_addr);

}


void MainWindow::showMain(){

    ui->loginStatus->setVisible(false);
    this->show();
}

