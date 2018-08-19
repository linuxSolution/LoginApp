#ifndef DNS_DIALOG_H
#define DNS_DIALOG_H

#include <QDialog>

namespace Ui {
class Dns_dialog;
}

class Dns_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dns_dialog(QWidget *parent = 0);
    ~Dns_dialog();

private slots:

    void on_cancelButton_clicked();

    void on_unlockButton_clicked();

    void on_defaultlockButton_clicked();

private:
    Ui::Dns_dialog *ui;
};

#endif // DNS_DIALOG_H
