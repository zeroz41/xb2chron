#ifndef CLASSES_EVENT_LIPSYNCMANAGER_H
#define CLASSES_EVENT_LIPSYNCMANAGER_H

#include "mm/mtl/FixedVector.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
class LipsyncRes;

// table 0x7100B3D2C0; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::LipsyncManager>
class LipsyncManager : public IManager, public mm::mtl::Singleton<LipsyncManager> {
public:
    virtual ~LipsyncManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
    unsigned char pad_10[0x8];
    // the loaded lip-sync resources (LipsyncManager::load pushes each new LipsyncRes); the name is not the original's
    mm::mtl::FixedVector<LipsyncRes*, 8> m_res;  // 0x18
};
}  // namespace event

#endif
