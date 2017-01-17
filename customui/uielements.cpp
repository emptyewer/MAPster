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

void UIElements::update_params_table(MainWindow *parent, Parameters list) {
  int count = 22;
  parent->ui->command_line->setText("<hisat exec> " + list.args.join(" "));
  parent->ui->parameter_table->clear();
  parent->ui->parameter_table->setRowCount(count);
  // Row 1
  QTableWidgetItem *w = new QTableWidgetItem;
  w->setText("Genome");
  parent->ui->parameter_table->setItem(0, 0, w);
  w = new QTableWidgetItem;
  w->setText(list.genome.name + "(" + list.genome.species + ") [-x]");
  parent->ui->parameter_table->setItem(0, 1, w);
  // Row 2
  w = new QTableWidgetItem;
  w->setText("Paired Reads");
  parent->ui->parameter_table->setItem(1, 0, w);
  w = new QTableWidgetItem;
  if (list.pairwise == true) {
    w->setText("True");
  } else {
    w->setText("False");
  }
  parent->ui->parameter_table->setItem(1, 1, w);
  // Row 3
  w = new QTableWidgetItem;
  w->setText("Threads");
  parent->ui->parameter_table->setItem(2, 0, w);
  w = new QTableWidgetItem;
  w->setText(QString::number(list.threads) + " [-p]");
  parent->ui->parameter_table->setItem(2, 1, w);
  // Row 4
  w = new QTableWidgetItem;
  w->setText("Reads (Set 1)");
  parent->ui->parameter_table->setItem(3, 0, w);
  w = new QTableWidgetItem;
  w->setText(list.reads1);
  parent->ui->parameter_table->setItem(3, 1, w);
  // Row 5
  w = new QTableWidgetItem;
  w->setText("Reads (Set 2)");
  parent->ui->parameter_table->setItem(4, 0, w);
  w = new QTableWidgetItem;
  w->setText(list.reads2);
  parent->ui->parameter_table->setItem(4, 1, w);
  // Row 6
  w = new QTableWidgetItem;
  w->setText("Output");
  parent->ui->parameter_table->setItem(5, 0, w);
  w = new QTableWidgetItem;
  w->setText(list.output_filename + " [-S]");
  parent->ui->parameter_table->setItem(5, 1, w);
  // Row 7
  w = new QTableWidgetItem;
  w->setText("Format");
  parent->ui->parameter_table->setItem(6, 0, w);
  w = new QTableWidgetItem;
  if (list.inputfile_format == 0) {
    w->setText("FASTQ [-q]");
  } else if (list.inputfile_format == 1) {
    w->setText("FASTA [-f]");
  } else if (list.inputfile_format == 2) {
    w->setText("CUSTOM [-r]");
  }
  parent->ui->parameter_table->setItem(6, 1, w);
  // Row 8
  w = new QTableWidgetItem;
  w->setText("Skip # Reads");
  parent->ui->parameter_table->setItem(7, 0, w);
  w = new QTableWidgetItem;
  w->setText(QString::number(list.skip) + " [-s/--skip]");
  parent->ui->parameter_table->setItem(7, 1, w);
  // Row 9
  w = new QTableWidgetItem;
  w->setText("Align # Reads");
  parent->ui->parameter_table->setItem(8, 0, w);
  w = new QTableWidgetItem;
  w->setText(QString::number(list.align) + " [-u/--qupto]");
  parent->ui->parameter_table->setItem(8, 1, w);
  // Row 10
  w = new QTableWidgetItem;
  w->setText("5' Trim #");
  parent->ui->parameter_table->setItem(9, 0, w);
  w = new QTableWidgetItem;
  w->setText(QString::number(list.trim5) + " [-5/--trim5]");
  parent->ui->parameter_table->setItem(9, 1, w);
  // Row 11
  w = new QTableWidgetItem;
  w->setText("3' Trim #");
  parent->ui->parameter_table->setItem(10, 0, w);
  w = new QTableWidgetItem;
  w->setText(QString::number(list.trim3) + " [-3/--trim3]");
  parent->ui->parameter_table->setItem(10, 1, w);
  // Row 12
  w = new QTableWidgetItem;
  w->setText("Input quality");
  parent->ui->parameter_table->setItem(11, 0, w);
  w = new QTableWidgetItem;
  if (list.phred33) {
    w->setText("Phred33 [--phred33]");
  } else {
    w->setText("Phred64 [--phred64]");
  }
  parent->ui->parameter_table->setItem(11, 1, w);
  // Row 13
  w = new QTableWidgetItem;
  w->setText("Ignore Quality");
  parent->ui->parameter_table->setItem(12, 0, w);
  w = new QTableWidgetItem;
  if (list.ignore_quals) {
    w->setText("True [--ignore-quals]");
  } else {
    w->setText("False [--ignore-quals]");
  }
  parent->ui->parameter_table->setItem(12, 1, w);
  // Row 14
  w = new QTableWidgetItem;
  w->setText("Do not align to forward reference");
  parent->ui->parameter_table->setItem(13, 0, w);
  w = new QTableWidgetItem;
  if (list.nofw) {
    w->setText("True [--nofw]");
  } else {
    w->setText("False [--nofw]");
  }
  parent->ui->parameter_table->setItem(13, 1, w);
  // Row 15
  w = new QTableWidgetItem;
  w->setText("Do not align to reverse reference");
  parent->ui->parameter_table->setItem(14, 0, w);
  w = new QTableWidgetItem;
  if (list.nofw) {
    w->setText("True [--norc]");
  } else {
    w->setText("False [--norc]");
  }
  parent->ui->parameter_table->setItem(14, 1, w);
  // Row 16
  w = new QTableWidgetItem;
  w->setText("Mismatch penalties");
  parent->ui->parameter_table->setItem(15, 0, w);
  w = new QTableWidgetItem;
  w->setText("min: " + QString::number(list.mp_mn) + ", max: " +
             QString::number(list.mp_mx) + " [--mp]");
  parent->ui->parameter_table->setItem(15, 1, w);
  // Row 17
  w = new QTableWidgetItem;
  w->setText("Soft Clipping");
  parent->ui->parameter_table->setItem(16, 0, w);
  w = new QTableWidgetItem;
  if (list.soft_clipping) {
    w->setText("True [--no-softclip]");
  } else {
    w->setText("False [--no-softclip]");
  }
  parent->ui->parameter_table->setItem(16, 1, w);
  // Row 18
  w = new QTableWidgetItem;
  w->setText("Soft-clipping penalties");
  parent->ui->parameter_table->setItem(17, 0, w);
  w = new QTableWidgetItem;
  w->setText("min: " + QString::number(list.sp_mn) + ", max: " +
             QString::number(list.sp_mx) + " [--sp]");
  parent->ui->parameter_table->setItem(17, 1, w);
  // Row 19
  w = new QTableWidgetItem;
  w->setText("Ambiguous Character penalty");
  parent->ui->parameter_table->setItem(18, 0, w);
  w = new QTableWidgetItem;
  w->setText(QString::number(list.np) + " [--np]");
  parent->ui->parameter_table->setItem(18, 1, w);
  // Row 20
  w = new QTableWidgetItem;
  w->setText("Read gap penalties");
  parent->ui->parameter_table->setItem(19, 0, w);
  w = new QTableWidgetItem;
  w->setText("open: " + QString::number(list.rdg1) + ", extend: " +
             QString::number(list.rdg2) + " [--rdg]");
  parent->ui->parameter_table->setItem(19, 1, w);
  // Row 21
  w = new QTableWidgetItem;
  w->setText("Reference gap penalties");
  parent->ui->parameter_table->setItem(20, 0, w);
  w = new QTableWidgetItem;
  w->setText("open: " + QString::number(list.rfg1) + ", extend: " +
             QString::number(list.rfg2) + " [--rfg]");
  parent->ui->parameter_table->setItem(20, 1, w);
  // Row 22
  w = new QTableWidgetItem;
  w->setText("Downstream transcriptome assembly");
  parent->ui->parameter_table->setItem(21, 0, w);
  w = new QTableWidgetItem;
  if (list.dta) {
    w->setText("True [--dta]");
  } else {
    w->setText("False [--dta]");
  }
  parent->ui->parameter_table->setItem(21, 1, w);
  // Row 8
  //  w = new QTableWidgetItem;
  //  w->setText("Chr prefix");
  //  parent->ui->parameter_table->setItem(7, 0, w);
  //  w = new QTableWidgetItem;
  //  if (list.chr) {
  //    w->setText("True [--add-chrname]");
  //  } else {
  //    w->setText("False [--remove-chrname]");
  //  }
  //  parent->ui->parameter_table->setItem(7, 1, w);
}

