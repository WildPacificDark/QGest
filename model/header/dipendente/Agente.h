#ifndef Agente_H
#define Agente_H
#include "Dipendente.h"

class Agente : public Dipendente {

  public:
    Agente(const QString& = "", const QString& = "", const QString& = "", const QString& = "", const Queue<UniqueID>& = Queue<UniqueID>(),
           const QString& = "", double = 0.4, double = 0.2);

    Agente(const QString& = "", const QString& = "", const QString& = "", const QString& = "", const QString& = "", double = 0.4, double = 0.2);

    // Virtuali
    virtual Agente* clone() const;
    virtual double stipendio(double) const;

    // Distruttore
    virtual ~Agente() {};

    // Import/Export
    static Persona* Import(const QDomNodeList&);
    static void Export(QDomDocument&, const Agente&);
};


#endif // Agente_H
