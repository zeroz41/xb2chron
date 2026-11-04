#ifndef CLASSES_GF_SCOM_ADD_WP_H
#define CLASSES_GF_SCOM_ADD_WP_H

#include "classes/gf/SCOM.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B060
class SCOM_ADD_WP : public ::gf::SCOM {
public:
    explicit SCOM_ADD_WP(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // Placeholder name: nothing in 1.0.0's place names it. A member: it builds this class (type 7, its table) in mode
    // 3 for a driver; its caller is btl::CharacterManager::AddExpWpSp.
    static unsigned long createForBdatid(int driver, int, unsigned int);

    // the names are not the original's: what exec reads
    union {
        GF_OBJ_HANDLE* m_handle;  // modes 0-2: the object whose driver gets the WP
        unsigned int m_driver;    // mode 3: the driver itself
    };
    int m_value;
    unsigned int m_value2;
    int m_mode;
};
}  // namespace gf

#endif
