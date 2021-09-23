#ifndef CLIENTE_BUSINESS_H
#define CLIENTE_BUSINESS_H
#include "Cliente.h"

class Cliente_Business final : public Cliente {
  private:
    QString ragioneSociale;
    QString piva;
    QString cfAzienda;

  public:
    Cliente_Business(
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
      const QString& = "", // CAP
      // Cliente Business
      const QString& = "", // Ragione Sociale
      const QString& = "", //P.IVA
      const QString& = ""  // CF Azienda
    );

    Cliente_Business(
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
      const QString& = "", // CAP
      // Cliente Business
      const QString& = "", // Ragione Sociale
      const QString& = "", //P.IVA
      const QString& = ""  // CF Azienda
    );

    QString getRagioneSociale() const;
    QString getPiva() const;
    QString getCFAzienda() const;

    void setRagioneSociale(const QString&);
    void setPiva(const QString&);
    void setCFAzienda(const QString&);

    virtual Cliente_Business* clone() const;
    virtual ~Cliente_Business() {}

    Cliente_Business& operator=(const Cliente_Business&);
    bool operator==(const Cliente_Business&) const;
    bool operator!=(const Cliente_Business&) const;

    // Import/Export
    static Persona* Import(const QDomNodeList&);
    static void Export(QDomDocument&, const Cliente_Business&);
};

#endif // CLIENTE_BUSINESS_H
