#ifndef CLASSES_EVENT_QUESTMANAGER_H
#define CLASSES_EVENT_QUESTMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D698; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::QuestManager>
class QuestManager : public IManager, public mm::mtl::Singleton<QuestManager> {
public:
    QuestManager() : m_flags(0) {}
    virtual ~QuestManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // 1.0.0's clear() (0x71000F54E4)
    void clear();
    // StatusManager::judge and change call it: false while the quest event UI runs (it pauses the frame then)
    bool entry(unsigned int id, bool* result);
    // StatusManager::change calls them (the same wait as entry); the last argument of setComp is unused
    bool setComp(unsigned int id, unsigned int task, bool);
    // openResult when result is set, else openEntry (the parameter names are not the original's)
    bool disp(unsigned int id, bool result);

private:
    // bit 0: active (1.0.0's isActive; setComp sets it); the name is not the original's
    unsigned int m_flags;  // 0x10
};

}  // namespace event

#endif
