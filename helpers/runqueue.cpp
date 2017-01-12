#include "runqueue.h"
#include "files.h"

RunQueue::RunQueue() {
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
QString RunQueue::current_date_time() {
  QDateTime dateTime = dateTime.currentDateTime();
  return dateTime.toString("yyyy-MM-dd");
}

void RunQueue::add_job(Parameters p) {
  QString error_string = NULL;
  if (p.output_filename == NULL) {
      error_string += "Output Filename is Not Valid!";
  }

  if (error_string == NULL) {
    queue.append(p);
  } else {
    VError e = VError(error_string);
    e.show();
  }
}

Parameters RunQueue::get_current_parameters() {
  return queue.at(current_index);
}

void RunQueue::set_current_index(int i) { current_index = i; }

QList<QString> RunQueue::get_output_names() {
  QList<QString> names;
  for (int i = 0; i < queue.count(); i++) {
    Parameters p = queue.at(i);
    names.append(p.output_filename);
  }
  return names;
}

QList<int> RunQueue::get_current_states() {
  QList<int> states;
  for (int i = 0; i < queue.count(); i++) {
    Parameters p = queue.at(i);
    states.append(p.state);
  }
  return states;
}

int RunQueue::get_jobs_count() { return queue.count(); }

void RunQueue::update_state(int index, int state) {
  queue[index].state = state;
}

QProcess *RunQueue::run(int index) {
  Files f = Files();
  QString appdir = QCoreApplication::applicationDirPath();
  QString appdir_hisat = QDir(appdir).filePath("hisat2");
  QString hisat_executable = QDir(appdir_hisat).filePath("hisat2");
  Parameters p = queue.at(index);
  QString output_path =
      QDir(f.get_mapster_output_dir()).filePath(current_date_time());
  f.make_directory(output_path);
  QString output_filename = QDir(output_path).filePath(p.output_filename);

  QString genome_path =
      QDir(f.get_mapster_genomes_dir()).filePath(p.genome.internal_name);
  QStringList arguments;
  if (p.pairwise == true) {
  arguments << "-x" << genome_path << "-1" << p.reads1 << "-2" << p.reads2
            << "-S" << output_filename << "-p" << QString::number(p.threads);
    }
  else {
      arguments << "-x" << genome_path << "-U" << p.reads1 << "-S" << output_filename << "-p" << QString::number(p.threads);
    }
  proc = new QProcess();
  proc->start(hisat_executable, arguments);
  return proc;
}
