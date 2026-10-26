#ifndef CLASSES_GF_SCOM_ENBOOK_BOSS_TIME_H
#define CLASSES_GF_SCOM_ENBOOK_BOSS_TIME_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B6B720
class SCOM_ENBOOK_BOSS_TIME : public ::gf::SCOM {
public:
    // Utility::RegisterEnemyBook passes its handle and value
    static unsigned long create(GF_OBJ_HANDLE* handle, unsigned int time);
    virtual ~SCOM_ENBOOK_BOSS_TIME();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
