#include <iostream>
#include "UniqueID.hpp"

// sourse: https://www.oreilly.com/library/view/c-cookbook/0596007612/ch08s09.html

int UniqueID::nextID = 0;

UniqueID::UniqueID() {
   id = ++nextID;
}

UniqueID::UniqueID(const UniqueID& orig) {
   id = orig.id;
}

UniqueID& UniqueID::operator=(const UniqueID& orig) {
   id = orig.id;
   return(*this);
};