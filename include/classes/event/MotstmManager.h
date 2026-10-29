#ifndef CLASSES_EVENT_MOTSTMMANAGER_H
#define CLASSES_EVENT_MOTSTMMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/StmManager.h"
#include "mm/mtl/Bitflag.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3C558; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::MotstmManager>
class MotstmManager : public IManager, public mm::mtl::Singleton<MotstmManager> {
public:
    virtual ~MotstmManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void update();  // out of line
    // 1.0.0's clear and render (3.0.1 inlines them into OnEventProc; defined inline in CharaObj.cpp)
    void clear();
    void render();
    // 0x10 bit 0: create sets it, render needs it, clear zeroes it (the name is not the original's). A Bitflag:
    // render loads it 4-aligned (GVN does not widen it over m_dispFlags)
    mm::mtl::Bitflag<32> m_flags;
    unsigned int m_dispFlags;  // 0x14 bit 0: 1.0.0's setDisp(bool), render needs it (the name is not the original's)
    StmManager m_stmManager;  // 0x18 (sizeof 0x70 = s_instance's size; the name is not the original's)
};
}  // namespace event

#endif
