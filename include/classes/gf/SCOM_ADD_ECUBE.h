#ifndef CLASSES_GF_TUNK_B6AF70_H
#define CLASSES_GF_TUNK_B6AF70_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AF70 (no RTTI name): a type-0x53 request whose exec passes m_value to GfWeapon's unit's fn_71002DA4FC (a
// MsgUnk_1000034 to the arena game mode); the free function fn_7100558BAC (GfReqSmallCom.h) creates it
class SCOM_ADD_ECUBE : public ::gf::SCOM {
public:
    explicit SCOM_ADD_ECUBE(int value) : SCOM(SCOM_TYPE(0x53)), m_value(value) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    int m_value;  // the name is not the original's: the create function's argument
};
}  // namespace gf

#endif
