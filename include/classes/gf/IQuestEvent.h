#ifndef CLASSES_GF_IQUESTEVENT_H
#define CLASSES_GF_IQUESTEVENT_H

namespace gf { class QuestChangeParam; }
namespace gf { class QuestCompleteChildParam; }
namespace gf { class QuestCompleteParam; }
namespace gf { class QuestOrderParam; }
namespace gf { class QuestPreCompleteParam; }
namespace gf { class QuestStateParam; }
namespace gf { class QuestTaskParam; }

namespace gf {
// table none (its derived classes')
class IQuestEvent {
public:
    virtual ~IQuestEvent();  // slot 0
    virtual void qevAchievementCount(gf::QuestOrderParam const&) {}  // slot 2
    virtual void qevOrderQuest(gf::QuestOrderParam const&) = 0;  // slot 3
    virtual void qevCompleteQuest(gf::QuestCompleteParam const&);  // slot 4
    virtual void qevPreCompleteQuest(gf::QuestPreCompleteParam const&) {}  // slot 5
    virtual void qevChangeTaskState(gf::QuestTaskParam const&) {}  // slot 6
    virtual void qevLoadTaskState(unsigned int) {}  // slot 7
    virtual void qevCompleteChildQuest(gf::QuestCompleteChildParam const&) = 0;  // slot 8
    virtual void qevChangeQuestState(gf::QuestStateParam const&) {}  // slot 9
    virtual void qevChangeCurrentQuest(gf::QuestChangeParam const&) {}  // slot 10
    virtual void qevChangeTaskCondition(gf::QuestTaskParam const&) {}  // slot 11
};
}  // namespace gf

#endif
