#ifndef FORMDIPENDENTI_H
#define FORMDIPENDENTI_H
#include "FormPersone.h"

class FormDipendenti : public FormPersone {
  Q_OBJECT
  private:

    QLineEdit* cod;
    QLineEdit* rit;
    QLineEdit* guad;
    QComboBox* tipoAg;
    QLineEdit* fisso;
    QLineEdit* bonus;

    QRegularExpression codAG;
    QValidator* codValidator;

  public:
    FormDipendenti(Gestionale&, QWidget* = nullptr);
    FormDipendenti(Gestionale &, const QString&, int, int, QWidget* = nullptr);

    QString getCodice() const;
    double getRitenuta() const;
    double getGuadagno() const;
    bool getTipo() const;
    double getFisso() const;
    double getBonus() const;

    virtual void editPersona(const Persona&);
    virtual ~FormDipendenti() {};

};

#endif // FORM_H
