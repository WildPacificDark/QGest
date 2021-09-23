#include "../../header/cliente/Cliente_Business.h"

Cliente_Business::Cliente_Business(
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
  const QString& cp, // CAP
  const QString& rs,
  const QString& p_iva,
  const QString& cf_a
) : Cliente(n, c, e, t, ids, cf, dn, tp, nd, sd, rd, i, cm, pv, cp), ragioneSociale(rs), piva(p_iva), cfAzienda(cf_a) {};

Cliente_Business::Cliente_Business(
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
  const QString& cp, // CAP
  const QString& rs,
  const QString& p_iva,
  const QString& cf_a
) : Cliente(n, c, e, t, cf, dn, tp, nd, sd, rd, i, cm, pv, cp), ragioneSociale(rs), piva(p_iva), cfAzienda(cf_a) {};

QString Cliente_Business::getRagioneSociale() const { return ragioneSociale; }
QString Cliente_Business::getPiva() const { return piva; }
QString Cliente_Business::getCFAzienda() const { return cfAzienda; }

void Cliente_Business::setRagioneSociale(const QString & q) { ragioneSociale = q; }
void Cliente_Business::setPiva(const QString& p) { piva = p; }
void Cliente_Business::setCFAzienda(const QString& cf) { cfAzienda = cf; }

Cliente_Business* Cliente_Business::clone() const { return new Cliente_Business(*this); }

Cliente_Business& Cliente_Business::operator=(const Cliente_Business& c) {
  if(this != &c) {
    Cliente::operator=(c);
    ragioneSociale = c.ragioneSociale;
    piva = c.piva;
    cfAzienda = c.cfAzienda;
  }
  return *this;
}

bool Cliente_Business::operator==(const Cliente_Business& c) const {
  return Cliente::operator==(c) && ragioneSociale == c.ragioneSociale && piva == c.piva && cfAzienda == c.cfAzienda;
}

bool Cliente_Business::operator!=(const Cliente_Business& c) const {
  return Cliente::operator==(c) && ragioneSociale == c.ragioneSociale && piva == c.piva && cfAzienda == c.cfAzienda;
}

Persona* Cliente_Business::Import(const QDomNodeList& list) {
  Queue<QDomNode> nodeList;
  Queue<QString> string;
  Queue<Data> data;
  Documento doc;
  Queue<UniqueID> ids;

  for(int i = 0; i < list.length(); ++i) nodeList.push_back(list.at(i));

  Cliente::Import(nodeList, string, data, doc, ids);

  if(string.size() < 13)
    for(unsigned int i = string.size(); i < 13; ++i)
      string.push_back(QString(""));

  if(data.size() < 3)
    for(unsigned int i = data.size(); i < 3; ++i)
      data.push_back(Data());

  return new Cliente_Business(string[0], string[1], string[2], string[3], ids, string[4], data[0], doc, string[5], data[1],
      data[2], string[6], string[7], string[8], string[9], string[10], string[11], string[12]);
}

void Cliente_Business::Export(QDomDocument& dom, const Cliente_Business& c) {

  QDomElement cliente(dom.createElement("cliente"));
  cliente.setAttribute("tipo", "business");

  Cliente::Export(dom, cliente, c);

  cliente.appendChild(Persona::newQDomElement(dom, "ragioneSociale", "string", c.getRagioneSociale()));
  cliente.appendChild(Persona::newQDomElement(dom, "piva", "string", c.getPiva()));
  cliente.appendChild(Persona::newQDomElement(dom, "cfAzienda", "string", c.getCFAzienda()));

  dom.firstChild().appendChild(cliente);

}
