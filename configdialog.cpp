#include "configdialog.h"
#include "ui_configdialog.h"

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <QtSql>

#include <QFileDialog>
#include <QDir>
#include <QLibrary>
//#include "lib/id3.h"





using namespace std;

typedef struct{
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[40];
    unsigned long genre;
}mp3Tag;



configdialog::configdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configdialog)
{
    ui->setupUi(this);

    //connect
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_buttonBox_accepted());
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(on_buttonBox_rejected());



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
    directorypath = dialog.selectedFiles().value(0);


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

//scaned ausgewaehlten ordner nach .mp3
void configdialog::on_pushButton_add_rescan_clicked()
{
    //dir aus Datenbank

    QSqlQuery q;
    QString chosendir;
    QStringList mp3;
    QStringList files;
    int counter = 0;
    q.prepare("select Dir from Dir where id =1");
    q.exec();
    q.next();

    chosendir = q.value(0).toString();

    QDirIterator it(chosendir, mp3 << "*.mp3", QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(it.hasNext())
    {
        files << it.next();

        counter++;
    }

    for(int i = 0; i < counter; ++i)
    {
       gettagsandadd(files.at(i),i);
    }

}

//holt MEtadaten und schreibt des ganze in die Datenbank
void configdialog::gettagsandadd(QString Filelink, int i)
{


    std::string thisfile = Filelink.toUtf8().constData();
    mp3Tag tag;
    char achar[128] = {0};

    const char * c = thisfile.c_str();
    ifstream File;
    File.open(c, ios::binary);

    File.seekg(-128, ios::end);
    //File.read(reinterpret_cast<char *>(&tag), 128);
    File.read(achar, 128);
    File.close();

    memcpy(tag.tag, achar, 3);
    memcpy(tag.title, achar + 3, 30);
    memcpy(tag.artist, achar + 33, 30);
    memcpy(tag.album, achar + 63, 30);


    QString stitle = QString::fromUtf8(tag.title);
    QString sartist = QString::fromUtf8(tag.artist);
    QString salbum = QString::fromUtf8(tag.album);




        QSqlQuery q;

        q.prepare("insert or replace into Music(FID, URL, TITLE, ARTIST, ALBUM) values(:FID, :URL, :TITLE, :ARTIST, :ALBUM)");
        q.bindValue(":FID", i+1);
        q.bindValue(":URL", Filelink);
        q.bindValue(":TITLE", stitle);
        q.bindValue(":ARTIST", sartist);
        q.bindValue(":ALBUM", salbum);
        if(!q.exec())
        {
            qDebug() << q.lastError().text();
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
