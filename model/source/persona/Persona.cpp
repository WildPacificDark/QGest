#include "../../header/persona/Persona.h"

int Persona::numElem = 4;

Persona::Persona(const QString& n, const QString& s, const QString& m, const QString& p, const Queue<UniqueID> ids)
  : nome(n), cognome(s), email(m), telefono(p), conAssociato(ids) {}

Persona::Persona(const Persona& p) : nome(p.nome), cognome(p.cognome), email(p.email), telefono(p.telefono), conAssociato(p.conAssociato) {}

// Metodi getter
QString Persona::getNome() const { return nome; }
QString Persona::getCognome() const { return cognome; }
QString Persona::getEmail() const { return email; }
QString Persona::getTelefono() const { return telefono; }
Queue<UniqueID> Persona::getContrattiAssociati() const { return conAssociato; }

// Metodi setter
void Persona::setNome(const QString& n) { nome = n; }
void Persona::setCognome(const QString& s) { cognome = s; }
void Persona::setEmail(const QString& m) { email = m; }
void Persona::setTelefono(const QString& p) { telefono = p; }

void Persona::addContrattoAssociato(const UniqueID& u) { conAssociato.push_back(u); }

void Persona::addContrattoAssociato(int u) { conAssociato.push_back(UniqueID(u)); }

void Persona::rimuoviContrattoAssociato(const UniqueID& id) {
  try {
    for(auto it = conAssociato.begin(); it != conAssociato.end(); ++it) {
      if(*it == id) conAssociato.erase(it);
    }
  } catch (Queue_Exception& e) { qDebug() << e.what(); }
}

void Persona::rimuoviContrattoAssociato(int id) {
  try {
    for(auto it = conAssociato.begin(); it != conAssociato.end(); ++it) {
      if((*it).get() == (unsigned int)id) conAssociato.erase(it);
    }
  } catch (Queue_Exception& e) { qDebug() << e.what(); }
}


// Operatori
Persona& Persona::operator=(const Persona& p) {
  if(this != &p) {
    nome = p.nome;
    cognome = p.cognome;
    email = p.email;
    telefono = p.telefono;
    conAssociato = p.conAssociato;
  }
  return *this;
}

bool Persona::operator!=(const Persona& p) const {
  return nome != p.nome || cognome != p.cognome || email != p.email || telefono != p.telefono;
}

bool Persona::operator==(const Persona& p) const {
  return nome == p.nome && cognome == p.cognome && email == p.email && telefono == p.telefono;
}

QDomElement Persona::newQDomElement(QDomDocument& dom, const QString& name, const QString& type, const QString& value) {
  QDomElement elem(dom.createElement(name));
  elem.setAttribute("nodeType", type);
  elem.appendChild(dom.createTextNode(value));
  return elem;
}

void Persona::Import(const Queue<QDomNode>& nodeList, Queue<QString>& stringList) {
  for(unsigned int i = 0; i < nodeList.size(); ++i) {
    QDomNode curNode(nodeList[i]);
    stringList.push_back(curNode.toElement().text());
  }
}

void Persona::Export(QDomDocument& dom, QDomElement& persona, const Persona& p) {
  persona.appendChild(Persona::newQDomElement(dom, "nome", "string", p.getNome()));
  persona.appendChild(Persona::newQDomElement(dom, "cognome", "string", p.getCognome()));
  persona.appendChild(Persona::newQDomElement(dom, "email", "string", p.getEmail()));
  persona.appendChild(Persona::newQDomElement(dom, "telefono", "string", p.getTelefono()));
}
