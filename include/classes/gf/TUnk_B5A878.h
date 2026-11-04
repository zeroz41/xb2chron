#ifndef CLASSES_GF_TUNK_B5A878_H
#define CLASSES_GF_TUNK_B5A878_H

#include "classes/gf/GfMenuBtlchAdapter/IConverter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B5A878 (weak); the id a GfMenuReferenceNumber's value holds, 0 without one. The symbols leave the
// class unnamed (GfMenuBtlchAdapter::createFromReference builds it); they had it as GfMenuBattleAdapter::ReferenceIndexConverter,
// whose getIndex(int&) writes its result (GfMenuBattleAdapter::update passes it a local) where this one returns it.
class TUnk_B5A878 : public ::gf::GfMenuBtlchAdapter::IConverter {
public:
    TUnk_B5A878(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference) : m_reference(reference) {}
    virtual ~TUnk_B5A878() { m_reference = nullptr; }  // slot 0
    virtual unsigned int fn_7100334D68() {  // slot 2
        if (m_reference) {
            return m_reference->m_value;
        }
        return 0;
    }
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_reference;
};
}  // namespace gf

#endif
