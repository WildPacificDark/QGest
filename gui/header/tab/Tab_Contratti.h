#ifndef TAB_CONTRATTI_H
#define TAB_CONTRATTI_H
#include "../MainWindow.h"
#include "../ContextButton.h"
#include "../dialog/FormContratti.h"

enum Action { None, Added, Deleted, Modified, Saved };

class Tab_Contratti : public QWidget {
  Q_OBJECT

  private:
    Gestionale& gest;

    QGridLayout* grid;
    QTableWidget* table;
    ContextButton* button;

    Queue<Contratto*> undoBuffer;
    //Queue<Contratto*> redoBuffer;

    Queue<Action> undoStateBuffer;
    //Queue<Action> redoStateBuffer;

  protected:
    void creaCelle();
    void selectedCell();

  public:
    Tab_Contratti(Gestionale& g);

    QTableWidget* getTable() const;
    ContextButton* getContextButton() const;
    Queue<Contratto*> getCtrBuffer() const;
    Queue<Action> getActionBuffer() const;
    void updateView(Action = Action::None);

    ~Tab_Contratti();

  public slots:
    void addContratto();
    void editContratto();
    void deleteContratto();
    //void redo();
    void undo();
    void save();
};

#endif // TAB_CONTRATTI_H
