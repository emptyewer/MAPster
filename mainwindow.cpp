#include "mainwindow.h"
#include "customui/uielements.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  //  setupViews();
  setupSlots();
  f = Files();
  f.create_documents_folder();

  UIElements().setup_other_elements(this);

  q = RunQueue();
  populate_genomes_list();
  genome_index = 0;
}

MainWindow::~MainWindow() {
  delete ui;
  delete mManager;
}

void MainWindow::addLine(QString qsLine) { qDebug() << qsLine; }

void MainWindow::progress(int nPercentage) {
  ui->progress_bar->setValue(nPercentage);
  QString s = ui->download_label->text();
  s = d_label + " [" + QString::number(nPercentage) + "%] ...";
  ui->download_label->setText(s);
}

void MainWindow::finished() {
  ui->download_label->setText("Extracting...");
  f.untar_files_mac(genomes_list[genome_index]);
  ui->progress_bar->setVisible(false);
  ui->download_label->setVisible(false);
  ui->run_button->setEnabled(true);
}

void MainWindow::setupSlots() {
  mManager = new DownloadManager(this);
  connect(mManager, SIGNAL(addLine(QString)), this, SLOT(addLine(QString)));
  connect(mManager, SIGNAL(downloadComplete()), this, SLOT(finished()));
  connect(mManager, SIGNAL(progress(int)), this, SLOT(progress(int)));
  connect(ui->output_filename, SIGNAL(editingFinished()),
          SLOT(output_file_text_changed()));
}

void MainWindow::output_file_text_changed() {
  UIElements().add_extension_to_output(this, &f);
}

void MainWindow::on_pairwise_on_clicked(bool checked) {
  if (checked) {
  }
  UIElements().pairwise_toggle(this, 1);
}

void MainWindow::on_pairwise_off_clicked(bool checked) {
  if (checked) {
  }
  UIElements().pairwise_toggle(this, 0);
}

// void MainWindow::on_folder_tree_clicked(const QModelIndex &index) {
//  QString path = drivesModel->fileInfo(index).absoluteFilePath();
//  ui->file_list->setRootIndex(filesModel->setRootPath(path));
//}

void MainWindow::make_directory(QString path) {
  if (!QDir(path).exists()) {
    QDir().mkpath(path);
  }
}

void MainWindow::populate_genomes_list() {
  genomes_list = f.get_genomes_list();
  BOOST_FOREACH (Genome g, genomes_list) { add_to_genome_box(g); }
}

void MainWindow::add_to_genome_box(Genome g) {
  QString s = QString::number(g.index + 1) + ". " + g.name + " (" + g.species +
              ", " + g.type + ")";
  ui->genome_box->addItem(s);
}

void MainWindow::on_genome_box_currentIndexChanged(int index) {
  genome_index = index;
  download_genome_if_absent();
  if (genomes_list[genome_index].type.compare("genome") == 0) {
    ui->k->setValue(5);
  } else {
    ui->k->setValue(10);
  }
}

void MainWindow::download_genome_if_absent() {
  QString genome_file_path = f.get_genome_filepath(genomes_list[genome_index]);
  // If genome file is not extracted then untar
  if (!QFile(f.get_mapster_genomes_dir() + "/" +
             genomes_list[genome_index].internal_name + ".1.ht2")
           .exists()) {
    if (QFile(genome_file_path).exists()) {
      f.untar_files_mac(genomes_list[genome_index]);
    } else {
      qDebug() << "Doesn't Exist";
      mManager->download(f.get_genome_url(genomes_list[genome_index]),
                         genome_file_path);
      d_label = "Downloading " + genomes_list[genome_index].name + " (" +
                genomes_list[genome_index].species + ", " +
                genomes_list[genome_index].type + ") ...";
      ui->download_label->setText(d_label);
      ui->run_button->setEnabled(false);
      ui->progress_bar->setVisible(true);
      ui->download_label->setVisible(true);
    }
  }
}

void MainWindow::on_add_to_queue_button_clicked() {
  UIElements().add_extension_to_output(this, &f);
  q.add_job(UIElements().get_parameters(this));
  update_jobs_table();
}

void MainWindow::update_jobs_table() {
  ui->jobs_table->setRowCount(q.get_jobs_count());
  QList<QString> names = q.get_output_names();
  QList<int> states = q.get_current_states();
  for (int i = 0; i < q.get_jobs_count(); i++) {
    QTableWidgetItem *c0 = new QTableWidgetItem;
    if (states.at(i) == 0) {
      c0->setText("Waiting");
      QIcon icon(":/images/waiting.png");
      c0->setIcon(icon);
    } else if (states.at(i) == 1) {
      c0->setText("Running");
      QIcon icon(":/images/running.png");
      c0->setIcon(icon);
    } else {
      c0->setText("Finished");
      QIcon icon(":/images/done.png");
      c0->setIcon(icon);
    }
    QTableWidgetItem *c1 = new QTableWidgetItem(names.at(i));
    ui->jobs_table->setItem(i, 0, c0);
    ui->jobs_table->setItem(i, 1, c1);
  }
}

