#include "../../header/dialog/Form.h"

Form::Form(Gestionale& _gest, QWidget* parent) : QDialog(parent), gest(_gest) {}

Form::Form(Gestionale& _gest, const QString& title, int w, int h, QWidget* parent) : QDialog(parent), gest(_gest){
  setWindowTitle(title);
  setWindowFlags(Qt::Dialog);
  setWindowModality(Qt::WindowModal);
  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  resize(w, h);
  setSizePolicy(sizePolicy);
  setMinimumSize(QSize(w, h));
  setMaximumSize(QSize(w + 100, h + 100));

  buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
  buttonBox->setLocale(QLocale(QLocale::Italian));

  doubleReg.setPattern("^([0-9]*)|([0-9]*[\\.||\\,]([0-9]{1}|[0-9]{2}))$");
  doubleValidator = new QRegularExpressionValidator(doubleReg, this);


  notEmpty.setPattern("(.|\\s)*\\S(.|\\s)*");
  stringValidator = new QRegularExpressionValidator(notEmpty, this);

  formLayout = new QFormLayout;
  mainLayout = new QVBoxLayout;

  mainLayout->addLayout(formLayout, Qt::AlignTop);
  mainLayout->addWidget(buttonBox);

  setLayout(mainLayout);
}

Form::Form(const Form& f) : QDialog(nullptr), buttonBox(f.buttonBox), formLayout(f.formLayout),
 mainLayout(f.mainLayout), gest(f.gest), notEmpty(f.notEmpty), doubleReg(f.doubleReg), stringValidator(f.stringValidator),
 doubleValidator(f.doubleValidator) {}
