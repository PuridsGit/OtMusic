#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include <QVector>
class scanner : public QObject
{
    Q_OBJECT
public:
    explicit scanner(QObject *parent = 0);

private:
    void gettagsandadd(QStringList files);

    QVector <QVector<QString>> stringVector;

signals:
    void updateProgressbar(int i);
    void switchProgressbar();

public slots:

    void doWork();
    void quitWorking();
};

#endif // SCANNER_H
