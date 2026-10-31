#ifndef CLASSES_EVENT_CSSNDMANAGER_H
#define CLASSES_EVENT_CSSNDMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixStr.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3CD78; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::CsSndManager>
class CsSndManager : public IManager, public mm::mtl::Singleton<CsSndManager> {
public:
    // inline: Singleton<CsSndManager>::getPtr's static constructs it in SkipManager::setSkipVolume
    CsSndManager()
        : m_flags(0), pad_14(0), m_bgmHandle0(0), m_bgmHandle1(0), pad_238(0), m_bgmFrame1(0.0f) {}
    virtual ~CsSndManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void update();  // out of line
    void render();  // out of line
    // OnEventProc's clear (inlined; the names are not the original's): stops each playing bgm
    void clear();
    void stop0();
    void stop1();
    // fields OnEventProc's clear resets (the names are not the original's)
    unsigned int m_flags;  // 0x10 bit 0: bgm 0 plays, bit 1: bgm 1 plays
    unsigned int pad_14;
    unsigned int m_bgmHandle0;  // 0x18 fw::SoundManager::stopBgm's handle
    unsigned int m_bgmHandle1;  // 0x1c fw::SoundManager::stopBgm's handle
    mm::mtl::FixStr<256> m_bgmName0;  // 0x20 emptied with m_bgmHandle0
    mm::mtl::FixStr<256> m_bgmName1;  // 0x124 emptied with m_bgmHandle1
    unsigned char pad_228[0x10];
    unsigned long pad_238;  // the constructor zeroes it
    // SkipManager::setSkipVolume restarts bgm 1 at (FrameManager's frame + this) / 30 seconds (the name is not
    // the original's)
    float m_bgmFrame1;  // 0x240
    unsigned char pad_244[0x4];
};
}  // namespace event

#endif
