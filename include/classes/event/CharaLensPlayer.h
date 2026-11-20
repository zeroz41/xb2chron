#ifndef CLASSES_EVENT_CHARALENSPLAYER_H
#define CLASSES_EVENT_CHARALENSPLAYER_H

#include "mm/Vec2.h"

namespace event { class CharaIKUpdater; }

namespace event {
// table 0x7100B3CA58
class CharaLensPlayer {
public:
    CharaLensPlayer()
        : pad_8(0), pad_10(mm::Vec2::zero), pad_20(mm::Vec2::zero), pad_30(mm::Vec2::zero), m_ik(nullptr) {}
    virtual ~CharaLensPlayer() {}  // slot 0

    int pad_8;
    unsigned char pad_c[0x4];
    mm::Vec2 pad_10;
    mm::Vec2 pad_20;
    mm::Vec2 pad_30;
    // the IK updater 1.0.0's create(CharaIKUpdater*) stores; the name is not the original's
    CharaIKUpdater* m_ik;  // 0x40
};
}  // namespace event

#endif
