#include "../header/UniqueID.h"

/* UNIQUE ID */

// Costruttore
UniqueID::UniqueID() : id(++nextID) {}

UniqueID::UniqueID(unsigned int n) : id(n) {}

UniqueID::UniqueID(const UniqueID& uid) : id(uid.id) {}

unsigned int UniqueID::get() const { return id; }

unsigned int UniqueID::nextID = 0;

void UniqueID::setId(unsigned int u) { nextID = u; }

bool UniqueID::operator==(const UniqueID & u) const { return id == u.id; }
bool UniqueID::operator!=(const UniqueID & u) const { return id != u.id; }
