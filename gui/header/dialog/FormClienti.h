#ifndef FORMCONTRATTI_H
#define FORMCONTRATTI_H
#include "FormPersone.h"

class FormClienti : public FormPersone {
  Q_OBJECT
  private:

    QLineEdit* cf;
    QDateTimeEdit* dataN;
    QComboBox* tipoDoc;
    QLineEdit* numDoc;
    QDateTimeEdit* rilDoc;
    QDateTimeEdit* scaDoc;
    QLineEdit* indirizzo;
    QLineEdit* comune;
    QLineEdit* provincia;
    QLineEdit* cap;
    QComboBox* tipoC;
    QLineEdit* ragSoc;
    QLineEdit* p_iva;
    QLineEdit* cf_azienda;

    QRegularExpression pv;
    QRegularExpression piva;
    QRegularExpression cfAz;

    QValidator* pvValidator;
    QValidator* pivaValidator;
    QValidator* cfAzValidator;

  public:
    FormClienti(Gestionale&, QWidget* = nullptr);
    FormClienti(Gestionale &, const QString&, int, int, QWidget* = nullptr);
    FormClienti(const FormClienti&);

    QString getCF() const;
    Data getDataNascita() const;
    Documento getTipoDocumento() const;
    QString getNumeroDoc() const;
    Data getScadenzaDoc() const;
    Data getRilascioDoc() const;
    QString getIndirizzo() const;
    QString getComune() const;
    QString getProvincia() const;
    QString getCAP() const;
    QString getRagioneSociale() const;
    QString getPiva() const;
    QString getCFAzienda() const;
    tipoCliente getTipo() const;

    virtual void editPersona(const Persona&);
    virtual ~FormClienti() {};
};

#endif // FORM_H
