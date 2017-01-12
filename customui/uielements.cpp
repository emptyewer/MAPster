#include "uielements.h"
#include <QThread>

UIElements::UIElements() {}

UIElements::~UIElements() {}

QString UIElements::get_read_file_list(VListWidget *list) {
  QString reads;
  int count = list->count();
  bool first = true;
  for (int i = 0; i < count; i++) {
    reads += list->item(i)->text();
    if (first == true && count > 1 && i + 1 != count) {
      reads += ',';
    }
  }
  return reads;
}

Parameters UIElements::get_parameters(MainWindow *parent) {
  Parameters params;
  if (parent->ui->pairwise_on) {
    params.pairwise = true;
    params.reads1 = get_read_file_list(parent->ui->selected_files_list1);
    params.reads2 = get_read_file_list(parent->ui->selected_files_list2);

  } else {
    params.pairwise = false;
    params.reads1 = get_read_file_list(parent->ui->selected_files_list1);
  }
  params.output_filename = parent->ui->output_filename->text();
  params.threads = parent->ui->threads_sbox->value();
  params.genome = parent->genomes_list[parent->genome_index];
  return params;
}

void UIElements::pairwise_toggle(MainWindow *parent, int i) {
  if (i == 0) {
    parent->ui->selected_files_list2->setVisible(false);
    parent->ui->selected_files2_label->setVisible(false);
    parent->ui->selected_files1_label->setText("Unpaired Reads");
  } else {
    parent->ui->selected_files_list1->setVisible(true);
    parent->ui->selected_files_list2->setVisible(true);
    parent->ui->selected_files2_label->setVisible(true);
    parent->ui->selected_files1_label->setText("Paired Reads (Set 1)");
    parent->ui->selected_files2_label->setText("Paired Reads (Set 2)");
  }
}

QFileSystemModel *UIElements::setup_folder_view(MainWindow *parent) {
  QString homeLocation = QStandardPaths::locate(
      QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
  QFileSystemModel *drivesModel = new QFileSystemModel();
  drivesModel->setReadOnly(false);
  drivesModel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
  drivesModel->setRootPath(homeLocation);
  parent->ui->folder_tree->setModel(drivesModel);
  parent->ui->folder_tree->setRootIndex(drivesModel->setRootPath(homeLocation));
  parent->ui->folder_tree->hideColumn(1);
  parent->ui->folder_tree->hideColumn(2);
  parent->ui->folder_tree->hideColumn(3);
  parent->ui->folder_tree->hideColumn(4);
  return drivesModel;
}

QFileSystemModel *UIElements::setup_files_view(MainWindow *parent) {
  QString homeLocation = QStandardPaths::locate(
      QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
  QFileSystemModel *filesModel = new QFileSystemModel();
  filesModel->setReadOnly(false);
  filesModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
  filesModel->setRootPath(homeLocation);
  parent->ui->file_list->setModel(filesModel);
  parent->ui->file_list->setRootIndex(filesModel->setRootPath(homeLocation));
  return filesModel;
}

void UIElements::setup_other_elements(MainWindow *parent) {
  parent->ui->progress_bar->setVisible(false);
  parent->ui->download_label->setVisible(false);
  parent->ui->output_dir_label->setVisible(false);
  if (QThread::idealThreadCount() < 0) {
    parent->ui->threads_sbox->setMaximum(1);
    parent->ui->threads_sbox->setValue(1);
  } else {
    parent->ui->threads_sbox->setMaximum(QThread::idealThreadCount());
    parent->ui->threads_sbox->setValue(QThread::idealThreadCount());
  }
}

void UIElements::add_extension_to_output(MainWindow *parent, Files *f) {
  QString text = parent->ui->output_filename->text();
  QString error_string = NULL;
  if (text == NULL) {
      error_string += "Output Filename is Not Valid!";
  }

  if (error_string == NULL) {
      QFileInfo fi(text);
      if (fi.completeSuffix() != "sam") {
        parent->ui->output_filename->setText(text + ".sam");
      }
      parent->ui->output_dir_label->setText("Output will be saved to: " +
                                    f->get_mapster_output_dir());
      parent->ui->output_dir_label->setVisible(true);
  } else {
    VError e = VError(error_string);
    e.show();
  }

}
