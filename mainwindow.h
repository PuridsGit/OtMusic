#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QDebug>
#include <QDialog>
#include <QListView>
#include <QListWidget>
#include <QListWidgetItem>

#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery.h>
#include <QtSql/QSqlError>

#include <QtDebug>
#include <QFileInfo>

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaService>
#include <QMediaMetaData>

#include <QWidget>
#include <QtWidgets>

#include <QFileDialog>

#include <QDir>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_pushButton_stop_clicked();
    void on_pushButton_play_clicked();
    void on_horizontalSlider_progress_sliderMoved(int position);
    void on_horizontalSlider_volume_sliderMoved(int position);
    void on_durationChanged(qint64 position);
    void on_positionChanged(qint64 position);
    void on_pushButton_pause_clicked();
    void on_ActionOptionenTriggered();
    void on_pushButton_clearplaylist_clicked();

    void listWidget_artist_itemClicked(QListWidgetItem *item);
    void listWidget_Album_itemClicked(QListWidgetItem *item);

    void listWidget_artist_itemDoubleClicked(QListWidgetItem *item);
    void listWidget_album_itemDoubleClicked(QListWidgetItem *item);
    void listWidget_title_itemDoubleClicked(QListWidgetItem *item);
    void listWidget_playlist_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_next_clicked();

    void on_pushButton_previous_clicked();

private:
    Ui::MainWindow *ui;

    QStringList querytoStringlist(QString query);
    void addtoPlaylist(QStringList titles, QStringList URLs);

    QMediaPlayer* player;
    QMediaPlaylist* playlist;

};

#endif // MAINWINDOW_H
