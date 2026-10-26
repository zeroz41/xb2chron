#ifndef CLASSES_GF_TUNK_B5B968_H
#define CLASSES_GF_TUNK_B5B968_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuBladeList.h"

namespace gf {
// table 0x7100B5B968 (no RTTI, no 1.0.0 symbol): a GfMenuCharDataAdapter converter new in 3.0.1, built only by
// GfMenuCharDataAdapter::fn_710033A5D0: the driver a blade list's entry is set to (GfDataBlade::getSetDriver).
class TUnk_B5B968 : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    // index -1: the list's selected one
    TUnk_B5B968(const GfMenuBladeList* list, int index) : m_list(list), m_index(index) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    // (the names are not the original's)
    const GfMenuBladeList* m_list;
    int m_index;
};
}  // namespace gf

#endif
