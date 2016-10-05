#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupViews();
    create_documents_folder();
    get_genome_list();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupViews()
{
    QString homeLocation = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
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

    selected_listWidget = ui->selected_files_list1;
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
}

void MainWindow::on_pairwise_off_clicked(bool checked)
{
    ui->selected_files_list2->setVisible(false);
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

void MainWindow::get_genome_list()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    qDebug() << manager->get(QNetworkRequest(QUrl("ftp://ftp.ccb.jhu.edu/pub/infphilo/hisat2/data/")));
}


void MainWindow::make_directory(QString path)
{
    if (!QDir(path).exists())
    {
        QDir().mkpath(path);
    }
}

void MainWindow::create_documents_folder()
{
    QString documents_dir = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory);
    QString mapster_dir = QDir(documents_dir).filePath("MAPster Files");
    make_directory(mapster_dir);
    QString mapster_settings_dir = QDir(mapster_dir).filePath("Configs");
    make_directory(mapster_settings_dir);
    QString mapster_queues_dir = QDir(mapster_dir).filePath("Queues");
    make_directory(mapster_queues_dir);
    QString mapster_genomes_dir = QDir(mapster_dir).filePath("Genomes");
    make_directory(mapster_genomes_dir);
}

void MainWindow::Run()
{
    char command[1024];
    sprintf(command, "hisat2/hisat2");
    system((char *)command);
}