Parameters UIElements::get_parameters(MainWindow *parent) {
  Parameters params;
  if (parent->ui->pairwise_on->isChecked()) {
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
  // Read Input options
  if (parent->ui->fastq_reads->isChecked()) {
    params.inputfile_format = 0;
  } else if (parent->ui->fasta_reads->isChecked()) {
    params.inputfile_format = 1;
  } else if (parent->ui->custom_reads->isChecked()) {
    params.inputfile_format = 2;
  }
  params.skip = parent->ui->skip_first->value();
  params.align = parent->ui->align_first->value();
  params.trim3 = parent->ui->trim3->value();
  params.trim5 = parent->ui->trim5->value();
  params.phred33 = parent->ui->phread33->isChecked();
  params.phred64 = parent->ui->phread64->isChecked();

  // Read Alignment options
  params.ignore_quals = parent->ui->ignore_quals->isChecked();
  params.nofw = parent->ui->nofw->isChecked();
  params.norc = parent->ui->norc->isChecked();
  params.soft_clipping = parent->ui->softclipping->isChecked();
  params.dta = parent->ui->dta->isChecked();
  // Read Scoring options
  params.mp_mx = parent->ui->mp_mx->value();
  params.mp_mn = parent->ui->mp_mn->value();
  params.sp_mx = parent->ui->sp_mx->value();
  params.sp_mn = parent->ui->sp_mn->value();
  params.np = parent->ui->np->value();
  params.rdg1 = parent->ui->rdg1->value();
  params.rdg2 = parent->ui->rdg2->value();
  params.rfg1 = parent->ui->rfg1->value();
  params.rfg2 = parent->ui->rfg2->value();

  // Read Reporting options
  params.k = parent->ui->k->value();
  params.max_seeds = parent->ui->max_seeds->value();
  params.secondary = parent->ui->secondary->isChecked();

  // Read Output options
  params.time = parent->ui->time->isChecked();
  params.un = parent->ui->un->isChecked();
  params.un_gz = parent->ui->ungz->isChecked();
  params.un_bz2 = parent->ui->unbz2->isChecked();
  params.al = parent->ui->al->isChecked();
  params.al_gz = parent->ui->algz->isChecked();
  params.al_bz2 = parent->ui->albz2->isChecked();
  params.metrics = parent->ui->metrics->isChecked();
  params.chr = parent->ui->chr->isChecked();
  params.reorder = parent->ui->reorder->isChecked();
  return params;
}

void UIElements::pairwise_toggle(MainWindow *parent, int i) {
  if (i == 0) {
    parent->ui->selected_files_list2->setVisible(false);
    parent->ui->selected_files2_label->setVisible(false);
    parent->ui->selected_files1_label->setText("Unpaired Reads [-U]");
  } else {
    parent->ui->selected_files_list1->setVisible(true);
    parent->ui->selected_files_list2->setVisible(true);
    parent->ui->selected_files2_label->setVisible(true);
    parent->ui->selected_files1_label->setText("Paired Reads [-1]");
    parent->ui->selected_files2_label->setText("Paired Reads [-2]");
  }
}

// QFileSystemModel *UIElements::setup_folder_view(MainWindow *parent) {
//  QString homeLocation = QStandardPaths::locate(
//      QStandardPaths::HomeLocation, QString(),
//      QStandardPaths::LocateDirectory);
//  QFileSystemModel *drivesModel = new QFileSystemModel();
//  drivesModel->setReadOnly(false);
//  drivesModel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
//  drivesModel->setRootPath(homeLocation);
//  parent->ui->folder_tree->setModel(drivesModel);
//  parent->ui->folder_tree->setRootIndex(drivesModel->setRootPath(homeLocation));
//  parent->ui->folder_tree->hideColumn(1);
//  parent->ui->folder_tree->hideColumn(2);
//  parent->ui->folder_tree->hideColumn(3);
//  parent->ui->folder_tree->hideColumn(4);
//  return drivesModel;
//}

// QFileSystemModel *UIElements::setup_files_view(MainWindow *parent) {
//  QString homeLocation = QStandardPaths::locate(
//      QStandardPaths::HomeLocation, QString(),
//      QStandardPaths::LocateDirectory);
//  QFileSystemModel *filesModel = new QFileSystemModel();
//  filesModel->setReadOnly(false);
//  filesModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
//  filesModel->setRootPath(homeLocation);
//  parent->ui->file_list->setModel(filesModel);
//  parent->ui->file_list->setRootIndex(filesModel->setRootPath(homeLocation));
//  return filesModel;
//}

void UIElements::setup_other_elements(MainWindow *parent) {
  parent->ui->progress_bar->setVisible(false);
  parent->ui->download_label->setVisible(false);
  //  parent->ui->output_dir_label->setVisible(false);
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
    parent->ui->statusBar->showMessage("Output will be saved to: " +
                                       f->get_mapster_output_dir());
    //    parent->ui->output_dir_label->setText();
    //    parent->ui->output_dir_label->setVisible(true);
  } else {
    VError e = VError(error_string);
    e.show();
  }
}

