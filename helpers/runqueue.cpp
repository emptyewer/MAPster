#include "runqueue.h"
#include "helpers/files.h"

RunQueue::RunQueue() {}

RunQueue::~RunQueue() { delete proc; }

void RunQueue::add_job(Parameters p) {
  QString error_string = NULL;
  if (p.output_filename == NULL) {
    error_string += "Output Filename is Not Valid!";
  }

  if (error_string == NULL) {
    queue.append(construct_command_line(p));
  } else {
    VError e = VError(error_string);
    e.show();
  }
}

void RunQueue::remove_job(int index) { queue.removeAt(index); }

Parameters RunQueue::construct_command_line(Parameters p) {
  Files f = Files();
  QString output_path = f.get_output_dir();

  QString output_filename = QDir(output_path).filePath(p.output_filename);

  QString genome_path =
      QDir(f.get_mapster_genomes_dir()).filePath(p.genome.internal_name);

  QString fname = QFileInfo(output_filename).baseName();

  QStringList arguments;
  if (p.pairwise == true) {
    arguments << " -x"
              << "\"" + genome_path.replace(" ", "\\ ") + "\""
              << "-1"
              << "\"" + p.reads1.replace(" ", "\\ ") + "\""
              << "-2"
              << "\"" + p.reads2.replace(" ", "\\ ") + "\""
              << "-S"
              << "\"" + output_filename.replace(" ", "\\ ") + "\""
              << "-p" << QString::number(p.threads);
  } else {
    arguments << " -x"
              << "\"" + genome_path.replace(" ", "\\ ") + "\""
              << "-U"
              << "\"" + p.reads1.replace(" ", "\\ ") + "\""
              << "-S"
              << "\"" + output_filename.replace(" ", "\\ ") + "\""
              << "-p" << QString::number(p.threads);
  }
  // set command line arguments for proper input file format
  if (p.inputfile_format == 0) {
    arguments << "-q";
  } else if (p.inputfile_format == 1) {
    arguments << "-f";
  } else if (p.inputfile_format == 2) {
    arguments << "-r";
  }
  // Skip the first # reads
  if (p.skip > 0) {
    arguments << "-s" << QString::number(p.skip);
  }
  // Align the first # reads
  if (p.align > 0) {
    arguments << "-u" << QString::number(p.align);
  }
  // Trim # bases from 5' end of each read
  if (p.trim5 > 0) {
    arguments << "-5" << QString::number(p.trim5);
  }
  // Trim # bases from 3' end of each read
  if (p.trim3 > 0) {
    arguments << "-3" << QString::number(p.trim3);
  }
  // Phread33
  if (p.phred33) {
    arguments << "--phred33";
  }
  // Phred64
  if (p.phred64) {
    arguments << "--phred64";
  }
  // Ignore quality values
  if (p.ignore_quals) {
    arguments << "--ignore-quals";
  }
  // no forward strand matching
  if (p.nofw) {
    arguments << "--nofw";
  }
  // No reverse complement matching
  if (p.norc) {
    arguments << "--norc";
  }
  // Set mismatch penalties
  if (p.mp_mx != 6 && p.mp_mn != 2) {
    arguments << "--mp" << QString::number(p.mp_mx) << ","
              << QString::number(p.mp_mn);
  }
  // Set soft-clipping penalties
  if (p.soft_clipping) {
    if (p.sp_mx != 2 && p.sp_mn != 1) {
      arguments << "--sp" << QString::number(p.sp_mx) << ","
                << QString::number(p.sp_mn);
    }
  } else {
    arguments << "--no-softclip";
  }
  // Penalty for ambiguous character
  if (p.np != 1) {
    arguments << "--np" << QString::number(p.np);
  }
  // Read gap penalties
  if (p.rdg1 != 5 && p.rdg2 != 3) {
    arguments << "--rdg" << QString::number(p.rdg1) << ","
              << QString::number(p.rdg2);
  }
  // Reference gap penalties
  if (p.rfg1 != 5 && p.rfg2 != 3) {
    arguments << "--rfg" << QString::number(p.rfg1) << ","
              << QString::number(p.rfg2);
  }
  // Downstream transcriptome assembly
  if (p.dta) {
    arguments << "--dta";
  }
  // Max seeds and number of distinct alignments
  if ((p.genome.type.compare("genome") == 0 && p.k != 5 && p.max_seeds != 5) ||
      (p.genome.type.compare("genome") != 0 && p.k != 10 &&
       p.max_seeds != 10)) {
    arguments << "-k" << QString::number(p.k);
    arguments << "--max-seeds" << QString::number(p.max_seeds);
  }
  // Report secondary alignments
  if (p.secondary) {
    arguments << "--secondary";
  }
  // Write time required to load the index files and align the reads
  if (p.time) {
    arguments << "-t";
  }
  // Write unparied reads that fail to align
  if (p.un) {
    if (p.un_gz) {
      arguments << "--un-gz"
                << "\"" +
                       QDir(output_path).filePath(fname + "_unp_once.sam.gz") +
                       "\"";
    } else if (p.un_bz2) {
      arguments << "--un-bz2"
                << "\"" +
                       QDir(output_path).filePath(fname + "_unp_once.sam.bz2") +
                       "\"";
    } else {
      arguments << "--un"
                << "\"" + QDir(output_path).filePath(fname + "_unp_once.sam") +
                       "\"";
    }
  }
  // Write unparied reads that align at least once
  if (p.al) {
    if (p.al_gz) {
      arguments << "--al-gz"
                << "\"" +
                       QDir(output_path).filePath(fname + "_unp_fail.sam.gz") +
                       "\"";
    } else if (p.al_bz2) {
      arguments << "--al-bz2"
                << "\"" +
                       QDir(output_path).filePath(fname + "_unp_fail.sam.bz2") +
                       "\"";
    } else {
      arguments << "--al"
                << "\"" +
                       QDir(output_path).filePath(fname + "_unp_fail.sam.gz") +
                       "\"";
    }
  }
  // Print only erros and alignments
  if (p.quiet) {
    arguments << "--quiet";
  }
  // Metrics
  if (p.metrics) {
    arguments << "--met-file"
              << QDir(output_path).filePath(fname + "_metrics.txt");
    arguments << "--met" << QString::number(5);
  }
  // Add chr prefix
  if (p.chr) {
    arguments << "--add-chrname";
  } else {
    arguments << "--remove-chrname";
  }
  // Reorder SAM records
  if (p.reorder) {
    arguments << "--reorder";
  }
  // Memory Mapped IO
  if (p.mm) {
    arguments << "--mm";
  }
  p.args = arguments;
  return p;
}

