#ifndef CLASSES_GF_GFMENUPOUCHADAPTER_REFERENCEDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUPOUCHADAPTER_REFERENCEDRIVERCONVERTER_H

#include "classes/gf/GfMenuPouchAdapter.h"
#include "classes/gf/GfMenuPouchAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {
// table 0x7100B5D850; a fixed pouch of the driver GfMenuReference has at a reference index
class GfMenuPouchAdapter::ReferenceDriverConverter : public ::gf::GfMenuPouchAdapter::IConverter {
public:
    ReferenceDriverConverter(unsigned int pouch, unsigned int reference) : m_pouch(pouch), m_reference(reference) {}
    virtual ~ReferenceDriverConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getPouchIndex() { return m_pouch; }  // slot 2
    virtual unsigned int getDriverId() { return GfMenuReference::getReferenceDriverID(m_reference); }  // slot 3
    unsigned int m_pouch;
    unsigned int m_reference;  // GfMenuReference::getReferenceDriverID's index
};
}  // namespace gf

#endif
