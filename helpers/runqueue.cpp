#include "runqueue.h"

runqueue::runqueue() {}

void runqueue::add_job(parameters p) { queue.append(p); }

parameters runqueue::get_current_parameters() {
  return queue.at(current_index);
}

void runqueue::increase_current_index() { current_index += 1; }

void runqueue::decrease_current_index() { current_index -= 1; }

QList<QString> runqueue::get_output_names() {
  QList<QString> names;
  for (int i = 0; i < queue.count(); i++) {
    parameters p = queue.at(i);
    names.append(p.output_filename);
  }
  return names;
}

QList<int> runqueue::get_running_states() {
  QList<int> states;
  for (int i = 0; i < queue.count(); i++) {
    parameters p = queue.at(i);
    states.append(p.state);
  }
  return states;
}

int runqueue::get_jobs_count() {
  return queue.count();
}

