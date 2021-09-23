#include "../../header/dialog/FormContratti.h"

FormContratti::FormContratti(Gestionale& _gest, QWidget* parent) : Form(_gest, parent) {}

FormContratti::FormContratti(Gestionale& _gest, const QString& title, int w, int h, QWidget* parent) : Form(_gest, title, w, h, parent) {

  connect(buttonBox, &QDialogButtonBox::accepted, this, &FormContratti::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

  Id = new QLineEdit;
  Agenzia = new QLineEdit;
  dataStipula = new QDateTimeEdit;
  dataSpedizione = new QDateTimeEdit;
  Agente = new QComboBox;
  Cliente = new QComboBox;
  tipoCliente = new QComboBox;
  Fornitore = new QLineEdit;
  Offerta = new QLineEdit;
  tipoContratto = new QComboBox;
  Gettone = new QLineEdit;
  Sdd = new QLineEdit;
  Mail = new QLineEdit;

  Id->setEnabled(false);
  Id->setStyleSheet("background-color: rgb(225, 225, 225);");

  Queue<Dipendente*> d = gest.getAllAgenti();

  int i = 0;
  for(auto it = d.begin(); it != d.end(); ++it, ++i) {
    Agente->insertItem(i, QString((*it)->getCognome()).append(" ").append((*it)->getNome()).append(" - ").append((*it)->getCodice()));
  }

  Queue<class Cliente*> c = gest.getAllClienti();

  i = 0;
  for(auto it = c.begin(); it != c.end(); ++it, ++i) {
    Cliente->insertItem(i, QString((*it)->getCognome()).append(" ").append((*it)->getNome()).append(" - ").append((*it)->getCF()));
  }

  tipoCliente->insertItem(0, "Domestico");
  tipoCliente->insertItem(1, "Business");

  tipoContratto->insertItem(0, "Luce");
  tipoContratto->insertItem(1, "Gas");
  tipoContratto->insertItem(2, "Telefonia");

  dataStipula->setDate(QDate::currentDate());
  dataStipula->setMinimumDate(QDate::currentDate().addDays(-365));
  dataStipula->setMaximumDate(QDate::currentDate());
  dataStipula->setDisplayFormat("yyyy/MM/dd");

  dataSpedizione->setDate(QDate::currentDate());
  dataSpedizione->setMinimumDate(QDate::currentDate().addDays(-365));
  dataSpedizione->setMaximumDate(QDate::currentDate());
  dataSpedizione->setDisplayFormat("yyyy/MM/dd");

  Agenzia->setValidator(stringValidator);
  Fornitore->setValidator(stringValidator);
  Offerta->setValidator(stringValidator);

  Gettone->setValidator(doubleValidator);
  Sdd->setValidator(doubleValidator);
  Mail->setValidator(doubleValidator);

  formLayout->addRow("Id:", Id);
  formLayout->addRow("Agenzia:", Agenzia);
  formLayout->addRow("Data Stipula:", dataStipula);
  formLayout->addRow("Data Invio:", dataSpedizione);
  formLayout->addRow("Agente:", Agente);
  formLayout->addRow("Cliente:", Cliente);
  formLayout->addRow("Tipo Cliente:", tipoCliente);
  formLayout->addRow("Fornitore:", Fornitore);
  formLayout->addRow("Offerta:", Offerta);
  formLayout->addRow("Tipo Contratto:", tipoContratto);
  formLayout->addRow("Gettone:", Gettone);
  formLayout->addRow("Canvas SDD:", Sdd);
  formLayout->addRow("Canvas Email:", Mail);
}


int FormContratti::getId() const { return Id->text().toInt(); }

QString FormContratti::getAgenzia() const { return Agenzia->text(); }

Data FormContratti::getDataStipula() const { return Data(dataStipula->text()); }

Data FormContratti::getDataSpedizione() const { return Data(dataSpedizione->text()); }

Dipendente* FormContratti::getAgente() const {
  QString cod = Agente->currentText();
  QStringList list = cod.split(" ");
  return gest.getDipendente(ricerca::Codice_Dipendente, list.at(list.size() - 1));
}

Cliente* FormContratti::getCliente() const {
  QString cod = Cliente->currentText();
  QStringList list = cod.split(" ");
  return gest.getCliente(ricerca::Codice_Fiscale, list.at(list.size() - 1));
}

enum tipoCliente FormContratti::getTipoCliente() const {
  if(tipoCliente->currentText() == "Domestico") return tipoCliente::Domestico;
  return tipoCliente::Business;
}

QString FormContratti::getFornitore() const { return Fornitore->text(); }

QString FormContratti::getOfferta() const { return Offerta->text(); }

enum tipoContratto FormContratti::getTipoContratto() const {
  switch(tipoContratto->currentIndex()) {
    case 0:
      return tipoContratto::Luce;
    case 1:
      return tipoContratto::Gas;
    case 2:
      return tipoContratto::Telefonia;
  }
  return tipoContratto::Luce;
}

double FormContratti::getGettone() const { return (Gettone->text()).toDouble(); }

double FormContratti::getSDD() const { return (Sdd->text()).toDouble(); }

double FormContratti::getMail() const { return (Mail->text()).toDouble(); }

void FormContratti::accept() {
  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Warning);
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.setWindowTitle("Attenzione");

  if(Agenzia->hasAcceptableInput()) {
    if(Fornitore->hasAcceptableInput()) {
      if(!Offerta->hasAcceptableInput()) {
        msgBox.setText("Il campo Offerta non può restare vuoto.");
        msgBox.exec();
      } else {
          if(Gettone->hasAcceptableInput()) {
            if(Sdd->hasAcceptableInput()) {
              if(Mail->hasAcceptableInput())
                QDialog::accept();
              else {
                msgBox.setText("I valori di Canvas Email sono errati.");
                msgBox.exec();
              }
            } else {
              msgBox.setText("I valori di Canvas SDD sono errati.");
              msgBox.exec();
            }
          } else {
            msgBox.setText("I valori di Gettone sono errati.");
            msgBox.exec();
          }
        }
    } else {
      msgBox.setText("Il campo Fornitore non può restare vuoto.");
      msgBox.exec();
    }
  } else {
    msgBox.setText("Il campo Agenzia non può restare vuoto.");
    msgBox.exec();
  }
}

