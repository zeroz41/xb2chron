#ifndef CLASSES_GF_TUNK_B6AD28_H
#define CLASSES_GF_TUNK_B6AD28_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AD28 (no RTTI name): a type-0x55 request whose exec sends the arena game mode (TUnk_B535D0) a
// MsgUnk_1000034 carrying m_type and m_param; five create placeholders queue it with a fixed type and parameter 0
class TUnk_B6AD28 : public ::gf::SCOM {
public:
    explicit TUnk_B6AD28(unsigned int type) : SCOM(SCOM_TYPE(0x55)), m_type(type), m_param(0) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long fn_710056B66C();
    static unsigned long fn_710056B6F4();
    static unsigned long fn_710056B77C();
    static unsigned long fn_710056B804();
    static unsigned long fn_710056B88C();

    // the names are not the original's: the message's type and its first parameter word
    unsigned int m_type;
    unsigned int m_param;
};
}  // namespace gf

#endif
