#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupViews();
    setupSlots();
    f = files();
    f.create_documents_folder();
    populate_genomes_list();
    genome_index = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete drivesModel;
    delete filesModel;
}

void MainWindow::setupViews()
{
    QString homeLocation = QStandardPaths::locate(QStandardPaths::HomeLocation,
                                                  QString(),
                                                  QStandardPaths::LocateDirectory);
    drivesModel = new QFileSystemModel(this);
    drivesModel->setReadOnly(false);
    drivesModel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    drivesModel->setRootPath(homeLocation);

    ui->folder_tree->setModel(drivesModel);
    ui->folder_tree->setRootIndex(drivesModel->setRootPath(homeLocation));
    ui->folder_tree->hideColumn(1);
    ui->folder_tree->hideColumn(2);
    ui->folder_tree->hideColumn(3);
    ui->folder_tree->hideColumn(4);

    filesModel = new QFileSystemModel(this);
    filesModel->setReadOnly(false);
    filesModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filesModel->setRootPath(homeLocation);
    ui->file_list->setModel(filesModel);
    ui->file_list->setRootIndex(filesModel->setRootPath(homeLocation));

    ui->progress_bar->setVisible(false);
    ui->download_label->setVisible(false);
}

void MainWindow::addLine(QString qsLine)
{
    qDebug() << qsLine;
}


void MainWindow::progress(int nPercentage)
{
    ui->progress_bar->setValue(nPercentage);
    QString s = ui->download_label->text();
    s = d_label + " [" + QString::number(nPercentage) + "%] ...";
    ui->download_label->setText(s);
}


void MainWindow::finished()
{
    ui->progress_bar->setVisible(false);
    ui->download_label->setVisible(false);
    ui->download_label->setText("Downloading...");
    ui->run_button->setEnabled(true);
//    ui->downloadBtn->setEnabled(true);
//    ui->pauseBtn->setEnabled(false);
//    ui->resumeBtn->setEnabled(false);
}

void MainWindow::setupSlots()
{
    mManager = new DownloadManager(this);
    connect(mManager, SIGNAL(addLine(QString)), this, SLOT(addLine(QString)));
    connect(mManager, SIGNAL(downloadComplete()), this, SLOT(finished()));
    connect(mManager, SIGNAL(progress(int)), this, SLOT(progress(int)));
}

void MainWindow::on_file_list_doubleClicked(const QModelIndex &index)
{
    qDebug() << filesModel->fileInfo(index).absoluteFilePath();
//    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
//    item->setCheckState(Qt::Unchecked);
}

void MainWindow::on_pairwise_on_clicked(bool checked)
{
    ui->selected_files_list1->setVisible(true);
    ui->selected_files_list2->setVisible(true);
    ui->selected_files2_label->setVisible(true);
    ui->selected_files1_label->setText("Paired Reads (Set 1)");
    ui->selected_files2_label->setText("Paired Reads (Set 2)");
}

void MainWindow::on_pairwise_off_clicked(bool checked)
{
    ui->selected_files_list2->setVisible(false);
    ui->selected_files2_label->setVisible(false);
    ui->selected_files1_label->setText("Unpaired Reads");
}

void MainWindow::on_selected_files_list1_clicked()
{
    qDebug() << "Clicked";
}

void MainWindow::on_folder_tree_clicked(const QModelIndex &index)
{
    QString path = drivesModel->fileInfo(index).absoluteFilePath();
    ui->file_list->setRootIndex(filesModel->setRootPath(path));
}

void MainWindow::make_directory(QString path)
{
    if (!QDir(path).exists())
    {
        QDir().mkpath(path);
    }
}

void MainWindow::populate_genomes_list()
{
    genomes_list = f.get_genomes_list();
    BOOST_FOREACH(genome g, genomes_list) {
        add_to_genome_box(g);
    }
}

void MainWindow::add_to_genome_box(genome g)
{
    QString s =  QString::number(g.index + 1) + ". " + g.name + " (" +
            g.species + ", " + g.type + ")";
    ui->genome_box->addItem(s);
}

void MainWindow::on_genome_box_currentIndexChanged(int index)
{
    genome_index = index;
    download_genome_if_absent();
}

void MainWindow::download_genome_if_absent()
{
    QString genome_file_name = f.get_genome_filename(genomes_list[genome_index]);
    qDebug() << genome_file_name;
    if (!QFile(genome_file_name).exists())
    {
        qDebug() << "Doesn't Exist";
        mManager->download(f.get_genome_url(genomes_list[genome_index]),
                           genome_file_name);
        d_label =  "Downloading " + genomes_list[genome_index].name +
                " (" + genomes_list[genome_index].species + ", " +
                genomes_list[genome_index].type + ") ...";
        ui->download_label->setText(d_label);
        ui->run_button->setEnabled(false);
        ui->progress_bar->setVisible(true);
        ui->download_label->setVisible(true);
    }
}

void MainWindow::Run()
{
    char command[1024];
    sprintf(command, "hisat2/hisat2");
    system((char *)command);
}
