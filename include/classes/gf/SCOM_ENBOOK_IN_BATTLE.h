#ifndef CLASSES_GF_SCOM_ENBOOK_IN_BATTLE_H
#define CLASSES_GF_SCOM_ENBOOK_IN_BATTLE_H

#include "classes/gf/SCOM.h"
#include "classes/gf/DataParamAcc.h"
namespace gf { class GF_OBJ_HANDLE; }

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B6F0
class SCOM_ENBOOK_IN_BATTLE : public ::gf::SCOM {
public:
    SCOM_ENBOOK_IN_BATTLE(SCOM_TYPE type, unsigned long handle, unsigned int value) : SCOM(type, handle), m_value(value) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(GF_OBJ_HANDLE* handle);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
};
}  // namespace gf

#endif
