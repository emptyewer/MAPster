#ifndef UIELEMENTS_H
#define UIELEMENTS_H
#include "helpers/includes.h"
#include "helpers/mystructs.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpers/files.h"

class UIElements
{
public:
  UIElements();
  static Parameters get_parameters(MainWindow *parent);
  void pairwise_toggle(MainWindow *parent, int i);
  QFileSystemModel* setup_folder_view(MainWindow *parent);
  QFileSystemModel* setup_files_view(MainWindow *parent);
  void setup_other_elements(MainWindow *parent);
  void add_extension_to_output(MainWindow *parent, Files *f);
  ~UIElements();
private:
  static QString get_read_file_list(VListWidget *list);
};

#endif // UIELEMENTS_H
