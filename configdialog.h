#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

#include <QtSql>
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class configdialog;
}

class configdialog : public QDialog
{
    Q_OBJECT

public:
    explicit configdialog(QWidget *parent = 0);
    ~configdialog();



private slots:

    void on_progressBarupdate(int i);
    void on_switchProgressbar();
    void on_pushButton_chooseDir_clicked();

    void on_pushButton_add_rescan_clicked();


    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::configdialog *ui;

    void gettagsandadd(QString Filelink, int i);

};

#endif // CONFIGDIALOG_H
