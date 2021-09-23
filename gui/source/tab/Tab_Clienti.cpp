#include "../../header/tab/Tab_Clienti.h"
#include <QList>

Tab_Clienti::Tab_Clienti(Tab_Contratti* tab, Gestionale& g)
  : gest(g), grid(new QGridLayout), table(new QTableWidget(gest.getNumClienti(), 17, this)), ref(tab) {

  QStringList headers;
  headers << "Nome" << "Cognome" << "Codice Fiscale" << "Ragione Sociale" << "P.IVA" << "CF Azienda" << "Email" << "Telefono"  << "Data Nascita"
          << "Tipo Documento" << "Num. Documento" << "Rilascio Doc." << "Scadenza Doc." << "Indirizzo"
          << "Comune" << "Proincia" << "CAP";

  table->setAlternatingRowColors(true);  // Colori alternati

  table->setEditTriggers(QAbstractItemView::NoEditTriggers); // Celle non editabili
  table->setSelectionBehavior(QAbstractItemView::SelectRows); // Seleziona riga intera
  table->setSelectionMode(QAbstractItemView::SingleSelection); // Selezione singola

  table->setHorizontalHeaderLabels(headers);
  table->verticalHeader()->hide(); // nascondi Header verticale
  table->setStyleSheet( // Applica stile all' header
    "QHeaderView::section {\
      background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #616161, stop: 0.5 #505050,\
      stop: 0.6 #434343, stop:1 #656565);\
      color: white;\
      padding-left: 4px;\
      border: 1px solid #6c6c6c;\
    }"
  );

  creaCelle();
  table->resizeColumnsToContents();

  QPalette p = palette();
  p.setColor(QPalette::Inactive, QPalette::Highlight, QColor(150, 150, 150));
  p.setColor(QPalette::Inactive, QPalette::HighlightedText, QColor(255, 255, 255));
  table->setPalette(p);

  connect(table, &QTableWidget::itemSelectionChanged, this, &Tab_Clienti::selectedCell);

  button = new ContextButton;

  connect(button->addButton, &QPushButton::clicked, this, &Tab_Clienti::addCliente);
  connect(button->editButton, &QPushButton::clicked, this, &Tab_Clienti::editCliente);
  connect(button->deleteButton, &QPushButton::clicked, this, &Tab_Clienti::deleteCliente);
  connect(button->undoButton, &QPushButton::clicked, this, &Tab_Clienti::undo);
  connect(button->saveButton, &QPushButton::clicked, this, &Tab_Clienti::save);

  grid->addLayout(button->layout, 0, 0);
  grid->addWidget(table, 1, 0);

  setLayout(grid);
}

Tab_Clienti::~Tab_Clienti() {
  delete button;
  delete table;
  delete grid;
}

/// Protected

void Tab_Clienti::creaCelle() {
  Queue<Cliente*> ctr = gest.getAllClienti();
  QFont f;
  f.setBold(true);

  int row = 0;

  for(; row < table->rowCount(); ++row) {
    table->setRowHeight(row, 24);

    Cliente_Business* cb(dynamic_cast<Cliente_Business*>(&(*ctr[row])));
    QMap <int, QString>val;

    val.insert(0, ctr[row]->getNome());
    val.insert(1, ctr[row]->getCognome());
    val.insert(2, ctr[row]->getCF());
    val.insert(3, cb ? cb->getRagioneSociale() : "N/D");
    val.insert(4, cb ? cb->getPiva() : "N/D");
    val.insert(5, cb ? cb->getCFAzienda() : "N/D");
    val.insert(6, ctr[row]->getEmail());
    val.insert(7, ctr[row]->getTelefono());
    val.insert(8, ctr[row]->getDataNascita().toString());
    val.insert(9, ctr[row]->getTipoDocumentoString());
    val.insert(10, ctr[row]->getNumeroDoc());
    val.insert(11, ctr[row]->getRilascioDoc().toString());
    val.insert(12, ctr[row]->getScadenzaDoc().toString());
    val.insert(13, ctr[row]->getIndirizzo());
    val.insert(14, ctr[row]->getComune());
    val.insert(15, ctr[row]->getProvincia());
    val.insert(16, ctr[row]->getCAP());

    for(int column = 0; column < val.size(); ++column) {
      table->setItem(row, column, new QTableWidgetItem(val.value(column)));
    }

    val.clear();

    table->item(row, 8)->setTextAlignment(Qt::AlignCenter);
    table->item(row, 11)->setTextAlignment(Qt::AlignCenter);
    table->item(row, 12)->setTextAlignment(Qt::AlignCenter);
    table->item(row, 15)->setTextAlignment(Qt::AlignCenter);
  }
}

// SLOTS

void Tab_Clienti::undo() {
  // Estrapolo dalla coda di undo l'azione da annullare
  Cliente* clt(undoBuffer.pop_back()->clone());
  Action state = undoStateBuffer.pop_back();

  // E inserisco in redo l'azione da ripristinare
  //redoBuffer.push_back(ctr->clone());
  //redoStateBuffer.push_back(state);

  // Azione da annullare
  switch(state) {
    case Action::Added:
      gest.eliminaCliente(*clt, false);
      break;
    case Action::Deleted: {
        gest.addCliente(*clt);
      }
      break;
    case Action::Modified: {
        gest.modificaCliente(*clt, *gest.getCliente(ricerca::Codice_Fiscale, clt->getCF()));
      break;
    }
    default:
      break;
  }
  updateView();
  ref->updateView();
}

