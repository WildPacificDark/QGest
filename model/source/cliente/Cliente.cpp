#include "../../header/cliente/Cliente.h"

Cliente::Cliente(// Persona
  const QString& n, // Nome
  const QString& c, // Cognome
  const QString& e, // Email
  const QString& t, // Telefono
  const Queue<UniqueID>& id,
  // Cliente
  const QString& cf, // CF
  const Data& dn,    // Data nascita
  const Documento& td, // Tipo Doc
  const QString& nd, // Numero Doc
  const Data& sd,  // Data scadenza doc
  const Data & rd, // Data rilascio doc
  const QString& i, // Indirizzo
  const QString& cm, // Comune
  const QString& pv, // Provincia
  const QString & cp) // CAP
  : Persona(n, c, e, t, id),
    codiceFiscale(cf),
    dataNascita(dn),
    tipoDoc(td),
    numDoc(nd),
    scadDoc(sd),
    rilDoc(rd),
    indirizzo(i),
    comune(cm),
    provincia(pv),
    cap(cp) {}

Cliente::Cliente(// Persona
  const QString& n, // Nome
  const QString& c, // Cognome
  const QString& e, // Email
  const QString& t, // Telefono
  // Cliente
  const QString& cf, // CF
  const Data& dn,    // Data nascita
  const Documento& td, // Tipo Doc
  const QString& nd, // Numero Doc
  const Data& sd,  // Data scadenza doc
  const Data & rd, // Data rilascio doc
  const QString& i, // Indirizzo
  const QString& cm, // Comune
  const QString& pv, // Provincia
  const QString & cp) // CAP
  : Persona(n, c, e, t),
    codiceFiscale(cf),
    dataNascita(dn),
    tipoDoc(td),
    numDoc(nd),
    scadDoc(sd),
    rilDoc(rd),
    indirizzo(i),
    comune(cm),
    provincia(pv),
    cap(cp) {}

Cliente::Cliente(const Cliente& c)
  : Persona(c),
    codiceFiscale(c.codiceFiscale),
    dataNascita(c.dataNascita),
    tipoDoc(c.tipoDoc),
    numDoc(c.numDoc),
    scadDoc(c.scadDoc),
    rilDoc(c.rilDoc),
    indirizzo(c.indirizzo),
    comune(c.comune),
    provincia(c.provincia),
    cap(c.cap) {}

// Metodi getter
QString Cliente::getCF() const { return codiceFiscale; }
Data Cliente::getDataNascita() const { return dataNascita; }
Documento Cliente::getTipoDocumento() const { return tipoDoc; }
int Cliente::getTipoDocumentoInt() const { return (int)tipoDoc; }
QString Cliente::getNumeroDoc() const { return numDoc; }
Data Cliente::getScadenzaDoc() const { return scadDoc; }
Data Cliente::getRilascioDoc() const { return rilDoc; }
QString Cliente::getIndirizzo() const { return indirizzo; }
QString Cliente::getComune() const { return comune; }
QString Cliente::getProvincia() const { return provincia; }
QString Cliente::getCAP() const { return cap; }

QString Cliente::getTipoDocumentoString() const {
  switch(tipoDoc) {
    case Documento::CartaIdentita:
      return QString("Carta D'Identità");
    case Documento::Patente:
      return QString("Patente");
    case Documento::Passaporto:
      return QString("Passaporto");
  }
}

// Metodi setter
void Cliente::setCF(const QString& cf) { codiceFiscale = cf; }
void Cliente::setDataNasvita(const Data& d) { dataNascita = d; }
void Cliente::setTipoDoc(const Documento& d) { tipoDoc = d; }
void Cliente::setTipoDoc(int d) { tipoDoc = (Documento)d; }
void Cliente::setNumeroDoc(const QString& n) { numDoc = n; }
void Cliente::setScadenzaDoc(const Data& s) { scadDoc = s; }
void Cliente::setRilascioDoc(const Data& r) { rilDoc = r; }
void Cliente::setIndirizzo(const QString& i) { indirizzo = i; }
void Cliente::setComune(const QString& c) { comune = c; }
void Cliente::setProvincia(const QString& p) { provincia = p; }
void Cliente::setCAP(const QString& c) { cap = c; }

