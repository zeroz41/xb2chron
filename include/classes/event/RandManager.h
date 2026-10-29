#ifndef CLASSES_EVENT_RANDMANAGER_H
#define CLASSES_EVENT_RANDMANAGER_H

namespace event { enum MSG_TYPE : int; }

#include "classes/event/RandPlayer.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event {
// table 0x7100B3D3C0; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::RandManager>
class RandManager : public IManager, public mm::mtl::Singleton<RandManager> {
public:
    virtual ~RandManager();  // slot 0
    RandManager();  // out of line (Singleton<RandManager>::getPtr calls it)
    // evt_rand.play: returns false while the script has to wait
    bool play(int no);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // 1.0.0's RandManager::clear (0x71000E996C) and update (0x71000E99BC); 3.0.1 inlines them into OnEventProc
    void clear() {
        m_player.clear();
        m_flags = 0;
    }
    void update() {
        if (m_flags & 1) {
            m_player.update();
        }
    }
    unsigned int m_flags;  // 0x10 (the name is not the original's)
    unsigned int pad_14;
    RandPlayer m_player;  // 0x18 (the name is not the original's)
};
}  // namespace event

#endif
