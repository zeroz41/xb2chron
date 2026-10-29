#ifndef CLASSES_EVENT_DEBUGMANAGER_H
#define CLASSES_EVENT_DEBUGMANAGER_H

namespace event { enum MSG_TYPE : int; }

#include "mm/mtl/FixStr.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event {
// table 0x7100B3BFD0; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::DebugManager>
class DebugManager : public IManager, public mm::mtl::Singleton<DebugManager> {
public:
    virtual ~DebugManager();  // slot 0
    // the constructor (out of line: the unit has it at its own address, Singleton<T>::getPtr calls it)
    DebugManager();
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    bool isMovieDebug() const;
    void render();
    // 1.0.0's DebugManager::update (0x7100096898); 3.0.1 inlines it into OnEventProc
    void update() {
        if (m_flags & 2) {
            if (m_messageTime-- <= 0) {
                m_flags &= ~2;
            }
        }
        if (m_flags & 4) {
            if (m_warningTime-- <= 0) {
                m_flags &= ~4;
            }
        }
    }

private:
    // 1.0.0's setX(bool)/isX() pairs set and test its bits (setMovieDebug: bit 16); the name is not the original's
    unsigned int m_flags;  // 0x10
    mm::mtl::FixStr<256> pad_14;
    // frames left of the message (bit 1) and the warning (bit 2); the name is not the original's
    int m_messageTime;  // 0x118
    mm::mtl::FixStr<256> pad_11c;
    int m_warningTime;  // 0x220
    unsigned int pad_224;
    unsigned char pad_228[0x40];
};
}  // namespace event

#endif
