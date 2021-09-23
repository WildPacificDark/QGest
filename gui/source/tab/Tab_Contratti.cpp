#include "../../header/tab/Tab_Contratti.h"
#include <QList>

Tab_Contratti::Tab_Contratti(Gestionale& g)
  : gest(g), grid(new QGridLayout), table(new QTableWidget(gest.getNumContratti(), 13, this)) {

  QStringList headers;
  headers << "Id" << "Agenzia" << "Data Stipula" << "Data Spedizione" << "Agente" << "Cliente"
          << "Tipo Cliente" << "Fornitore" << "Offerta" << "Tipo Ctr." << "Gettone" << "SDD" << "Email";

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

  connect(table, &QTableWidget::itemSelectionChanged, this, &Tab_Contratti::selectedCell);

  button = new ContextButton;

  connect(button->addButton, &QPushButton::clicked, this, &Tab_Contratti::addContratto);
  connect(button->editButton, &QPushButton::clicked, this, &Tab_Contratti::editContratto);
  connect(button->deleteButton, &QPushButton::clicked, this, &Tab_Contratti::deleteContratto);
  connect(button->undoButton, &QPushButton::clicked, this, &Tab_Contratti::undo);
  //connect(button->redoButton, &QPushButton::clicked, this, &Tab_Contratti::redo);
  connect(button->saveButton, &QPushButton::clicked, this, &Tab_Contratti::save);

  grid->addLayout(button->layout, 0, 0);
  grid->addWidget(table, 1, 0);

  setLayout(grid);

}

Tab_Contratti::~Tab_Contratti() {
  delete button;
  delete table;
  delete grid;
}

/// Protected

void Tab_Contratti::creaCelle() {
  Queue<Contratto*> ctr = gest.getAllContratti();
  QFont f;
  f.setBold(true);

  int row = 0;

  for(; row < table->rowCount(); ++row) {
    table->setRowHeight(row, 24);

    QMap <int, QString>val;
    val.insert(0, QString::number(ctr[row]->getId().get()));
    val.insert(1, ctr[row]->getAgenzia());
    val.insert(2, ctr[row]->getDataStipula().toString());
    val.insert(3, ctr[row]->getDataSpedizione().toString());

    Dipendente* d(gest.getDipendente(ricerca::Codice_Dipendente, ctr[row]->getIdAgente()));
    val.insert(4, d ? QString("%1%2").arg(d->getCognome().at(0)).arg(d->getNome().at(0)) : "N/D");

    Cliente* c(gest.getCliente(ricerca::Codice_Fiscale, ctr[row]->getIdCliente()));
    if(c) {
      if(Cliente_Business* b = dynamic_cast<Cliente_Business*>(c)) {
        val.insert(5, b->getRagioneSociale());
      } else { val.insert(5, c->getNome() + " " + c->getCognome()); }
    } else { val.insert(5, "N/D"); }

    val.insert(6, ctr[row]->getTipoClienteToString());
    val.insert(7, ctr[row]->getFornitore());
    val.insert(8, ctr[row]->getOfferta());
    val.insert(9,ctr[row]->getTipoContrattoToString());
    val.insert(10, QString::number(ctr[row]->getGettoneBase()));
    val.insert(11, QString::number(ctr[row]->getCanvasSDD()));
    val.insert(12, QString::number(ctr[row]->getCanvassMail()));

    for(int column = 0; column < val.size(); ++column) {
      table->setItem(row, column, new QTableWidgetItem(val.value(column)));
    }

    // Id
    table->item(row, 0)->setForeground(QBrush(QColor(255, 0, 0)));
    table->item(row, 0)->setTextAlignment(Qt::AlignCenter);
    // Data Stipula
    table->item(row, 2)->setTextAlignment(Qt::AlignCenter);
    // Data Invio
    table->item(row, 3)->setTextAlignment(Qt::AlignCenter);
    // Agente
    table->item(row, 4)->setTextAlignment(Qt::AlignCenter);
    table->item(row, 4)->setFont(f);
    // Gettone Base
    table->item(row, 10)->setFont(f);
    table->item(row, 10)->setTextAlignment(Qt::AlignCenter);
    table->item(row, 10)->setForeground(QColor(0, 86, 143));
    // Canvas SDD
    table->item(row, 11)->setFont(f);
    table->item(row, 11)->setTextAlignment(Qt::AlignCenter);
    table->item(row, 11)->setForeground(QColor(0, 86, 143));
    // Canvas Mail
    table->item(row, 12)->setFont(f);
    table->item(row, 12)->setTextAlignment(Qt::AlignCenter);
    table->item(row, 12)->setForeground(QColor(0, 86, 143));

    val.clear();
  }
}

// SLOTS

