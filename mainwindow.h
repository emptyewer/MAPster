#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <stdio.h>
#include <algorithm>
#include <QtWidgets>
#include <QDebug>
#include <cstdlib>
#include <boost/foreach.hpp>

#include "helpers/mystructs.h"
#include "download/downloadmanager.h"
#include "helpers/files.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_folder_tree_clicked(const QModelIndex &index);
    void on_file_list_doubleClicked(const QModelIndex &index);
    void on_pairwise_on_clicked(bool checked);
    void on_pairwise_off_clicked(bool checked);
    void on_selected_files_list1_clicked();
    void on_genome_box_currentIndexChanged(int index);
    void addLine(QString qsLine);
    void progress(int nPercentage);
    void finished();

private:
    Ui::MainWindow *ui;
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
    DownloadManager* mManager;
    QString d_label;
    files f;
    int genome_index;
};

#endif // MAINWINDOW_H
