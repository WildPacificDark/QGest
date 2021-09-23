#include "../header/ContextButton.h"

ContextButton::ContextButton(QWidget* parent) : QWidget(parent) {
  addButton = new QPushButton;
  editButton = new QPushButton;
  deleteButton = new QPushButton;
  undoButton = new QPushButton;
  //redoButton = new QPushButton;
  saveButton = new QPushButton;
  moneyButton = new QPushButton;

  QString stylesheet = "\
    QPushButton { border: none; background-color: white; } \
    QPushButton:hover { background-color: rgb(245, 245, 245); border: 1px solid rgb(200, 200, 200); }\
    QPushButton:pressed { background-color: rgb(220, 220, 220); border: 1px solid rgb(200, 200, 200); }";

  addButton->setIcon(QIcon(":/img/plus.png"));
  addButton->setIconSize(QSize(20, 20));
  addButton->setFixedSize(QSize(32, 32));
  addButton->setStyleSheet(stylesheet);
  addButton->setToolTip("Aggiungi");
  addButton->setCursor(Qt::PointingHandCursor);

  editButton->setIcon(QIcon(":/img/editing.png"));
  editButton->setIconSize(QSize(20, 20));
  editButton->setFixedSize(QSize(32, 32));
  editButton->setStyleSheet(stylesheet);
  editButton->setToolTip("Modifica");
  editButton->setCursor(Qt::PointingHandCursor);

  deleteButton->setIcon(QIcon(":/img/cancel.png"));
  deleteButton->setIconSize(QSize(20, 20));
  deleteButton->setFixedSize(QSize(32, 32));
  deleteButton->setStyleSheet(stylesheet);
  deleteButton->setToolTip("Elimina");
  deleteButton->setCursor(Qt::PointingHandCursor);

  undoButton->setIcon(QIcon(":/img/undo.png"));
  undoButton->setIconSize(QSize(20, 20));
  undoButton->setFixedSize(QSize(32, 32));
  undoButton->setStyleSheet(stylesheet);
  undoButton->setToolTip("Annulla modifiche");
  undoButton->setCursor(Qt::PointingHandCursor);

  /*redoButton->setIcon(QIcon(":/img/redo.png"));
  redoButton->setIconSize(QSize(20, 20));
  redoButton->setFixedSize(QSize(32, 32));
  redoButton->setStyleSheet(stylesheet);
  redoButton->setToolTip("Ripristina modifiche");
  redoButton->setCursor(Qt::PointingHandCursor);*/

  saveButton->setIcon(QIcon(":/img/diskette.png"));
  saveButton->setIconSize(QSize(20, 20));
  saveButton->setFixedSize(QSize(32, 32));
  saveButton->setStyleSheet(stylesheet);
  saveButton->setToolTip("Salva");
  saveButton->setCursor(Qt::PointingHandCursor);

  moneyButton->setIcon(QIcon(":/img/wallet.png"));
  moneyButton->setIconSize(QSize(20, 20));
  moneyButton->setFixedSize(QSize(32, 32));
  moneyButton->setStyleSheet(styleSheet());
  saveButton->setToolTip("Calcola Stipendio");
  moneyButton->setCursor(Qt::PointingHandCursor);

  addButton->show();
  editButton->show();
  deleteButton->show();
  undoButton->show();
  //redoButton->show();
  saveButton->show();
  moneyButton->hide();

  addButton->setEnabled(true);
  editButton->setEnabled(false);
  deleteButton->setEnabled(false);
  undoButton->setEnabled(false);
  //redoButton->setEnabled(false);
  saveButton->setEnabled(true);
  moneyButton->setEnabled(false);

  layout = new QHBoxLayout;
  layout->addWidget(saveButton, Qt::AlignLeft);
  layout->addWidget(undoButton);
  //layout->addWidget(redoButton);
  layout->addWidget(addButton);
  layout->addWidget(editButton);
  layout->addWidget(deleteButton);
  layout->addWidget(moneyButton);
  layout->addStretch();
  layout->setSpacing(0);
  layout->setContentsMargins(0,0,0,0);
}
