#ifndef UIELEMENTS_H
#define UIELEMENTS_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpers/includes.h"
#include "helpers/mystructs.h"

class UIElements
{
public:
  UIElements();
  parameters get_parameters(MainWindow *parent);
  void pairwise_toggle(MainWindow *parent, int i);
};

#endif // UIELEMENTS_H
