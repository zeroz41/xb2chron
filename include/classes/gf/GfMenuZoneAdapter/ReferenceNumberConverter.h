#ifndef CLASSES_GF_GFMENUZONEADAPTER_REFERENCENUMBERCONVERTER_H
#define CLASSES_GF_GFMENUZONEADAPTER_REFERENCENUMBERCONVERTER_H

#include "classes/gf/GfMenuZoneAdapter.h"
#include "classes/gf/GfMenuZoneAdapter/IConverter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B5E328; the zone a GfMenuReferenceNumber's value names
class GfMenuZoneAdapter::ReferenceNumberConverter : public ::gf::GfMenuZoneAdapter::IConverter {
public:
    ReferenceNumberConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference) : m_reference(reference) {}
    virtual ~ReferenceNumberConverter() { m_reference = nullptr; }  // slot 0
    virtual unsigned int getZoneId() { return m_reference->m_value; }  // slot 2
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_reference;
};
}  // namespace gf

#endif
