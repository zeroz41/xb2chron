#ifndef CLASSES_GF_SCOM_OBJ_WARP_POS_H
#define CLASSES_GF_SCOM_OBJ_WARP_POS_H

#include "classes/gf/SCOM.h"

#include "fw/Transform.h"
namespace gf { class GF_OBJ_HANDLE; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B240
class SCOM_OBJ_WARP_POS : public ::gf::SCOM {
public:
    // warps an object to pos facing rot (GfEvtModelSalvage::setTransform; the last flag's meaning is not known)
    explicit SCOM_OBJ_WARP_POS(SCOM_TYPE type) : SCOM(type) {}
    static void create(GF_OBJ_HANDLE* handle, const mm::Vec3& pos, const mm::Vec3& rot, bool arg);
    // Placeholder name: nothing in 1.0.0's symbols names it. A member because it builds SCOM_OBJ_WARP_POS (its table,
    // type 17, line 782 after create's). What it does: create with a ready transform (no rotation conversion);
    // callers TitleStatePlayEvent::update, GfGameScene::fn_71002C6D48 and fn_71002CB810.
    static void fn_710055AA2C(GF_OBJ_HANDLE* handle, const fw::Transform& transform, bool arg);
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned char pad_1c[0x4];
    GF_OBJ_HANDLE* m_value;
    unsigned char pad_28[0x8];
    fw::Transform m_value2;  // create's position and rotation
    bool m_value3;
};
}  // namespace gf

#endif
