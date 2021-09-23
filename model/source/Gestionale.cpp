#include "../header/Gestionale.h"

/** GESTIONALE */

QString Gestionale::defaultFile("data.xml");

QString Gestionale::defaultFilePath("/");

QString Gestionale::getDefaultFile() { return defaultFile; }

QString Gestionale::getDefaultFilePath() { return defaultFilePath; }

void Gestionale::setDefaultFilePath(const QString& path) { defaultFilePath = path; }

Gestionale::Gestionale() {}

Gestionale::Gestionale(const Gestionale& gest) : persone(gest.persone), contratti(gest.contratti) {}

// Metodi getter

int Gestionale::getNumClienti() const {
  int i = 0;
  auto it = persone.begin();
  while(it != persone.end()) {
    if(dynamic_cast<Cliente*>(*it)) ++i;
    ++it;
  }
  return i;
}

int Gestionale::getNumDipendenti() const {
  int i = 0;
  auto it = persone.begin();
  while(it != persone.end()) {
    if(dynamic_cast<Dipendente*>(*it)) ++i;
    ++it;
  }
  return i;
}

int Gestionale::getNumContratti() const { return contratti.size(); }

// Cliente

Queue<Cliente*> Gestionale::getAllClienti() const {
  Queue<Cliente*> cliente;
  for(auto it = persone.begin(); it != persone.end(); ++it) {
    if(Cliente* c = dynamic_cast<Cliente*>(*it)) cliente.push_back(c);
  }
  return cliente;
};


Cliente* Gestionale::getCliente(const ricerca& ric, const QString& key) const {
  Queue<Persona*>::iterator it(persone.begin());
  Cliente* c = nullptr;
  switch(ric) {
    case ricerca::Nome:
      for(; it != persone.end(); ++it)
        if((c = dynamic_cast<Cliente*>(*it)) && c->getNome() == key) return c;
      break;
    case ricerca::Cognome:
      for(; it != persone.end(); ++it)
        if((c = dynamic_cast<Cliente*>(*it)) && c->getCognome() == key) return c;
      break;
    case ricerca::Codice_Fiscale:
      for(; it != persone.end(); ++it)
        if((c = dynamic_cast<Cliente*>(*it)) && c->getCF() == key) return c;
      break;
    default:
      return nullptr;
      break;
  }
  return nullptr;
}

/// Dipendente

Queue<Dipendente*> Gestionale::getAllAgenti() const {
  Queue<Dipendente*> dipendente;
  Dipendente* a = nullptr;
  for(auto it = persone.begin(); it != persone.end(); ++it) {
    if((a = dynamic_cast<Dipendente*>(*it))) dipendente.push_back(a);
  }
  return dipendente;
};

Dipendente* Gestionale::getDipendente(const ricerca& ric, const QString& key) const {
  Queue<Persona*>::iterator it(persone.begin());
  Dipendente* a = nullptr;
  switch(ric) {
    case ricerca::Nome:
      for(; it != persone.end(); ++it)
        if((a = dynamic_cast<Dipendente*>(*it)) && a->getNome() == key) return a;
      break;
    case ricerca::Cognome:
      for(; it != persone.end(); ++it)
        if((a = dynamic_cast<Dipendente*>(*it)) && a->getCognome() == key) return a;
      break;
    case ricerca::Codice_Dipendente:
      for(; it != persone.end(); ++it) {
        if((a = dynamic_cast<Dipendente*>(*it)) && a->getCodice() == key) return a;
      }
      break;
    default:
      return nullptr;
      break;
  }
  return nullptr;
}

Queue<Contratto*> Gestionale::getAllContratti() const { return contratti; }

Contratto* Gestionale::getContrattoById(const UniqueID& u) const {
  Queue<Contratto*>::iterator it = contratti.begin();
  for(; it != contratti.end() && u != (*it)->getId(); ++it);
  return (*it);
}

Contratto* Gestionale::getContrattoById(unsigned int u) const {
  Queue<Contratto*>::iterator it = contratti.begin();
  for(; it != contratti.end() && u != (*it)->getId().get(); ++it);
  return (*it);
}

Queue<Contratto*> Gestionale::getContrattiByTipo(const tipoContratto& t) const {
  Queue<Contratto*> aux;
  for(auto it = contratti.begin(); it != contratti.end(); ++it)
    if((*it)->getTipoContratto() == t) aux.push_back(*it);
  return aux;
}

template<typename T>
Queue<Contratto*> Gestionale::getContrattiByPersona(const T& persona) const {
  Queue<Contratto*> aux;
  Queue<UniqueID> uid = persona.getContrattiAssociati();
  for(auto i = uid.begin(); i != uid.end(); ++i) {
    for(auto j = contratti.begin(); j != contratti.end(); ++j) {
      if(*i == (*j)->getId()) {
        aux.push_back(*j);
        break;
      }
    }
  }
  return aux;
}

