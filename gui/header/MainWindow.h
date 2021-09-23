#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>
#include <QStringList>
#include <QComboBox>
#include <QLineEdit>
#include <QHeaderView>
#include <QMap>
#include <QDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "../../model/header/Gestionale.h"

class MainWindow : public QWidget {
  Q_OBJECT
  private:
     Gestionale& gest;
     QTabWidget* tabWidget;

  public:
    MainWindow(Gestionale&, QWidget* = nullptr);
    ~MainWindow() { delete tabWidget; }
};

#endif
