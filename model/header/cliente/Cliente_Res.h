#ifndef CLIENTE_RES_H
#define CLIENTE_RES_H
#include "Cliente.h"

class Cliente_Residenziale final : public Cliente {
  public:
    Cliente_Residenziale(
      const QString& = "", // Nome
      const QString& = "", // Cognome
      const QString& = "", // Email
      const QString& = "", // Telefono
      const Queue<UniqueID>& = Queue<UniqueID>(),
      // Cliente
      const QString&  = "", // CF
      const Data& = Data(),    // Data nascita
      const Documento& = Documento::CartaIdentita, // Tipo documento
      const QString& = "", // Numero Doc
      const Data& = Data(),    // Data scadenza doc
      const Data& = Data(),    // Data rilascio doc
      const QString& = "", // Indirizzo
      const QString& = "", // Comune
      const QString& = "", // Provincia
      const QString& = ""  // CAP
    );

    Cliente_Residenziale(
      const QString& = "", // Nome
      const QString& = "", // Cognome
      const QString& = "", // Email
      const QString& = "", // Telefono
      // Cliente
      const QString&  = "", // CF
      const Data& = Data(),    // Data nascita
      const Documento& = Documento::CartaIdentita, // Tipo documento
      const QString& = "", // Numero Doc
      const Data& = Data(),    // Data scadenza doc
      const Data& = Data(),    // Data rilascio doc
      const QString& = "", // Indirizzo
      const QString& = "", // Comune
      const QString& = "", // Provincia
      const QString& = ""  // CAP
    );

    virtual Cliente_Residenziale* clone() const;
    virtual ~Cliente_Residenziale() {};

    // Import/Export
    static Persona* Import(const QDomNodeList&);
    static void Export(QDomDocument&, const Cliente_Residenziale&);


    // Operatori
    Cliente_Residenziale& operator=(const Cliente_Residenziale&);
    bool operator==(const Cliente_Residenziale&) const;
    bool operator!=(const Cliente_Residenziale&) const;
};

#endif // CLIENTE_RES_H
