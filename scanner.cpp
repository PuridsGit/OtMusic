#include "scanner.h"

#define TAGLIB_STATIC

#include <QtSql>
#include <QMessageBox>
#include "taglib/fileref.h"

scanner::scanner(QObject *parent) : QObject(parent)
{

}

//scan chosen dir with Qdiriterator
void scanner::doWork()
{
    //dir aus Datenbank

    QSqlQuery q;
    QString chosendir;
    QStringList mp3;
    QStringList files;

    q.prepare("select Dir from Dir where id =1");
    q.exec();
    q.next();

    chosendir = q.value(0).toString();

    //turn on progressbar and set it to 15%
    emit switchProgressbar();
    emit updateProgressbar(15);

    //scann directory for all files
    QDirIterator it(chosendir, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(it.hasNext())
    {
        files << it.next();
    }

    emit updateProgressbar(45);

    gettagsandadd(files);

}

//add files to database
void scanner::gettagsandadd(QStringList files)
{
    int length = files.length();

    //progressbar variables
    int progressbarCurrent = 45;
    int progressbarHelper = length/50;
    int helper = 0;

    //actually adding to database
    for(int i = 0; i < length; i++)
    {
        if(files.at(i).endsWith("mp3") || files.at(i).endsWith("wav") || files.at(i).endsWith("flac"))
        {
            TagLib::FileRef fileRef(files.at(i).toStdString().data());
            QString Title = fileRef.tag()->title().toCString();
            QString Artist = fileRef.tag()->artist().toCString();
            QString Album = fileRef.tag()->album().toCString();

//            QString qTitle = QString::from;
//            QString qArtist = QString::fromCString(artist);
//            QString qAlbum = QString::fromCString(album);


            QSqlQuery q;

            q.prepare("insert or replace into Music(FID, URL, TITLE, ARTIST, ALBUM) values(:FID, :URL, :TITLE, :ARTIST, :ALBUM)");
            q.bindValue(":FID", i);
            q.bindValue(":URL", files.at(i));
            q.bindValue(":TITLE", Title);
            q.bindValue(":ARTIST", Artist);
            q.bindValue(":ALBUM", Album);
            if(!q.exec())
            {
                qDebug() << q.lastError().text();
            }

            //progressbar update
            helper++;
            if(helper == progressbarHelper)
            {
                progressbarCurrent++;
                emit updateProgressbar(progressbarCurrent);
                helper = 0;
            }
        }
    }

    //turn off progressbar
    emit switchProgressbar();

    //display message that scan is completed
    QMessageBox messageBox;
    messageBox.setText("Scan complete");
    messageBox.exec();


}
