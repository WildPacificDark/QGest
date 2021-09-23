#include "../../header/dipendente/Manager.h"

Manager::Manager(const QString& n, const QString& c, const QString& e, const QString& t, const Queue<UniqueID>& id, const QString& cod, double s, double p, double r, double f)
  : Dipendente(n, c, e, t, id, cod, s, p), fissoMensile(r), bonus(f) {}

Manager::Manager(const QString& n, const QString& c, const QString& e, const QString& t, const QString& cod, double s, double p, double r, double f)
  : Dipendente(n, c, e, t, cod, s, p), fissoMensile(r), bonus(f) {}

// Metodi getter
double Manager::getFissoMensile() const { return fissoMensile; }
double Manager::getBonus() const { return bonus; }

// Metodi setter
void Manager::setFissoMensile(double f) { fissoMensile = f; }
void Manager::setBonus(double b) { bonus = b; }

// Virtuali
Manager* Manager::clone() const { return new Manager(*this); }

double Manager::stipendio(double fatturato) const {
  double stipendio = fatturato - (fatturato * getPercGuadagno());
  if(getNumContratti() > 5) stipendio += stipendio * bonus;
  stipendio -= stipendio * getRitenuta();
  return stipendio + fissoMensile;
}

// Operatori
bool Manager::operator==(const Manager& m) const { return Dipendente::operator==(m) && fissoMensile == m.fissoMensile && bonus == m.bonus; }
bool Manager::operator!=(const Manager& m) const { return Dipendente::operator!=(m) || fissoMensile != m.fissoMensile || bonus != m.bonus; }

// Import
Persona* Manager::Import(const QDomNodeList& list) {
  Queue<QString> string;
  Queue<UniqueID> id;
  Queue<double> d;

  Dipendente::Import(list, string, id, d);

  if(string.size() < 5)
    for(unsigned int i = string.size(); i < 5; ++i)
      string.push_back(QString(""));

  if(d.size() < 4)
    for(unsigned int i = d.size(); i < 4; ++i)
      d.push_back(0);

  return new Manager(string[0], string[1], string[2], string[3], id, string[4], d[0], d[1], d[2], d[3]);
}

void Manager::Export(QDomDocument& dom, const Manager& m) {
  QDomElement manager(dom.createElement("dipendente"));
  manager.setAttribute("tipo", "manager");

  Dipendente::Export(dom, manager, m);

  manager.appendChild(Persona::newQDomElement(dom, "fissoMensile", "double", QString::number(m.getFissoMensile())));
  manager.appendChild(Persona::newQDomElement(dom, "bonus", "double", QString::number(m.getBonus())));

  dom.firstChild().appendChild(manager);
}
