#ifndef UNIQUEID_H
#define UNIQUEID_H

class UniqueID {
  private:
    unsigned int id;
    static unsigned int nextID;

  public:
      UniqueID();
      UniqueID(unsigned int);
      UniqueID(const UniqueID&);
      unsigned int get() const;
      static void setId(unsigned int);

      UniqueID& operator=(const UniqueID&) = delete;
      bool operator==(const UniqueID&) const;
      bool operator!=(const UniqueID&) const;

};

#endif // UNIQUEID_H
