#ifndef CLASSES_EVENT_EFFECTMANAGER_H
#define CLASSES_EVENT_EFFECTMANAGER_H

namespace event { enum MSG_TYPE : int; }
namespace event { class EffectRes; }

#include "mm/mtl/FixedVector.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event {
// table 0x7100B3CED8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::EffectManager>
class EffectManager : public IManager, public mm::mtl::Singleton<EffectManager> {
public:
    virtual ~EffectManager();  // slot 0
    EffectManager();  // out of line (Singleton<EffectManager>::getPtr calls it)
    // called by the evt_setup script plugin (application/BF2/ScriptPlayText); a result its callers ignore is declared void
    void loadResource(const char* name);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2

    // named by the symbols: makes and keeps an EffectRes for name unless one of that name is kept
    void load(const char* name);
    // 1.0.0's isEffectDisp (0x71000DF598; 3.0.1 inlines it: ObjectManager::render)
    bool isEffectDisp() const { return m_dispFlags & 1; }
    // bit 0: stream mode (1.0.0's isStreamMode), bit 1: offscreen mode (setOffscrMode); the name is not the original's
    unsigned int m_flags;  // 0x10
    // bit 0: effects shown (1.0.0's setEffectDisp/isEffectDisp); the name is not the original's
    unsigned int m_dispFlags;  // 0x14
    mm::mtl::FixedVector<EffectRes*, 16> m_entries;  // 0x18 (size 0x98); the name is not the original's
    // 1.0.0's getResPack returns its +0x50
    EffectRes* pad_a0;  // 0xa0
    // 1.0.0's getOffscrID returns it, setOffscrMode stores it; the name is not the original's
    unsigned int m_offscrID;  // 0xa8
    unsigned int pad_ac;
};
}  // namespace event

#endif