Queue<Contratto*> Gestionale::getContrattiByCliente(const Cliente& cliente) const { return getContrattiByPersona<Cliente>(cliente); }

Queue<Contratto*> Gestionale::getContrattiByDipendente(const Dipendente& dipendente) const { return getContrattiByPersona<Dipendente>(dipendente); }

Queue<Contratto*> Gestionale::getContrattiByFornitore(const QString& key) const {
  Queue<Contratto*> aux;
  for(auto it = contratti.begin(); it != contratti.end(); ++it)
    if((*it)->getFornitore() == key) aux.push_back(*it);
  return aux;
}

Queue<Contratto*> Gestionale::getContrattiByAgenzia(const QString& key) const {
  Queue<Contratto*> aux;
  for(auto it = contratti.begin(); it != contratti.end(); ++it)
    if((*it)->getAgenzia() == key) aux.push_back(*it);
  return aux;
}

double Gestionale::stipendioDipendente(const Dipendente& agn) const {
  Queue<Contratto*> aux = getContrattiByDipendente(agn);
  double fatturato = 0;
  for(auto it = aux.begin(); it != aux.end(); ++it) fatturato += (*it)->compenso();
  return std::ceil(agn.stipendio(fatturato) * 100.0) / 100.0;
}

void Gestionale::addCliente(const Cliente& c) { persone.push_back(c.clone()); }

void Gestionale::addDipendente(const Dipendente& a) { persone.push_back(a.clone()); }

void Gestionale::addContratto(const Contratto &ctr, Cliente &c, Dipendente &a) {
  contratti.push_back(ctr.clone());
  c.addContrattoAssociato((*contratti.lastElem())->getId());
  a.addContrattoAssociato((*contratti.lastElem())->getId());
}

// Setter

template<typename T>
void Gestionale::modificaPersona(const T& nuovo, const T& vecchio) {
  if(typeid(nuovo) == typeid(vecchio) && vecchio != nuovo) {
    auto it = persone.begin();
    try {
      for(; it != persone.end(); ++it) {
        if(dynamic_cast<T*>(*it) && **it == vecchio) {
          it = persone.erase(it);
          break;
        }
      }
      persone.insert(it, nuovo.clone());
    } catch (Queue_Exception& e) { qDebug() << e.what(); }
  }
}

void Gestionale::modificaCliente(const Cliente& nuovo, const Cliente& vecchio) {
  modificaPersona<Cliente>(nuovo, vecchio);
  Queue<Contratto*> ctr = getContrattiByCliente(nuovo);
  if(dynamic_cast<const Cliente_Residenziale*>(&nuovo)) {
    for(auto it = ctr.begin(); it != ctr.end(); ++it)
      (*it)->setIdCliente(nuovo.getCF());
  } else {
    const Cliente_Business *c = dynamic_cast<const Cliente_Business*>(&nuovo);
    for(auto it = ctr.begin(); it != ctr.end(); ++it)
      (*it)->setIdCliente(c->getCFAzienda());
  }
}

void Gestionale::modificaDipendente(const Dipendente& nuovo, const Dipendente& vecchio) {
  modificaPersona<Dipendente>(nuovo, vecchio);
  Queue<Contratto*> ctr = getContrattiByDipendente(nuovo);
  for(auto it = ctr.begin(); it != ctr.end(); ++it)
    (*it)->setIdAgente(nuovo.getCodice());
}

void Gestionale::modificaContratto(const Contratto& nuovo, const Contratto& vecchio) {
  if(vecchio != nuovo) {
    auto it = contratti.begin();
    try {
      for(; it != contratti.end(); ++it) {
        if(**it == vecchio) {
          it = contratti.erase(it);
          break;
        }
      }
      contratti.insert(it, nuovo.clone());
    } catch (Queue_Exception& e) { qDebug() << e.what(); }
  }
}

template<typename T>
void Gestionale::eliminaPersona(const Persona& p) {
  for(auto it = persone.begin(); it != persone.end(); ++it) {
    Persona* aux = nullptr;
    try {
      if((aux = dynamic_cast<T*>(*it)) && *aux == p) {
        it = persone.erase(it);
        break;
      }
    } catch (Queue_Exception& e) { qDebug() << e.what(); }
  }
}

