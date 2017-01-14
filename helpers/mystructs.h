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
  // Input options
  int inputfile_format = 0;
  bool skip = 0;
  int align = 0;
  int trim5 = 0;
  int trim3 = 0;
  bool phred33;
  bool phred64;
  // Alignment options
  bool ignore_quals;
  bool nofw;
  bool norc;
  // Scoring options
  int mp_mx = 0;
  int mp_mn = 0;
  int sp_mx = 0;
  int sp_mn = 0;
  bool soft_clipping;
  int np = 0;
  int rdg1 = 0;
  int rdg2 = 0;
  int rfg1 = 0;
  int rfg2 = 0;
  // Reporting options
  int k = 0;
  int max_seeds = 0;
  bool secondary;
  // Output options
  bool time;
  bool un;
  bool un_gz;
  bool un_bz2;
  bool al;
  bool al_gz;
  bool al_bz2;
  bool quiet;
  bool metrics;
  bool chr;
  // Performance options
  bool reorder;
  QStringList args;
};

#endif // MYSTRUCTS_H
