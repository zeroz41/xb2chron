#ifndef CLASSES_EVENT_MANIMANAGER_H
#define CLASSES_EVENT_MANIMANAGER_H

#include "classes/ml/IWorkEvent.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/Mat44.h"
#include "mm/mtl/Bitflag.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; }
namespace ml { class EventView; }

namespace event {
// the manipulator kinds changeManipulate switches to: OnKeyDown passes 1 for 'W', 2 for 'E', 3 for 'R';
// clearManipulate stores 1 (no evidence names the enumerators)
enum MANI_TYPE : int;

// table 0x7100B3DB00; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::ManiManager>
class ManiManager : public IManager, public mm::mtl::Singleton<ManiManager>, public ::ml::IWorkEvent {
public:
    // one registered manipulator target (1.0.0's name; 0x110 bytes: FixedVector<Item, 512> spans 0x20..0x22020)
    struct Item {
        unsigned char pad_0[0x110];
    };
    // inline: its D1/D0 and thunks sit in the unit's tail (0x710014BCFC); only m_items' clear is left of it
    virtual ~ManiManager() {}  // slot 0
    // the first new virtual is the key function (0x710011C390, defined before OnKeyDown and OnEventProc)
    virtual bool OnMouseButtonDown(ml::EventView*);  // slot 3
    virtual bool OnKeyDown(ml::EventView*);  // slot 4
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
    void clearManipulate();
    void update();
    void updateManipulate();
    void render();
    void changeManipulate(MANI_TYPE type);

    // bit 0: enabled, bit 1: attached to the view as a work event, bit 2: a manipulator is set (1.0.0's
    // clear/clearManipulate/update test and clear them; the names are not the original's)
    mm::mtl::Bitflag<32> m_flags;  // 0x18
    // bit 0 tested with m_flags' bits 0 and 2 before updateManipulate (the name is not the original's)
    mm::mtl::Bitflag<32> m_debugFlags;  // 0x1C
    mm::mtl::FixedVector<Item, 512> m_items;  // 0x20 (the name is not the original's)
    unsigned char pad_22028[0x8];
    MANI_TYPE m_type;  // 0x22030 clearManipulate stores 1 (the name is not the original's)
    unsigned char pad_22034[0xc];
    mm::Mat44 m_mats[5];  // 0x22040 the constructor sets each to identity (the name is not the original's)
};
}  // namespace event

#endif
