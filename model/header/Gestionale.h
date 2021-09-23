#ifndef GESTIONALE_H
#define GESTIONALE_H
#include <QFile>
#include <cmath>
#include <typeinfo>
#include "Exception.h"
#include "cliente/Cliente_Res.h"
#include "cliente/Cliente_Business.h"
#include "dipendente/Agente.h"
#include "dipendente/Manager.h"
#include "Contratto.h"

enum class ricerca { Nome, Cognome, Codice_Fiscale, Codice_Dipendente };

class Gestionale {
  private:

    static QString defaultFile;
    static QString defaultFilePath;

    Queue<Persona*> persone;
    Queue<Contratto*> contratti;

    // Funzioni di utilità
    template<typename T> void modificaPersona(const T&, const T&);
    template<typename T> void eliminaPersona(const Persona&);
    template<typename T> Queue<Contratto*> getContrattiByPersona(const T&) const;

  public:

    // Costruttore
    Gestionale();
    Gestionale(const Gestionale&);

    // Operatore di assegnazione reso non disponibile
    Gestionale& operator=(const Gestionale&) = delete;

    // Metodi Getter
    Cliente* getCliente(const ricerca&, const QString&) const;
    Queue<Cliente*> getAllClienti() const;

    Dipendente* getDipendente(const ricerca&, const QString&) const;
    Queue<Dipendente*> getAllAgenti() const;

    Contratto* getContrattoById(const UniqueID&) const;
    Contratto* getContrattoById(unsigned int) const;
    Queue<Contratto*> getAllContratti() const;
    Queue<Contratto*> getContrattiByTipo(const tipoContratto&) const;
    Queue<Contratto*> getContrattiByCliente(const Cliente&) const;
    Queue<Contratto*> getContrattiByDipendente(const Dipendente&) const;
    Queue<Contratto*> getContrattiByFornitore(const QString&) const;
    Queue<Contratto*> getContrattiByAgenzia(const QString&) const;

    int getNumClienti() const;
    int getNumDipendenti() const;
    int getNumContratti() const;

    static QString getDefaultFile();
    static QString getDefaultFilePath();

    // Setter
    void addCliente(const Cliente&);
    void addDipendente(const Dipendente&);
    void addContratto(const Contratto&, Cliente&, Dipendente&);

    void modificaCliente(const Cliente&, const Cliente&);
    void modificaDipendente(const Dipendente&, const Dipendente&);
    void modificaContratto(const Contratto&, const Contratto&);

    void eliminaCliente(const Cliente&, bool);
    void eliminaDipendente(const Dipendente&, bool);
    void eliminaContratto(const Contratto&);

    double stipendioDipendente(const Dipendente&) const;

    static void setDefaultFilePath(const QString&);

    // Import\Export
    void Import(const QString&);
    void Export() const;
};

#endif // GESTIONALE_H
