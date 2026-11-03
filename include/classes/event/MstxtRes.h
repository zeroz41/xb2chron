#ifndef CLASSES_EVENT_MSTXTRES_H
#define CLASSES_EVENT_MSTXTRES_H

#include "classes/event/IResEvent.h"
#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3C5A0
class MstxtRes : public IResEvent {
public:
    // named by the symbols (MstxtManager::load news one, 0x58 bytes)
    MstxtRes(const char* name);
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~MstxtRes();  // slot 1
    // bit 0: loading (OnResEvent clears it), bit 1: loaded (set on a type 3 event), bit 2: its BDAT is registered (the destructor unregisters it); the name is not the original's
    unsigned int m_flags;  // 0x8
    // the name it was made with (the constructor copies it; MstxtManager::load compares it); the name is not the original's
    mm::mtl::FixStr<32> m_name;  // 0xc
    // the name's file part with "_ms" appended: the constructor loads bdat/<language>/<it>.bdat (the name is not the
    // original's)
    mm::mtl::FixStr<32> m_fileName;  // 0x30
    unsigned char pad_54[0x4];
};
}  // namespace event

#endif
