#ifndef CLASSES_EVENT_VOLUMEPLAYER_H
#define CLASSES_EVENT_VOLUMEPLAYER_H

#include "mm/mtl/FixedVector.h"

namespace event {
// table 0x7100B3D8D0; VolumeManager::OnEventProc's update builds it through mm::mtl::Singleton<VolumePlayer>
class VolumePlayer {
public:
    // a category volume change update applies each frame (0x10 bytes; the names are not the original's)
    struct Entry {
        bool m_reset;           // 0x0 0: update sets the category volume back to 1
        int m_cate;             // 0x4 the fw::SoundCategory update passes to GfGameEvent::setCategoryVolume
        float m_volume;         // 0x8
        float m_frame;          // 0xc update passes it in seconds (* 1/30)
    };

    virtual ~VolumePlayer() {}  // slot 0 (weak: the D2 resets m_entries)
    void update();  // out of line
    mm::mtl::FixedVector<Entry, 40> m_entries;  // 0x8 (count at 0x288; the name is not the original's)
};
}  // namespace event

#endif
