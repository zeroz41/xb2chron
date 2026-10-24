#ifndef CLASSES_GF_SCOM_ADD_WP_H
#define CLASSES_GF_SCOM_ADD_WP_H

#include "classes/gf/SCOM.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B060
class SCOM_ADD_WP : public ::gf::SCOM {
public:
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

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
