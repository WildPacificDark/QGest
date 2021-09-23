#ifndef CLIENTEH
#define CLIENTEH

#include "../persona/Persona.h"

enum class Documento { CartaIdentita = 0, Patente = 1, Passaporto = 2 };

class Cliente : public Persona {
  private:
   QString codiceFiscale;
   Data dataNascita;
   Documento tipoDoc; // Tipo documento
   QString numDoc; // Numero documento
   Data scadDoc; // Data di scadenza del documento
   Data rilDoc; // Data di rilascio del documento
   QString indirizzo;
   QString comune;
   QString provincia;
   QString cap;

  protected:
   Cliente(const QString& = "", const QString& = "", const QString& = "", const QString& = "", const Queue<UniqueID>& = Queue<UniqueID>(), const QString& = "", const Data& = Data(),
           const Documento& = Documento::CartaIdentita, const QString& = "", const Data& = Data(), const Data& = Data(), const QString& = "",
           const QString& = "", const QString& = "", const QString& = "");

   Cliente(const QString& = "", const QString& = "", const QString& = "", const QString& = "", const QString& = "", const Data& = Data(),
           const Documento& = Documento::CartaIdentita, const QString& = "", const Data& = Data(), const Data& = Data(), const QString& = "",
           const QString& = "", const QString& = "", const QString& = "");

   Cliente(const Cliente&);

   // Import/Export
   static void Import(const Queue<QDomNode>&, Queue<QString>&, Queue<Data>&, Documento&, Queue<UniqueID>&id);
   static void Export(QDomDocument&, QDomElement&, const Cliente&c);

  public:
    // Metodi getter
    QString getCF() const;
    Data getDataNascita() const;
    Documento getTipoDocumento() const;
    int getTipoDocumentoInt() const;
    QString getTipoDocumentoString() const;
    QString getNumeroDoc() const;
    Data getScadenzaDoc() const;
    Data getRilascioDoc() const;
    QString getIndirizzo() const;
    QString getComune() const;
    QString getProvincia() const;
    QString getCAP() const;

    // Metodi setter
    void setCF(const QString&);
    void setDataNasvita(const Data&);
    void setTipoDoc(const Documento&);
    void setTipoDoc(int);
    void setNumeroDoc(const QString&);
    void setScadenzaDoc(const Data&);
    void setRilascioDoc(const Data&);
    void setIndirizzo(const QString&);
    void setComune(const QString&);
    void setProvincia(const QString&);
    void setCAP(const QString&);

    virtual Cliente* clone() const = 0;
    virtual ~Cliente() {};

    // Operatori
    Cliente& operator=(const Cliente&);
    bool operator==(const Cliente&) const;
    bool operator!=(const Cliente&) const;
};

#endif // CLIENTEH