void Tab_Contratti::undo() {
  // Estrapolo dalla coda di undo l'azione da annullare
  Contratto* ctr = undoBuffer.pop_back();
  Action state = undoStateBuffer.pop_back();

  // E inserisco in redo l'azione da ripristinare
  //redoBuffer.push_back(ctr->clone());
  //redoStateBuffer.push_back(state);

  // Azione da annullare
  switch(state) {
    case Action::Added:
      gest.eliminaContratto(*ctr);
      break;
    case Action::Deleted: {
        Cliente* c(gest.getCliente(ricerca::Codice_Fiscale, ctr->getIdCliente()));
        Dipendente* d(gest.getDipendente(ricerca::Codice_Dipendente, ctr->getIdAgente()));
        gest.addContratto(*ctr->clone(), *c, *d);
      }
      break;
    case Action::Modified: {
        gest.modificaContratto(*ctr->clone(), *(gest.getContrattoById(ctr->getId())));
      break;
    }
    default:
      break;
  }
  delete ctr;
  updateView();
}

void Tab_Contratti::save() {
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
  // Cancella il buffer redo/undo
  //redoBuffer.clear();
  //redoStateBuffer.clear();

  button->undoButton->setEnabled(false);
  //button->redoButton->setEnabled(false);
}

// Public

void Tab_Contratti::updateView(Action curState) {
  if(curState != Action::None)
    undoStateBuffer.push_back(curState);

  table->setRowCount(gest.getNumContratti());

  creaCelle();

  if(!table->rowCount()) {
     button->editButton->setEnabled(false);
     button->deleteButton->setEnabled(false);
     QMessageBox msgBox(QMessageBox::Information, "Attenzione", "Tutti i contratti sono stati eliminati.", QMessageBox::Ok);
     msgBox.exec();
  }

  if(undoBuffer.size()) button->undoButton->setEnabled(true);
  else button->undoButton->setEnabled(false);
}

void Tab_Contratti::selectedCell() {
  QItemSelectionModel *select = table->selectionModel();
  if(select->hasSelection()) {
    button->editButton->setEnabled(true);
    button->deleteButton->setEnabled(true);
  }
}

void Tab_Contratti::addContratto() {
  QMessageBox msgBox(QMessageBox::Icon::Information, "Avviso", "Puoi inserire solo contratti di clienti esistenti. Per aggiungere un contratto intestato \
ad un nuovo cliente, è prima necessario registrare tale cliente.", QMessageBox::Ok);
  msgBox.exec();
  FormContratti form = FormContratti(gest, "Aggiungi Contratto", 350, 400, this);
  if(form.exec() == QDialog::Accepted) {
    Cliente* c(form.getCliente());
    Dipendente* d(form.getAgente());
    if(c && d) {
      Contratto* ctr = new Contratto(c->getCF(), d->getCodice(), form.getTipoContratto(), form.getTipoCliente(), form.getDataStipula(),
        form.getDataSpedizione(), form.getAgenzia(), form.getFornitore(), form.getOfferta(), form.getGettone(), form.getSDD(), form.getMail());
      gest.addContratto(*ctr->clone(), *c, *d);
      // Clono il contratto nel buffer
      undoBuffer.push_back(ctr->clone());
      delete ctr;
      // Aggiorna la vista
      updateView(Action::Added);
    } else {
      QMessageBox msgBox(QMessageBox::Icon::Critical, "Errore", "Si è verificato un errore nell'inserimento del contratto.", QMessageBox::Ok);
      msgBox.exec();
    }
  }
};

void Tab_Contratti::editContratto() {
  QItemSelectionModel *select = table->selectionModel();
  if(select->hasSelection()) {
    int id = select->selectedRows(0).at(0).data().toString().toInt();
    Contratto* vecchio = gest.getContrattoById(id);
    FormContratti form = FormContratti(gest, "Modifica Contratto", 350, 400, this);
    form.editContratto(*vecchio);
    if(form.exec() == QDialog::Accepted) {
      Cliente* c(form.getCliente());
      Dipendente* d(form.getAgente());
      if(c && d) {
        Contratto* nuovo = new Contratto(form.getId(), c->getCF(), d->getCodice(), form.getTipoContratto(), form.getTipoCliente(),
          form.getDataStipula(), form.getDataSpedizione(), form.getAgenzia(), form.getFornitore(), form.getOfferta(),
          form.getGettone(), form.getSDD(), form.getMail());
        // Clono il contratto nel buffer prima di modificarlo
        undoBuffer.push_back(vecchio->clone());
        // Modifico il contratto
        gest.modificaContratto(*nuovo->clone(), *vecchio);
        // Elimino il temporaneo
        delete nuovo;
        // Aggiorna la vista
        updateView(Action::Modified);
      } else {
        QMessageBox msgBox(QMessageBox::Icon::Critical, "Errore", "Si è verificato un errore nella modifica del contratto.", QMessageBox::Ok);
        msgBox.exec();
      }
    }
  }
}

void Tab_Contratti::deleteContratto() {
  if(gest.getNumContratti() > 0) {
    QList<QTableWidgetItem*> list = table->selectedItems();
    int id = list.at(0)->text().toInt();
    Contratto* ctr = gest.getContrattoById(UniqueID(id));
    if(ctr) {
      // Clono il contratto nel buffer prima di eliminarlo
      undoBuffer.push_back(ctr->clone());
      // Elimino il contratto
      gest.eliminaContratto(*ctr);
      // Aggiorna la vista
      updateView(Action::Deleted);
    }
  }
}
