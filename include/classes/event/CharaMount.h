#ifndef CLASSES_EVENT_CHARAMOUNT_H
#define CLASSES_EVENT_CHARAMOUNT_H

#include "classes/event/ICmd.h"
#include "mm/Vec3.h"
#include "mm/Quat.h"

namespace gf { class GfEvtModel; }

namespace event {
// table 0x7100B3E798; base event::ICmd (its slots; CharaObj queues it as a command)
class CharaMount : public ::event::ICmd {
public:
    CharaMount() : m_model(nullptr), m_parent(nullptr), pad_18(), m_pos(mm::Vec3::zero), m_rot(mm::Quat::zero) {}
    virtual ~CharaMount() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // the field names are not the original's
    // the mounting model: update's getObj(m_model->m_handle) transform is saved and restored around the mount
    gf::GfEvtModel* m_model;  // 0x8
    // the model mounted on (update stores the param's val 0; term resets the mount and clears it)
    gf::GfEvtModel* m_parent;  // 0x10
    unsigned char pad_18[0x8];
    // the transform's position and rotation before the mount (update saves them; term restores them)
    mm::Vec3 m_pos;  // 0x20
    mm::Quat m_rot;  // 0x30
};
}  // namespace event

#endif