// Operatori
Cliente& Cliente::operator=(const Cliente& c) {
  if(this != &c) {
    Persona::operator=(c);
    codiceFiscale = c.codiceFiscale;
    dataNascita = c.dataNascita;
    tipoDoc = c.tipoDoc;
    numDoc = c.numDoc;
    scadDoc = c.scadDoc;
    rilDoc = c.rilDoc;
    indirizzo = c.indirizzo;
    comune = c.comune;
    provincia = c.provincia;
    cap = c.cap;
  }
  return *this;
}

bool Cliente::operator==(const Cliente& c) const {
  return Persona::operator==(c) && codiceFiscale == c.codiceFiscale && dataNascita == c.dataNascita && tipoDoc == c.tipoDoc
         && numDoc == c.numDoc && scadDoc == c.scadDoc && rilDoc == c.rilDoc && indirizzo == c.indirizzo
         && comune == c.comune && provincia == c.provincia && cap == c.cap;
}

bool Cliente::operator!=(const Cliente& c) const {
  return Persona::operator!=(c) || codiceFiscale != c.codiceFiscale || dataNascita != c.dataNascita || tipoDoc != c.tipoDoc
         || numDoc != c.numDoc || scadDoc != c.scadDoc || rilDoc != c.rilDoc || indirizzo != c.indirizzo
         || comune != c.comune || provincia != c.provincia || cap != c.cap;
}

void Cliente::Import(const Queue<QDomNode>& nodeList, Queue<QString>& stringList, Queue<Data>& dataList, Documento& doc, Queue<UniqueID>& id) {
  Queue<QDomNode> p;
  QDomElement elem;
  for(int i = 0; i < Persona::numElem; ++i) { p.push_back(nodeList[i]); }

  Persona::Import(p, stringList);

  for(unsigned int i = Persona::numElem; i < nodeList.size(); ++i) {
    elem = nodeList[i].toElement();
    if(elem.attribute("nodeType").toStdString() == "string") stringList.push_back(elem.text());
    if(elem.attribute("nodeType").toStdString() == "data") dataList.push_back(Data(elem.text()));
    if(elem.attribute("nodeType").toStdString() == "int") doc = (Documento)elem.text().toInt();
    if(elem.attribute("nodeType").toStdString() == "unique") {
      QDomNodeList ids = elem.childNodes();
      for(int j = 0; j < ids.length(); ++j)
        id.push_back(UniqueID(ids.at(j).toElement().text().toUInt()));
    }
  }
}

void Cliente::Export(QDomDocument& dom, QDomElement& cliente, const Cliente& c) {

  Persona::Export(dom, cliente, c);

  cliente.appendChild(Persona::newQDomElement(dom, "cf", "string", c.getCF()));
  cliente.appendChild(Persona::newQDomElement(dom, "dataNascita", "data", c.getDataNascita().toString()));
  cliente.appendChild(Persona::newQDomElement(dom, "tipoDoc", "int", QString::number(c.getTipoDocumentoInt())));
  cliente.appendChild(Persona::newQDomElement(dom, "numeroDoc", "string", c.getNumeroDoc()));
  cliente.appendChild(Persona::newQDomElement(dom, "scadenzaDoc", "data", c.getScadenzaDoc().toString()));
  cliente.appendChild(Persona::newQDomElement(dom, "rilascioDoc", "data", c.getRilascioDoc().toString()));
  cliente.appendChild(Persona::newQDomElement(dom, "indirizzo", "string", c.getIndirizzo()));
  cliente.appendChild(Persona::newQDomElement(dom, "comune", "string", c.getComune()));
  cliente.appendChild(Persona::newQDomElement(dom, "provincia", "string", c.getProvincia()));
  cliente.appendChild(Persona::newQDomElement(dom, "cap", "string", c.getCAP()));

  QDomElement idCtr(dom.createElement("idContratti"));
  idCtr.setAttribute("nodeType", "unique");

  Queue<UniqueID> id = c.getContrattiAssociati();

  for(auto it = id.begin(); it != id.end(); ++it)
    idCtr.appendChild(Persona::newQDomElement(dom, "id", "", QString::number((*it).get())));

  cliente.appendChild(idCtr);
}
