#ifndef RUNQUEUE_H
#define RUNQUEUE_H
#include "helpers/includes.h"
#include "helpers/mystructs.h"

class runqueue
{
public:
  runqueue();
  void add_job(parameters p);
  parameters get_current_parameters();
  void increase_current_index();
  void decrease_current_index();
  QList<QString> get_output_names();
  QList<int> get_running_states();
  int get_jobs_count();

private:
  int current_index = 0;
   QVector<parameters> queue;
};

#endif // RUNQUEUE_H
