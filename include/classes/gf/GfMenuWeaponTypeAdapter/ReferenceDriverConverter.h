#ifndef CLASSES_GF_GFMENUWEAPONTYPEADAPTER_REFERENCEDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUWEAPONTYPEADAPTER_REFERENCEDRIVERCONVERTER_H

#include "classes/gf/GfMenuWeaponTypeAdapter.h"
#include "classes/gf/GfMenuWeaponTypeAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B5E0A0; the driver GfMenuReference has at a reference index, the weapon type a GfMenuReferenceNumber's
// value names, and a fixed arts index
class GfMenuWeaponTypeAdapter::ReferenceDriverConverter : public ::gf::GfMenuWeaponTypeAdapter::IConverter {
public:
    ReferenceDriverConverter(unsigned int driver, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> wpnType,
                             unsigned int artsIndex)
        : m_driver(driver), m_wpnType(wpnType), m_artsIndex(artsIndex) {}
    virtual ~ReferenceDriverConverter() { m_wpnType = nullptr; }  // slot 0
    virtual unsigned int getDriverId() { return GfMenuReference::getReferenceDriverID(m_driver); }  // slot 2
    virtual unsigned int getWpnType() { return m_wpnType->m_value; }  // slot 3
    virtual unsigned int getArtsIndex() { return m_artsIndex; }  // slot 4
    unsigned int m_driver;  // GfMenuReference::getReferenceDriverID's index
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_wpnType;
    unsigned int m_artsIndex;
};
}  // namespace gf

#endif
