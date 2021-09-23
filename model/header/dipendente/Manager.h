#ifndef MANAGER_H
#define MANAGER_H
#include "Dipendente.h"

class Manager : public Dipendente {
  private:

    double fissoMensile;
    double bonus;

  public:
    Manager(const QString& ="", const QString& = "", const QString& = "", const QString& = "", const Queue<UniqueID>& = Queue<UniqueID>(),
            const QString& = "", double = 0.5, double = 0.2, double = 200, double = 0.15);

    Manager(const QString& ="", const QString& = "", const QString& = "", const QString& = "", const QString& = "", double = 0.5,
            double = 0.2, double = 200, double = 0.15);


    // Metodi getter
    double getFissoMensile() const;
    double getBonus() const;

    // Metodi setter
    void setFissoMensile(double);
    void setBonus(double);

    // Virtuali
    virtual Manager* clone() const;
    virtual double stipendio(double) const;

    // Distruttore
    virtual ~Manager() {};

    // Operatori
    bool operator==(const Manager&) const;
    bool operator!=(const Manager&) const;

    static Persona* Import(const QDomNodeList&);
    static void Export(QDomDocument&, const Manager&);
};


#endif // MANAGER_H
