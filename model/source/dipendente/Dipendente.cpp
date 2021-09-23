#include "../../header/dipendente/Dipendente.h"

// Costruttore
Dipendente::Dipendente(const QString& n, const QString& c, const QString& e, const QString& t, const Queue<UniqueID>& ids, const QString& cod, double p, double r)
  : Persona(n, c, e, t, ids), codDipendente(cod), percGuadagno(p), ritenutaAcc(r) {}

Dipendente::Dipendente(const QString& n, const QString& c, const QString& e, const QString& t, const QString& cod, double p, double r)
  : Persona(n, c, e, t), codDipendente(cod), percGuadagno(p), ritenutaAcc(r) {}


//Metodi getter
QString Dipendente::getCodice() const { return codDipendente; }

double Dipendente::getPercGuadagno() const { return percGuadagno; }

double Dipendente::getRitenuta() const { return ritenutaAcc; }

unsigned int Dipendente::getNumContratti() const { return getContrattiAssociati().size(); }

// Metodi setter
void Dipendente::setCodice(const QString& c) { codDipendente = c; }

void Dipendente::setPercGuadagno(double p) { percGuadagno = p; }

void Dipendente::setRitenuta(double r) { ritenutaAcc = r; }

// Operatori
bool Dipendente::operator==(const Dipendente& d) const {
  return Persona::operator==(d) && d.codDipendente == codDipendente && d.percGuadagno == percGuadagno && d.ritenutaAcc == ritenutaAcc;
}

bool Dipendente::operator!=(const Dipendente& d) const {
  return Persona::operator==(d) || d.codDipendente != codDipendente || d.percGuadagno != percGuadagno || d.ritenutaAcc != ritenutaAcc;
}

// Import
void Dipendente::Import(const QDomNodeList& list, Queue<QString>& string, Queue<UniqueID>& id, Queue<double>& d) {

  Queue<QDomNode> nodeList;

  for(int i = 0; i < list.length(); ++i) nodeList.push_back(list.at(i));

  Persona::Import(nodeList, string);

  for(int i = Persona::numElem; i < list.length(); ++i) {
    QDomElement elem = list.at(i).toElement();
    if(elem.attribute("nodeType").toStdString() == "string") string.push_back(elem.text());
    if(elem.attribute("nodeType").toStdString() == "double") d.push_back(elem.text().toDouble());
    if(elem.attribute("nodeType").toStdString() == "unique") {
      QDomNodeList ids = elem.childNodes();
      for(int j = 0; j < ids.length(); ++j)
        id.push_back(UniqueID(ids.at(j).toElement().text().toUInt()));
    }
  }
}

// Export
void Dipendente::Export(QDomDocument& dom, QDomElement& dipendente, const Dipendente& a) {
  Persona::Export(dom, dipendente, a);
  dipendente.appendChild(Persona::newQDomElement(dom, "codiceDipendente", "string", a.getCodice()));
  dipendente.appendChild(Persona::newQDomElement(dom, "percGuadagno", "double", QString::number(a.getPercGuadagno())));
  dipendente.appendChild(Persona::newQDomElement(dom, "ritenutaAcconto", "double", QString::number(a.getRitenuta())));

  QDomElement idCtr(dom.createElement("idContratti"));
  idCtr.setAttribute("nodeType", "unique");

  Queue<UniqueID> id = a.getContrattiAssociati();

  for(auto it = id.begin(); it != id.end(); ++it)
    idCtr.appendChild(Persona::newQDomElement(dom, "id", "", QString::number((*it).get())));

  dipendente.appendChild(idCtr);
}
