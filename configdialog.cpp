#include "configdialog.h"
#include "scanner.h"
#include "ui_configdialog.h"

#include <QtSql>
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>

configdialog::configdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configdialog)
{
    ui->setupUi(this);

    //connect
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_buttonBox_accepted()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(on_buttonBox_rejected()));



    QSqlQuery querry;
    querry.prepare("select Dir from Dir where id = 1");
    querry.exec();
    querry.next();


    ui->lineEdit->setText(querry.value(0).toString());

}

configdialog::~configdialog()
{
    delete ui;
}

//ordner aussuchen, welcher spaeter durchsucht wird
void configdialog::on_pushButton_chooseDir_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    if(dialog.exec())
    {
        QString directorypath = dialog.selectedFiles().value(0);

        qDebug() << directorypath;
        ui->lineEdit->setText(directorypath);

        QSqlQuery querry;
        querry.prepare("insert or replace into Dir(Dir ,id) " "values(:dir, (select id from dir where id = 1))");
        querry.bindValue(":dir",directorypath);

        if(!querry.exec())
        {
            qDebug() << querry.lastError().text();
        }
    }


}


//thread scan load
configdialog::on_pushButton_add_rescan_clicked()
{
    if(ui->lineEdit->text().length() > 0)
    {
        QThread scanThread = new QThread();
        scanner scanObject = new scanner();

        scanObject.moveToThread(&scanThread);
        connect(scanThread, &QThread::started, scanObject, scanner::doWork());
        connect(scanThrad, &QThread::finished, scanThread, QObject::deleteLater());
        connect(scanThrad, &QThread::finished, scanObject, QObject::deleteLater());
        connect(scanThread, &scanner::updateProgressbar, configdialog::on_progressBarupdate);
        connect(scanThread, &scanner::switchProgressbar, configdialog::on_switchProgressbar);

        scanThread.start();
    }
    else
    {
        QMessageBox messageBox;
        messageBox.setText("No directory chosen");
        messageBox.exec();
    }
}

void configdialog::on_progressBarupdate(int i)
{
    ui->progressBar->setValue(i);
}

void configdialog::on_switchProgressbar()
{
    if(ui->progressBar->enabled())
    {
        ui->progressBar->setEnabled(false);
    }
    else
    {
        ui->progressBar->setEnabled(true);
    }
}



void configdialog::on_buttonBox_accepted()
{
    this->close();
}

void configdialog::on_buttonBox_rejected()
{
    this->close();
}
