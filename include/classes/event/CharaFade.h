#ifndef CLASSES_EVENT_CHARAFADE_H
#define CLASSES_EVENT_CHARAFADE_H

#include "classes/event/AnmF32.h"
#include "classes/event/ICmd.h"
namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3E7D0
class CharaFade : public ::event::ICmd {
public:
    // inline: D2 is emitted in CharaObj's destructor, D0 sits in CharaObj's tail; update is the key function
    CharaFade() : m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {}
    virtual ~CharaFade() {}  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    // the character's gf object (-1: none; update then leaves the alpha alone); the name is not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x8
    AnmF32 m_anm;  // 0x10 the alpha curve (CharaObj holds one at 0xb80); the name is not the original's
};
}  // namespace event

#endif
