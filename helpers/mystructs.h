#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

#include <QString>
#include <QUrl>

struct Genome {
  int index;
  QString name;
  QString type;
  QString species;
  QUrl url;
  QString internal_name;
};

struct Parameters {
  Genome genome;
  bool pairwise;
  int threads;
  QString reads1;
  QString reads2;
  QString output_filename = NULL;
  int state = 0;
};

#endif // MYSTRUCTS_H
