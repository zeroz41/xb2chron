#ifndef CLASSES_GF_GFMENUREFERENCEQUEST_H
#define CLASSES_GF_GFMENUREFERENCEQUEST_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace gf { class QuestID; }

namespace gf {
// table 0x7100B636C8; a counted quest a menu object shares with GfMenuQuestAdapter (its reference count at 8,
// which GfMenuQuestAdapter::createFromReference adds to)
class GfMenuReferenceQuest : public ::mm::mtl::ReferenceObject {
public:
    virtual ~GfMenuReferenceQuest();  // slot 0
    virtual void getQuest(gf::QuestID&) const;  // slot 2
};
}  // namespace gf

#endif
