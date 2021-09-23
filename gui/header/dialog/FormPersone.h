#ifndef FORMPERSONE_H
#define FORMPERSONE_H
#include "Form.h"

class FormPersone : public Form {
  Q_OBJECT

  protected:
    QLineEdit* Nome;
    QLineEdit* Cognome;
    QLineEdit* Email;
    QLineEdit* Telefono;

    QRegularExpression codFis;
    QRegularExpression phone;

    QValidator* cfValidator;
    QValidator* phoneValidator;

  public:
    FormPersone(Gestionale&, QWidget* = nullptr);
    FormPersone(Gestionale&, const QString&, int, int, QWidget* = nullptr);
    FormPersone(const FormPersone&);

    QString getNome() const;
    QString getCognome() const;
    QString getEmail() const;
    QString getTelefono() const;
    virtual void editPersona(const Persona&) = 0;

    virtual ~FormPersone() {};
};

#endif // FORM_H
