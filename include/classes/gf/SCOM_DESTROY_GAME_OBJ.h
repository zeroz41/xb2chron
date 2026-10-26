#ifndef CLASSES_GF_SCOM_DESTROY_GAME_OBJ_H
#define CLASSES_GF_SCOM_DESTROY_GAME_OBJ_H

#include "classes/gf/SCOM.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B270
class SCOM_DESTROY_GAME_OBJ : public ::gf::SCOM {
public:
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // queues a request destroying the object after time seconds (gf_req_scom.cpp's; GfRelSmnEnemy::disposeEnemies
    // calls it; the parameter names are not the original's)
    static void create(GF_OBJ_HANDLE* handle, float time, unsigned int attribute);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned char pad_1c[0x4];
    GF_OBJ_HANDLE* m_value;
    float m_value2;
    unsigned int m_value3;
};
}  // namespace gf

#endif
