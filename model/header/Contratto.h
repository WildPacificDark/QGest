#ifndef CONTRATTO_H
#define CONTRATTO_H
#include <QtXml>
#include "data/Data.h"
#include "Queue.h"
#include "UniqueID.h"

enum tipoContratto { Luce = 0, Gas = 1, Telefonia = 2 };
enum tipoCliente { Domestico = 0, Business = 1 };

class Contratto {
  private:
    UniqueID idContratto; // Identificativo contratto
    QString idCliente; // Identificativo cliente (cf)
    QString idAgente; // Identificativo agente (codice agente)
    tipoContratto tipo;
    tipoCliente tipoC;
    Data dataStipula;    // Data di stipula
    Data dataSpedizione; // Data di invio al BO
    QString agenzia;     // Agenzia a cui viene inviato
    QString fornitore;   // Fornitore del servizio
    QString nomeOfferta; // Offerta Stipulata
    double gettoneBase;  // Guadagno base sul contratto
    double canvasSDD;    // Guadagno extra se pagamento con RID Bancario
    double canvasMail;   // Guadagno extra se bolletta inviata tramite mail

    static QDomElement newQDomElement(QDomDocument&, const QString&, const QString&, const QString&);

  public:
    // Costruttore
    Contratto(const UniqueID, const QString& = "", const QString& = "", const tipoContratto& = tipoContratto::Luce, const tipoCliente& = tipoCliente::Domestico,
              const Data& = Data(), const Data& = Data(), const QString& = "", const QString& = "", const QString& = "", const double& = 0.00,
              const double& = 0.00, const double& = 0.00);

    Contratto(const QString& = "", const QString& = "", const tipoContratto& = tipoContratto::Luce, const tipoCliente& = tipoCliente::Domestico,
              const Data& = Data(), const Data& = Data(), const QString& = "", const QString& = "", const QString& = "", const double& = 0.00,
              const double& = 0.00, const double& = 0.00);

    // Costruttore di copia
    Contratto(const Contratto&);

    // Getter
    UniqueID getId() const;
    QString getIdCliente() const;
    QString getIdAgente() const;
    tipoContratto getTipoContratto() const;
    QString getTipoContrattoToString() const;
    tipoCliente getTipoCliente() const;
    QString getTipoClienteToString() const;
    Data getDataStipula() const;
    Data getDataSpedizione() const;
    QString getAgenzia() const;
    QString getFornitore() const;
    QString getOfferta() const;
    double getGettoneBase() const;
    double getCanvasSDD() const;
    double getCanvassMail() const;

    // Setter
    void setIdCliente(const QString&);
    void setIdAgente(const QString&);
    void setTipoContratto(const tipoContratto&);
    void setTipoCliente(const tipoCliente&);
    void setDataStipula(const Data&);
    void setDataSpedizione(const Data&);
    void setAgenzia(const QString&);
    void setFornitore(const QString&);
    void setOfferta(const QString&);
    void setGettoneBase(const double&);
    void setCanvasSDD(const double&);
    void setCanvassMail(const double&);

    // Distruttore
    virtual ~Contratto() {};

    virtual double compenso() const;
    virtual Contratto* clone() const;

    // Operatori
    Contratto& operator=(const Contratto&);
    bool operator==(const Contratto&) const;
    bool operator!=(const Contratto&) const;

    // Import/Export
    static Contratto* Import(const QDomNodeList&);
    static void Export(QDomDocument&, const Contratto&);
};

#endif // CONTRATTO_H
