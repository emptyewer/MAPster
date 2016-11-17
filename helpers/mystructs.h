#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

#include <QString>
#include <QUrl>

struct genome {
    int index;
    QString name;
    QString type;
    QString species;
    QUrl url;
};

struct parameters {
    genome genome;
    bool pairwise;
    int threads;
    QString reads1;
    QString reads2;
    QString output_filename;
};

#endif // MYSTRUCTS_H
