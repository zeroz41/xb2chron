#ifndef CLASSES_FW_PADRESEVENT_H
#define CLASSES_FW_PADRESEVENT_H

#include "classes/anm/ReferenceObject.h"

namespace fw {

// one key of an action: what it asks of the pad (fw::PadRelay::checkAction's switch: 0 held, 1 not held, 2 pressed,
// 3 released, 4 repeating, 5 double pressed, 6 and 7 two more of fw::PadData's bit sets) and which key
// (fw::getPadKey's PadActKey). The names are not the original's.
struct ResKey {
    unsigned int m_kind;
    unsigned int m_key;
};

// an action's keys: it fires when every one holds (fw::PadRelay::checkAction). The names are not the original's.
struct ResAction {
    const ResKey* m_keys;
    unsigned int m_keyCount;
};

// a named action: fw::PadRelay::update invokes the handler bound to m_name when one of its actions holds. The
// names are not the original's.
struct ResActionInfo {
    const char* m_name;
    const ResAction* m_actions;
    unsigned int m_actionCount;
};

// a named axis: fw::PadRelay::invokeAxis calls its handler with stick axis m_axis (0 LX, 1 LY, 2 RX, 3 RY) scaled
// by m_scale. The names are not the original's.
struct ResAxisInfo {
    const char* m_name;
    unsigned int m_axis;
    float m_scale;
};

// table 0x7100B428E0; a pad event resource ("PADD" binary, fw::PadEventImporter::create): its named actions and
// axes. The field names are not the original's.
class PadResEvent : public ::anm::ReferenceObject {
public:
    // in place in its binary: only its table is installed
    PadResEvent() {}
    virtual ~PadResEvent() {}  // slot 0: inline (the table's slot holds anm::ReferenceObject's destructor)


    const ResActionInfo* m_actions;
    unsigned int m_actionCount;
    const ResAxisInfo* m_axes;
    unsigned int m_axisCount;
};

}  // namespace fw

#endif
