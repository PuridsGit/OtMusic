#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>

class scanner : public QObject
{
    Q_OBJECT
public:
    explicit scanner(QObject *parent = 0);

private:
    void gettagsandadd(QStringList files);

signals:
    void updateProgressbar(int i);
    void switchProgressbar();

public slots:

    void doWork();
};

#endif // SCANNER_H
