#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "download/downloadmanager.h"
#include "helpers/files.h"
#include "helpers/includes.h"
#include "helpers/mystructs.h"
#include "helpers/runqueue.h"
#include "ui_about.h"
#include "ui_mainwindow.h"
#include "ui_preferences.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  Ui::MainWindow *ui = nullptr;
  QDialog *prefs = nullptr;
  Ui::PreferencePane *preferences_ui = nullptr;
  QVector<Genome> genomes_list;
  int genome_index;
  ~MainWindow();

private slots:
  //  void on_folder_tree_clicked(const QModelIndex &index);
  void on_pairwise_on_clicked(bool checked);
  void on_pairwise_off_clicked(bool checked);
  void on_genome_box_currentIndexChanged(int index);
  void on_add_to_queue_button_clicked();
  void on_run_button_clicked();
  void addLine(QString qsLine);
  void progress(int nPercentage);
  void finished();
  void update_jobs_table();
  void run_next_in_queue();
  void on_clear_queue_button_clicked();
  void output_file_text_changed();
  void on_nofw_clicked();
  void on_norc_clicked();
  void on_k_valueChanged(int arg1);
  void on_ungz_stateChanged(int arg1);
  void on_unbz2_stateChanged(int arg1);
  void on_algz_stateChanged(int arg1);
  void on_albz2_stateChanged(int arg1);
  void on_fastq_reads_clicked();
  void on_fasta_reads_clicked();
  void on_custom_reads_clicked();
  void on_un_stateChanged(int arg1);
  void on_al_stateChanged(int arg1);
  void on_softclipping_stateChanged(int arg1);
  void on_jobs_table_clicked(const QModelIndex &index);
  void on_genome_clicked();
  void on_rnaseq_clicked();
  void on_shrna_clicked();
  void on_actionContents_triggered();
  void on_actionParameters_triggered();
  void on_actionDefault_Parameters_triggered();
  void on_actionSet_Default_Paths_triggered();
  void ref_button_clicked();
  void output_button_clicked();
  void on_open_output_clicked();
  void on_preferences_clicked();
  void on_quit_current_job_button_clicked();
  void on_reference_dir_clicked();

private:
  void set_custom_style();
  void Run();
  void setupPaths();
  void setupViews();
  void setupSlots();
  void populate_genomes_list();
  void make_directory(QString path);
  void add_to_genome_box(Genome g);
  void download_genome_if_absent(Genome g);
  DownloadManager *mManager;
  bool downloading;
  bool running;
  QString d_label;
  Files *f;
  RunQueue *q;
  int total_jobs;
  int current_job;
  QProcess *current_proc = nullptr;
  QTimer *timer;
};

#endif // MAINWINDOW_H
