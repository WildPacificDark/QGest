#include "../header/Contratto.h"

Contratto::Contratto(const UniqueID i, const QString& cf, const QString& codAg, const tipoContratto& t, const tipoCliente& tc, const Data& ds, const Data &dp,
                      const QString& ag, const QString& fo, const QString &no, const double& gb, const double& cs, const double& cm) :
  idContratto(i), idCliente(cf), idAgente(codAg), tipo(t), tipoC(tc), dataStipula(ds), dataSpedizione(dp), agenzia(ag),
  fornitore(fo), nomeOfferta(no), gettoneBase(gb), canvasSDD(cs), canvasMail(cm) {}

Contratto::Contratto(const QString& cf, const QString& codAg, const tipoContratto& t, const tipoCliente& tc, const Data& ds, const Data &dp,
                     const QString& ag, const QString& fo, const QString &no, const double& gb, const double& cs, const double& cm) :
  idCliente(cf), idAgente(codAg), tipo(t), tipoC(tc), dataStipula(ds), dataSpedizione(dp), agenzia(ag),
  fornitore(fo), nomeOfferta(no), gettoneBase(gb), canvasSDD(cs), canvasMail(cm) {}

Contratto::Contratto(const Contratto& c) :
  idContratto(c.idContratto),
  idCliente(c.idCliente),
  idAgente(c.idAgente),
  tipo(c.tipo),
  tipoC(c.tipoC),
  dataStipula(c.dataStipula),
  dataSpedizione(c.dataSpedizione),
  agenzia(c.agenzia),
  fornitore(c.fornitore),
  nomeOfferta(c.nomeOfferta),
  gettoneBase(c.gettoneBase),
  canvasSDD(c.canvasSDD),
  canvasMail(c.canvasMail) {}

// Metodi getter

UniqueID Contratto::getId() const { return idContratto; }

QString Contratto::getIdCliente() const { return idCliente; }

QString Contratto::getIdAgente() const { return idAgente; }

tipoContratto Contratto::getTipoContratto() const { return tipo; }

tipoCliente Contratto::getTipoCliente() const { return tipoC; }

Data Contratto::getDataStipula() const { return dataStipula; }

Data Contratto::getDataSpedizione() const { return dataSpedizione; }

QString Contratto::getAgenzia() const { return agenzia; }

QString Contratto::getFornitore() const { return fornitore; }

QString Contratto::getOfferta() const { return nomeOfferta; }

double Contratto::getGettoneBase() const { return gettoneBase; }

double Contratto::getCanvasSDD() const { return canvasSDD; }

double Contratto::getCanvassMail() const { return canvasMail; }

// Metodi setter

void Contratto::setIdCliente(const QString& i) { idCliente = i; }

void Contratto::setIdAgente(const QString& i) { idAgente = i; }

void Contratto::setTipoContratto(const tipoContratto& t) { tipo = t; }

void Contratto::setDataStipula(const Data& d) { dataStipula = d; }

void Contratto::setDataSpedizione(const Data& d)  { dataSpedizione = d; }

void Contratto::setAgenzia(const QString& a) { agenzia = a; }

void Contratto::setFornitore(const QString& f) { fornitore = f; }

void Contratto::setOfferta(const QString& n) { nomeOfferta = n; }

void Contratto::setGettoneBase(const double& g) { gettoneBase = g; }

void Contratto::setCanvasSDD(const double& c) { canvasSDD = c; }

void Contratto::setCanvassMail(const double& c)  { canvasMail = c; }

QString Contratto::getTipoContrattoToString() const {
  QString s;
  switch(tipo) {
    case tipoContratto::Luce:
      s.append("Luce");
      break;
    case tipoContratto::Gas:
      s.append("Gas");
      break;
    case tipoContratto::Telefonia:
      s.append("Telefonia");
      break;
  }
  return s;
}

QString Contratto::getTipoClienteToString() const {
  QString s;
  switch(tipoC) {
    case tipoCliente::Business:
      s.append("Business");
      break;
    case tipoCliente::Domestico:
      s.append("Domestico");
      break;
  }
  return s;
}

Contratto* Contratto::clone() const { return new Contratto(*this); }

double Contratto::compenso() const { return gettoneBase + canvasSDD + canvasMail; }

// Operatori

Contratto& Contratto::operator=(const Contratto& c) {
  if(this != &c) {
    tipo = c.tipo;
    tipoC = c.tipoC;
    dataStipula = c.dataStipula;
    dataSpedizione = c.dataSpedizione;
    agenzia = c.agenzia;
    fornitore = c.fornitore;
    nomeOfferta = c.nomeOfferta;
    gettoneBase = c.gettoneBase;
    canvasSDD = c.canvasSDD;
    canvasMail = c.canvasMail;
  }
  return *this;
}

