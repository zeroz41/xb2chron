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
    SCOM_ENBOOK_BOSS_TIME(SCOM_TYPE type, unsigned long handle, unsigned int enemy, unsigned int time)
        : SCOM(type, handle), m_enemy(enemy), m_time(time) {}
    static unsigned long create(GF_OBJ_HANDLE* handle, unsigned int time);
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    unsigned int m_enemy;  // the object's BDAT ID (the name is not the original's)
    unsigned int m_time;   // (the name is not the original's)
};
}  // namespace gf

#endif
