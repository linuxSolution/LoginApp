#include "dns_dialog.h"
#include "ui_dns_dialog.h"

Dns_dialog::Dns_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dns_dialog)
{
    ui->setupUi(this);

}

Dns_dialog::~Dns_dialog()
{
    delete ui;
}


void Dns_dialog::on_cancelButton_clicked()
{
    this->close();
}

//system("chattr +i /etc/resolv.conf");
 //system("chattr -i /etc/resolv.conf");

void Dns_dialog::on_unlockButton_clicked()
{
    system("chattr -i /etc/resolv.conf");
}

void Dns_dialog::on_defaultlockButton_clicked()
{
    system("chattr -i /etc/resolv.conf");
    system("echo nameserver 8.8.8.8 > /etc/resolv.conf");
    system("chattr +i /etc/resolv.conf");
}
