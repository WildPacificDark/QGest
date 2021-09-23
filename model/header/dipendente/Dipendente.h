#ifndef DIPENDENTE_H
#define DIPENDENTE_H
#include <QString>
#include "../persona/Persona.h"

class Dipendente : public Persona {
  private:
    QString codDipendente;
    double percGuadagno;
    double ritenutaAcc;

  protected:
    Dipendente(const QString&, const QString&, const QString&, const QString&, const Queue<UniqueID>&, const QString& = "", double = 0.4, double = 0.2);
    Dipendente(const QString&, const QString&, const QString&, const QString&, const QString& = "", double = 0.4, double = 0.2);

    // Import/Export
    static void Import(const QDomNodeList&, Queue<QString>&, Queue<UniqueID>&, Queue<double> &);
    static void Export(QDomDocument&, QDomElement&, const Dipendente&);

  public:
    // Metodi getter
    QString getCodice() const;
    double getPercGuadagno() const;
    double getRitenuta() const;
    unsigned int getNumContratti() const;

    // Metodi setter
    void setCodice(const QString&);
    void setPercGuadagno(double);
    void setRitenuta(double);

    // Virtuali
    virtual Dipendente* clone() const = 0;
    virtual double stipendio(double) const = 0;

    // Distruttore
    virtual ~Dipendente() {};

    // Operatori
    bool operator==(const Dipendente&) const;
    bool operator!=(const Dipendente&) const;
};

#endif // DIPENDENTE_H
