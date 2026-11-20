#ifndef CLASSES_EVENT_CHARATURNROT_H
#define CLASSES_EVENT_CHARATURNROT_H

#include "classes/event/ICmd.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace event { class CharaDysUpdater; }

namespace event {
// table 0x7100B3E450
class CharaTurnRot : public ::event::ICmd {
public:
    CharaTurnRot() : m_flags(0), m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_dys(nullptr) {}
    virtual ~CharaTurnRot() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4

    // bit 0: term resets the turn and clears it; the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned int pad_c;
    // the character's gf object (term ends its turn); the name is not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10
    // the character's dynamics updater (term resets its movement); the name is not the original's
    CharaDysUpdater* m_dys;  // 0x18
};
}  // namespace event

#endif
