#include "../../header/cliente/Cliente_Res.h"

Cliente_Residenziale::Cliente_Residenziale(
  const QString& n, // Nome
  const QString& c, // Cognome
  const QString& e, // Email
  const QString& t, // Telefono
  const Queue<UniqueID>& ids,
  // Cliente
  const QString& cf, // CF
  const Data& dn,    // Data nascita
  const Documento& tp, // Tipo documento
  const QString& nd, // Numero Doc
  const Data& sd,    // Data scadenza doc
  const Data& rd,    // Data rilascio doc
  const QString& i, // Indirizzo
  const QString& cm, // Comune
  const QString& pv, // Provincia
  const QString& cp // CAP
) : Cliente(n, c, e, t, ids, cf, dn, tp, nd, sd, rd, i, cm, pv, cp) {};

Cliente_Residenziale::Cliente_Residenziale(
  const QString& n, // Nome
  const QString& c, // Cognome
  const QString& e, // Email
  const QString& t, // Telefono
  // Cliente
  const QString& cf, // CF
  const Data& dn,    // Data nascita
  const Documento& tp, // Tipo documento
  const QString& nd, // Numero Doc
  const Data& sd,    // Data scadenza doc
  const Data& rd,    // Data rilascio doc
  const QString& i, // Indirizzo
  const QString& cm, // Comune
  const QString& pv, // Provincia
  const QString& cp // CAP
) : Cliente(n, c, e, t, cf, dn, tp, nd, sd, rd, i, cm, pv, cp) {};

Cliente_Residenziale* Cliente_Residenziale::clone() const { return new Cliente_Residenziale(*this); }

Cliente_Residenziale& Cliente_Residenziale::operator=(const Cliente_Residenziale& c) {
  if(this != &c) Cliente::operator=(c);
  return *this;
}

bool Cliente_Residenziale::operator==(const Cliente_Residenziale& c) const { return Cliente::operator==(c); }
bool Cliente_Residenziale::operator!=(const Cliente_Residenziale& c) const { return Cliente::operator!=(c); }

Persona* Cliente_Residenziale::Import(const QDomNodeList& list) {

  Queue<QDomNode> nodeList;
  Queue<QString> string;
  Queue<Data> data;
  Documento doc;
  Queue<UniqueID> ids;

  for(int i = 0; i < list.length(); ++i) nodeList.push_back(list.at(i));

  Cliente::Import(nodeList, string, data, doc, ids);

  if(string.size() < 10)
    for(unsigned int i = string.size(); i < 10; ++i)
      string.push_back(QString(""));

  if(data.size() < 3)
    for(unsigned int i = data.size(); i < 4; ++i)
      data.push_back(Data());

  return new Cliente_Residenziale(string[0], string[1], string[2], string[3], ids, string[4], data[0],
      doc, string[5], data[1], data[2], string[6], string[7], string[8], string[9]);
}

void Cliente_Residenziale::Export(QDomDocument& dom, const Cliente_Residenziale& c) {
  QDomElement cliente(dom.createElement("cliente"));
  cliente.setAttribute("tipo", "residenziale");

  Cliente::Export(dom, cliente, c);

  dom.firstChild().appendChild(cliente);
}
