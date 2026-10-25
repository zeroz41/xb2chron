#ifndef CLASSES_EVENT_STATUSMANAGER_H
#define CLASSES_EVENT_STATUSMANAGER_H

#include "classes/ml/IWorkEvent.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; }
// evt_status.judge's and evt_status.change's first argument (the script passes an int)
enum EVT_judge : int;
enum EVT_change : int;

namespace event {

// a base of event::StatusManager no evidence names yet
class TUnk_B3D790 {
public:
    virtual ~TUnk_B3D790() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};

// a base of event::StatusManager no evidence names yet
class TUnk_B3D808 {
public:
    virtual ~TUnk_B3D808() {}
};

// table 0x7100B3D790; base at 0x0 unknown (TUnk_B3D790), base at 0x10 unknown (TUnk_B3D808)
class StatusManager : public TUnk_B3D790, public ::ml::IWorkEvent, public TUnk_B3D808 {
public:
    // one row changeFromBdat reads from EVT_listList (0x20 bytes: five ints, then a pointer at 0x18); the name and
    // the layout's meaning are not the original's
    struct ListItem {
        unsigned char pad_0[0x18];
        void* pad_18;
    };

    StatusManager();
    virtual ~StatusManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // 1.0.0's init() (0x71000F69B8): clear(), then GfGameEvent::setCancelFlag(false)
    void init();
    // 1.0.0's clear() (0x71000F69D0): empties the list, then zeroes the flags
    void clear();
    // false while the judgement still waits (evt_status.judge then waits); the result goes to pResult; param1..param4 are the script's numbered arguments (names not the original's)
    bool judge(EVT_judge type, int param1, int param2, int param3, int param4, bool& pResult);
    // false while the change still waits (evt_status.change then waits)
    bool change(EVT_change type, int param1, int param2, int param3, int param4, const char* name);
    unsigned int getDriverByBladeId(unsigned int bladeId) const;

private:
    // bit 0 makes changeFromBdat do nothing; the name is not the original's
    unsigned int m_flags;  // 0x18
    // filled by changeFromBdat (asserts size() < capacity() for 32 rows); the name is not the original's
    mm::mtl::FixedVector<ListItem, 32> m_list;  // 0x20 (size at 0x420)
};

}  // namespace event

#endif
