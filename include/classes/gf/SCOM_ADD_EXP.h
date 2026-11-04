#ifndef CLASSES_GF_SCOM_ADD_EXP_H
#define CLASSES_GF_SCOM_ADD_EXP_H

#include "classes/gf/SCOM.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B030
class SCOM_ADD_EXP : public ::gf::SCOM {
public:
    explicit SCOM_ADD_EXP(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // 2.0.0's symbols name it. A member: it builds this class (type 4, its table) with
    // no object (m_value3 -1); its caller is btl::CharacterManager::AddExpWpSp.
    static unsigned long createBattleExp(unsigned int, unsigned int);
    static unsigned long createInnExp(unsigned int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
    int m_value2;
    unsigned char pad_24[0x4];
    GF_OBJ_HANDLE* m_value3;
    bool m_value4;
};
}  // namespace gf

#endif
