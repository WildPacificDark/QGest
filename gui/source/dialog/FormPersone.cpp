#include "../../header/dialog/FormPersone.h"

FormPersone::FormPersone(Gestionale& _gest, QWidget* parent) : Form(_gest, parent) {}

FormPersone::FormPersone(Gestionale& _gest, const QString& title, int w, int h, QWidget* parent) : Form(_gest, title, w, h, parent) {
  Nome = new QLineEdit;
  Cognome = new QLineEdit;
  Email = new QLineEdit;
  Telefono = new QLineEdit;

  codFis.setPattern("^[A-Z]{6}\\d{2}[A-Z]\\d{2}[A-Z]\\d{3}[A-Z]$");
  phone.setPattern("^(\\+?[0-9]{2})?[0-9]{10}$");

  cfValidator = new QRegularExpressionValidator(codFis, this);
  phoneValidator = new QRegularExpressionValidator(phone, this);

  Nome->setValidator(stringValidator);
  Cognome->setValidator(stringValidator);
  Email->setValidator(stringValidator);
  Telefono->setValidator(phoneValidator);

  formLayout->addRow("Nome:", Nome);
  formLayout->addRow("Cognome:", Cognome);
  formLayout->addRow("Email:", Email);
  formLayout->addRow("Telefono:", Telefono);
}

FormPersone::FormPersone(const FormPersone& f) : Form(f), Nome(f.Nome), Cognome(f.Cognome), Email(f.Email), Telefono(f.Telefono),
  codFis(f.codFis), phone(f.phone), cfValidator(f.cfValidator), phoneValidator(f.phoneValidator) {}

QString FormPersone::getNome() const{ return Nome->text(); }

QString FormPersone::getCognome() const { return Cognome->text(); }

QString FormPersone::getEmail() const { return Email->text(); }

QString FormPersone::getTelefono() const { return Telefono->text(); }
