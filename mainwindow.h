#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include "download/downloadmanager.h"
#include "helpers/files.h"
#include "helpers/includes.h"
#include "helpers/mystructs.h"
#include "helpers/runqueue.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  Ui::MainWindow *ui;
  ~MainWindow();

private slots:
  void on_folder_tree_clicked(const QModelIndex &index);
  void on_file_list_doubleClicked(const QModelIndex &index);
  void on_pairwise_on_clicked(bool checked);
  void on_pairwise_off_clicked(bool checked);
  void on_selected_files_list1_clicked();
  void on_genome_box_currentIndexChanged(int index);
  void on_add_to_queue_button_clicked();
  void addLine(QString qsLine);
  void progress(int nPercentage);
  void finished();
  void update_jobs_table();

private:
  void Run();
  void setupPaths();
  void setupViews();
  void setupSlots();
  void populate_genomes_list();
  void make_directory(QString path);
  void add_to_genome_box(genome g);
  void download_genome_if_absent();
  QFileSystemModel *drivesModel;
  QFileSystemModel *filesModel;
  QVector<genome> genomes_list;
  DownloadManager *mManager;
  QString d_label;
  files f;
  int genome_index;
  runqueue q;
};

#endif // MAINWINDOW_H
