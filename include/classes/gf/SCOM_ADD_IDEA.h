#ifndef CLASSES_GF_SCOM_ADD_IDEA_H
#define CLASSES_GF_SCOM_ADD_IDEA_H

#include "classes/gf/SCOM.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B0C0
class SCOM_ADD_IDEA : public ::gf::SCOM {
public:
    explicit SCOM_ADD_IDEA(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long create(GF_OBJ_HANDLE*, unsigned int, int);
    static unsigned long create(unsigned int, unsigned int, int);

    // the names are not the original's: what the create functions store (their arguments, in order)
    int m_value;
    int m_value2;
    unsigned int m_value3;
    GF_OBJ_HANDLE* m_value4;
};
}  // namespace gf

#endif
