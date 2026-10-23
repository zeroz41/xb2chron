#ifndef CLASSES_EVENT_MSTXTMANAGER_H
#define CLASSES_EVENT_MSTXTMANAGER_H

#include "mm/mtl/FixedVector.h"


namespace event { enum MSG_TYPE : int; }

namespace event {
class MstxtRes;
// a base of event::MstxtManager no evidence names yet
class TUnk_B3C5C8 {
public:
    virtual ~TUnk_B3C5C8() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::MstxtManager no evidence names yet
class TUnk_B3C5F0 {
public:
    virtual ~TUnk_B3C5F0() {}
};
// table 0x7100B3C5C8; base at 0x0 unknown (TUnk_B3C5C8), base at 0x8 unknown (TUnk_B3C5F0)
class MstxtManager : public TUnk_B3C5C8, public TUnk_B3C5F0 {
public:
    virtual ~MstxtManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
    // the loaded message-text resources (MstxtManager::load pushes each new MstxtRes); the name is not the original's
    mm::mtl::FixedVector<MstxtRes*, 16> m_res;  // 0x10
    // the resource whose BDAT is registered (registerBdat stores it, clear unregisters it); the name is not the original's
    MstxtRes* m_bdatRes;  // 0x98
};
}  // namespace event

#endif
