#ifndef CLASSES_GF_GFMENUMISSIONADAPTER_REFERENCECONVERTER_H
#define CLASSES_GF_GFMENUMISSIONADAPTER_REFERENCECONVERTER_H

#include "classes/gf/GfMenuMissionAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B5D770
class GfMenuMissionAdapter::ReferenceConverter : public ::gf::GfMenuMissionAdapter::IConverter {
public:
    ReferenceConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference) : m_reference(reference) {}
    virtual ~ReferenceConverter();  // slot 0
    virtual unsigned int getMissionId();  // slot 2
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_reference;  // its m_value is the mission
};
}  // namespace gf

#endif
