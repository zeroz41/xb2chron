#ifndef CLASSES_GF_GFMENUSHOPADAPTER_REFERENCENUMBERCONVERTER_H
#define CLASSES_GF_GFMENUSHOPADAPTER_REFERENCENUMBERCONVERTER_H

#include "classes/gf/GfMenuShopAdapter.h"
#include "classes/gf/GfMenuShopAdapter/IConverter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B5DA10; the shop a GfMenuReferenceNumber's value names
class GfMenuShopAdapter::ReferenceNumberConverter : public ::gf::GfMenuShopAdapter::IConverter {
public:
    ReferenceNumberConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference) : m_reference(reference) {}
    virtual ~ReferenceNumberConverter() { m_reference = nullptr; }  // slot 0
    virtual unsigned int getShopID() { return m_reference->m_value; }  // slot 2
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_reference;
};
}  // namespace gf

#endif
