#ifndef CLASSES_EVENT_LIPSYNCMANAGER_H
#define CLASSES_EVENT_LIPSYNCMANAGER_H

#include "mm/mtl/FixedVector.h"


namespace event { enum MSG_TYPE : int; }

namespace event {
class LipsyncRes;
// a base of event::LipsyncManager no evidence names yet
class TUnk_B3D2C0 {
public:
    virtual ~TUnk_B3D2C0() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::LipsyncManager no evidence names yet
class TUnk_B3D2E8 {
public:
    virtual ~TUnk_B3D2E8() {}
};
// table 0x7100B3D2C0; base at 0x0 unknown (TUnk_B3D2C0), base at 0x8 unknown (TUnk_B3D2E8)
class LipsyncManager : public TUnk_B3D2C0, public TUnk_B3D2E8 {
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
