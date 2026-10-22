#ifndef CLASSES_GF_GFQUESTEVENT_H
#define CLASSES_GF_GFQUESTEVENT_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfQuestEvent; }

namespace gf {
// table 0x7100B56D70: the quest UI an event opens (its functions work on the singleton)
class GfQuestEvent : public ::mm::mtl::PtrSingleton< ::gf::GfQuestEvent> {
public:
    GfQuestEvent();
    virtual ~GfQuestEvent();  // slot 0
    // opens a quest's order; true unless there is no instance
    static bool setQuestEntry(unsigned int id);
    static int getQuestState(unsigned int id);
    static void setQuestComp(unsigned int id, unsigned int task);
    static bool getQuestComp(unsigned int id, unsigned int task);
    // whether the entry or the result UI is up
    static bool isActive();
    static void openEntry(unsigned int id);
    static void openResult(unsigned int id);
    static void clearDispUI();

    bool m_dispEntry;  // openEntry's (and setQuestEntry's) UI is up; clearDispUI clears it. The name is not the original's
    bool m_dispResult;  // openResult's UI is up; clearDispUI clears it. The name is not the original's
};
}  // namespace gf

#endif
