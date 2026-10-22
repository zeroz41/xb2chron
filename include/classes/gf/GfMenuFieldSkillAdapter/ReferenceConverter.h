#ifndef CLASSES_GF_GFMENUFIELDSKILLADAPTER_REFERENCECONVERTER_H
#define CLASSES_GF_GFMENUFIELDSKILLADAPTER_REFERENCECONVERTER_H

#include "classes/gf/GfMenuFieldSkillAdapter.h"
#include "classes/gf/GfMenuFieldSkillAdapter/IConverter.h"
#include "classes/gf/GfMenuReferenceFs.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B5BDE8; the skill a GfMenuReferenceFs holds
class GfMenuFieldSkillAdapter::ReferenceConverter : public ::gf::GfMenuFieldSkillAdapter::IConverter {
public:
    ReferenceConverter(mm::mtl::IntrusivePtr<GfMenuReferenceFs> reference) : m_reference(reference) {}
    virtual ~ReferenceConverter();  // slot 0
    virtual void getFieldSkill(MenuFieldSkill& skill);  // slot 2
    mm::mtl::IntrusivePtr<GfMenuReferenceFs> m_reference;
};
}  // namespace gf

#endif
