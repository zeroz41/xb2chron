#ifndef CLASSES_GF_GFMENUREFERENCEQUEST_H
#define CLASSES_GF_GFMENUREFERENCEQUEST_H

namespace gf { class QuestID; }

namespace gf {
// table 0x7100B636C8
class GfMenuReferenceQuest {
public:
    virtual ~GfMenuReferenceQuest();  // slot 0
    virtual void getQuest(gf::QuestID&) const;  // slot 2
};
}  // namespace gf

#endif
