#ifndef CLASSES_GF_TUNK_B5B9F8_H
#define CLASSES_GF_TUNK_B5B9F8_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {
// table 0x7100B5B9F8 (no RTTI, no 1.0.0 symbol): a GfMenuCharDataAdapter converter new in 3.0.1, built only by
// GfMenuCharDataAdapter::createFromNpcIDList: an ID list's entry as an NPC (type 6).
class TUnk_B5B9F8 : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    // index -1: the list's selected one
    TUnk_B5B9F8(const GfMenuIDList* list, int index) : m_list(list), m_index(index) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    // (the names are not the original's)
    const GfMenuIDList* m_list;
    int m_index;
};
}  // namespace gf

#endif