void MainWindow::run_next_in_queue() {
  total_jobs = q.get_jobs_count();
  update_jobs_table();
  if (current_proc->processId() == 0) {
    q.update_state(current_job, 2);
    current_job += 1;
    if (current_job < total_jobs) {
      q.update_state(current_job, 1);
      current_proc = q.run(current_job);
    } else {
      update_jobs_table();
      timer->stop();
      ui->run_button->setEnabled(true);
    }
  }
}

void MainWindow::on_clear_queue_button_clicked() {
  ui->jobs_table->clear();
  q.queue.clear();
  q.set_current_index(0);
}

void MainWindow::on_run_button_clicked() {
  total_jobs = q.get_jobs_count();
  current_job = 0;
  q.update_state(current_job, 1);
  update_jobs_table();
  current_proc = q.run(current_job);

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(run_next_in_queue()));
  timer->start(1000);
  ui->run_button->setEnabled(false);
}

/* Proper checks to reset GUI parameters that are interlinked with each other
 *
*/

void MainWindow::on_nofw_clicked() {
  if (ui->norc->isChecked()) {
    if (ui->norc->isChecked()) {
      ui->norc->setChecked(false);
    }
  }
}

void MainWindow::on_norc_clicked() {
  if (ui->norc->isChecked()) {
    if (ui->nofw->isChecked()) {
      ui->nofw->setChecked(false);
    }
  }
}

void MainWindow::on_k_valueChanged(int arg1) { ui->max_seeds->setValue(arg1); }

void MainWindow::on_ungz_stateChanged(int arg1) {
  if (ui->ungz->isChecked()) {
    if (ui->unbz2->isChecked()) {
      ui->unbz2->setChecked(false);
    }
  }
}

void MainWindow::on_unbz2_stateChanged(int arg1) {
  if (ui->unbz2->isChecked()) {
    if (ui->ungz->isChecked()) {
      ui->ungz->setChecked(false);
    }
  }
}

void MainWindow::on_algz_stateChanged(int arg1) {
  if (ui->algz->isChecked()) {
    if (ui->albz2->isChecked()) {
      ui->unbz2->setChecked(false);
    }
  }
}

void MainWindow::on_albz2_stateChanged(int arg1) {
  if (ui->albz2->isChecked()) {
    if (ui->algz->isChecked()) {
      ui->ungz->setChecked(false);
    }
  }
}

void MainWindow::on_fastq_reads_clicked() {
  ui->ignore_quals->setChecked(false);
}

void MainWindow::on_fasta_reads_clicked() {
  ui->ignore_quals->setChecked(true);
}

void MainWindow::on_custom_reads_clicked() {
  ui->ignore_quals->setChecked(true);
}

void MainWindow::on_un_stateChanged(int arg1) {
  if (!ui->un->isChecked()) {
    ui->ungz->setChecked(false);
    ui->unbz2->setChecked(false);
    ui->ungz->setEnabled(false);
    ui->unbz2->setEnabled(false);
  } else {
    ui->ungz->setEnabled(true);
    ui->unbz2->setEnabled(true);
  }
}

void MainWindow::on_al_stateChanged(int arg1) {
  if (!ui->al->isChecked()) {
    ui->algz->setChecked(false);
    ui->albz2->setChecked(false);
    ui->algz->setEnabled(false);
    ui->albz2->setEnabled(false);
  } else {
    ui->algz->setEnabled(true);
    ui->albz2->setEnabled(true);
  }
}

void MainWindow::on_softclipping_stateChanged(int arg1) {
  if (!ui->softclipping->isChecked()) {
    ui->sp_mn->setEnabled(false);
    ui->sp_mx->setEnabled(false);
    ui->sp_max_lbl->setEnabled(false);
    ui->sp_min_lbl->setEnabled(false);
    ui->sp_tail_lbl->setEnabled(false);
  } else {
    ui->sp_mn->setEnabled(true);
    ui->sp_mx->setEnabled(true);
    ui->sp_max_lbl->setEnabled(true);
    ui->sp_min_lbl->setEnabled(true);
    ui->sp_tail_lbl->setEnabled(true);
  }
}

void MainWindow::on_jobs_table_clicked(const QModelIndex &index) {
  UIElements().update_params_table(this, q.get_parameters(index.row()));
}
