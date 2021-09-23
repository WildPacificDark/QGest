#include "../../header/dialog/FormDipendenti.h"

FormDipendenti::FormDipendenti(Gestionale& _gest, QWidget* parent) : FormPersone(_gest, parent) {}

FormDipendenti::FormDipendenti(Gestionale& _gest, const QString& title, int w, int h, QWidget* parent) : FormPersone(_gest, title, w, h, parent) {

  QString disabled("background-color: rgb(225, 225, 225);");
  QString enabled("background-color: rgb(255, 255, 255);");

  connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

  cod = new QLineEdit;
  rit = new QLineEdit;
  guad = new QLineEdit;
  fisso = new QLineEdit;
  bonus = new QLineEdit;
  tipoAg = new QComboBox;

  codAG.setPattern("^[A-Z]{6}$");
  codValidator = new QRegularExpressionValidator(codAG, this);

  cod->setValidator(codValidator);
  rit->setValidator(doubleValidator);
  guad->setValidator(doubleValidator);
  fisso->setValidator(doubleValidator);
  bonus->setValidator(doubleValidator);

  fisso->setEnabled(false);
  bonus->setEnabled(false);

  fisso->setStyleSheet(disabled);
  bonus->setStyleSheet(disabled);

  tipoAg = new QComboBox;
  tipoAg->insertItem(0, "Agente");
  tipoAg->insertItem(1, "Manager");


  connect(tipoAg, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
    if(index) {
      fisso->setEnabled(true);
      bonus->setEnabled(true);
      fisso->setStyleSheet(enabled);
      bonus->setStyleSheet(enabled);
    } else {
      fisso->setEnabled(false);
      bonus->setEnabled(false);
      fisso->setStyleSheet(disabled);
      bonus->setStyleSheet(disabled);

    }
  });

  formLayout->addRow("Codice Agente:", cod);
  formLayout->addRow("Tipo Agente:", tipoAg);
  formLayout->addRow("Ritenuta:", rit);
  formLayout->addRow("Perc. Guadagno:", guad);
  formLayout->addRow("Fisso:", fisso);
  formLayout->addRow("Bonus:", bonus);
}

QString FormDipendenti::getCodice() const { return cod->text(); }
double FormDipendenti::getRitenuta() const { return rit->text().toDouble(); }
double FormDipendenti::getGuadagno() const { return guad->text().toDouble(); }
bool FormDipendenti::getTipo() const { return tipoAg->currentIndex(); }
double FormDipendenti::getFisso() const { return fisso->text().toDouble(); }
double FormDipendenti::getBonus() const { return bonus->text().toDouble(); };

void FormDipendenti::editPersona(const Persona& p) {
  const Dipendente* d = dynamic_cast<const Dipendente*>(&p);
  const Manager* m = dynamic_cast<const Manager*>(&p);

  tipoAg->setEnabled(false);
  Nome->setText(d->getNome());
  Cognome->setText(d->getCognome());
  Email->setText(d->getEmail());
  Telefono->setText(d->getTelefono());
  cod->setText(d->getCodice());
  rit->setText(QString::number(d->getRitenuta()));
  guad->setText(QString::number(d->getPercGuadagno()));
  tipoAg->setCurrentIndex(m ? 1 : 0);
  if(m) {
    fisso->setText(QString::number(m->getFissoMensile()));
    bonus->setText(QString::number(m->getBonus()));
  }
}
