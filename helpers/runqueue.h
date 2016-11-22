#ifndef RUNQUEUE_H
#define RUNQUEUE_H
#include "helpers/includes.h"
#include "helpers/mystructs.h"

class runqueue {

public:
  runqueue();
  void add_job(parameters p);
  parameters get_current_parameters();
  void set_current_index(int i);
  QList<QString> get_output_names();
  QList<int> get_current_states();
  int get_jobs_count();
  QProcess *run(int index);
  void update_state(int index, int state);
  QVector<parameters> queue;

private:
  int current_index = 0;
  QString current_date_time();
  QProcess *proc;

private slots:
};

#endif // RUNQUEUE_H
