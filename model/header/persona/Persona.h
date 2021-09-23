#ifndef PERSONA_H
#define PERSONA_H
#include <QtXml>
#include <QDebug>
#include "../data/Data.h"
#include "../Queue.h"
#include "../UniqueID.h"

class Persona {
  private:

    QString nome;
    QString cognome;
    QString email;
    QString telefono;
    Queue<UniqueID> conAssociato;

  protected:

    static int numElem;

    Persona(const QString& = "Mario", const QString& = "Rossi", const QString& = "insert@mail.here", const QString& = "0123456789", const Queue<UniqueID> = Queue<UniqueID>());
    Persona(const Persona&);

    // Import/Export
    static QDomElement newQDomElement(QDomDocument&, const QString&, const QString&, const QString&);
    static void Import(const Queue<QDomNode>&, Queue<QString>&);
    static void Export(QDomDocument&, QDomElement&, const Persona&);

  public:

    // Metodi getter
    QString getNome() const;
    QString getCognome() const;
    QString getEmail() const;
    QString getTelefono() const;
    Queue<UniqueID> getContrattiAssociati() const;

    // Metodi setter
    void setNome(const QString&);
    void setCognome(const QString&);
    void setEmail(const QString&);
    void setTelefono(const QString&);
    void addContrattoAssociato(const UniqueID&);
    void addContrattoAssociato(int);
    void rimuoviContrattoAssociato(const UniqueID&);
    void rimuoviContrattoAssociato(int);

    //virtuali
    virtual Persona* clone() const = 0;

    // Distruttore
    virtual ~Persona() = default;

    // Operatori
    Persona& operator=(const Persona&);
    bool operator==(const Persona&) const;
    bool operator!=(const Persona&) const;
};

#endif // PERSONA_H
