#ifndef DOWNLOADLIST_H
#define DOWNLOADLIST_H

#include <QObject>



class DownloadList : public QObject
{
    Q_OBJECT
public:
    explicit DownloadList(QObject *parent = 0);

signals:

public slots:
};

#endif // DOWNLOADLIST_H
