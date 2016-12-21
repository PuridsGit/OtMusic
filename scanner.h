#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>

class scanner : public QObject
{
    Q_OBJECT
public:
    explicit scanner(QObject *parent = 0);

private:
    gettagsandadd(QStringList files);

signals:
    void done();
    void updateProgressbar(int i);
    void switchProgressbar();

public slots:

    void doWork();
};

#endif // SCANNER_H
