#ifndef RUNQUEUE_H
#define RUNQUEUE_H
#include "helpers/includes.h"
#include "helpers/mystructs.h"

class RunQueue {

public:
  RunQueue();
  void add_job(Parameters p);
  void remove_job(int index);
  Parameters get_current_parameters();
  Parameters get_parameters(int index);
  void set_current_index(int i);
  QList<QString> get_output_names();
  QList<int> get_current_states();
  int get_jobs_count();
  QProcess *run(int index);
  void update_state(int index, int state);
  void quit_current_job();
  QVector<Parameters> queue;
  ~RunQueue();

private:
  int current_index = 0;
  QString current_date_time();
  Parameters construct_command_line(Parameters p);
  QProcess *proc;
private slots:
};

#endif // RUNQUEUE_H
