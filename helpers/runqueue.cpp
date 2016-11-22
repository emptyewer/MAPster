#include "runqueue.h"
#include "files.h"

runqueue::runqueue() {}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
QString runqueue::current_date_time() {
  QDateTime dateTime = dateTime.currentDateTime();
  return dateTime.toString("yyyy-MM-dd");
}

void runqueue::add_job(parameters p) { queue.append(p); }

parameters runqueue::get_current_parameters() {
  return queue.at(current_index);
}

void runqueue::set_current_index(int i) { current_index = i; }


QList<QString> runqueue::get_output_names() {
  QList<QString> names;
  for (int i = 0; i < queue.count(); i++) {
    parameters p = queue.at(i);
    names.append(p.output_filename);
  }
  return names;
}

QList<int> runqueue::get_current_states() {
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

void runqueue::update_state(int index, int state) {
  queue[index].state = state;
}

QProcess* runqueue::run(int index) {
  files f = files();
  QString appdir = QCoreApplication::applicationDirPath();
  QString appdir_hisat = QDir(appdir).filePath("hisat2");
  QString hisat_executable = QDir(appdir_hisat).filePath("hisat2");
  parameters p = queue.at(index);
  QString output_path = QDir(f.get_mapster_output_dir()).filePath(current_date_time());
  f.make_directory(output_path);
  QString output_filename = QDir(output_path).filePath(p.output_filename);

  QString genome_path = QDir(f.get_mapster_genomes_dir()).filePath(p.genome.internal_name);
  QStringList arguments;
  arguments << "-x" << genome_path << "-1" << p.reads1 << "-2" << p.reads2 << "-S" << output_filename << "-p" << QString::number(p.threads);
//  std::string command_str = command.toStdString();
//  system(command_str.c_str());
  proc = new QProcess();
  proc->start(hisat_executable, arguments);
  return proc;
}
