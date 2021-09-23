#include <QApplication>
#include <QStandardPaths>
#include "gui/header/MainWindow.h"
#include "model/header/Gestionale.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Gestionale gest;
   // Imposta la directory di lettura/scrittura
  QStringList paths = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
  gest.setDefaultFilePath(paths.at(0));
  // Controlla se esiste il file di dati
  QString file = gest.getDefaultFilePath() + '/' + gest.getDefaultFile();
  // Se il file non esiste, leggo i dati conservati internamente all'applicazione
  if(!QFile::exists(file)) {
    gest.Import(":/xml/data.xml");
    gest.Export(); // Creo il file per le successive letture/scritture
  } else { gest.Import(file); }

  MainWindow w(gest);
  w.show();

  return app.exec();



  return 0;
}
