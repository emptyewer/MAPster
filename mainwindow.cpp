#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileSystemModel>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupViews();
    setupPaths();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupViews()
{
    ui->folder_tree->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->folder_tree->setDragEnabled(true);
    ui->folder_tree->viewport()->setAcceptDrops(false);
    ui->folder_tree->setDropIndicatorShown(true);

    ui->files1_list->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->files1_list->viewport()->setAcceptDrops(true);
    ui->files1_list->setDropIndicatorShown(true);
    ui->files1_list->setDragDropMode(QAbstractItemView::InternalMove);

    ui->files2_list->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->files2_list->viewport()->setAcceptDrops(true);
    ui->files2_list->setDropIndicatorShown(true);
}

void MainWindow::setupPaths()
{
    QFileSystemModel *folder_model = new QFileSystemModel;
    folder_model->setReadOnly(false);
    QString homeLocation = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    const QModelIndex mdl_index = folder_model->setRootPath(homeLocation);
    folder_model->setFilter(QDir::AllEntries|QDir::NoDotAndDotDot);
    ui->folder_tree->setModel(folder_model);
    ui->folder_tree->setRootIndex(mdl_index);
    ui->folder_tree->hideColumn(1);
    ui->folder_tree->hideColumn(2);
    ui->folder_tree->hideColumn(3);
    ui->folder_tree->hideColumn(4);

     QFileSystemModel *files1_model = new QFileSystemModel;
     files1_model->setReadOnly(false);
     ui->files1_list->setModel(files1_model);
     QFileSystemModel *files2_model = new QFileSystemModel;
     ui->files2_list->setModel(files2_model);

}

void MainWindow::Run()
{
    char command[1024];
    sprintf(command, "hisat2/hisat2");
    system((char *)command);
}
