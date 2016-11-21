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
  QString internal_name;
};

struct parameters {
  genome genome;
  bool pairwise;
  int threads;
  QString reads1;
  QString reads2;
  QString output_filename;
  int state = 0;
};

#endif // MYSTRUCTS_H