void FormContratti::editContratto(const Contratto& ctr) {
  Id->setText(QString::number(ctr.getId().get()));
  Agenzia->setText(ctr.getAgenzia());
  dataStipula->setDate(QDate(ctr.getDataStipula().getAnno(), ctr.getDataStipula().getMese(), ctr.getDataStipula().getGiorno()));
  dataSpedizione->setDate(QDate(ctr.getDataSpedizione().getAnno(), ctr.getDataSpedizione().getMese(), ctr.getDataSpedizione().getGiorno()));

  for(int i = 0; i < Agente->count(); ++i) {
    QString s = Agente->itemText(i);
    QStringList list = s.split(" ");
    if(list.at(list.size() - 1) == ctr.getIdAgente()) {
      Agente->setCurrentIndex(i);
      break;
    }
  }

  for(int i = 0; i < Cliente->count(); ++i) {
    QString s = Cliente->itemText(i);
    QStringList list = s.split(" ");
    if(list.at(list.size() - 1) == ctr.getIdCliente()) {
      Cliente->setCurrentIndex(i);
      break;
    }
  }

  if(!ctr.getTipoCliente())
    tipoCliente->setCurrentIndex(0);
  else
    tipoCliente->setCurrentIndex(1);

  Fornitore->setText(ctr.getFornitore());
  Offerta->setText(ctr.getOfferta());
  tipoContratto->setCurrentIndex(ctr.getTipoContratto());
  Gettone->setText(QString::number(ctr.getGettoneBase()));
  Sdd->setText(QString::number(ctr.getCanvasSDD()));
  Mail->setText(QString::number(ctr.getCanvassMail()));
}
