#ifndef CLASSES_EVENT_EFFECTMANAGER_H
#define CLASSES_EVENT_EFFECTMANAGER_H

namespace event { enum MSG_TYPE : int; }

#include "mm/mtl/FixedVector.h"

namespace event {
// a base of event::EffectManager no evidence names yet
class TUnk_B3CED8 {
public:
    virtual ~TUnk_B3CED8() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::EffectManager no evidence names yet
class TUnk_B3CF00 {
public:
    virtual ~TUnk_B3CF00() {}
};
// table 0x7100B3CED8; base at 0x0 unknown (TUnk_B3CED8), base at 0x8 unknown (TUnk_B3CF00)
class EffectManager : public TUnk_B3CED8, public TUnk_B3CF00 {
public:
    virtual ~EffectManager();  // slot 0
    EffectManager();  // out of line (Singleton<EffectManager>::getPtr calls it)
    // called by the evt_setup script plugin (application/BF2/ScriptPlayText); a result its callers ignore is declared void
    void loadResource(const char* name);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2

    // what load() makes (1.0.0's clear() calls each one's slot 2); the name is not the original's
    struct Entry;
    // bit 0: stream mode (1.0.0's isStreamMode), bit 1: offscreen mode (setOffscrMode); the name is not the original's
    unsigned int m_flags;  // 0x10
    // bit 0: effects shown (1.0.0's setEffectDisp/isEffectDisp); the name is not the original's
    unsigned int m_dispFlags;  // 0x14
    mm::mtl::FixedVector<Entry*, 16> m_entries;  // 0x18 (size 0x98); the name is not the original's
    // 1.0.0's getResPack returns its +0x50
    Entry* pad_a0;  // 0xa0
    // 1.0.0's getOffscrID returns it, setOffscrMode stores it; the name is not the original's
    unsigned int m_offscrID;  // 0xa8
    unsigned int pad_ac;
};
}  // namespace event

#endif
