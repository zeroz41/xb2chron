#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"

namespace gf {
// table none (its derived classes'): the object an adapter shows; change* reach the converter of their kind through
// the from* slots (nullptr for another kind)
class GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char& objType, unsigned int& objId) = 0;  // slot 0
    virtual GfObjConverter* fromGfObj() { return nullptr; }  // slot 1
    virtual PartyDriverConverter* fromPartyDriver() { return nullptr; }  // slot 2
    virtual PartyBladeConverter* fromPartyBlade() { return nullptr; }  // slot 3
};
}  // namespace gf

#endif
