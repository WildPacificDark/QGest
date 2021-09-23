#include "../../header/dipendente/Agente.h"

Agente::Agente(const QString& n, const QString& c, const QString& e, const QString& t, const Queue<UniqueID>& id, const QString& cod, double p, double r)
  : Dipendente(n, c, e, t, id, cod, p, r) {}

Agente::Agente(const QString& n, const QString& c, const QString& e, const QString& t, const QString& cod, double p, double r)
  : Dipendente(n, c, e, t, cod, p, r) {}


// Virtuali
Agente* Agente::clone() const { return new Agente(*this); }

double Agente::stipendio(double fatturato) const {
  double stipendio = fatturato - (fatturato * getPercGuadagno());
  stipendio -= stipendio * getRitenuta();
  return stipendio;
}

// Import
Persona* Agente::Import(const QDomNodeList& list) {
  Queue<QString> string;
  Queue<UniqueID> id;
  Queue<double> d;

  Dipendente::Import(list, string, id, d);

  if(string.size() < 5)
    for(unsigned int i = string.size(); i < 6; ++i)
      string.push_back(QString(""));

  if(d.size() < 2)
    for(unsigned int i = d.size(); i < 3; ++i)
      d.push_back(0);

  return new Agente(string[0], string[1], string[2], string[3], id, string[4], d[0], d[1]);
}

// Export
void Agente::Export(QDomDocument& dom, const Agente& a) {
  QDomElement agente(dom.createElement("dipendente"));
  agente.setAttribute("tipo", "agente");
  Dipendente::Export(dom, agente, a);
  dom.firstChild().appendChild(agente);
}
