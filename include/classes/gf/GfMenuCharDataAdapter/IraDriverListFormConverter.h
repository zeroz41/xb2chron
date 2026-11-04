#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_IRADRIVERLISTFORMCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_IRADRIVERLISTFORMCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuDriverList.h"

namespace gf {
// table 0x7100B5B9C8 (2.0.0's symbols name it): a GfMenuCharDataAdapter converter new in 3.0.1, built only by
// GfMenuCharDataAdapter::createFromIraDriverListForm: the driver (type 3) of a party (GfDataParty::getDriver) at the
// party index of a driver list's entry (GfDataParty::getDriverPartyID).
class GfMenuCharDataAdapter::IraDriverListFormConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    IraDriverListFormConverter(const GfMenuDriverList* list, unsigned int index, unsigned int party)
        : m_list(list), m_index(index), m_party(party) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    // (the names are not the original's)
    const GfMenuDriverList* m_list;
    unsigned int m_index;
    unsigned int m_party;
};
}  // namespace gf

#endif
