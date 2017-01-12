#ifndef VLISTWIDGET_H
#define VLISTWIDGET_H

#include <QListWidget>
#include "helpers/includes.h"

class VListWidget : public QListWidget {
public:
  explicit VListWidget(QWidget *parent = Q_NULLPTR);

protected:
  void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
  void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
  void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
  void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
};

#endif // VLISTWIDGET_H
