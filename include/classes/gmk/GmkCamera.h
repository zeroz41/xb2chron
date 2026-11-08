#ifndef CLASSES_GMK_GMKCAMERA_H
#define CLASSES_GMK_GMKCAMERA_H

#include "classes/fw/Camera.h"
#include "classes/gf/GimmickCamera.h"
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
        CreateInfo() : m_attr(0), pad_105(true), pad_106(0), m_hasTransform(false), m_pos(mm::Vec3::zero), m_rotY(0.0f) {}
        // the transform of the LOD object with that id (GfFieldLod::findTransform); sets m_hasTransform
        bool validateTransform(unsigned short lodId);
        // the object's world transform (GfObjAcc::getWorldTransformNoSync); sets m_hasTransform
        bool validateTransform(gf::GF_OBJ_HANDLE* handle);
        mm::mtl::FixStr<256> m_name;  // the row's gmkCamName
        unsigned char m_attr;         // the row's camGim_ATR when nonzero
        bool pad_105;                 // 1 by default; GfFieldMapGimmick::create stores 0 to it; create() passes it to
                                      // GimmickCamera::setAuto
        unsigned char pad_106;
        bool m_hasTransform;  // set by validateTransform
        // 0x108: alignment gap (create copies the info member-wise and skips these 8 bytes)
        mm::Vec3 m_pos;  // set by validateTransform
        float m_rotY;    // set by validateTransform (an atan2 of the rotation)
    };
    // create(*info) when info is given (the GfFieldMapGimmick constructor passes none)
    explicit GmkCamera(const CreateInfo* info);
    // inline: GfFieldMapGimmick's destructor stores this table and calls dispose() in place, then releases m_camera
    virtual ~GmkCamera() {  // slot 0
        dispose();
    }
    void dispose();
    bool isLoaded() const;
    bool isEnd() const;
    void update(float dt);
    // starts the sequence at seqWaitToPlay
    void play();
    void seqWaitToPlay(float dt);
    // the step create() starts the sequence at
    void seqWaitToLoaded(float dt);
    // the step the others move on to: shows the party again, pops and releases the camera once it has played
    void seqWaitToEnd(float dt);
    // hides (disp false, when the camera starts) or shows the party; m_attr 2 passes true as the second argument,
    // 1 false (meaning not known)
    static void setDispOfParty(bool disp, bool);
    void create(const CreateInfo& info);
    unsigned char pad_8[0x8];
    // 0x10: the camera's CreateInfo (the constructor builds its defaults in place: FixStr, 0/1/0/false, Vec3::zero
    // copied as one 8-byte and one 4-byte load, 0). Its m_name: create() asserts the length (FixStr's m_nLen < LEN);
    // GfFieldMapGimmick::onFsSucceeded plays the camera only when it is not empty (the name is not the original's)
    CreateInfo m_info;
    // released by the destructor; isLoaded/isEnd ask it (gf::GimmickCamera::isLoaded/isPlayEnd; the name is not the
    // original's)
    mm::mtl::IntrusivePtr<fw::Camera> m_camera;  // a gf::GimmickCamera (GimmickCamera::create returns the base type)
    void (GmkCamera::*m_seq)(float);  // the sequence step (play() sets seqWaitToPlay; the name is not the original's)
    unsigned char pad_158[0x8];
};
}  // namespace gmk

#endif
