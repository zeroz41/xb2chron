#ifndef CLASSES_EVENT_AGELOGMANAGER_H
#define CLASSES_EVENT_AGELOGMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Bitflag.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3C618; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::AgelogManager>
class AgelogManager : public IManager, public mm::mtl::Singleton<AgelogManager> {
public:
    virtual ~AgelogManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2 (the key function: its definition emits the table)
    void render();

    // "C:/MonolithSoft/BF2/agelog": the folder the log path is formatted under (render prints it)
    static const char* LOG_DIR;

private:
    // bit 0 and bit 1: OnEventProc sets bit 1 when only bit 0 is set and clears it on messages 10 and 12; the
    // name is not the original's. A Bitflag: OnEventProc's load of it is 4-aligned (GVN does not widen it over
    // m_path's first byte), as a plain field at 0x10 it would be 8-aligned
    mm::mtl::Bitflag<32> m_flags;  // 0x10
    // "<LOG_DIR>/nx/agelog_<date>.txt", formatted once; the name is not the original's
    mm::mtl::FixStr<128> m_path;  // 0x14
};
}  // namespace event

#endif