void UIElements::setDefaults(MainWindow *parent) {
  parent->ui->fasta_reads->setChecked(true);
  parent->ui->skip_first->setValue(0);
  parent->ui->align_first->setValue(0);
  parent->ui->trim5->setValue(0);
  parent->ui->trim3->setValue(0);
  parent->ui->ignore_quals->setChecked(false);
  parent->ui->nofw->setChecked(false);
  parent->ui->norc->setChecked(false);
  parent->ui->dta->setChecked(false);
  parent->ui->mp_mx->setValue(6);
  parent->ui->mp_mn->setValue(2);
  parent->ui->sp_mx->setValue(2);
  parent->ui->sp_mn->setValue(1);
  parent->ui->np->setValue(1);
  parent->ui->rdg1->setValue(5);
  parent->ui->rdg2->setValue(3);
  parent->ui->rfg1->setValue(5);
  parent->ui->rfg2->setValue(3);
  if (parent->genomes_list[parent->genome_index].type.compare("genome") == 0) {
    parent->ui->k->setValue(5);
  } else {
    parent->ui->k->setValue(10);
  }
  parent->ui->secondary->setChecked(false);
  parent->ui->un->setChecked(false);
  parent->ui->ungz->setChecked(false);
  parent->ui->unbz2->setChecked(false);
  parent->ui->al->setChecked(false);
  parent->ui->algz->setChecked(false);
  parent->ui->albz2->setChecked(false);
  parent->ui->time->setChecked(false);
  parent->ui->quiet->setChecked(false);
  parent->ui->metrics->setChecked(false);
  parent->ui->reorder->setChecked(false);
  parent->ui->chr->setChecked(false);
}
