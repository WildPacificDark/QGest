#ifndef TAB_DIPENDENTI_H
#define TAB_DIPENDENTI_H
#include "../MainWindow.h"
#include "Tab_Contratti.h"
#include "Tab_Clienti.h"
#include "Tab_Contratti.h"
#include "../dialog/FormDipendenti.h"

class Tab_Dipendenti : public QWidget {
  Q_OBJECT

  enum Action { None, Added, Deleted, Modified, Saved };

  private:
    Gestionale& gest;

    QGridLayout* grid;
    QTableWidget* table;
    ContextButton* button;
    Tab_Contratti* ref_a;
    Tab_Clienti* ref_b;
    Queue<Dipendente*> undoBuffer;
    //Queue<Contratto*> redoBuffer;

    Queue<Action> undoStateBuffer;
    //Queue<Action> redoStateBuffer;

  protected:
    void creaCelle();
    void selectedCell();

  public:
    Tab_Dipendenti(Tab_Contratti*, Tab_Clienti*, Gestionale& g);
    void updateView(Action = Action::None);
    ~Tab_Dipendenti();

  public slots:
    void calcolaStipendio();
    void addDipendente();
    void editDipendente();
    void deleteDipendente();
    //void redo();
    void undo();
    void save();
};


#endif // TAB_CONTRATTI_H
