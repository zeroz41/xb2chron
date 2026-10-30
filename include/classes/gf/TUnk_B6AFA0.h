#ifndef CLASSES_GF_TUNK_B6AFA0_H
#define CLASSES_GF_TUNK_B6AFA0_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AFA0 (no RTTI name): a type-0x54 request whose exec passes m_value to GfWeapon's unit's fn_71002DA570 (a
// MsgUnk_1000034 to the arena game mode); the free function fn_7100558D28 (GfReqSmallCom.h) creates it
class TUnk_B6AFA0 : public ::gf::SCOM {
public:
    explicit TUnk_B6AFA0(int value) : SCOM(SCOM_TYPE(0x54)), m_value(value) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    int m_value;  // the name is not the original's: the create function's argument
};
}  // namespace gf

#endif
