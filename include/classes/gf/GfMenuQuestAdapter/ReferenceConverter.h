#ifndef CLASSES_GF_GFMENUQUESTADAPTER_REFERENCECONVERTER_H
#define CLASSES_GF_GFMENUQUESTADAPTER_REFERENCECONVERTER_H

#include "classes/gf/GfMenuQuestAdapter.h"
#include "classes/gf/GfMenuQuestAdapter/IConverter.h"
#include "classes/gf/GfMenuReferenceQuest.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
// table 0x7100B5D8A8; the quest a GfMenuReferenceQuest holds
class GfMenuQuestAdapter::ReferenceConverter : public ::gf::GfMenuQuestAdapter::IConverter {
public:
    ReferenceConverter(mm::mtl::IntrusivePtr<GfMenuReferenceQuest> reference) : m_reference(reference) {}
    virtual ~ReferenceConverter() { m_reference = nullptr; }  // slot 0
    virtual void getQuestID(QuestID& id) { m_reference->getQuest(id); }  // slot 2
    mm::mtl::IntrusivePtr<GfMenuReferenceQuest> m_reference;
};
}  // namespace gf

#endif
