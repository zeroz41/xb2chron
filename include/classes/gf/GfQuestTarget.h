#ifndef CLASSES_GF_GFQUESTTARGET_H
#define CLASSES_GF_GFQUESTTARGET_H

#include "classes/gf/IQuestEvent.h"

namespace gf { class QuestChangeParam; }
namespace gf { class QuestCompleteChildParam; }
namespace gf { class QuestOrderParam; }
namespace gf { class QuestStateParam; }
namespace gf { class QuestTaskParam; }

namespace gf {
// a base of gf::GfQuestTarget no evidence names yet
class TUnk_B56DF8 {
public:
    virtual ~TUnk_B56DF8();
    virtual void qevChangeTaskState(gf::QuestTaskParam const&) = 0;
    virtual void qevChangeQuestState(gf::QuestStateParam const&) = 0;
    virtual void qevOrderQuest(gf::QuestOrderParam const&) = 0;
    virtual void qevCompleteChildQuest(gf::QuestCompleteChildParam const&) = 0;
    virtual void qevChangeCurrentQuest(gf::QuestChangeParam const&) = 0;
    virtual void qevChangeTaskCondition(gf::QuestTaskParam const&) = 0;
};
// table 0x7100B56DF8; base at 0x0 unknown (TUnk_B56DF8)
class GfQuestTarget : public TUnk_B56DF8, public ::gf::IQuestEvent {
public:
    virtual ~GfQuestTarget();  // slot 0
    virtual void qevChangeTaskState(gf::QuestTaskParam const&);  // slot 2
    virtual void qevChangeQuestState(gf::QuestStateParam const&);  // slot 3
    virtual void qevOrderQuest(gf::QuestOrderParam const&);  // slot 4
    virtual void qevCompleteChildQuest(gf::QuestCompleteChildParam const&);  // slot 5
    virtual void qevChangeCurrentQuest(gf::QuestChangeParam const&);  // slot 6
    virtual void qevChangeTaskCondition(gf::QuestTaskParam const&);  // slot 7
};
}  // namespace gf

#endif
