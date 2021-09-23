#include "../header/MainWindow.h"
#include "../header/tab/Tab_Contratti.h"
#include "../header/tab/Tab_Clienti.h"
#include "../header/tab/Tab_Dipendenti.h"

MainWindow::MainWindow(Gestionale& _gest, QWidget* parent) : QWidget(parent), gest(_gest) {

  tabWidget = new QTabWidget;

  Tab_Contratti* t_ctr = new Tab_Contratti(gest);
  Tab_Clienti* t_clt = new Tab_Clienti(t_ctr, gest);
  Tab_Dipendenti* t_dip = new Tab_Dipendenti(t_ctr, t_clt, gest);

  tabWidget->addTab(t_ctr, "Contratti");
  tabWidget->addTab(t_clt, "Clienti");
  tabWidget->addTab(t_dip, "Dipendenti");

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(tabWidget);
  setMaximumWidth(1800);
  setMinimumWidth(1000);
  setMinimumHeight(500);
  setLayout(mainLayout);
  setWindowTitle(tr("Gestionale"));

}