void Gestionale::eliminaCliente(const Cliente& c, bool assoc) {
  if(assoc) {
    // Elimino i contratti associati al cliente
    for(auto it = contratti.begin(); it != contratti.end(); ++it) {
      if((*it)->getIdCliente() == c.getCF()) {
        Dipendente* d = getDipendente(ricerca::Codice_Dipendente, (*it)->getIdAgente());
        UniqueID id = (*it)->getId();
        it = contratti.erase(it);
        d->rimuoviContrattoAssociato(id);
      }
    }
  }
  eliminaPersona<Cliente>(c);
}

void Gestionale::eliminaDipendente(const Dipendente& d, bool assoc) {
  if(assoc) {
    // Elimino i clienti e i relativi contratti associati all'agente
    Queue<Contratto*> ctr = getContrattiByDipendente(d);
    Queue<QString> cod;

    for(auto it = ctr.begin(); it != ctr.end(); ++it)
      cod.push_back((*it)->getIdCliente());

    for(auto i = cod.begin(); i != cod.end(); ++i) {
      for(auto j = persone.begin(); j != persone.end(); ++j) {
        Cliente* c = dynamic_cast<Cliente*>(*j);
        if(c && c->getCF() == *i) eliminaCliente(*c, true);
      }
    }
  }
  eliminaPersona<Dipendente>(d);
}

void Gestionale::eliminaContratto(const Contratto& c) {
  try{
    for(auto it = contratti.begin(); it != contratti.end(); ++it) {
      if(**it == c) {
        Cliente* c = getCliente(ricerca::Codice_Fiscale, (*it)->getIdCliente());
        Dipendente* d = getDipendente(ricerca::Codice_Dipendente, (*it)->getIdAgente());
        UniqueID id = (*it)->getId();
        it = contratti.erase(it);
        c->rimuoviContrattoAssociato(id);
        d->rimuoviContrattoAssociato(id);
        break;
      }
    }
  } catch (Queue_Exception& e) { qDebug() << e.what(); }
}

void Gestionale::Import(const QString& file) {
  QDomDocument doc;
  QFile xmlFile(file);
  QByteArray xml;

  try {
    if(xmlFile.open(QFile::ReadOnly | QFile::Text)) {
      xml = xmlFile.readAll();
      xmlFile.close();
    } else throw Err_File_Handling("Impossibile aprire il file!");
  } catch(Exception& e) {
    qDebug() << e.what();
  }

  doc.setContent(xml);

  QDomNodeList clienti(doc.elementsByTagName("cliente"));
  QDomNodeList agenti(doc.elementsByTagName("dipendente"));
  QDomNodeList ctr(doc.elementsByTagName("contratto"));

  Persona* p = nullptr;
  Contratto* c = nullptr;

  for(int i = 0; i < clienti.size(); ++i) {
    QDomElement elem = clienti.at(i).toElement();
    if(elem.attribute("tipo").toStdString() == "residenziale")
      p = Cliente_Residenziale::Import(clienti.at(i).childNodes());
    else
      p = Cliente_Business::Import(clienti.at(i).childNodes());
    persone.push_back(p->clone());
    delete p;
  }

  for(int i = 0; i < agenti.size(); ++i) {
    QDomElement elem = agenti.at(i).toElement();
    if(elem.attribute("tipo").toStdString() == "agente")
      p = Agente::Import(agenti.at(i).childNodes());
    else
      p = Manager::Import(agenti.at(i).childNodes());
    persone.push_back(p->clone());
    delete p;
  }

  for(int i = 0; i < ctr.size(); ++i) {
    QDomElement elem = ctr.at(i).toElement();
    c = Contratto::Import(ctr.at(i).childNodes());
    contratti.push_back(c->clone());
    delete c;
  }
}

void Gestionale::Export() const {
  QFile file(defaultFilePath + '/' + defaultFile);
  if(!file.open(QFile::WriteOnly | QFile::Text)) {
    file.close();
    throw Err_File_Handling("Errore nella scrittura dei dati");
    return;
  }

  QDomDocument xml;
  QDomElement root(xml.createElement("root"));
  xml.appendChild(root);

  for(auto it = persone.begin(); it != persone.end(); ++it) {
    if(Cliente_Residenziale* c = dynamic_cast<Cliente_Residenziale*>(*it)) Cliente_Residenziale::Export(xml, *c);
    if(Cliente_Business* c = dynamic_cast<Cliente_Business*>(*it)) Cliente_Business::Export(xml, *c);
    if(Agente* a = dynamic_cast<Agente*>(*it)) Agente::Export(xml, *a);
    if(Manager* m = dynamic_cast<Manager*>(*it)) Manager::Export(xml, *m);
  }

  for(auto it = contratti.begin(); it != contratti.end(); ++it) Contratto::Export(xml, **it);

  QTextStream output(&file);
  output << xml.toString();
}
