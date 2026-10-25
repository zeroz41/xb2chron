#ifndef CLASSES_GF_GFMENUGFOBJADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUGFOBJADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuGfObjAdapter.h"

namespace gf {
// table none (its derived classes')
class GfMenuGfObjAdapter::IConverter {
public:
    virtual GF_OBJ_HANDLE* getGfObjHandle() = 0;  // slot 0: the object to show now
    // itself as a PartyDriverConverter / PartyBladeConverter when it is one, none otherwise
    virtual PartyDriverConverter* fromPartyDriver() { return nullptr; }  // slot 1
    virtual PartyBladeConverter* fromPartyBlade() { return nullptr; }  // slot 2
};
}  // namespace gf

#endif
