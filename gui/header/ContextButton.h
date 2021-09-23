#ifndef CONTEXTBUTTON_H
#define CONTEXTBUTTON_H
#include "MainWindow.h"
class ContextButton : public QWidget {
  Q_OBJECT
  public:
    QPushButton* addButton;
    QPushButton* editButton;
    QPushButton* deleteButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* saveButton;
    QPushButton* moneyButton;

    QHBoxLayout* layout;

    ContextButton(QWidget* = nullptr);

    QHBoxLayout* getLayout() const{ return layout; }

};

#endif // CONTEXTBUTTON_H
