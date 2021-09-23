#include "../../header/dialog/FormClienti.h"

FormClienti::FormClienti(Gestionale& _gest, QWidget* parent) : FormPersone(_gest, parent) {}

FormClienti::FormClienti(Gestionale& _gest, const QString& title, int w, int h, QWidget* parent) : FormPersone(_gest, title, w, h, parent) {

  QRegularExpression capReg("^([0-9]{5})$");
  pv.setPattern("^[A-Z]{2}$");
  piva.setPattern("^[0-9]{11}$");
  cfAz.setPattern("^([0-9]{11})|([A-Z]{6}\\d{2}[A-Z]\\d{2}[A-Z]\\d{3}[A-Z])$");

  QValidator *capValidator = new QRegularExpressionValidator(capReg, this);
  pvValidator = new QRegularExpressionValidator(pv, this);
  pivaValidator = new QRegularExpressionValidator(piva, this);
  cfAzValidator = new QRegularExpressionValidator(cfAz, this);

  QString disabled("background-color: rgb(225, 225, 225);");
  QString enabled("background-color: rgb(255, 255, 255);");

  connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

  cf = new QLineEdit;
  numDoc = new QLineEdit;
  indirizzo = new QLineEdit;
  comune = new QLineEdit;
  provincia = new QLineEdit;
  cap = new QLineEdit;
  ragSoc = new QLineEdit;
  p_iva = new QLineEdit;
  cf_azienda = new QLineEdit;

  cf->setValidator(cfValidator);
  numDoc->setValidator(stringValidator);
  indirizzo->setValidator(stringValidator);
  comune->setValidator(stringValidator);
  provincia->setValidator(pvValidator);
  cap->setValidator(capValidator);
  ragSoc->setValidator(stringValidator);
  p_iva->setValidator(pivaValidator);
  cf_azienda->setValidator(cfAzValidator);

  ragSoc->setEnabled(false);
  p_iva->setEnabled(false);
  cf_azienda->setEnabled(false);

  ragSoc->setStyleSheet(disabled);
  p_iva->setStyleSheet(disabled);
  cf_azienda->setStyleSheet(disabled);

  tipoDoc = new QComboBox;
  tipoDoc->insertItem(0, "Carta Identità");
  tipoDoc->insertItem(1, "Patente");
  tipoDoc->insertItem(2, "Passaporto");

  tipoC = new QComboBox;
  tipoC->insertItem(0, "Domestico");
  tipoC->insertItem(1, "Business");

  dataN = new QDateTimeEdit;
  dataN->setDate(QDate::currentDate());
  dataN->setMinimumDate(QDate::currentDate().addYears(-99));
  dataN->setMaximumDate(QDate::currentDate().addYears(-18));
  dataN->setDisplayFormat("yyyy/MM/dd");

  rilDoc = new QDateTimeEdit;
  rilDoc->setDate(QDate::currentDate());
  rilDoc->setMinimumDate(QDate::currentDate().addYears(-10));
  rilDoc->setMaximumDate(QDate::currentDate());
  rilDoc->setDisplayFormat("yyyy/MM/dd");

  scaDoc = new QDateTimeEdit;
  scaDoc->setDate(QDate::currentDate());
  scaDoc->setMinimumDate(QDate::currentDate().addDays(-90));
  scaDoc->setMaximumDate(QDate::currentDate().addYears(10));
  scaDoc->setDisplayFormat("yyyy/MM/dd");

  connect(tipoC, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
    if(index) {
      ragSoc->setEnabled(true);
      p_iva->setEnabled(true);
      cf_azienda->setEnabled(true);
      ragSoc->setStyleSheet(enabled);
      p_iva->setStyleSheet(enabled);
      cf_azienda->setStyleSheet(enabled);
    } else {
      ragSoc->setEnabled(false);
      p_iva->setEnabled(false);
      cf_azienda->setEnabled(false);
      ragSoc->setStyleSheet(disabled);
      p_iva->setStyleSheet(disabled);
      cf_azienda->setStyleSheet(disabled);
    }
  });

  formLayout->addRow("Codice Fiscale:", cf);
  formLayout->addRow("Data Nascita:", dataN);
  formLayout->addRow("Tipo Documento:", tipoDoc);
  formLayout->addRow("Numero Doc.:", numDoc);
  formLayout->addRow("Rilascio Doc.:", rilDoc);
  formLayout->addRow("Scadenza Doc.:", scaDoc);
  formLayout->addRow("Indirizzo:", indirizzo);
  formLayout->addRow("Comune:", comune);
  formLayout->addRow("Provincia:", provincia);
  formLayout->addRow("CAP:", cap);
  formLayout->addRow("Tipo Cliente:", tipoC);
  formLayout->addRow("Ragione Sociale:", ragSoc);
  formLayout->addRow("P.Iva:", p_iva);
  formLayout->addRow("Codice Fiscale:", cf_azienda);
}


// Metodi getter
QString FormClienti::getCF() const { return cf->text(); }

Data FormClienti::getDataNascita() const { return Data(dataN->text()); }

QString FormClienti::getNumeroDoc() const { return numDoc->text(); }

Data FormClienti::getScadenzaDoc() const { return Data(scaDoc->text()); }

Data FormClienti::getRilascioDoc() const { return Data(rilDoc->text()); }

QString FormClienti::getIndirizzo() const { return indirizzo->text(); }

QString FormClienti::getComune() const { return comune->text(); }

QString FormClienti::getProvincia() const { return provincia->text(); }

QString FormClienti::getCAP() const { return cap->text(); }

Documento FormClienti::getTipoDocumento() const {
  switch(tipoDoc->currentIndex()) {
    case 0:
      return Documento::CartaIdentita;
    case 1:
      return Documento::Patente;
    case 2:
      return Documento::Passaporto;
  }
  return Documento::CartaIdentita;
}

tipoCliente FormClienti::getTipo() const {
  if(tipoC->currentIndex()) return tipoCliente::Business;
  else return tipoCliente::Domestico;
}

QString FormClienti::getRagioneSociale() const { return ragSoc->text(); }

QString FormClienti::getPiva() const { return p_iva->text(); }

QString FormClienti::getCFAzienda() const { return cf_azienda->text(); }

void FormClienti::editPersona(const Persona& p) {
  const Cliente* c = dynamic_cast<const Cliente*>(&p);
  tipoC->setEnabled(false);
  Nome->setText(c->getNome());
  Cognome->setText(c->getCognome());
  Email->setText(c->getEmail());
  Telefono->setText(c->getTelefono());
  cf->setText(c->getCF());
  dataN->setDate(QDate(c->getDataNascita().getAnno(), c->getDataNascita().getMese(), c->getDataNascita().getGiorno()));
  tipoDoc->setCurrentIndex(c->getTipoDocumentoInt());
  numDoc->setText(c->getNumeroDoc());
  rilDoc->setDate(QDate(c->getRilascioDoc().getAnno(), c->getRilascioDoc().getMese(), c->getRilascioDoc().getGiorno()));
  scaDoc->setDate(QDate(c->getScadenzaDoc().getAnno(), c->getScadenzaDoc().getMese(), c->getScadenzaDoc().getGiorno()));
  indirizzo->setText(c->getIndirizzo());
  comune->setText(c->getComune());
  provincia->setText(c->getProvincia());
  cap->setText(c->getCAP());
  if(const Cliente_Business* b = dynamic_cast<const Cliente_Business*>(c)) {
    tipoC->setCurrentIndex(1);
    ragSoc->setText(b->getRagioneSociale());
    p_iva->setText(b->getPiva());
    cf_azienda->setText(b->getCFAzienda());
  }
}
