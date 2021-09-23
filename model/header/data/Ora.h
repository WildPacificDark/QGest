#ifndef Ora_H
#define Ora_H

#include <ostream>
#include <cstdlib>

using std::ostream;

class Ora {
  private:
    int sec;

  public:
    Ora(int = 0, int = 0, int = 0);

    int hours() const;
    int minutes() const;
    int seconds() const;

    Ora operator+(const Ora &);
    Ora operator-(const Ora &);
    bool operator==(const Ora &) const;
    bool operator>(const Ora &) const;
    bool operator<(const Ora &) const;
};

ostream& operator<<(ostream& os, const Ora& o);


#endif // Ora_H