Parameters RunQueue::get_current_parameters() {
  return queue.at(current_index);
}

Parameters RunQueue::get_parameters(int index) { return queue.at(index); }

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

void RunQueue::quit_current_job() {
  if (proc->state() == QProcess::Running) {
    QProcess getChilds;
    QString exe = "pgrep -P " + QString::number(proc->processId());
    getChilds.start(exe);
    getChilds.waitForFinished();
    QString output = getChilds.readAllStandardOutput();
    QStringList list = output.split("\n");
    QProcess p;
    foreach (QString pid, list) {
      p.start("kill " + pid);
      p.waitForFinished();
    }
    proc->terminate();
    proc->kill();
  }
}

QProcess *RunQueue::run(int index) {
  Files f = Files();
  QString hisat_executable = f.get_hisat_executable_path().replace(" ", "\\ ");
  Parameters p = queue.at(index);

  QString standard_output =
      QDir(f.get_output_dir()).filePath(p.output_filename + ".stdout.txt");

  // Launch the Process in a separate thread
  proc = new QProcess();
  proc->setProcessChannelMode(QProcess::MergedChannels);
  proc->setStandardOutputFile(standard_output);
  // Have to remove the quotes from the filepaths for QProcess to
  // function properly
  QStringList list;
  foreach (QString s, p.args) {
    s.replace("\"", "");
    list.append(s);
  }
  //  proc->start(hisat_executable, p.args);
  proc->start(hisat_executable, list);
  return proc;
}
