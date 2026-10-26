#ifndef CLASSES_GF_TUNK_B5B938_H
#define CLASSES_GF_TUNK_B5B938_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuBladeList.h"

namespace gf {
// table 0x7100B5B938 (no RTTI, no 1.0.0 symbol): a GfMenuCharDataAdapter converter new in 3.0.1, built only by
// GfMenuCharDataAdapter::fn_710033A480: the driver who created a blade list's entry (GfDataBlade::getCreator).
// Possibly 1.0.0's BladeSetConverter's successor, but its code differs, so it keeps the placeholder name.
class TUnk_B5B938 : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    // index -1: the list's selected one
    TUnk_B5B938(const GfMenuBladeList* list, int index) : m_list(list), m_index(index) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    // (the names are not the original's)
    const GfMenuBladeList* m_list;
    int m_index;
};
}  // namespace gf

#endif
