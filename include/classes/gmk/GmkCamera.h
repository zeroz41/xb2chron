#ifndef CLASSES_GMK_GMKCAMERA_H
#define CLASSES_GMK_GMKCAMERA_H

#include "classes/fw/Camera.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/FixStr.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gmk {
// table 0x7100B52548; 0x160 bytes on a 16-byte boundary (GfFieldMapGimmick holds one at 0xB0, after its GmkAcc
// ends at 0xA8)
class alignas(16) GmkCamera {
public:
    // what create() builds the camera from (GfFieldMapGimmick::create fills one; the names are not the original's)
    class CreateInfo {
    public:
        CreateInfo() : m_attr(0), pad_105(1), pad_106(0), m_hasTransform(false), m_pos(mm::Vec3::zero), m_rotY(0.0f) {}
        // the transform of the LOD object with that id (GfFieldLod::findTransform); sets m_hasTransform
        bool validateTransform(unsigned short lodId);
        // the object's world transform (GfObjAcc::getWorldTransformNoSync); sets m_hasTransform
        bool validateTransform(gf::GF_OBJ_HANDLE* handle);
        mm::mtl::FixStr<256> m_name;  // the row's gmkCamName
        unsigned char m_attr;         // the row's camGim_ATR when nonzero
        unsigned char pad_105;        // 1 by default; GfFieldMapGimmick::create stores 0 to it
        unsigned char pad_106;
        bool m_hasTransform;  // set by validateTransform
        unsigned char pad_108[0x8];
        mm::Vec3 m_pos;  // set by validateTransform
        float m_rotY;    // set by validateTransform (an atan2 of the rotation)
    };
    explicit GmkCamera(const CreateInfo* info);
    // inline: GfFieldMapGimmick's destructor stores this table and calls dispose() in place, then releases m_camera
    virtual ~GmkCamera() {  // slot 0
        dispose();
    }
    void dispose();
    bool isLoaded() const;
    bool isEnd() const;
    void update(float dt);
    void play();
    void create(const CreateInfo& info);
    unsigned char pad_8[0x8];
    // the camera's name: create() asserts its length (FixStr's m_nLen < LEN); GfFieldMapGimmick::onFsSucceeded plays the
    // camera only when it is not empty (the name is not the original's)
    mm::mtl::FixStr<256> m_name;
    unsigned char pad_114[0x2c];
    mm::mtl::IntrusivePtr<fw::Camera> m_camera;  // released by the destructor (the name is not the original's)
    unsigned char pad_148[0x18];
};
}  // namespace gmk

#endif
