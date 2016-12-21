#include "scanner.h"

#include <QtSql>
#include <QMessageBox>
#include "taglib/fileref.h"

scanner::scanner(QObject *parent) : QObject(parent)
{

}

//scan chosen dir with Qdiriterator
scanner::doWork()
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
scanner::gettagsandadd(QStringList files)
{
    int length = files.length();
    TagLib::FileRef fileRef;

    //progressbar variables
    int progressbarCurrent = 45;
    int progressbarHelper = length/50;
    int helper = 0;

    //actually adding to database
    for(int i = 0; i < length; i++)
    {
        if(files.at(i).endsWith("mp3") || files.at(i).endsWith("wav") || files.at(i).endsWith("flac"))
        {
            fileRef(files.at(i));
            QString title = fileRef.tag()->title();
            QString artist = fileRef.tag()->artist();
            QString album = fileRef.tag()->album();

            QSqlQuery q;

            q.prepare("insert or replace into Music(FID, URL, TITLE, ARTIST, ALBUM) values(:FID, :URL, :TITLE, :ARTIST, :ALBUM)");
            q.bindValue(":FID", i);
            q.bindValue(":URL", files.at(i));
            q.bindValue(":TITLE", title);
            q.bindValue(":ARTIST", artist);
            q.bindValue(":ALBUM", album);
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
