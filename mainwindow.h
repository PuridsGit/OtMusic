#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QDebug>
#include <QDialog>
#include <QListView>
#include <QListWidget>
#include <QListWidgetItem>

#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
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

    QStringList makeStringList(QString string);

    void on_listWidget_artist_itemClicked(QListWidgetItem *item);

    void on_listWidget_Album_itemClicked(QListWidgetItem *item);

    void on_listWidget_title_itemClicked(QListWidgetItem *item);

    void on_pushButton_clearplaylist_clicked();

    void on_listWidget_playlist_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;



};

#endif // MAINWINDOW_H
