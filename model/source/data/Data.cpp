#include "../../header/data/Data.h"

Data::Data(int y, int m , int d) {
  if(isValid(y, m, d)) {
    anno = y;
    mese = m;
    giorno = d;
  } else { throw Data_Exception("Data non valida!"); }
}

Data::Data(const QString& s) { parseString(s); }

Data::Data(const Data& d) {
  if(isValid(d.getAnno(), d.getMese(), d.getGiorno())) {
    giorno = d.getGiorno();
    mese = d.getMese();
    anno = d.getAnno();
  } else { throw Data_Exception("Data non valida!"); }
}

int Data::getGiorno() const { return giorno; }

int Data::getMese() const { return mese; }

int Data::getAnno() const { return anno; }

QString Data::getData() const {
  return QString("%1/%2/%3").arg(anno).arg(mese, 2, 10, QLatin1Char('0')).arg(giorno, 2, 10, QLatin1Char('0'));
}

bool Data::isValid() const { return isValid(anno, mese, giorno); }

bool Data::isValid(int y, int m, int d) const {
  const int MIN_VALIDanno = 1900;
  const int MAX_VALIDanno = 9999;
  if(d < 1 || d > 31) return false;
  if(m < 1 || m > 12) return false;
  if(y < MIN_VALIDanno || y > MAX_VALIDanno) return false;
  if(m == 2) {
    if(isLeap(y)) return (d <= 29);
    else return (d <= 28);
  }
  if(m == 4 || m == 6 || m == 9 || m == 11) return (d <= 30);
  return true;
}

bool Data::isLeap(int y) const { return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0); }

bool Data::setData(int y, int m, int d) {
  if(!isValid(y, m, d)) return false;
  anno = y;
  mese = m;
  giorno = d;
  return true;
}

Data& Data::operator=(const Data& d) {
  if(d != *this) {
    giorno = d.giorno;
    mese = d.mese;
    anno = d.anno;
  }
  return *this;
}

bool Data::operator!=(const Data & d) const {
  return d.getGiorno() != getGiorno() || d.getMese() != getMese() || d.getAnno() != getAnno();
}

bool Data::operator==(const Data & d) const {
  return d.getGiorno() == getGiorno() && d.getMese() == getMese() && d.getAnno() == getAnno();
}

void Data::parseString(const QString& s) {
  QStringList x = s.split(QRegularExpression("-|/|\\\\"));
  if(x.size() > 1) setData(x[0].toInt(), x[1].toInt(), x[2].toInt());
}

QString Data::toString() const {
  QString data("%1/%2/%3");
  return data.arg(anno).arg(mese, 2, 10, QLatin1Char('0')).arg(giorno, 2, 10, QLatin1Char('0'));
}
