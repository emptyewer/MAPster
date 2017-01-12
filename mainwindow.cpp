#include "mainwindow.h"
#include "customui/uielements.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  //  setupViews();
  setupSlots();
  f = Files();
  f.create_documents_folder();

  drivesModel = UIElements().setup_folder_view(this);
  filesModel = UIElements().setup_files_view(this);
  UIElements().setup_other_elements(this);

  q = RunQueue();
  populate_genomes_list();
  genome_index = 0;
}

MainWindow::~MainWindow() {
  delete ui;
  delete drivesModel;
  delete filesModel;
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

void MainWindow::on_folder_tree_clicked(const QModelIndex &index) {
  QString path = drivesModel->fileInfo(index).absoluteFilePath();
  ui->file_list->setRootIndex(filesModel->setRootPath(path));
}

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
