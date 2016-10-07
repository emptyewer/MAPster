#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include "mystructs.h"
#include <QVector>

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

private:
    Ui::MainWindow *ui;
    void Run();
    void setupPaths();
    void setupViews();
    void create_documents_folder();
    void make_directory(QString path);
    void add_to_genome_box(genome g);

    QFileSystemModel *drivesModel;
    QFileSystemModel *filesModel;
    QVector<genome> genomes_list;
};

#endif // MAINWINDOW_H
