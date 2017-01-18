#include "vlistwidget.h"
#include "helpers/includes.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

VListWidget::VListWidget(QWidget *parent) {
  setAcceptDrops(true);
  setAutoFillBackground(true);
  overlay = false;
}

void VListWidget::dropEvent(QDropEvent *event) {
  QString path = event->mimeData()->urls()[0].path();
  new QListWidgetItem(path, this);
}

void VListWidget::dragMoveEvent(QDragMoveEvent *event) {
  event->acceptProposedAction();
}

void VListWidget::dragLeaveEvent(QDragLeaveEvent *event) { event->accept(); }

void VListWidget::dragEnterEvent(QDragEnterEvent *event) {
  const QMimeData *mimeData = event->mimeData();
  if (mimeData->hasUrls()) {
    QList<QUrl> urlList = mimeData->urls();
    QString text;
    for (int i = 0; i < urlList.size() && i < 32; ++i) {
      text += urlList.at(i).path();
    }
    QFileInfo fileInfo(text);
    if (fileInfo.suffix().compare("fastq") == 0 ||
        fileInfo.suffix().compare("gz") == 0 ||
        fileInfo.suffix().compare("fa") == 0 ||
        fileInfo.suffix().compare("fasta") == 0 ||
        fileInfo.suffix().compare("fq") == 0 ||
        fileInfo.suffix().compare("mfa") == 0 ||
        fileInfo.suffix().compare("fna") == 0 ||
        fileInfo.suffix().compare("txt") == 0) {
      event->accept();
    } else {
      event->ignore();
    }
  } else {
    event->ignore();
  }
  //  event->acceptProposedAction();
  //  if (event->source()->objectName() == "file_list") {
  //    if (event->mimeData())
  //      event->accept();
  //    else
  //      event->ignore();
  //  }
}

void VListWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == 68) {
    this->clear();
  }
}