bool Contratto::operator==(const Contratto& c) const {
  return idContratto == c.idContratto && idCliente == c.idCliente && idAgente == c.idAgente && tipo == c.tipo &&
      tipoC == c.tipoC && dataStipula == c.dataStipula && dataSpedizione == c.dataSpedizione && agenzia == c.agenzia &&
      nomeOfferta == c.nomeOfferta && gettoneBase == c.gettoneBase && canvasSDD == c.canvasSDD && canvasMail == c.canvasMail;
};
bool Contratto::operator!=(const Contratto& c) const {
  return idContratto != c.idContratto || idCliente != c.idCliente || idAgente != c.idAgente || tipo != c.tipo ||
      tipoC != c.tipoC || dataStipula != c.dataStipula || dataSpedizione != c.dataSpedizione || agenzia != c.agenzia ||
      nomeOfferta != c.nomeOfferta || gettoneBase != c.gettoneBase || canvasSDD != c.canvasSDD || canvasMail != c.canvasMail;
};

QDomElement Contratto::newQDomElement(QDomDocument& dom, const QString& name, const QString& type, const QString& value) {
  QDomElement elem(dom.createElement(name));
  elem.setAttribute("nodeType", type);
  elem.appendChild(dom.createTextNode(value));
  return elem;
}

Contratto* Contratto::Import(const QDomNodeList& nodeList) {
  Queue<QString> string;
  Queue<Data> data;
  Queue<double> gettone;
  unsigned int id = 0;
  tipoContratto tipo = tipoContratto::Luce;
  tipoCliente tipoC = tipoCliente::Domestico;

  for(int i = 0; i < nodeList.size(); ++i) {
    QDomElement elem = nodeList.at(i).toElement();
    if(elem.attribute("nodeType").toStdString() == "string") string.push_back(elem.text());
    if(elem.attribute("nodeType").toStdString() == "data") data.push_back(Data(elem.text()));
    if(elem.attribute("nodeType").toStdString() == "unique") id = elem.text().toUInt();
    if(elem.attribute("nodeType").toStdString() == "double") gettone.push_back(elem.text().toDouble());
    if(elem.attribute("nodeType").toStdString() == "ctrType") tipo = (tipoContratto)elem.text().toInt();
    if(elem.attribute("nodeType").toStdString() == "cliType") tipoC = (tipoCliente)elem.text().toInt();
  }

  UniqueID::setId(id);

  if(string.size() < 5)
    for(unsigned int i = string.size(); i < 5; ++i)
      string.push_back(QString(""));

  if(data.size() < 2)
    for(unsigned int i = data.size(); i < 2; ++i)
      data.push_back(Data());

  if(gettone.size() < 3)
    for(unsigned int i = data.size(); i < 3; ++i)
      gettone.push_back(0);

  return new Contratto(UniqueID(id), string[0], string[1], tipo, tipoC, data[0], data[1], string[2], string[3], string[4], gettone[0], gettone[1], gettone[2]);
}

void Contratto::Export(QDomDocument& dom, const Contratto& c) {
  QDomElement contratto(dom.createElement("contratto"));

  contratto.appendChild(Contratto::newQDomElement(dom, "idContratto", "unique", QString::number(c.getId().get())));
  contratto.appendChild(Contratto::newQDomElement(dom, "idCliente", "string", c.getIdCliente()));
  contratto.appendChild(Contratto::newQDomElement(dom, "idAgente", "string", c.getIdAgente()));
  contratto.appendChild(Contratto::newQDomElement(dom, "tipoContratto", "ctrType", QString::number(c.getTipoContratto())));
  contratto.appendChild(Contratto::newQDomElement(dom, "tipoCliente", "cliType", QString::number(c.getTipoCliente())));
  contratto.appendChild(Contratto::newQDomElement(dom, "dataStipula", "data", c.getDataStipula().toString()));
  contratto.appendChild(Contratto::newQDomElement(dom, "dataSpedizione", "data", c.getDataSpedizione().toString()));
  contratto.appendChild(Contratto::newQDomElement(dom, "agenzia", "string", c.getAgenzia()));
  contratto.appendChild(Contratto::newQDomElement(dom, "fornitore", "string", c.getFornitore()));
  contratto.appendChild(Contratto::newQDomElement(dom, "nomeOfferta", "string", c.getOfferta()));
  contratto.appendChild(Contratto::newQDomElement(dom, "gettoneBase", "double", QString::number(c.getGettoneBase())));
  contratto.appendChild(Contratto::newQDomElement(dom, "canvasSDD", "double", QString::number(c.getCanvasSDD())));
  contratto.appendChild(Contratto::newQDomElement(dom, "canvasMail", "double", QString::number(c.getCanvassMail())));

  dom.firstChild().appendChild(contratto);
}
