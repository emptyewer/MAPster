#include "helpers/error.h"
#include <QMessageBox>

VError::VError(QString msg) { message = msg; }

void VError::show() {
  QMessageBox(QMessageBox::Critical, "Error", message, QMessageBox::Close)
      .exec();
}
