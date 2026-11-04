#ifndef CLASSES_GF_TUNK_B5B908_H
#define CLASSES_GF_TUNK_B5B908_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B908 (no RTTI, no 1.0.0 symbol): a GfMenuCharDataAdapter converter new in 3.0.1, built only by
// GfMenuCharDataAdapter::createFromReferenceBladeSet: the blade (type 4) in a slot of a reference driver (GfMenuReference::getReferenceDriverID).
class TUnk_B5B908 : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    TUnk_B5B908(unsigned int index, int slot) : m_index(index), m_slot(slot) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    // (the names are not the original's)
    unsigned int m_index;  // GfMenuReference's driver index
    int m_slot;
};
}  // namespace gf

#endif
