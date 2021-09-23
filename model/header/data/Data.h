#ifndef Data_H
#define Data_H
#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include "../Exception.h"

class Data {
  private:
    int giorno, mese, anno;

  public:
    Data(int = 1970, int = 1, int = 1);
    Data(const QString&);
    Data(const Data& d);
    ~Data() = default;

    int getGiorno() const;
    int getMese() const;
    int getAnno() const;
    QString getData() const;
    bool isValid() const;
    bool isValid(const int, const int, const int) const;
    bool isLeap(int) const;
    bool setData(int, int, int);

    Data& operator= (const Data&);
    bool operator== (const Data&) const;
    bool operator!= (const Data&) const;

    void parseString(const QString&);
    QString toString() const;
};

#endif // Data_H
