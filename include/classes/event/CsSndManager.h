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
    // SeqManager's exec plays the named bgm as bgm 1: bgm 0's handle is started when bit 0 is set or bgm 0 has
    // that name, else the name is played paused (stopping a running bgm 1 first)
    void play(const char* name);
    // out of line (0x71000EEEA0; FrameManager::pause passes whether a sound pause type is set)
    void pause(bool);
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
    // update's watch of bgm 1 (the names are not the original's): the last play time read, how many updates it
    // stayed there, how many times the stall made it pause, the event frame play started it at
    float m_lastPlayTime;  // 0x228
    int m_stallCount;      // 0x22c
    int m_stallPauses;     // 0x230
    float m_startFrame;    // 0x234
    unsigned long pad_238;  // the constructor zeroes it
    // SkipManager::setSkipVolume restarts bgm 1 at (FrameManager's frame + this) / 30 seconds (the name is not
    // the original's)
    float m_bgmFrame1;  // 0x240
    unsigned char pad_244[0x4];
};
}  // namespace event

#endif
