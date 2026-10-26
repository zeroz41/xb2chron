#ifndef CLASSES_GF_GFMENUITEMADAPTER_POUCHREFERENCEDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUITEMADAPTER_POUCHREFERENCEDRIVERCONVERTER_H

#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuItemAdapter/IConverter.h"

namespace gf { class MenuItemInfo; }

namespace gf {
// table 0x7100B5CE08
class GfMenuItemAdapter::PouchReferenceDriverConverter : public ::gf::GfMenuItemAdapter::IConverter {
public:
    PouchReferenceDriverConverter(unsigned int pouch, unsigned int reference) {
        m_reference = reference;  // stored before m_pouch (the callers' register order shows it)
        m_pouch = pouch;
    }
    virtual ~PouchReferenceDriverConverter();  // slot 0
    virtual void getItemInfo(gf::MenuItemInfo&);  // slot 2
    unsigned int m_pouch;      // the pouch slot (GfPouchUtil::getPouch's second argument)
    unsigned int m_reference;  // the GfMenuReference driver reference index
};
}  // namespace gf

#endif
