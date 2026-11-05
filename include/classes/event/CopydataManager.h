#ifndef CLASSES_EVENT_COPYDATAMANAGER_H
#define CLASSES_EVENT_COPYDATAMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixStr.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3E160; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::CopydataManager>
class CopydataManager : public IManager, public mm::mtl::Singleton<CopydataManager> {
public:
    // inline: Singleton<CopydataManager>::getPtr's static constructs it in place (Manager::Manager,
    // FrameManager::tail)
    CopydataManager() : pad_10(0), m_name("evtEditor"), pad_58(0), pad_60(0), pad_68(0), pad_70(0), pad_78(0) {}
    virtual ~CopydataManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2

    int pad_10;
    // "evtEditor" (the name is not the original's)
    mm::mtl::FixStr<64> m_name;  // 0x14 (length at 0x54)
    unsigned long pad_58;
    unsigned long pad_60;
    unsigned long pad_68;
    unsigned long pad_70;
    unsigned long pad_78;
};
}  // namespace event

#endif
