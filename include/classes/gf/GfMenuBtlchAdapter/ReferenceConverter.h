#ifndef CLASSES_GF_GFMENUBTLCHADAPTER_REFERENCECONVERTER_H
#define CLASSES_GF_GFMENUBTLCHADAPTER_REFERENCECONVERTER_H

#include "classes/gf/GfMenuBtlchAdapter/IConverter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B5A878 (weak); the id a GfMenuReferenceNumber's value holds, 0 without one. 2.0.0's
// symbols name it (GfMenuBtlchAdapter::createFromReference builds it); it is like
// GfMenuBattleAdapter::ReferenceIndexConverter, whose getIndex(int&) writes its result (GfMenuBattleAdapter::update
// passes it a local) where this one returns it.
class GfMenuBtlchAdapter::ReferenceConverter : public ::gf::GfMenuBtlchAdapter::IConverter {
public:
    ReferenceConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference) : m_reference(reference) {}
    virtual ~ReferenceConverter() { m_reference = nullptr; }  // slot 0
    virtual unsigned int getBtlchID() {  // slot 2
        if (m_reference) {
            return m_reference->m_value;
        }
        return 0;
    }
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_reference;
};
}  // namespace gf

#endif
