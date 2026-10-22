#ifndef CLASSES_GF_GFMENUHANAPARTSADAPTER_REFERENCENUMBERCONVERTER_H
#define CLASSES_GF_GFMENUHANAPARTSADAPTER_REFERENCENUMBERCONVERTER_H

#include "classes/gf/GfMenuHanaPartsAdapter.h"
#include "classes/gf/GfMenuHanaPartsAdapter/IConverter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B5C9F8; the part a GfMenuReferenceNumber's value names
class GfMenuHanaPartsAdapter::ReferenceNumberConverter : public ::gf::GfMenuHanaPartsAdapter::IConverter {
public:
    ReferenceNumberConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference) : m_reference(reference) {}
    virtual ~ReferenceNumberConverter();  // slot 0
    virtual unsigned int getPartsId();  // slot 2
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_reference;
};
}  // namespace gf

#endif
