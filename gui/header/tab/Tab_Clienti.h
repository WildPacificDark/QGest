#ifndef TAB_CLIENTI_H
#define TAB_CLIENTI_H
#include "../MainWindow.h"
#include "../dialog/FormClienti.h"
#include "Tab_Contratti.h"

class Tab_Clienti : public QWidget {
  Q_OBJECT

  enum Action { None, Added, Deleted, Modified, Saved };

  private:
    Gestionale& gest;

    QGridLayout* grid;
    QTableWidget* table;
    ContextButton* button;
    Tab_Contratti* ref;
    Queue<Cliente*> undoBuffer;
    //Queue<Contratto*> redoBuffer;

    Queue<Action> undoStateBuffer;
    //Queue<Action> redoStateBuffer;

  protected:
    void creaCelle();
    void selectedCell();

  public:
    Tab_Clienti(Tab_Contratti*, Gestionale& g);
    void updateView(Action = Action::None);
    ~Tab_Clienti();

  public slots:
    void addCliente();
    void editCliente();
    void deleteCliente();
    //void redo();
    void undo();
    void save();
};

#endif // TAB_CLIENTI_H
