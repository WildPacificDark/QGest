#ifndef FORM_H
#define FORM_H
#include <QDateTimeEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "../MainWindow.h"

class Form : public QDialog {
  Q_OBJECT
  protected:
    QDialogButtonBox *buttonBox;
    QFormLayout* formLayout;
    QVBoxLayout* mainLayout;
    Gestionale& gest;

    QRegularExpression notEmpty;
    QRegularExpression doubleReg;
    QValidator* stringValidator;
    QValidator *doubleValidator;

  public:
    Form(Gestionale&, QWidget* = nullptr);
    Form(Gestionale&, const QString&, int = 350, int = 400, QWidget* = nullptr);
    Form(const Form&);
    virtual ~Form() {};
};

#endif // FORM_H
