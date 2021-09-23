#include <QList>
#include "../../header/tab/Tab_Dipendenti.h"
#include "../../header/dialog/FormDipendenti.h"

Tab_Dipendenti::Tab_Dipendenti(Tab_Contratti* tab_ctr, Tab_Clienti* tab_ctl, Gestionale& g)
  : gest(g), grid(new QGridLayout), table(new QTableWidget(gest.getNumDipendenti(), 17, this)), ref_a(tab_ctr), ref_b(tab_ctl) {

  QStringList headers;
  headers << "Nome" << "Cognome" << "Codice Agente" << "Tipo Agente" << "Telefono" << "Email" << "Ritenuta Acconto" << "Perc. Guadagno" << "Fisso" << "Bonus";

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

  connect(table, &QTableWidget::itemSelectionChanged, this, &Tab_Dipendenti::selectedCell);

  button = new ContextButton;

  connect(button->addButton, &QPushButton::clicked, this, &Tab_Dipendenti::addDipendente);
  connect(button->editButton, &QPushButton::clicked, this, &Tab_Dipendenti::editDipendente);
  connect(button->deleteButton, &QPushButton::clicked, this, &Tab_Dipendenti::deleteDipendente);
  connect(button->undoButton, &QPushButton::clicked, this, &Tab_Dipendenti::undo);
  connect(button->saveButton, &QPushButton::clicked, this, &Tab_Dipendenti::save);
  connect(button->moneyButton, &QPushButton::clicked, this, &Tab_Dipendenti::calcolaStipendio);

  button->moneyButton->show();
  button->moneyButton->setEnabled(true);

  grid->addLayout(button->layout, 0, 0);
  grid->addWidget(table, 1, 0);

  setLayout(grid);
}

Tab_Dipendenti::~Tab_Dipendenti() {
  delete button;
  delete table;
  delete grid;
}

/// Protected

void Tab_Dipendenti::creaCelle() {
  Queue<Dipendente*> ctr = gest.getAllAgenti();
  QFont f;
  f.setBold(true);

  int row = 0;

  for(; row < table->rowCount(); ++row) {
    table->setRowHeight(row, 24);

    Manager* m(dynamic_cast<Manager*>(&(*ctr[row])));
    QMap <int, QString>val;

    val.insert(0, ctr[row]->getNome());
    val.insert(1, ctr[row]->getCognome());
    val.insert(2, ctr[row]->getCodice());
    val.insert(3, m ? "Manager" : "Agente");
    val.insert(4, ctr[row]->getTelefono());
    val.insert(5, ctr[row]->getEmail());
    val.insert(6, QString::number(ctr[row]->getRitenuta()));
    val.insert(7, QString::number(ctr[row]->getPercGuadagno()));
    val.insert(8, m ? QString::number(m->getFissoMensile()) : "N/D");
    val.insert(9, m ? QString::number(m->getBonus()) : "N/D");

    for(int column = 0; column < val.size(); ++column) {
      table->setItem(row, column, new QTableWidgetItem(val.value(column)));
    }

    val.clear();

    table->item(row, 5)->setTextAlignment(Qt::AlignCenter);
    table->item(row, 6)->setTextAlignment(Qt::AlignCenter);
    table->item(row, 7)->setTextAlignment(Qt::AlignCenter);
    table->item(row, 8)->setTextAlignment(Qt::AlignCenter);
  }

  table->setColumnCount(10);
}

// SLOTS

