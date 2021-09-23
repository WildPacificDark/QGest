#ifndef FORMCONTRATTI_H
#define FORMCONTRATTI_H
#include "Form.h"

class FormContratti : public Form {
  Q_OBJECT
  private:
    QLineEdit* Id;
    QLineEdit* Agenzia;
    QDateTimeEdit* dataStipula;
    QDateTimeEdit* dataSpedizione;
    QComboBox* Agente;
    QComboBox* Cliente;
    QComboBox* tipoCliente;
    QLineEdit* Fornitore;
    QLineEdit* Offerta;
    QComboBox* tipoContratto;
    QLineEdit* Gettone;
    QLineEdit* Sdd;
    QLineEdit* Mail;

  public:
    FormContratti(Gestionale&, QWidget* = nullptr);
    FormContratti(Gestionale &, const QString&, int, int, QWidget* = nullptr);

    int getId() const;
    QString getAgenzia() const;
    Data getDataStipula() const;
    Data getDataSpedizione() const;
    Dipendente* getAgente() const;
    class Cliente* getCliente() const;
    QString getFornitore() const;
    QString getOfferta() const;
    enum tipoContratto getTipoContratto() const;
    enum tipoCliente getTipoCliente() const;
    double getGettone() const;
    double getSDD() const;
    double getMail() const;

    void editContratto(const Contratto&);

    virtual ~FormContratti() {};

  public slots:
    void accept();
};

#endif // FORM_H
