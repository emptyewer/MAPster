#include "vlistwidget.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

VListWidget::VListWidget(QWidget *parent)
{
    setAcceptDrops(true);
}

void VListWidget::dropEvent(QDropEvent *event)
{
    QString path = event->mimeData()->urls()[0].path();
    new QListWidgetItem(path, this);
}

void VListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData())
        event->accept();
    else
        event->ignore();
}

void VListWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == 68) {
      this->clear();
  }
}