void Tab_Dipendenti::calcolaStipendio() {
  QItemSelectionModel *select = table->selectionModel();
  if(select->hasSelection()) {
    Dipendente* d = gest.getDipendente(ricerca::Codice_Dipendente, table->item(table->currentRow(), 2)->text());
    QString text("Il compenso totale di ");
    text.append(d->getNome()).append(" ").append(d->getCognome()).append(" è: ");
    text.append(QString::number(gest.stipendioDipendente(*d)));
    QMessageBox msgBox(QMessageBox::Information, "Stipendio", text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
  }
}

void Tab_Dipendenti::undo() {
  // Estrapolo dalla coda di undo l'azione da annullare
  Dipendente* clt(undoBuffer.pop_back()->clone());
  Action state = undoStateBuffer.pop_back();

  // E inserisco in redo l'azione da ripristinare
  //redoBuffer.push_back(ctr->clone());
  //redoStateBuffer.push_back(state);

  // Azione da annullare
  switch(state) {
    case Action::Added:
      gest.eliminaDipendente(*clt, false);
      break;
    case Action::Deleted: {
        gest.addDipendente(*clt);
      }
      break;
    case Action::Modified: {
        gest.modificaDipendente(*clt, *gest.getDipendente(ricerca::Codice_Dipendente, clt->getCodice()));
      break;
    }
    default:
      break;
  }
  updateView();
  ref_a->updateView();
  ref_b->updateView();
}

void Tab_Dipendenti::save() {
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

void Tab_Dipendenti::updateView(Action curState) {
  if(curState != Action::None)
    undoStateBuffer.push_back(curState);

  table->setRowCount(gest.getNumDipendenti());

  creaCelle();

  if(!table->rowCount()) {
     button->editButton->setEnabled(false);
     button->deleteButton->setEnabled(false);
     QMessageBox msgBox(QMessageBox::Information, "Attenzione", "Tutti gli agenti sono stati eliminati.", QMessageBox::Ok);
     msgBox.exec();
  }

  if(undoBuffer.size()) button->undoButton->setEnabled(true);
  else button->undoButton->setEnabled(false);

  //if(redoBuffer.size()) button->redoButton->setEnabled(true);
  //else button->redoButton->setEnabled(false);
}

void Tab_Dipendenti::selectedCell() {
  QItemSelectionModel *select = table->selectionModel();
  if(select->hasSelection()) {
    button->editButton->setEnabled(true);
    button->deleteButton->setEnabled(true);
  }
}

void Tab_Dipendenti::addDipendente() {
  FormDipendenti form = FormDipendenti(gest, "Aggiungi Dipendente", 400, 325, this);
  if(form.exec() == QDialog::Accepted) {
    if(form.getTipo()) {
      Dipendente* c(new Manager(form.getNome(), form.getCognome(), form.getEmail(), form.getTelefono(), form.getCodice(),
                                form.getGuadagno(), form.getRitenuta(), form.getFisso(), form.getBonus()));
      gest.addDipendente(*c->clone());
      delete c;
    } else {
      Dipendente* c(new Agente(form.getNome(), form.getCognome(), form.getEmail(), form.getTelefono(), form.getCodice(),
                               form.getGuadagno(), form.getRitenuta()));
      gest.addDipendente(*c->clone());
      delete c;
    }
    // Aggiorna la vista
    updateView(Action::Added);
  }
}

void Tab_Dipendenti::editDipendente() {
  QItemSelectionModel *select = table->selectionModel();
  if(select->hasSelection()) {
    FormDipendenti form = FormDipendenti(gest, "Modifica Dipendente", 400, 325, this);
    Dipendente* vecchio = gest.getDipendente(ricerca::Codice_Dipendente, table->item(table->currentRow(), 2)->text());
    form.editPersona(*vecchio);
    if(form.exec() == QDialog::Accepted) {
      if(form.getTipo()) {
        Dipendente* nuovo(new Manager(form.getNome(), form.getCognome(), form.getEmail(), form.getTelefono(), form.getCodice(),
                                      form.getGuadagno(), form.getRitenuta(), form.getFisso(), form.getBonus()));
        gest.modificaDipendente(*nuovo->clone(), *vecchio);
        delete nuovo;
      } else {
        Dipendente* nuovo(new Agente(form.getNome(), form.getCognome(), form.getEmail(), form.getTelefono(), form.getCodice(),
                                     form.getGuadagno(), form.getRitenuta()));
        gest.modificaDipendente(*nuovo->clone(), *vecchio);
        delete nuovo;
      }
      updateView(Action::Modified);
    }
  }
}

void Tab_Dipendenti::deleteDipendente() {
  if(gest.getNumDipendenti() > 0) {
    QList<QTableWidgetItem*> list = table->selectedItems();
    QString cf = list.at(2)->text();
    Dipendente* clt = gest.getDipendente(ricerca::Codice_Dipendente, cf);
    if(clt) {
      // Clono il Dipendente nel buffer prima di eliminarlo
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
          gest.eliminaDipendente(*clt, true);
          break;
        case QMessageBox::No:
          gest.eliminaDipendente(*clt, false);
          break;
      }
      // Aggiorna la vista
      updateView(Action::Deleted);
      ref_a->updateView();
      ref_b->updateView();
    }
  }
}
