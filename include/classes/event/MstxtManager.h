#ifndef CLASSES_EVENT_MSTXTMANAGER_H
#define CLASSES_EVENT_MSTXTMANAGER_H

#include "mm/mtl/FixedVector.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
class MstxtRes;

// table 0x7100B3C5C8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::MstxtManager>
class MstxtManager : public IManager, public mm::mtl::Singleton<MstxtManager> {
public:
    // inline: Singleton<MstxtManager>::getPtr's guarded init (in SeqManager::isSetupSceneEnd) zeroes m_bdatRes
    MstxtManager() : m_bdatRes(nullptr) {}
    virtual ~MstxtManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
    // named by the symbols: makes and keeps a MstxtRes for name unless one of that name is kept
    void load(const char* name);
    // named by the symbols: unregisters the current resource's BDAT, then registers the one named name
    void registerBdat(const char* name);
    // the loaded message-text resources (MstxtManager::load pushes each new MstxtRes); the name is not the original's
    mm::mtl::FixedVector<MstxtRes*, 16> m_res;  // 0x10
    // the resource whose BDAT is registered (registerBdat stores it, clear unregisters it); the name is not the original's
    MstxtRes* m_bdatRes;  // 0x98
};
}  // namespace event

#endif