void Tab_Clienti::save() {
  QMessageBox msgBox(QMessageBox::Question, "Salva", "Salvare la cartella di lavoro?");
  msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Save);
  msgBox.setButtonText(QMessageBox::Save, tr("Salva"));
  msgBox.setButtonText(QMessageBox::Cancel, tr("Annulla"));
  int ret = msgBox.exec();
  switch (ret) {
    case QMessageBox::Save:
        gest.Export();
        undoBuffer.clear();
        undoStateBuffer.clear();
        break;
    case QMessageBox::Cancel: // Cancel was clicked
        break;
    default: // should never be reached
        break;
  }
  //redoBuffer.clear();
  //redoStateBuffer.clear();

  button->undoButton->setEnabled(false);
  //button->redoButton->setEnabled(false);
}

// Public

void Tab_Clienti::updateView(Action curState) {
  if(curState != Action::None)
    undoStateBuffer.push_back(curState);

  table->setRowCount(gest.getNumClienti());

  creaCelle();

  if(!table->rowCount()) {
     button->editButton->setEnabled(false);
     button->deleteButton->setEnabled(false);
     QMessageBox msgBox(QMessageBox::Information, "Attenzione", "Tutti i clienti sono stati eliminati.", QMessageBox::Ok);
     msgBox.exec();
  }

  if(undoBuffer.size()) button->undoButton->setEnabled(true);
  else button->undoButton->setEnabled(false);

  //if(redoBuffer.size()) button->redoButton->setEnabled(true);
  //else button->redoButton->setEnabled(false);
}
void Tab_Clienti::selectedCell() {
  QItemSelectionModel *select = table->selectionModel();
  if(select->hasSelection()) {
    button->editButton->setEnabled(true);
    button->deleteButton->setEnabled(true);
  }
}

void Tab_Clienti::addCliente() {
  FormClienti form = FormClienti(gest, "Aggiungi Cliente", 400, 575, this);
  if(form.exec() == QDialog::Accepted) {
    if(form.getTipo()) {
      Cliente* c(new Cliente_Business(form.getNome(), form.getCognome(), form.getEmail(), form.getTelefono(),
        form.getCF(), form.getDataNascita(), form.getTipoDocumento(), form.getNumeroDoc(), form.getScadenzaDoc(),
        form.getRilascioDoc(), form.getIndirizzo(), form.getComune(), form.getProvincia(), form.getCAP(),
        form.getRagioneSociale(), form.getPiva(), form.getCFAzienda()));
      gest.addCliente(*c->clone());
      delete c;
    } else {
      Cliente* c(new Cliente_Residenziale(form.getNome(), form.getCognome(), form.getEmail(), form.getTelefono(),
        form.getCF(), form.getDataNascita(), form.getTipoDocumento(), form.getNumeroDoc(), form.getScadenzaDoc(),
        form.getRilascioDoc(), form.getIndirizzo(), form.getComune(), form.getProvincia(), form.getCAP()));
      gest.addCliente(*c->clone());
      delete c;
    }
    // Aggiorna la vista
    updateView(Action::Added);
  }
}

void Tab_Clienti::editCliente() {
  QItemSelectionModel *select = table->selectionModel();
  if(select->hasSelection()) {
    FormClienti form = FormClienti(gest, "Modifica Cliente", 400, 575, this);
    Cliente* vecchio = gest.getCliente(ricerca::Codice_Fiscale, table->item(table->currentRow(), 2)->text());
    form.editPersona(*vecchio);
    if(form.exec() == QDialog::Accepted) {
      if(form.getTipo()) {
        Cliente* nuovo(new Cliente_Business(form.getNome(), form.getCognome(), form.getEmail(), form.getTelefono(),
          form.getCF(), form.getDataNascita(), form.getTipoDocumento(), form.getNumeroDoc(), form.getScadenzaDoc(),
          form.getRilascioDoc(), form.getIndirizzo(), form.getComune(), form.getProvincia(), form.getCAP(),
          form.getRagioneSociale(), form.getPiva(), form.getCFAzienda()));
        gest.modificaCliente(*nuovo->clone(), *vecchio);
        delete nuovo;
      } else {
        Cliente* nuovo(new Cliente_Residenziale(form.getNome(), form.getCognome(), form.getEmail(), form.getTelefono(),
          form.getCF(), form.getDataNascita(), form.getTipoDocumento(), form.getNumeroDoc(), form.getScadenzaDoc(),
          form.getRilascioDoc(), form.getIndirizzo(), form.getComune(), form.getProvincia(), form.getCAP()));
        gest.modificaCliente(*nuovo->clone(), *vecchio);
        delete nuovo;
      }
      updateView(Action::Modified);
    }
  }
}

void Tab_Clienti::deleteCliente() {
  if(gest.getNumClienti() > 0) {
    QList<QTableWidgetItem*> list = table->selectedItems();
    QString cf = list.at(2)->text();
    Cliente* clt = gest.getCliente(ricerca::Codice_Fiscale, cf);
    if(clt) {
      // Clono il cliente nel buffer prima di eliminarlo
      undoBuffer.push_back(clt);
      // Rimuovere anche i contratti associati?
      QMessageBox msgBox(QMessageBox::Question, "Elimina", "Vuoi eliminare anche i contratti associati?");
      msgBox.setInformativeText("Questa operazione NON è reversibile.");
      msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
      msgBox.setDefaultButton(QMessageBox::Yes);
      msgBox.setButtonText(QMessageBox::Yes, tr("Si"));
      int ret = msgBox.exec();
      switch (ret) {
        case QMessageBox::Yes:
          gest.eliminaCliente(*clt, true);
          break;
        case QMessageBox::No:
          gest.eliminaCliente(*clt, false);
          break;
      }
      // Aggiorna la vista
      updateView(Action::Deleted);
      ref->updateView();
    }
  }
}
