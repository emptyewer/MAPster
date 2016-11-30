#ifndef ERROR_H
#define ERROR_H
#include <QWidget>

class VError
{
public:
  VError(QString msg);
  void show();
private:
  QString message = "Error";
};

#endif // ERROR_H
