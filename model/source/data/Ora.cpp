#include "../../header/data/Ora.h"

Ora::Ora(int o, int m, int s) {
  if(o < 0 || o > 23 || m < 0 || m > 59 || s < 0 || s > 59) { sec = 0; }
  else { sec = o * 3600 + m * 60 + s; }
}

int Ora::hours() const { return sec / 3600; }
int Ora::minutes() const { return (sec / 60) % 60; }
int Ora::seconds() const { return sec % 60; }

Ora Ora::operator+(const Ora & o) {
  Ora aux;
  aux.sec = (sec + o.sec) % 86400;
  return aux;
}

Ora Ora::operator-(const Ora & o) {
  Ora aux;
  aux.sec = (sec - o.sec) % 86400;
  return aux;
}

bool Ora::operator==(const Ora & o) const { return sec == o.sec; }

bool Ora::operator>(const Ora & o) const { return sec > o.sec; }

bool Ora::operator<(const Ora & o) const { return sec < o.sec; }

ostream& operator<<(ostream& os, const Ora & o) {
  return os << o.hours() << ':' << o.minutes() <<':' << o.seconds();
}
